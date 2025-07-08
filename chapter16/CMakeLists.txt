# Chapter 16: 模板与泛型编程

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 函数模板
add_executable(function_templates function_templates.cpp)

# 类模板
add_executable(class_templates class_templates.cpp)

# 高级模板特性
add_executable(advanced_templates advanced_templates.cpp)

# 标准库模板
add_executable(standard_library_templates standard_library_templates.cpp)

# 打印编译信息
message(STATUS "Chapter 16: 模板与泛型编程演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - function_templates: 函数模板演示")
message(STATUS "  - class_templates: 类模板演示") 
message(STATUS "  - advanced_templates: 高级模板特性演示")
message(STATUS "  - standard_library_templates: 标准库模板演示") 