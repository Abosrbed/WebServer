#ifndef _EPOLL_CLASS_
#define _EPOLL_CLASS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <assert.h>
#include <netinet/in.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <cassert>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/epoll.h>
#include "http_conn.h"
#include "locker.h"
#include "pthreadpool.h"
#include "socket_control.h"
#include <log.h>
#include <lst_timer.h>
#include <stdexcept>

class epoll_class : public base
{
public:
    epoll_class(int port);
    ~epoll_class();
    void run();

private:
    //================== const ====================
    // 最大的文件描述符个数
    static const int MAX_FD = 65535;
    // 最大的监听的事件数量
    static const int MAX_EVENT_NUMBER = 10000;

    static const int TIMESLOT = 5; // 最小超时单位
    //================== 变量值 ====================
    // 线程池
    threadpool<http_conn> *pool;
    // 创建一个数组用于保存所有的客户端信息
    http_conn *users;
    // 监听的套接字
    int listenfd;
    // 创建epoll对象和事件数组
    epoll_event events[MAX_EVENT_NUMBER];
    static int epollfd;
    int ret;
    //========设置定时器相关参数=======
    // 主从线程管道通信
    static int pipefd[2];
    // 信号链表
    static sort_timer_lst timer_lst;
    // 创建连接资源数组
    client_data *users_timer = new client_data[MAX_FD];
    // 超时默认为False
    bool timeout = false;
    // 循环条件
    bool stop_server = false;

    //================== 功能 ====================
    // 添加信号捕捉
    void addsig(int sig, void(handler)(int), bool restart = true);
    // 信号处理函数
    static void sig_handler(int sig);
    // 信号 定时处理
    void timer_handler();
    static void cb_func(client_data *user_data);

    // 非阻塞的读,循环读取
    bool Read(http_conn &conn);
    // 非阻塞的读
    bool Write(http_conn &conn);
};

int epoll_class::epollfd = 0;
int epoll_class::pipefd[2] = {0, 0};
sort_timer_lst epoll_class::timer_lst;

// 添加信号捕捉
void epoll_class::addsig(int sig, void(handler)(int), bool restart)
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    sigfillset(&sa.sa_mask);
    if (restart)
        sa.sa_flags |= SA_RESTART;
    // 应用信号捕捉
    sigaction(sig, &sa, NULL);
}

// 定时处理任务，重新定时以不断触发SIGALRM信号
void epoll_class::timer_handler()
{
    timer_lst.tick();
    alarm(TIMESLOT);
}
void epoll_class::sig_handler(int sig)
{
    // 为保证函数的可重入性，保留原来的errno
    int save_errno = errno;
    int msg = sig;
    send(pipefd[1], (char *)&msg, 1, 0);
    errno = save_errno;
}

