# Chapter 17: 标准库特殊设施

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 正则表达式演示
add_executable(regex_demo regex_demo.cpp)

# 打印编译信息
message(STATUS "Chapter 17: 标准库特殊设施演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - regex_demo: 正则表达式和专门库设施演示") 