# 第 13 章：拷贝控制

本章详细介绍 C++中的拷贝控制，包括拷贝构造函数、拷贝赋值运算符、析构函数、移动语义等内容。

## 本章内容

### 1. 拷贝控制基础 (`copy_control_basics.cpp`)

- 拷贝构造函数
- 拷贝赋值运算符
- 析构函数
- 三五零法则

### 2. 移动语义 (`move_semantics.cpp`)

- 右值引用
- 移动构造函数
- 移动赋值运算符
- 完美转发

### 3. 拷贝控制最佳实践 (`copy_control_best_practices.cpp`)

- 异常安全
- 资源管理
- 性能优化
- 设计原则

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter13 copy_control_basics
./compile_and_run.sh chapter13 move_semantics
./compile_and_run.sh chapter13 copy_control_best_practices
```

## 学习要点

1. **拷贝语义**：理解深拷贝和浅拷贝
2. **移动语义**：掌握 C++11 的移动语义
3. **资源管理**：使用 RAII 管理资源
4. **性能优化**：通过移动语义提升性能

这一章是现代 C++对象语义的核心，为高效的对象管理打下基础。