// 定时器回调函数，删除非活动连接在socket上的注册事件，并关闭
void epoll_class::cb_func(client_data *user_data)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user_data->socket, 0);
    assert(user_data);
    close(user_data->socket);
    http_conn::m_user_count--;
    LOG_INFO("close fd %d", user_data->socket);
    Log::get_instance()->flush();
}
// 非阻塞的读,循环读取
bool epoll_class::Read(http_conn &conn)
{
    int m_sockfd = conn.get_sockfd();
    int m_read_index = conn.get_read_index();
    char *m_read_buf = conn.get_read_buf();

    // 缓冲已满
    if (m_read_index >= READ_BUFFER_SIZE)
    {
        return false;
    }
    // 读取字节
    while (true)
    {
        int bytes_read = recv(m_sockfd, m_read_buf + m_read_index, READ_BUFFER_SIZE - m_read_index, 0);
        if (bytes_read == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            else
                return false;
        }
        else if (bytes_read == 0)
        {
            return false;
        }
        m_read_index += bytes_read;
    }
    // 更新值
    // printf("read data:\n%s",m_read_buf);
    conn.set_read_index(m_read_index);
    return true;
}
// 非阻塞的写
bool epoll_class::Write(http_conn &conn)
{
    const int m_sockfd = conn.get_sockfd();
    int bytes_to_send = conn.get_bytes_to_send();
    iovec *m_iv = conn.get_iv();
    const int m_iv_count = conn.get_iv_count();

    if (bytes_to_send == 0)
    {
        // 将要发送的字节为0
        modfd(epollfd, m_sockfd, EPOLLIN);
        conn.clear();
        return true;
    }

    while (true)
    {
        int ret = writev(m_sockfd, m_iv, m_iv_count);
        if (ret > 0)
        {
        }
        if (ret <= -1)
        {
            // 发送失败
            if (errno == EAGAIN)
            { // 重试
                if (bytes_to_send >= m_iv[0].iov_len)
                {
                    m_iv[1].iov_base = (char *)m_iv[1].iov_base + (ret - m_iv[0].iov_len);
                    m_iv[1].iov_len -= (ret - m_iv[0].iov_len);
                    m_iv[0].iov_len = 0;
                }
                else
                { // 第一部分还没写完
                    m_iv[0].iov_base = (char *)(m_iv[0].iov_base) + ret;
                    m_iv[0].iov_len -= ret;
                }
                modfd(epollfd, m_sockfd, EPOLLOUT);
                return true;
            }
            conn.unmap();
            return false;
        }
        // 本次写成功
        // 维护还需发送字节数和已发送字节数
        bytes_to_send -= ret;
        // 发送结束
        if (bytes_to_send <= 0)
        { // 发送HTTP响应成功,释放内存
            conn.unmap();

            modfd(epollfd, m_sockfd, EPOLLIN);
            // 是否keep-alive
            if (conn.is_keepalive())
            {
                conn.clear();
                // 继续接受信息
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

epoll_class::epoll_class(int port)
{
    Log::get_instance()->init("ServerLog", 2000, 800000, 0); // 同步日志模型

    // 对SIGPIPE信号处理
    // 避免因为SIGPIPE退出
    addsig(SIGPIPE, SIG_IGN);

    // 创建数据库连接池
    connection_pool *connPool = connection_pool::GetInstance();
    connPool->init("localhost", "debian-sys-maint", "7BRI1rZOWHprgZaj", "yourdb", 3306, 8);

    // 创建线程池，初始化线程池
    pool = NULL;
    try
    {
        pool = new threadpool<http_conn>(connPool);
    }
    catch (const char *msg)
    {
        printf("error:%s\n", msg);
        exit(-1);
    }
    printf("begin\n");

    // 创建一个数组用于保存所有的客户端信息
    users = new http_conn[MAX_FD];

    users->initmysql_result(connPool);

    // 进行网络通信
    // 创建监听的套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        perror("socket");
        exit(-1);
    }

    // 绑定
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    // 设置端口复用(在绑定之前)
    int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    // 将 fd 和本地的 IP 和端口进行绑定
    ret = bind(listenfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }

    // 监听
    ret = listen(listenfd, 5);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }

    // 创建epoll
    epollfd = epoll_create(100);
    assert(epollfd != -1);

    // 将监听的文件描述符添加到epoll中
    // 监听socket listenfd 上是不能注册ONESHOT事件，否则就只能处理一个客户连接
    addfd(epollfd, listenfd, false);
    http_conn::m_user_count = 0;
    http_conn::st_m_epollfd = epollfd;

    ret = socketpair(PF_UNIX, SOCK_STREAM, 0, pipefd);
    assert(ret != -1);
    // 设置管道写端为非阻塞，为什么写端要非阻塞？
    setnonblocking(pipefd[1]);
    // 设置管道读端为ET非阻塞
    addfd(epollfd, pipefd[0], false);
    // 传递给主循环的信号值，这里只关注SIGALRM和SIGTERM
    addsig(SIGALRM, epoll_class::sig_handler, false);
    addsig(SIGTERM, epoll_class::sig_handler, false);

    // 每隔TIMESLOT时间触发SIGALRM信号
    alarm(TIMESLOT);
}

void epoll_class::run()
{
    // 进行监听
    while (true)
    {
        int num = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
        if (num < 0 && errno != EINTR)
        {
            printf("epoll fail\n");
            break;
        }

        // 循环遍历事件数组
        for (int i = 0; i < num; i++)
        {
            int sockfd = events[i].data.fd;

            if (events[i].data.fd == listenfd)
            { // 监听到新的客户端连接
                sockaddr_in client_addr;
                socklen_t client_addrlen = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addrlen);

                if (connfd < 0)
                {
                    LOG_ERROR("%s:errno is:%d", "accept error", errno);

                    printf("errno is: %d\n", errno);
                    continue;
                }
                // LT 模式
                //  判断文件描述符表是否满了
                if (http_conn::m_user_count >= MAX_FD)
                {
                    LOG_ERROR("%s", "Internal server busy");

                    // ?回写数据:服务器正忙
                    // 连接满了
                    close(connfd);
                    continue;
                }
                // 将新的客户的数据初始化,放到数组中

                users[connfd].init(connfd, client_addr);

                //================================================
                // 初始化client_data数据
                // 创建定时器，设置回调函数和超时时间，绑定用户数据，将定时器添加到链表中
                users_timer[connfd].address = client_addr;
                users_timer[connfd].socket = connfd;
                util_timer *timer = new util_timer;
                timer->user_data = &users_timer[connfd];
                timer->cb_func = cb_func;
                time_t cur = time(NULL);
                timer->exprie = cur + 3 * TIMESLOT;
                users_timer[connfd].timer = timer;
                timer_lst.add_timer(timer);
                //================================================
            }
            // 不是连接类型
            else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR))
            { // 异常断开等错误事件
                util_timer *timer = users_timer[sockfd].timer;
                timer->cb_func(&users_timer[sockfd]);

                if (timer)
                {
                    timer_lst.del_timer(timer);
                }
            }
            else if ((sockfd == pipefd[0]) && (events[i].events & EPOLLIN))
            {
                int sig;
                char signals[1024];

                // 从管道读端读出信号值，成功返回字节数，失败返回-1
                // 正常情况下，这里的ret返回值总是1，只有14和15两个ASCII码对应的字符
                int ret = recv(pipefd[0], signals, sizeof(signals), 0);
                if (ret == -1)
                {
                    continue;
                }
                else if (ret == 0)
                {
                    continue;
                }
                else
                { // 处理信号值对应的逻辑
                    for (int i = 0; i < ret; ++i)
                    { // 这里面明明是字符
                        switch (signals[i])
                        {
                            // 这里是整型
                        case SIGALRM:
                        {
                            timeout = true;
                            break;
                        }
                        case SIGTERM:
                        {
                            stop_server = true;
                        }
                        }
                    }
                }
            }
            // 网页的响应需要读取
            else if (events[i].events & EPOLLIN)
            {
                // printf("网页需要读取\n");
                util_timer *timer = users_timer[sockfd].timer;

                if (Read(users[sockfd]))
                {
                    LOG_INFO("deal with the client(%s)", inet_ntoa(users[sockfd].m_address.sin_addr));
                    Log::get_instance()->flush();
                    // 读完了
                    pool->append(users + sockfd);

                    // 若有数据传输，则将定时器往后延迟3个单位
                    // 并对新的定时器在链表上的位置进行调整
                    if (timer)
                    {
                        time_t cur = time(NULL);
                        timer->exprie = cur + 3 * TIMESLOT;
                        LOG_INFO("%s", "adjust timer once");
                        Log::get_instance()->flush();
                        timer_lst.adjust_timer(timer);
                    }
                }
                else
                {
                    timer->cb_func(&users_timer[sockfd]);
                    if (timer)
                    {
                        timer_lst.del_timer(timer);
                    }
                    // 读失败了
                }
            }
            // 需要写给网页响应
            else if (events[i].events & EPOLLOUT)
            {
                // printf("需要写给网页响应\n");
                util_timer *timer = users_timer[sockfd].timer;
                if (Write(users[sockfd]))
                {
                    // 写成功
                    LOG_INFO("send data to the client(%s)", inet_ntoa(users[sockfd].m_address.sin_addr));
                    Log::get_instance()->flush();

                    // 若有数据传输，则将定时器往后延迟3个单位
                    // 并对新的定时器在链表上的位置进行调整
                    if (timer)
                    {
                        time_t cur = time(NULL);
                        timer->exprie = cur + 3 * TIMESLOT;
                        LOG_INFO("%s", "adjust timer once");
                        Log::get_instance()->flush();
                        timer_lst.adjust_timer(timer);
                    }
                }
                else
                {
                    timer->cb_func(&users_timer[sockfd]);
                    if (timer)
                    {
                        timer_lst.del_timer(timer);
                    }
                }
            }
        }
        if (timeout)
        {
            timer_handler();
            timeout = false;
        }
    }
}
epoll_class::~epoll_class()
{
    // 结束后close
    close(epollfd);
    close(listenfd);
    close(pipefd[1]);
    close(pipefd[0]);
    delete[] users;
    delete[] users_timer;
    delete pool;
}

#endif