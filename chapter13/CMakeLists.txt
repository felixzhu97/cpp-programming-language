# Chapter 13: 拷贝控制

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 拷贝控制
add_executable(copy_control copy_control.cpp)

# 移动语义
add_executable(move_semantics move_semantics.cpp)

# 打印编译信息
message(STATUS "Chapter 13: 拷贝控制演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - copy_control: 拷贝控制演示")
message(STATUS "  - move_semantics: 移动语义演示") 