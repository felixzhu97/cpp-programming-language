cmake_minimum_required(VERSION 3.12)

# Chapter 9: 顺序容器
project(Chapter09_SequentialContainers)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 包含头文件目录
include_directories(${CMAKE_SOURCE_DIR}/common)

# 创建可执行文件

# 1. 容器概述
add_executable(container_overview container_overview.cpp)

# 2. vector 容器
add_executable(vector_container vector_container.cpp)

# 3. list 容器
add_executable(list_container list_container.cpp)

# 4. deque 容器
add_executable(deque_container deque_container.cpp)

# 5. array 容器
add_executable(array_container array_container.cpp)

# 6. forward_list 容器
add_executable(forward_list_container forward_list_container.cpp)

# 7. 容器适配器
add_executable(container_adapters container_adapters.cpp)

# 8. 高级操作
add_executable(advanced_operations advanced_operations.cpp)

# 添加到 Chapter09 目标
add_custom_target(Chapter09 DEPENDS
    container_overview
    vector_container
    list_container
    deque_container
    array_container
    forward_list_container
    container_adapters
    advanced_operations
)

# 打印构建信息
message(STATUS "Chapter 9: 顺序容器")
message(STATUS "  - container_overview: STL 容器分类和通用接口")
message(STATUS "  - vector_container: vector 动态数组详解")
message(STATUS "  - list_container: list 双向链表详解")
message(STATUS "  - deque_container: deque 双端队列详解")
message(STATUS "  - array_container: array 固定数组详解")
message(STATUS "  - forward_list_container: forward_list 单向链表详解")
message(STATUS "  - container_adapters: stack、queue、priority_queue 适配器")
message(STATUS "  - advanced_operations: 容器高级操作和特性")

# 设置输出目录
set_target_properties(
    container_overview
    vector_container
    list_container
    deque_container
    array_container
    forward_list_container
    container_adapters
    advanced_operations
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter09
) 