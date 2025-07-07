cmake_minimum_required(VERSION 3.10)
project(CppProgrammingLanguage)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器标志
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# 包含通用头文件目录
include_directories(common)

# 创建每个章节的子目录
add_subdirectory(chapter01)
add_subdirectory(chapter02)
add_subdirectory(chapter03)
add_subdirectory(chapter04)
add_subdirectory(chapter05)
add_subdirectory(chapter06)
add_subdirectory(chapter07)
add_subdirectory(chapter08)
add_subdirectory(chapter09)
add_subdirectory(chapter10)
add_subdirectory(chapter11)
add_subdirectory(chapter12)
add_subdirectory(chapter13)
add_subdirectory(chapter14)
add_subdirectory(chapter15)
add_subdirectory(chapter16)
add_subdirectory(chapter17)
add_subdirectory(chapter18)
add_subdirectory(chapter19)

# 创建一个目标来构建所有示例
add_custom_target(all_examples)

# 添加依赖
add_dependencies(all_examples 
    chapter01_examples
    chapter02_examples
    chapter03_examples
    chapter04_examples
    chapter05_examples
    chapter06_examples
    chapter07_examples
    chapter08_examples
    chapter09_examples
    chapter10_examples
    chapter11_examples
    chapter12_examples
    chapter13_examples
    chapter14_examples
    chapter15_examples
    chapter16_examples
    chapter17_examples
    chapter18_examples
    chapter19_examples
)

# 显示构建信息
message(STATUS "C++ Programming Language Examples")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}") 