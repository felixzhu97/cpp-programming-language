# Chapter 12: 动态内存

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 动态内存基础
add_executable(dynamic_memory_basics dynamic_memory_basics.cpp)

# 智能指针
add_executable(smart_pointers smart_pointers.cpp)

# 内存管理最佳实践
add_executable(memory_best_practices memory_best_practices.cpp)

# 高级内存技术
add_executable(advanced_memory advanced_memory.cpp)

# 打印编译信息
message(STATUS "Chapter 12: 动态内存演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - dynamic_memory_basics: 动态内存基础")
message(STATUS "  - smart_pointers: 智能指针演示")
message(STATUS "  - memory_best_practices: 内存管理最佳实践")
message(STATUS "  - advanced_memory: 高级内存技术") 