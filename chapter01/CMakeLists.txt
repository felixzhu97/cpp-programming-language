# 第一章：基础入门

# 创建可执行文件
add_executable(hello_world hello_world.cpp)
add_executable(input_output input_output.cpp)
add_executable(variables_demo variables_demo.cpp)
add_executable(simple_calculator simple_calculator.cpp)
add_executable(control_flow control_flow.cpp)

# 创建章节目标
add_custom_target(chapter01_examples)
add_dependencies(chapter01_examples 
    hello_world
    input_output
    variables_demo
    simple_calculator
    control_flow
)

# 为每个目标设置输出目录
set_target_properties(hello_world PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter01
)
set_target_properties(input_output PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter01
)
set_target_properties(variables_demo PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter01
)
set_target_properties(simple_calculator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter01
)
set_target_properties(control_flow PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/chapter01
) 