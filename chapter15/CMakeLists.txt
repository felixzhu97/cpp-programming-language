# Chapter 15: 面向对象程序设计

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 继承基础
add_executable(inheritance_basics inheritance_basics.cpp)

# 虚函数和多态
add_executable(virtual_functions_polymorphism virtual_functions_polymorphism.cpp)

# 继承中的拷贝控制
add_executable(inheritance_copy_control inheritance_copy_control.cpp)

# 多重继承
add_executable(multiple_inheritance multiple_inheritance.cpp)

# 打印编译信息
message(STATUS "Chapter 15: 面向对象程序设计演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - inheritance_basics: 继承基础演示")
message(STATUS "  - virtual_functions_polymorphism: 虚函数和多态演示")
message(STATUS "  - inheritance_copy_control: 继承中的拷贝控制演示")
message(STATUS "  - multiple_inheritance: 多重继承演示") 