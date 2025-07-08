# 第7章：类
cmake_minimum_required(VERSION 3.10)

# 设置编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含通用头文件目录
include_directories(${CMAKE_SOURCE_DIR}/common)

# 编译器警告选项
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 类的基础
add_executable(chapter07_class_basics class_basics.cpp)
target_link_libraries(chapter07_class_basics ${CMAKE_THREAD_LIBS_INIT})

# 构造函数和析构函数
add_executable(chapter07_constructors_destructors constructors_destructors.cpp)
target_link_libraries(chapter07_constructors_destructors ${CMAKE_THREAD_LIBS_INIT})

# 成员函数
add_executable(chapter07_member_functions member_functions.cpp)
target_link_libraries(chapter07_member_functions ${CMAKE_THREAD_LIBS_INIT})

# 访问控制
add_executable(chapter07_access_control access_control.cpp)
target_link_libraries(chapter07_access_control ${CMAKE_THREAD_LIBS_INIT})

# 类的组合
add_executable(chapter07_class_composition class_composition.cpp)
target_link_libraries(chapter07_class_composition ${CMAKE_THREAD_LIBS_INIT})

# 静态成员
add_executable(chapter07_static_members static_members.cpp)
target_link_libraries(chapter07_static_members ${CMAKE_THREAD_LIBS_INIT})

# 高级类特性
add_executable(chapter07_advanced_classes advanced_classes.cpp)
target_link_libraries(chapter07_advanced_classes ${CMAKE_THREAD_LIBS_INIT})

# 设置输出目录
set_target_properties(
    chapter07_class_basics
    chapter07_constructors_destructors
    chapter07_member_functions
    chapter07_access_control
    chapter07_class_composition
    chapter07_static_members
    chapter07_advanced_classes
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter07
)

# 添加自定义目标来构建所有第7章示例
add_custom_target(chapter07_examples
    DEPENDS 
    chapter07_class_basics
    chapter07_constructors_destructors
    chapter07_member_functions
    chapter07_access_control
    chapter07_class_composition
    chapter07_static_members
    chapter07_advanced_classes
)

# 打印构建信息
message(STATUS "Chapter 7 (Classes) examples configured")
message(STATUS "Available executables:")
message(STATUS "  - chapter07_class_basics")
message(STATUS "  - chapter07_constructors_destructors")
message(STATUS "  - chapter07_member_functions")
message(STATUS "  - chapter07_access_control")
message(STATUS "  - chapter07_class_composition")
message(STATUS "  - chapter07_static_members")
message(STATUS "  - chapter07_advanced_classes") 