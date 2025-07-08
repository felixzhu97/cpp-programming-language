/*
 * 第8章：IO库 - 文件输入输出
 * 展示文件流的基本操作、文件读写模式、二进制文件处理、文件位置指针
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

namespace file_io_demo {

// 1. 基本文件读写操作
void demonstrateBasicFileIO() {
    std::cout << "\n=== 基本文件读写演示 ===" << std::endl;
    
    // 写入文件
    std::cout << "\n1. 写入文件：" << std::endl;
    std::ofstream outFile("example.txt");
    
    if (outFile.is_open()) {
        outFile << "Hello, File I/O!" << std::endl;
        outFile << "这是第二行" << std::endl;
        outFile << "数字: " << 42 << ", 浮点数: " << 3.14159 << std::endl;
        outFile.close();
        std::cout << "文件写入完成" << std::endl;
    } else {
        std::cout << "无法打开文件进行写入" << std::endl;
        return;
    }
    
    // 读取文件
    std::cout << "\n2. 读取文件：" << std::endl;
    std::ifstream inFile("example.txt");
    
    if (inFile.is_open()) {
        std::string line;
        int lineNum = 1;
        
        while (std::getline(inFile, line)) {
            std::cout << "第" << lineNum++ << "行: " << line << std::endl;
        }
        inFile.close();
    } else {
        std::cout << "无法打开文件进行读取" << std::endl;
    }
    
    // 使用RAII方式（推荐）
    std::cout << "\n3. RAII方式文件操作：" << std::endl;
    {
        std::ofstream file("raii_example.txt");
        file << "RAII确保文件自动关闭" << std::endl;
        // 作用域结束时自动关闭文件
    }
    std::cout << "RAII文件操作完成" << std::endl;
}

// 2. 文件打开模式演示
void demonstrateFileOpenModes() {
    std::cout << "\n=== 文件打开模式演示 ===" << std::endl;
    
    // 创建初始文件
    {
        std::ofstream file("modes_test.txt");
        file << "原始内容第一行" << std::endl;
        file << "原始内容第二行" << std::endl;
    }
    
    // 1. 追加模式 (app)
    std::cout << "\n1. 追加模式 (app)：" << std::endl;
    {
        std::ofstream file("modes_test.txt", std::ios::app);
        file << "追加的内容" << std::endl;
    }
    
    // 读取并显示
    {
        std::ifstream file("modes_test.txt");
        std::string line;
        std::cout << "追加后的文件内容：" << std::endl;
        while (std::getline(file, line)) {
            std::cout << "  " << line << std::endl;
        }
    }
    
    // 2. 截断模式 (trunc) - 默认行为
    std::cout << "\n2. 截断模式 (trunc)：" << std::endl;
    {
        std::ofstream file("modes_test.txt", std::ios::trunc);
        file << "新内容替换了所有原有内容" << std::endl;
    }
    
    // 读取并显示
    {
        std::ifstream file("modes_test.txt");
        std::string line;
        std::cout << "截断后的文件内容：" << std::endl;
        while (std::getline(file, line)) {
            std::cout << "  " << line << std::endl;
        }
    }
    
    // 3. 读写模式组合
    std::cout << "\n3. 读写模式组合：" << std::endl;
    {
        // 以读写模式打开，文件必须存在
        std::fstream file("modes_test.txt", std::ios::in | std::ios::out);
        if (file) {
            std::string content;
            std::getline(file, content);
            std::cout << "读取到: " << content << std::endl;
            
            // 移动到文件开头
            file.seekp(0);
            file << "修改后的内容";
            
            std::cout << "内容已修改" << std::endl;
        }
    }
    
    // 4. 创建并读写模式
    std::cout << "\n4. 创建并读写模式：" << std::endl;
    {
        std::fstream file("new_file.txt", std::ios::out | std::ios::in | std::ios::trunc);
        file << "新创建文件的内容" << std::endl;
        
        // 移动到开头进行读取
        file.seekg(0);
        std::string line;
        std::getline(file, line);
        std::cout << "从新文件读取: " << line << std::endl;
    }
}

// 3. 二进制文件操作
void demonstrateBinaryFileIO() {
    std::cout << "\n=== 二进制文件操作演示 ===" << std::endl;
    
    // 定义一个简单的结构体
    struct Person {
        char name[50];
        int age;
        double salary;
        
        Person() = default;
        Person(const char* n, int a, double s) : age(a), salary(s) {
            strncpy(name, n, sizeof(name) - 1);
            name[sizeof(name) - 1] = '\0';
        }
        
        void display() const {
            std::cout << "姓名: " << name << ", 年龄: " << age 
                      << ", 薪水: " << salary << std::endl;
        }
    };
    
    // 写入二进制数据
    std::cout << "\n1. 写入二进制数据：" << std::endl;
    {
        std::ofstream file("binary_data.bin", std::ios::binary);
        if (file) {
            Person people[] = {
                Person("张三", 25, 5000.50),
                Person("李四", 30, 6500.75),
                Person("王五", 28, 5800.00)
            };
            
            size_t count = sizeof(people) / sizeof(Person);
            
            // 写入记录数量
            file.write(reinterpret_cast<const char*>(&count), sizeof(count));
            
            // 写入人员数据
            for (const auto& person : people) {
                file.write(reinterpret_cast<const char*>(&person), sizeof(Person));
            }
            
            std::cout << "已写入 " << count << " 条记录到二进制文件" << std::endl;
        }
    }
    
    // 读取二进制数据
    std::cout << "\n2. 读取二进制数据：" << std::endl;
    {
        std::ifstream file("binary_data.bin", std::ios::binary);
        if (file) {
            size_t count;
            
            // 读取记录数量
            file.read(reinterpret_cast<char*>(&count), sizeof(count));
            std::cout << "文件中有 " << count << " 条记录：" << std::endl;
            
            // 读取人员数据
            for (size_t i = 0; i < count; ++i) {
                Person person;
                file.read(reinterpret_cast<char*>(&person), sizeof(Person));
                
                if (file) {
                    std::cout << "记录 " << (i + 1) << ": ";
                    person.display();
                }
            }
        }
    }
    
    // 随机访问二进制文件
    std::cout << "\n3. 随机访问二进制文件：" << std::endl;
    {
        std::fstream file("binary_data.bin", std::ios::binary | std::ios::in | std::ios::out);
        if (file) {
            // 跳过记录数量，读取第二个记录
            file.seekg(sizeof(size_t) + sizeof(Person));
            
            Person person;
            file.read(reinterpret_cast<char*>(&person), sizeof(Person));
            
            std::cout << "第二条记录: ";
            person.display();
            
            // 修改并写回
            person.salary = 7000.00;
            file.seekp(sizeof(size_t) + sizeof(Person));
            file.write(reinterpret_cast<const char*>(&person), sizeof(Person));
            
            std::cout << "第二条记录已更新" << std::endl;
        }
    }
}

// 4. 文件位置指针操作
void demonstrateFilePositioning() {
    std::cout << "\n=== 文件位置指针操作演示 ===" << std::endl;
    
    // 创建测试文件
    {
        std::ofstream file("position_test.txt");
        file << "0123456789ABCDEFGHIJ" << std::endl;
        file << "第二行内容" << std::endl;
        file << "第三行更多内容" << std::endl;
    }
    
    std::cout << "\n1. 获取文件大小：" << std::endl;
    {
        std::ifstream file("position_test.txt");
        if (file) {
            // 移动到文件末尾
            file.seekg(0, std::ios::end);
            std::streampos fileSize = file.tellg();
            std::cout << "文件大小: " << fileSize << " 字节" << std::endl;
            
            // 回到文件开头
            file.seekg(0, std::ios::beg);
        }
    }
    
    std::cout << "\n2. 相对位置移动：" << std::endl;
    {
        std::ifstream file("position_test.txt");
        if (file) {
            // 从当前位置向前移动5个字符
            file.seekg(5, std::ios::cur);
            char ch;
            file.get(ch);
            std::cout << "从位置5读取字符: " << ch << std::endl;
            
            // 从当前位置再向前移动3个字符
            file.seekg(3, std::ios::cur);
            file.get(ch);
            std::cout << "从位置9读取字符: " << ch << std::endl;
            
            // 显示当前位置
            std::cout << "当前位置: " << file.tellg() << std::endl;
        }
    }
    
    std::cout << "\n3. 绝对位置移动：" << std::endl;
    {
        std::ifstream file("position_test.txt");
        if (file) {
            // 移动到绝对位置10
            file.seekg(10);
            char buffer[6] = {0};
            file.read(buffer, 5);
            std::cout << "从位置10读取5个字符: " << buffer << std::endl;
            
            // 移动到文件末尾前10个字符
            file.seekg(-10, std::ios::end);
            std::string remaining;
            std::getline(file, remaining);
            std::cout << "文件末尾前的内容: " << remaining << std::endl;
        }
    }
    
    std::cout << "\n4. 输出流位置操作：" << std::endl;
    {
        std::fstream file("position_test.txt", std::ios::in | std::ios::out);
        if (file) {
            // 移动到第一行的第6个字符位置
            file.seekp(6);
            std::cout << "在位置6插入字符 'X'" << std::endl;
            file.put('X');
            
            // 读取修改后的内容
            file.seekg(0);
            std::string line;
            std::getline(file, line);
            std::cout << "修改后的第一行: " << line << std::endl;
        }
    }
}

// 5. 大文件处理
void demonstrateLargeFileHandling() {
    std::cout << "\n=== 大文件处理演示 ===" << std::endl;
    
    // 创建一个相对较大的文件用于演示
    std::cout << "\n1. 创建大文件：" << std::endl;
    const int lineCount = 1000;
    {
        std::ofstream file("large_file.txt");
        for (int i = 1; i <= lineCount; ++i) {
            file << "这是第 " << std::setfill('0') << std::setw(4) << i 
                 << " 行，包含一些测试数据 " << i * i << std::endl;
        }
        std::cout << "已创建包含 " << lineCount << " 行的大文件" << std::endl;
    }
    
    // 分块读取大文件
    std::cout << "\n2. 分块读取大文件：" << std::endl;
    {
        std::ifstream file("large_file.txt");
        if (file) {
            const size_t bufferSize = 1024;
            char buffer[bufferSize];
            size_t totalBytes = 0;
            int chunkCount = 0;
            
            while (file.read(buffer, bufferSize) || file.gcount() > 0) {
                size_t bytesRead = file.gcount();
                totalBytes += bytesRead;
                chunkCount++;
                
                // 只显示前几个块的信息
                if (chunkCount <= 3) {
                    std::cout << "读取块 " << chunkCount 
                              << ": " << bytesRead << " 字节" << std::endl;
                }
            }
            
            std::cout << "总共读取: " << totalBytes << " 字节，分 " 
                      << chunkCount << " 块" << std::endl;
        }
    }
    
    // 逐行处理大文件
    std::cout << "\n3. 逐行处理大文件：" << std::endl;
    {
        std::ifstream file("large_file.txt");
        std::string line;
        int lineNum = 0;
        int targetLines[] = {1, 100, 500, 999, 1000};
        int targetIndex = 0;
        
        while (std::getline(file, line) && targetIndex < 5) {
            lineNum++;
            if (lineNum == targetLines[targetIndex]) {
                std::cout << "第 " << lineNum << " 行: " 
                          << line.substr(0, 50) << "..." << std::endl;
                targetIndex++;
            }
        }
    }
}

// 6. 文件状态和错误处理
void demonstrateFileErrorHandling() {
    std::cout << "\n=== 文件错误处理演示 ===" << std::endl;
    
    // 1. 文件不存在的情况
    std::cout << "\n1. 处理不存在的文件：" << std::endl;
    {
        std::ifstream file("nonexistent.txt");
        if (!file) {
            std::cout << "文件打开失败" << std::endl;
            if (file.fail()) {
                std::cout << "  - 原因: 文件不存在或权限不足" << std::endl;
            }
        }
    }
    
    // 2. 权限问题（模拟）
    std::cout << "\n2. 文件状态检查：" << std::endl;
    {
        std::ifstream file("example.txt");
        if (file.is_open()) {
            std::cout << "文件成功打开" << std::endl;
            
            // 检查文件状态
            std::cout << "  - good(): " << file.good() << std::endl;
            std::cout << "  - eof(): " << file.eof() << std::endl;
            std::cout << "  - fail(): " << file.fail() << std::endl;
            std::cout << "  - bad(): " << file.bad() << std::endl;
            
            // 读取到文件末尾
            std::string content((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
            
            std::cout << "读取后的状态：" << std::endl;
            std::cout << "  - eof(): " << file.eof() << std::endl;
            std::cout << "  - good(): " << file.good() << std::endl;
        }
    }
    
    // 3. 异常处理
    std::cout << "\n3. 文件操作异常处理：" << std::endl;
    {
        std::ifstream file("example.txt");
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        
        try {
            std::string content;
            while (std::getline(file, content)) {
                // 处理内容（这里只是读取）
            }
            std::cout << "文件读取成功完成" << std::endl;
        } catch (const std::ios_base::failure& e) {
            std::cout << "文件操作异常: " << e.what() << std::endl;
        }
    }
}

void demonstrateFileIO() {
    std::cout << "\n=== 文件输入输出演示 ===" << std::endl;
    
    // 1. 基本文件读写
    demonstrateBasicFileIO();
    
    // 2. 文件打开模式
    demonstrateFileOpenModes();
    
    // 3. 二进制文件操作
    demonstrateBinaryFileIO();
    
    // 4. 文件位置指针
    demonstrateFilePositioning();
    
    // 5. 大文件处理
    demonstrateLargeFileHandling();
    
    // 6. 错误处理
    demonstrateFileErrorHandling();
    
    std::cout << "\n=== 文件IO演示完成 ===" << std::endl;
}

} // namespace file_io_demo

int main() {
    file_io_demo::demonstrateFileIO();
    return 0;
} 