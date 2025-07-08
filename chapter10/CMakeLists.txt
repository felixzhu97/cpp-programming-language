# Chapter 10: 泛型算法

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 算法概述
add_executable(algorithm_overview algorithm_overview.cpp)

# 查找算法
add_executable(search_algorithms search_algorithms.cpp)

# 排序算法
add_executable(sorting_algorithms sorting_algorithms.cpp)

# 拷贝和移动算法
add_executable(copy_move_algorithms copy_move_algorithms.cpp)

# 修改算法
add_executable(modifying_algorithms modifying_algorithms.cpp)

# 数值算法
add_executable(numeric_algorithms numeric_algorithms.cpp)

# 集合算法
add_executable(set_algorithms set_algorithms.cpp)

# 高级算法技巧
add_executable(advanced_algorithms advanced_algorithms.cpp)

# 打印编译信息
message(STATUS "Chapter 10: 泛型算法演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - algorithm_overview: STL算法概述")
message(STATUS "  - search_algorithms: 查找算法演示")
message(STATUS "  - sorting_algorithms: 排序算法演示")
message(STATUS "  - copy_move_algorithms: 拷贝移动算法演示")
message(STATUS "  - modifying_algorithms: 修改算法演示")
message(STATUS "  - numeric_algorithms: 数值算法演示")
message(STATUS "  - set_algorithms: 集合算法演示")
message(STATUS "  - advanced_algorithms: 高级算法技巧演示") 