# 第 15 章：面向对象程序设计

本章详细介绍 C++的面向对象编程，包括继承、多态、虚函数等核心概念。

## 本章内容

### 1. 继承基础 (`inheritance_basics.cpp`)

- 基类和派生类
- 访问控制
- 继承的类型
- 构造和析构顺序

### 2. 虚函数和多态 (`virtual_functions_polymorphism.cpp`)

- 虚函数机制
- 运行时多态
- 虚函数表
- 抽象基类

### 3. 继承中的拷贝控制 (`inheritance_copy_control.cpp`)

- 派生类的拷贝构造
- 派生类的赋值运算符
- 派生类的析构函数
- 虚析构函数

### 4. 多重继承 (`multiple_inheritance.cpp`)

- 多重继承基础
- 虚继承
- 菱形继承问题
- 多重继承的设计

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter15 inheritance_basics
./compile_and_run.sh chapter15 virtual_functions_polymorphism
./compile_and_run.sh chapter15 inheritance_copy_control
./compile_and_run.sh chapter15 multiple_inheritance
```

## 学习要点

1. **继承机制**：理解 C++的继承体系
2. **多态性**：掌握运行时多态的实现
3. **虚函数**：理解虚函数的工作原理
4. **设计原则**：掌握面向对象设计的原则

这一章是 C++面向对象编程的核心，为构建复杂的类层次结构打下基础。
