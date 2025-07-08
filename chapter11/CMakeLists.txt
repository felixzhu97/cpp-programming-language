# Chapter 11: 关联容器

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# map 和 multimap 容器
add_executable(map_containers map_containers.cpp)

# set 和 multiset 容器
add_executable(set_containers set_containers.cpp)

# 无序容器
add_executable(unordered_containers unordered_containers.cpp)

# 关联容器操作
add_executable(associative_operations associative_operations.cpp)

# 打印编译信息
message(STATUS "Chapter 11: 关联容器演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - map_containers: map/multimap 容器演示")
message(STATUS "  - set_containers: set/multiset 容器演示")
message(STATUS "  - unordered_containers: 无序容器演示")
message(STATUS "  - associative_operations: 关联容器操作演示") 