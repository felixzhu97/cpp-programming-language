# Chapter 14: 重载运算与类型转换

cmake_minimum_required(VERSION 3.16)

# 设置编译器标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")

# 运算符重载
add_executable(operator_overloading operator_overloading.cpp)

# 类型转换运算符
add_executable(conversion_operators conversion_operators.cpp)

# 函数对象
add_executable(function_objects function_objects.cpp)

# Lambda 表达式
add_executable(lambda_expressions lambda_expressions.cpp)

# 打印编译信息
message(STATUS "Chapter 14: 重载运算与类型转换演示程序配置完成")
message(STATUS "包含的可执行文件:")
message(STATUS "  - operator_overloading: 运算符重载演示")
message(STATUS "  - conversion_operators: 类型转换运算符演示")
message(STATUS "  - function_objects: 函数对象演示")
message(STATUS "  - lambda_expressions: Lambda 表达式高级演示") 