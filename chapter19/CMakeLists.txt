# Chapter 19: 特殊工具和技术

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 多线程演示
add_executable(thread_demo thread_demo.cpp)
target_link_libraries(thread_demo pthread)

# 打印编译信息
message(STATUS "Chapter 19: 特殊工具和技术演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - thread_demo: 多线程和特殊工具演示") 