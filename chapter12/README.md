# 第 12 章：动态内存

本章详细介绍 C++中的动态内存管理，包括 new/delete、智能指针、分配器等内容。

## 本章内容

### 1. 动态内存基础 (`dynamic_memory_basics.cpp`)

- new 和 delete 操作符
- 内存分配和释放
- 内存泄露问题
- 野指针问题

### 2. 智能指针 (`smart_pointers.cpp`)

- unique_ptr
- shared_ptr
- weak_ptr
- 智能指针的选择

### 3. 内存管理最佳实践 (`memory_best_practices.cpp`)

- RAII 原则
- 异常安全
- 内存池
- 自定义分配器

### 4. 高级内存技术 (`advanced_memory.cpp`)

- placement new
- 内存对齐
- 内存映射
- 垃圾回收

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter12 dynamic_memory_basics
./compile_and_run.sh chapter12 smart_pointers
./compile_and_run.sh chapter12 memory_best_practices
./compile_and_run.sh chapter12 advanced_memory
```

## 学习要点

1. **内存安全**：掌握安全的内存管理技术
2. **智能指针**：理解现代 C++的内存管理方式
3. **性能优化**：了解内存管理对性能的影响
4. **异常安全**：在异常情况下的内存管理

这一章是现代 C++内存管理的核心，为编写安全高效的程序打下基础。
