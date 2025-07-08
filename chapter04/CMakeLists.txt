# 第四章：表达式和运算符

# 创建可执行文件
add_executable(arithmetic_operators arithmetic_operators.cpp)
add_executable(logical_operators logical_operators.cpp)
add_executable(bitwise_operators bitwise_operators.cpp)
add_executable(assignment_operators assignment_operators.cpp)
add_executable(operator_precedence operator_precedence.cpp)
add_executable(conditional_operator conditional_operator.cpp)
add_executable(sizeof_operator sizeof_operator.cpp)
add_executable(type_conversions type_conversions.cpp)

# 创建章节目标
add_custom_target(chapter04_examples)
add_dependencies(chapter04_examples 
    arithmetic_operators
    logical_operators
    bitwise_operators
    assignment_operators
    operator_precedence
    conditional_operator
    sizeof_operator
    type_conversions
)

# 为每个目标设置输出目录
set_target_properties(arithmetic_operators PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
)
set_target_properties(logical_operators PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
)
set_target_properties(bitwise_operators PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
)
set_target_properties(assignment_operators PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
)
set_target_properties(operator_precedence PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
)
set_target_properties(conditional_operator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
)
set_target_properties(sizeof_operator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
)
set_target_properties(type_conversions PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter04
) 