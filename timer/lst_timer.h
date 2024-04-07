#ifndef LST_TIMER
#define LST_TIMER

#include <time.h>
#include <netinet/in.h>
#include <iostream>
#define BUFFER_SIZE 64

class util_timer;

class client_data
{
public:
    // 客户端的socket地址
    sockaddr_in address;
    // socket 的文件描述符
    int socket;
    // 客户端的定时器
    util_timer *timer;
};

class util_timer
{
public:
    util_timer() : prev(NULL), next(NULL)
    {
    }

public:
    time_t exprie;                  // 任务超时时间
    void (*cb_func)(client_data *); // 任务回调函数
    client_data *user_data;
    util_timer *prev;
    util_timer *next;
};

class sort_timer_lst
{
private:
    util_timer *head;
    util_timer *tail;

public:
    sort_timer_lst() : head(NULL), tail(NULL)
    {
    }
    ~sort_timer_lst()
    {
        util_timer *tmp = head;
        while (tmp)
        {
            head = tmp->next;
            delete tmp;
            tmp = head;
        }
    }
    void add_timer(util_timer *timer)
    {
        if (!timer)
        {
            printf("timer is null\n");
            return;
        }
        if (!head)
        {
            tail = head = timer;
            return;
        }
        else if (timer->exprie <= head->exprie)
        {
            timer->next = head;
            head->prev = timer;
            head = timer;
            return;
        }
        add_timer(timer, head);
    }
    // 调整定时器，任务发生变化时，调整定时器在链表中的位置只考虑定时器的超时时间延长的情况。需要朝后移动
    void adjust_timer(util_timer *timer)
    {
        if (!timer)
        {
            printf("timer is null\n");
        }
        if (timer == tail || (timer->exprie <= timer->next->exprie))
        {
            return;
        }
        else if (timer == head)
        {
            head->prev = nullptr;
            timer->next = nullptr;
            add_timer(timer, head);
        }
        else
        {
            timer->next->prev = timer->prev->next;
            timer->prev->next = timer->next->prev;
            add_timer(timer, head);
        }
    }

    void del_timer(util_timer *timer)
    {
        if (!timer)
        {
            printf("timer is null\n");
            return;
        }
        if (timer == head && timer == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else if (timer == head)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else if (timer == tail)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            timer->next->prev = timer->prev->next;
            timer->prev->next = timer->next->prev;
        }
        delete timer;
        return;
    }
    // 信号每次出发就在处理函数中执行一次tick 以处理链表上到期的定时器
    void tick()
    {
        if (!head)
        {
            return;
        }
        // printf("time tick \n");
        LOG_INFO("%s", "timer tick");
        Log::get_instance()->flush();
        time_t cur = time(NULL);
        util_timer *tmp = head;
        // 链表容器为升序排列
        // 当前时间小于定时器的超时时间，后面的定时器也没有到期
        while (tmp)
        {
            if (cur < tmp->exprie)
                break;
            tmp->cb_func(tmp->user_data);
            head = tmp->next;
            if (head)
            {
                head->prev = nullptr;
            }
            delete tmp;
            tmp = head;
        }
    }

    void add_timer(util_timer *timer, util_timer *lst_head)
    {
        util_timer *prve = lst_head;
        util_timer *tmp = lst_head->next;

        while (tmp)
        {
            if (timer->exprie <= tmp->exprie)
            {
                timer->next = tmp;
                prve->next = timer;
                timer->prev = prve;
                tmp->prev = timer;
            }
            prve = tmp;
            tmp = prve->next;
        }

        if (!tmp)
        {
            prve->next = timer;
            timer->prev = prve;
            timer->next = NULL;
            tail = timer;
        }
    }
};

#endif