# 第 11 章：关联容器

本章详细介绍 C++标准库中的关联容器，包括 map、set、multimap、multiset 以及 unordered 容器的使用。

## 本章内容

### 1. 关联容器概述 (`associative_overview.cpp`)

- 关联容器的特点
- 有序容器 vs 无序容器
- 容器的选择原则
- 性能比较

### 2. set 和 multiset (`set_containers.cpp`)

- set 的基本操作
- multiset 的使用
- 自定义比较函数
- 查找和范围操作

### 3. map 和 multimap (`map_containers.cpp`)

- map 的基本操作
- multimap 的使用
- 键值对的操作
- map 的下标操作

### 4. 无序容器 (`unordered_containers.cpp`)

- unordered_set
- unordered_map
- 哈希函数
- 桶的概念

### 5. 关联容器的算法 (`associative_algorithms.cpp`)

- 查找操作
- 插入和删除
- 范围操作
- 算法适配

### 6. 自定义键类型 (`custom_key_types.cpp`)

- 自定义比较函数
- 自定义哈希函数
- 键类型的要求
- 性能考虑

### 7. 容器的高级特性 (`advanced_features.cpp`)

- 分配器
- 异常安全
- 移动语义
- 原位构造

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter11 associative_overview
./compile_and_run.sh chapter11 set_containers
./compile_and_run.sh chapter11 map_containers
./compile_and_run.sh chapter11 unordered_containers
./compile_and_run.sh chapter11 associative_algorithms
./compile_and_run.sh chapter11 custom_key_types
./compile_and_run.sh chapter11 advanced_features
```

## 学习要点

1. **容器选择**：理解关联容器的适用场景
2. **查找效率**：掌握不同容器的查找性能
3. **自定义类型**：学会使用自定义键类型
4. **哈希技术**：理解哈希容器的工作原理
5. **性能优化**：了解关联容器的性能特点

这一章是 STL 关联容器编程的核心，为高效的键值数据处理打下基础。
