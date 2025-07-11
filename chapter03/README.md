# 第 3 章：字符串、向量和数组

本章介绍 C++中的复合数据类型，包括字符串、向量和数组的使用。这些是 C++程序中处理数据集合的重要工具。

## 本章内容

### 1. 字符串操作 (`string_demo.cpp`)

- `string` 类型的基本使用
- 字符串的创建和初始化
- 字符串的连接和拼接
- 字符串的查找和替换
- 字符串的比较和排序
- 字符串和数值的转换
- 字符串的截取和子串操作
- 字符串的遍历方式

### 2. 向量容器 (`vector_demo.cpp`)

- `vector` 容器的基本概念
- 向量的创建和初始化
- 向量的增删改查操作
- 向量的动态扩容机制
- 向量的遍历方式
- 向量的排序和查找
- 向量的容量管理
- 二维向量的使用

### 3. 数组操作 (`array_demo.cpp`)

- C 风格数组的使用
- 数组的声明和初始化
- 数组的访问和修改
- 数组作为函数参数
- C++11 `std::array` 容器
- 数组与指针的关系
- 字符数组和字符串

### 4. 迭代器详解 (`iterator_demo.cpp`)

- 迭代器的概念和作用
- 不同类型的迭代器
- 迭代器的使用方法
- 迭代器与算法的配合
- 迭代器的失效问题
- 反向迭代器
- 迭代器适配器

### 5. 多维数组 (`multidimensional_arrays.cpp`)

- 二维数组的使用
- 多维数组的声明和初始化
- 多维数组的遍历
- 动态多维数组
- 多维向量的使用
- 矩阵运算基础

### 6. 综合练习 (`string_vector_practice.cpp`)

- 文本处理程序
- 学生成绩管理系统
- 单词统计和分析
- 数据排序和查找
- 购物车系统
- 矩阵运算程序
- 文本解析器

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter03 string_demo
./compile_and_run.sh chapter03 vector_demo
./compile_and_run.sh chapter03 array_demo
./compile_and_run.sh chapter03 iterator_demo
./compile_and_run.sh chapter03 multidimensional_arrays
./compile_and_run.sh chapter03 string_vector_practice
```

## 学习要点

1. **字符串处理**：掌握 C++字符串类的使用，理解字符串的内存管理。

2. **向量容器**：理解向量的动态特性，掌握向量的基本操作。

3. **数组概念**：理解数组的内存布局，掌握数组的使用方法。

4. **迭代器模式**：理解迭代器的作用，掌握迭代器的使用技巧。

5. **容器选择**：学会根据需求选择合适的容器类型。

6. **算法应用**：掌握常用算法在容器上的应用。

## 重点概念

- **容器类型**：序列容器的特点和使用场景
- **内存管理**：动态内存分配和释放
- **迭代器类型**：输入、输出、前向、双向、随机访问迭代器
- **算法复杂度**：时间复杂度和空间复杂度
- **异常安全**：容器操作的异常安全性

## 常见错误

1. **越界访问**：数组或向量的下标越界
2. **迭代器失效**：在遍历过程中修改容器
3. **内存泄露**：动态数组的内存管理错误
4. **空容器操作**：对空容器进行不当操作
5. **字符串编码**：字符串编码问题

## 最佳实践

1. 优先使用`vector`而非原始数组
2. 使用范围 for 循环遍历容器
3. 使用`string`而非 C 风格字符串
4. 注意迭代器的有效性
5. 预先分配足够的容器空间
6. 使用`const`保护只读数据

## 性能考虑

1. **向量扩容**：理解向量的扩容机制，适当使用`reserve()`
2. **字符串连接**：大量字符串连接时的性能优化
3. **数组访问**：二维数组的行优先访问
4. **迭代器效率**：选择合适的迭代器类型
5. **内存局部性**：利用内存局部性提高性能

## 扩展练习

1. 实现一个简单的字符串类，包含基本操作
2. 编写文本文件处理程序，统计词频
3. 实现矩阵类，支持基本的矩阵运算
4. 编写一个简单的文本编辑器
5. 实现一个学生信息管理系统
6. 编写程序解析 CSV 文件

## 相关算法

- **排序算法**：sort、stable_sort、partial_sort
- **查找算法**：find、find_if、binary_search
- **修改算法**：copy、transform、replace
- **数值算法**：accumulate、inner_product
- **字符串算法**：字符串匹配、正则表达式

这一章是 C++容器和算法的基础，为后续的 STL 学习打下坚实基础。
