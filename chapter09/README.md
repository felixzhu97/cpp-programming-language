# 第 9 章：顺序容器

本章详细介绍 C++标准库中的顺序容器，包括 vector、list、deque、array、forward_list 等容器的使用。

## 本章内容

### 1. 容器概述 (`container_overview.cpp`)

- STL 容器的分类
- 容器的通用接口
- 容器的选择原则
- 容器的性能特性

### 2. vector 容器 (`vector_container.cpp`)

- vector 的基本操作
- 动态扩容机制
- 内存管理
- 迭代器失效问题
- 性能优化技巧

### 3. list 容器 (`list_container.cpp`)

- 双向链表的实现
- list 的基本操作
- list 的特有操作
- 与 vector 的比较
- 使用场景分析

### 4. deque 容器 (`deque_container.cpp`)

- 双端队列的实现
- deque 的基本操作
- deque 的内存模型
- 与 vector 和 list 的比较
- 适用场景

### 5. array 容器 (`array_container.cpp`)

- 固定大小数组
- array 的基本操作
- 与 C 数组的比较
- 编译时大小检查
- 模板特化

### 6. forward_list 容器 (`forward_list_container.cpp`)

- 单向链表的实现
- forward_list 的基本操作
- 内存效率
- 特殊的迭代器
- 使用限制

### 7. 容器适配器 (`container_adapters.cpp`)

- stack 适配器
- queue 适配器
- priority_queue 适配器
- 适配器的实现原理
- 自定义适配器

### 8. 容器的高级操作 (`advanced_operations.cpp`)

- 容器的比较
- 容器的交换
- 容器的分配器
- 容器的异常安全
- 移动语义的应用

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter09 container_overview
./compile_and_run.sh chapter09 vector_container
./compile_and_run.sh chapter09 list_container
./compile_and_run.sh chapter09 deque_container
./compile_and_run.sh chapter09 array_container
./compile_and_run.sh chapter09 forward_list_container
./compile_and_run.sh chapter09 container_adapters
./compile_and_run.sh chapter09 advanced_operations
```

## 学习要点

1. **容器选择**：根据需求选择合适的容器
2. **性能特性**：理解不同容器的性能特点
3. **内存管理**：掌握容器的内存管理机制
4. **迭代器**：理解迭代器与容器的关系
5. **异常安全**：了解容器操作的异常安全性

## 重点概念

- **顺序容器**：维护元素顺序的容器
- **迭代器**：访问容器元素的统一接口
- **分配器**：内存管理的抽象
- **容器适配器**：基于其他容器的接口适配
- **异常安全**：操作失败时的状态保证

## 常见错误

1. **迭代器失效**：容器修改后迭代器失效
2. **容器选择错误**：没有选择合适的容器
3. **性能问题**：不了解容器的性能特性
4. **内存泄露**：容器中存储指针时的内存管理
5. **异常处理**：容器操作的异常处理不当

## 最佳实践

1. 优先使用 vector，除非有特殊需求
2. 预先分配足够的容器空间
3. 使用合适的插入和删除操作
4. 注意迭代器的生命周期
5. 使用移动语义优化性能
6. 合理使用容器的特有操作

这一章是 STL 容器编程的基础，为高效的数据结构使用打下基础。
