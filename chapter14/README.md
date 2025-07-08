# 第 14 章：重载运算与类型转换

本章详细介绍 C++中的运算符重载和类型转换，包括各种运算符的重载、类型转换运算符等内容。

## 本章内容

### 1. 运算符重载基础 (`operator_overloading_basics.cpp`)

- 运算符重载的原则
- 成员函数 vs 非成员函数
- 运算符重载的限制
- 常用运算符重载

### 2. 算术和关系运算符 (`arithmetic_relational_operators.cpp`)

- 算术运算符重载
- 关系运算符重载
- 复合赋值运算符
- 前缀和后缀运算符

### 3. 函数调用运算符 (`function_call_operator.cpp`)

- 函数对象
- 可调用对象
- lambda 表达式
- 标准库函数对象

### 4. 类型转换运算符 (`type_conversion_operators.cpp`)

- 转换构造函数
- 类型转换运算符
- explicit 关键字
- 避免意外转换

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter14 operator_overloading_basics
./compile_and_run.sh chapter14 arithmetic_relational_operators
./compile_and_run.sh chapter14 function_call_operator
./compile_and_run.sh chapter14 type_conversion_operators
```

## 学习要点

1. **运算符重载**：掌握运算符重载的设计原则
2. **类型转换**：理解隐式和显式类型转换
3. **函数对象**：掌握函数对象的使用技巧
4. **设计原则**：遵循重载运算符的最佳实践

这一章是 C++操作符定制化的核心，为创建用户友好的类接口打下基础。
