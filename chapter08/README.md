# 第 8 章：IO 库

本章详细介绍 C++的输入输出库，包括 iostream、文件 IO、字符串流、格式化输入输出等内容。

## 本章内容

### 1. IO 库基础 (`io_basics.cpp`)

- IO 库的层次结构
- 标准输入输出流
- 流的状态管理
- 错误处理
- 流的缓冲机制

### 2. 文件输入输出 (`file_io.cpp`)

- 文件流的基本操作
- 文件的打开和关闭
- 文件读写模式
- 二进制文件处理
- 文件位置指针

### 3. 字符串流 (`string_streams.cpp`)

- stringstream 的使用
- 字符串的格式化
- 字符串的解析
- 数据类型转换

### 4. 格式化输入输出 (`formatted_io.cpp`)

- 格式化控制
- 精度控制
- 宽度控制
- 对齐方式
- 数制转换

### 5. IO 操纵符 (`io_manipulators.cpp`)

- 内置操纵符
- 自定义操纵符
- 参数化操纵符
- 操纵符的实现原理

### 6. 流的继承体系 (`stream_hierarchy.cpp`)

- iostream 类层次
- 虚继承的使用
- 流的多态性
- 自定义流类

### 7. 高级 IO 特性 (`advanced_io.cpp`)

- 流的同步
- 流的绑定
- 流的重定向
- 内存映射文件
- 异步 IO

## 编译和运行

使用脚本运行：

```bash
./compile_and_run.sh chapter08 io_basics
./compile_and_run.sh chapter08 file_io
./compile_and_run.sh chapter08 string_streams
./compile_and_run.sh chapter08 formatted_io
./compile_and_run.sh chapter08 io_manipulators
./compile_and_run.sh chapter08 stream_hierarchy
./compile_and_run.sh chapter08 advanced_io
```

## 学习要点

1. **IO 流概念**：理解输入输出流的抽象概念
2. **文件处理**：掌握文件的读写操作
3. **格式化**：掌握数据的格式化输入输出
4. **错误处理**：学会处理 IO 操作中的错误
5. **性能优化**：了解 IO 操作的性能考虑

## 重点概念

- **流**：数据的抽象流动
- **缓冲区**：提高 IO 效率的机制
- **格式化**：数据的表示形式
- **状态标志**：流的状态管理
- **操纵符**：控制流行为的对象

## 常见错误

1. **文件打开失败**：未检查文件是否成功打开
2. **流状态错误**：未检查流的状态
3. **缓冲区问题**：缓冲区刷新时机错误
4. **格式化错误**：格式化参数不匹配
5. **资源泄露**：文件句柄未正确关闭

## 最佳实践

1. 总是检查 IO 操作的返回值
2. 使用 RAII 管理文件资源
3. 适当使用缓冲区
4. 选择合适的打开模式
5. 处理异常情况
6. 注意二进制和文本模式的区别

这一章是 C++输入输出编程的基础，为文件处理和数据交换打下基础。
