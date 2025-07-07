# 第三章：字符串、向量和数组

# 创建可执行文件
add_executable(string_demo string_demo.cpp)
add_executable(vector_demo vector_demo.cpp)
add_executable(array_demo array_demo.cpp)
add_executable(iterator_demo iterator_demo.cpp)
add_executable(multidimensional_arrays multidimensional_arrays.cpp)
add_executable(string_vector_practice string_vector_practice.cpp)

# 创建章节目标
add_custom_target(chapter03_examples)
add_dependencies(chapter03_examples 
    string_demo
    vector_demo
    array_demo
    iterator_demo
    multidimensional_arrays
    string_vector_practice
)

# 为每个目标设置输出目录
set_target_properties(string_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter03
)
set_target_properties(vector_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter03
)
set_target_properties(array_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter03
)
set_target_properties(iterator_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter03
)
set_target_properties(multidimensional_arrays PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter03
)
set_target_properties(string_vector_practice PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter03
) 