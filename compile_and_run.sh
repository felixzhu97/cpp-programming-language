#!/bin/bash

# C++ Programming Language Examples 编译运行脚本
# 使用方法: ./compile_and_run.sh <章节号> <示例名>
# 例如: ./compile_and_run.sh 01 hello_world

if [ $# -ne 2 ]; then
    echo "使用方法: $0 <章节号> <示例名>"
    echo "例如: $0 01 hello_world"
    echo "例如: $0 02 basic_types"
    echo "例如: $0 03 string_demo"
    exit 1
fi

CHAPTER="$1"
EXAMPLE="$2"

# 检查章节目录是否存在
CHAPTER_DIR="chapter$CHAPTER"
if [ ! -d "$CHAPTER_DIR" ]; then
    echo "错误: 章节目录 $CHAPTER_DIR 不存在"
    exit 1
fi

# 检查源文件是否存在
SOURCE_FILE="$CHAPTER_DIR/$EXAMPLE.cpp"
if [ ! -f "$SOURCE_FILE" ]; then
    echo "错误: 源文件 $SOURCE_FILE 不存在"
    exit 1
fi

# 编译
echo "正在编译 $SOURCE_FILE ..."
g++ -std=c++17 -I common "$SOURCE_FILE" -o "$EXAMPLE"

if [ $? -eq 0 ]; then
    echo "编译成功！正在运行..."
    echo "----------------------------------------"
    ./"$EXAMPLE"
    echo "----------------------------------------"
    echo "程序运行完成"
    
    # 清理可执行文件
    rm "$EXAMPLE"
else
    echo "编译失败！"
    exit 1
fi 