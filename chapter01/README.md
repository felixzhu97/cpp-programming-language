# 第 1 章：开始

本章介绍 C++编程的基础知识，包括第一个 C++程序的编写、基本的输入输出操作、变量的使用以及简单的控制流结构。

## 本章内容

### 1. Hello World 程序 (`hello_world.cpp`)

- 基本的 C++程序结构
- `#include` 预处理指令
- `main` 函数的作用
- 输出语句 `cout`
- 程序的编译和运行

### 2. 输入输出操作 (`input_output.cpp`)

- 标准输入流 `cin` 的使用
- 标准输出流 `cout` 的使用
- 错误输出流 `cerr` 的使用
- 输入输出的格式控制
- 字符串的输入输出
- 数值的输入输出

### 3. 变量演示 (`variables_demo.cpp`)

- 基本数据类型：`int`, `double`, `char`, `bool`
- 变量的声明和初始化
- 变量的命名规则
- 算术运算符的使用
- 变量值的修改和使用

### 4. 控制流程 (`control_flow.cpp`)

- 条件语句：`if`, `else if`, `else`
- 循环语句：`for`, `while`, `do-while`
- 比较运算符的使用
- 逻辑运算符的使用
- 循环控制语句

### 5. 简单计算器 (`simple_calculator.cpp`)

- 综合运用输入输出
- 基本的四则运算
- 用户交互设计
- 错误处理基础
- 程序结构设计

## 编译和运行

使用 CMake 编译：

```bash
mkdir build
cd build
cmake ..
make
```

或者使用脚本：

```bash
./compile_and_run.sh chapter01 hello_world
./compile_and_run.sh chapter01 input_output
./compile_and_run.sh chapter01 variables_demo
./compile_and_run.sh chapter01 control_flow
./compile_and_run.sh chapter01 simple_calculator
```

## 学习要点

1. **C++程序结构**：理解 C++程序的基本结构，包括预处理指令、函数定义等。

2. **输入输出流**：掌握标准输入输出流的使用，这是 C++程序与用户交互的基础。

3. **变量和数据类型**：学会声明和使用不同类型的变量，理解基本数据类型的特点。

4. **控制结构**：掌握条件语句和循环语句的使用，这是程序逻辑控制的基础。

5. **编程规范**：从一开始就养成良好的编程习惯，包括代码格式、变量命名等。

## 扩展练习

1. 修改`hello_world.cpp`，输出多行欢迎信息
2. 在`simple_calculator.cpp`中添加更多运算功能（幂运算、求余等）
3. 编写一个猜数字游戏，结合随机数生成和循环控制
4. 创建一个简单的菜单驱动程序，让用户选择不同的功能

## 注意事项

- 确保理解每个程序的基本逻辑
- 尝试修改程序参数，观察输出变化
- 注意编译错误信息，学会调试基本语法错误
- 理解程序的输入输出流向

这一章是 C++学习的起点，为后续章节打下坚实基础。
