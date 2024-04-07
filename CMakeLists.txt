cmake_minimum_required(VERSION 3.15)
project(Webserver)
set(CMAKE_CXX_STANDARD 11)

# 添加源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} s1)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/http s2)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/lock s3)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/PthreadPool s4)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/timer s5)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/log s6)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/CGImysql s7)

# 添加头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/http)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lock)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/PthreadPool)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/timer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/log)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CGImysql)

# 添加链接 MySQL 客户端库的指令
find_package(Threads REQUIRED)
find_library(MYSQL_CLIENT_LIB mysqlclient)

if(MYSQL_CLIENT_LIB)
    message(STATUS "MySQL client library found: ${MYSQL_CLIENT_LIB}")
    set(ALL ${s1} ${s2} ${s3} ${s4} ${s5} ${s6} ${s7})
    add_executable(main ${ALL})
    target_link_libraries(main ${MYSQL_CLIENT_LIB} Threads::Threads)

    # 启用调试标志
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g ")
else()
    message(FATAL_ERROR "MySQL client library not found.")
endif()
