# 第8章：IO库
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

# 查找线程库
find_package(Threads REQUIRED)

# IO库基础
add_executable(chapter08_io_basics io_basics.cpp)
target_link_libraries(chapter08_io_basics ${CMAKE_THREAD_LIBS_INIT})

# 文件输入输出
add_executable(chapter08_file_io file_io.cpp)
target_link_libraries(chapter08_file_io ${CMAKE_THREAD_LIBS_INIT})

# 字符串流
add_executable(chapter08_string_streams string_streams.cpp)
target_link_libraries(chapter08_string_streams ${CMAKE_THREAD_LIBS_INIT})

# 格式化输入输出
add_executable(chapter08_formatted_io formatted_io.cpp)
target_link_libraries(chapter08_formatted_io ${CMAKE_THREAD_LIBS_INIT})

# IO操纵符
add_executable(chapter08_io_manipulators io_manipulators.cpp)
target_link_libraries(chapter08_io_manipulators ${CMAKE_THREAD_LIBS_INIT})

# 流的继承体系
add_executable(chapter08_stream_hierarchy stream_hierarchy.cpp)
target_link_libraries(chapter08_stream_hierarchy ${CMAKE_THREAD_LIBS_INIT})

# 高级IO特性
add_executable(chapter08_advanced_io advanced_io.cpp)
target_link_libraries(chapter08_advanced_io Threads::Threads)

# 设置输出目录
set_target_properties(
    chapter08_io_basics
    chapter08_file_io
    chapter08_string_streams
    chapter08_formatted_io
    chapter08_io_manipulators
    chapter08_stream_hierarchy
    chapter08_advanced_io
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter08
)

# 添加自定义目标来构建所有第8章示例
add_custom_target(chapter08_examples
    DEPENDS 
    chapter08_io_basics
    chapter08_file_io
    chapter08_string_streams
    chapter08_formatted_io
    chapter08_io_manipulators
    chapter08_stream_hierarchy
    chapter08_advanced_io
)

# 打印构建信息
message(STATUS "Chapter 8 (IO Library) examples configured")
message(STATUS "Available executables:")
message(STATUS "  - chapter08_io_basics")
message(STATUS "  - chapter08_file_io")
message(STATUS "  - chapter08_string_streams")
message(STATUS "  - chapter08_formatted_io")
message(STATUS "  - chapter08_io_manipulators")
message(STATUS "  - chapter08_stream_hierarchy")
message(STATUS "  - chapter08_advanced_io") 