# 第五章：语句

# 创建可执行文件
add_executable(simple_statements simple_statements.cpp)
add_executable(conditional_statements conditional_statements.cpp)
add_executable(loop_statements loop_statements.cpp)
add_executable(jump_statements jump_statements.cpp)
add_executable(exception_handling exception_handling.cpp)
add_executable(statement_blocks statement_blocks.cpp)
add_executable(advanced_control_flow advanced_control_flow.cpp)

# 创建章节目标
add_custom_target(chapter05_examples)
add_dependencies(chapter05_examples 
    simple_statements
    conditional_statements
    loop_statements
    jump_statements
    exception_handling
    statement_blocks
    advanced_control_flow
)

# 为每个目标设置输出目录
set_target_properties(simple_statements PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter05
)
set_target_properties(conditional_statements PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter05
)
set_target_properties(loop_statements PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter05
)
set_target_properties(jump_statements PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter05
)
set_target_properties(exception_handling PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter05
)
set_target_properties(statement_blocks PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter05
)
set_target_properties(advanced_control_flow PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter05
) 