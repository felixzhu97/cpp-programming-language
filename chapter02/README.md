# 第 2 章：变量和基本类型

本章深入介绍 C++的变量系统和基本数据类型，包括内置类型、类型转换、常量、指针、引用等核心概念。

## 本章内容

### 1. 基本类型详解 (`basic_types.cpp`)

- 整数类型：`int`, `short`, `long`, `long long`
- 浮点类型：`float`, `double`, `long double`
- 字符类型：`char`, `wchar_t`, `char16_t`, `char32_t`
- 布尔类型：`bool`
- 空类型：`void`
- 有符号与无符号类型
- 类型的大小和范围

### 2. 类型转换 (`type_conversion.cpp`)

- 隐式类型转换
- 显式类型转换（强制类型转换）
- C++风格类型转换：
  - `static_cast`
  - `dynamic_cast`
  - `const_cast`
  - `reinterpret_cast`
- 类型转换的安全性

### 3. 常量详解 (`const_demo.cpp`)

- `const` 限定符
- 常量指针和指针常量
- 常量引用
- 常量表达式 `constexpr`
- 顶层 const 和底层 const
- 常量的初始化

### 4. 指针和引用 (`pointers_references.cpp`)

- 指针的定义和使用
- 指针运算
- 空指针 `nullptr`
- 指针数组和数组指针
- 二级指针
- 引用的定义和使用
- 引用与指针的区别

### 5. 复合类型 (`compound_types.cpp`)

- 数组类型
- 结构体 `struct`
- 枚举类型 `enum`
- 联合体 `union`
- 类类型简介

### 6. 类型推断 (`auto_decltype.cpp`)

- `auto` 关键字
- `decltype` 类型推断
- `auto` 与 `decltype` 的区别
- 返回类型推断
- 尾置返回类型

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter02 basic_types
./compile_and_run.sh chapter02 type_conversion
./compile_and_run.sh chapter02 const_demo
./compile_and_run.sh chapter02 pointers_references
./compile_and_run.sh chapter02 compound_types
./compile_and_run.sh chapter02 auto_decltype
```

## 学习要点

1. **类型系统**：理解 C++的类型系统，掌握基本类型的特点和使用场景。

2. **内存模型**：理解不同类型在内存中的存储方式和大小。

3. **类型转换**：掌握各种类型转换的使用场景和安全性考虑。

4. **常量语义**：理解 const 的作用和使用方式，掌握常量的正确使用。

5. **指针与引用**：理解指针和引用的概念、区别及使用场景。

6. **现代 C++特性**：掌握 auto 和 decltype 等 C++11 引入的类型推断特性。

## 重点概念

- **值类别**：左值、右值的概念
- **对象生存期**：自动对象、静态对象、动态对象
- **作用域**：块作用域、函数作用域、类作用域、命名空间作用域
- **链接性**：内部链接、外部链接、无链接
- **存储类别**：auto、register、static、extern、thread_local

## 常见错误

1. **未初始化变量**：使用未初始化的变量
2. **类型转换错误**：不安全的类型转换
3. **指针错误**：空指针解引用、野指针
4. **常量性错误**：试图修改常量
5. **引用错误**：未初始化的引用

## 最佳实践

1. 尽量使用初始化而非赋值
2. 优先使用 const 和 constexpr
3. 优先使用引用而非指针（在可能的情况下）
4. 使用 auto 简化类型声明
5. 避免不必要的类型转换
6. 使用 nullptr 而非 NULL

## 扩展练习

1. 实现一个简单的字符串类，理解指针和数组的关系
2. 编写程序测试不同类型的大小和对齐方式
3. 实现类型转换函数，理解转换的原理
4. 编写程序演示 const 的传递性
5. 实现简单的智能指针，理解指针的管理

这一章是 C++类型系统的基础，为后续章节的容器、函数、类等内容打下基础。
