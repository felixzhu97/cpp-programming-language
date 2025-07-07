# 第二章：变量和数据类型

# 创建可执行文件
add_executable(basic_types basic_types.cpp)
add_executable(type_conversion type_conversion.cpp)
add_executable(const_demo const_demo.cpp)
add_executable(pointers_references pointers_references.cpp)
add_executable(compound_types compound_types.cpp)
add_executable(auto_decltype auto_decltype.cpp)

# 创建章节目标
add_custom_target(chapter02_examples)
add_dependencies(chapter02_examples 
    basic_types
    type_conversion
    const_demo
    pointers_references
    compound_types
    auto_decltype
)

# 为每个目标设置输出目录
set_target_properties(basic_types PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter02
)
set_target_properties(type_conversion PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter02
)
set_target_properties(const_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter02
)
set_target_properties(pointers_references PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter02
)
set_target_properties(compound_types PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter02
)
set_target_properties(auto_decltype PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter02
) 