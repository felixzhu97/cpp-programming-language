# Chapter 18: 用于大型程序的工具

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 命名空间演示
add_executable(namespace_demo namespace_demo.cpp)

# 打印编译信息
message(STATUS "Chapter 18: 用于大型程序的工具演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - namespace_demo: 命名空间和大型程序工具演示") 