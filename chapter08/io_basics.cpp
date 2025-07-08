/*
 * 第8章：IO库 - IO基础
 * 展示IO库的层次结构、标准输入输出流、流状态管理、错误处理、缓冲机制
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

namespace io_basics_demo {

// 1. 流状态检查函数
void checkStreamState(std::ios& stream, const std::string& streamName) {
    std::cout << "\n" << streamName << " 流状态检查：" << std::endl;
    std::cout << "  good(): " << stream.good() << " (所有状态位都为false)" << std::endl;
    std::cout << "  eof():  " << stream.eof() << " (达到文件末尾)" << std::endl;
    std::cout << "  fail(): " << stream.fail() << " (下一次IO操作会失败)" << std::endl;
    std::cout << "  bad():  " << stream.bad() << " (流已损坏)" << std::endl;
    std::cout << "  rdstate(): " << stream.rdstate() << " (状态位)" << std::endl;
    
    if (stream.good()) {
        std::cout << "  --> 流状态正常" << std::endl;
    } else if (stream.eof()) {
        std::cout << "  --> 达到文件末尾" << std::endl;
    } else if (stream.fail()) {
        std::cout << "  --> IO操作失败" << std::endl;
    } else if (stream.bad()) {
        std::cout << "  --> 流严重错误" << std::endl;
    }
}

// 2. 演示标准输入输出流
void demonstrateStandardStreams() {
    std::cout << "\n=== 标准输入输出流演示 ===" << std::endl;
    
    // 标准输出流
    std::cout << "这是标准输出流 (cout)" << std::endl;
    std::cerr << "这是标准错误流 (cerr)" << std::endl;
    std::clog << "这是标准日志流 (clog)" << std::endl;
    
    // 输出流的层次关系
    std::cout << "\nIO流类型信息：" << std::endl;
    std::cout << "cout 类型: " << typeid(std::cout).name() << std::endl;
    std::cout << "cerr 类型: " << typeid(std::cerr).name() << std::endl;
    std::cout << "clog 类型: " << typeid(std::clog).name() << std::endl;
    
    // 检查流状态
    checkStreamState(std::cout, "cout");
    
    // 演示输入流（为了演示，使用字符串流模拟）
    std::cout << "\n输入流演示（模拟）：" << std::endl;
    std::istringstream input("123 456.78 hello");
    
    int intValue;
    double doubleValue;
    std::string stringValue;
    
    input >> intValue >> doubleValue >> stringValue;
    
    std::cout << "读取的整数: " << intValue << std::endl;
    std::cout << "读取的浮点数: " << doubleValue << std::endl;
    std::cout << "读取的字符串: " << stringValue << std::endl;
    
    checkStreamState(input, "input stringstream");
}

// 3. 演示流状态管理
void demonstrateStreamStates() {
    std::cout << "\n=== 流状态管理演示 ===" << std::endl;
    
    std::istringstream ss("123 abc 456");
    
    int value;
    
    // 第一次读取（成功）
    std::cout << "\n第一次读取整数：" << std::endl;
    ss >> value;
    std::cout << "读取到: " << value << std::endl;
    checkStreamState(ss, "ss");
    
    // 第二次读取（失败）
    std::cout << "\n第二次读取整数（会失败）：" << std::endl;
    ss >> value;
    std::cout << "读取到: " << value << std::endl;
    checkStreamState(ss, "ss");
    
    // 清除错误状态
    std::cout << "\n清除错误状态：" << std::endl;
    ss.clear();
    checkStreamState(ss, "ss");
    
    // 跳过错误数据
    std::string temp;
    ss >> temp;  // 读取 "abc"
    std::cout << "跳过的数据: " << temp << std::endl;
    
    // 再次读取（成功）
    std::cout << "\n再次读取整数：" << std::endl;
    ss >> value;
    std::cout << "读取到: " << value << std::endl;
    checkStreamState(ss, "ss");
    
    // 演示异常处理
    std::cout << "\n异常处理演示：" << std::endl;
    std::istringstream ss2("invalid");
    ss2.exceptions(std::ios::failbit);  // 设置异常标志
    
    try {
        int val;
        ss2 >> val;
    } catch (const std::ios::failure& e) {
        std::cout << "捕获IO异常: " << e.what() << std::endl;
    }
}

// 4. 演示缓冲机制
void demonstrateBuffering() {
    std::cout << "\n=== 缓冲机制演示 ===" << std::endl;
    
    // 输出缓冲
    std::cout << "\n输出缓冲演示：" << std::endl;
    std::cout << "这行不会立即显示（缓冲中）...";
    
    // 强制刷新缓冲区
    std::cout.flush();
    std::cout << " 现在显示！" << std::endl;
    
    // 使用 endl（包含换行和刷新）
    std::cout << "使用endl自动刷新" << std::endl;
    
    // 使用 ends（只刷新，不换行）
    std::cout << "使用ends刷新" << std::ends;
    std::cout << "（同一行）" << std::endl;
    
    // 缓冲区大小和状态
    std::cout << "\n缓冲区信息：" << std::endl;
    std::cout << "cout 缓冲区指针: " << std::cout.rdbuf() << std::endl;
    
    // 设置缓冲区模式
    std::cout << "\n设置无缓冲模式：" << std::endl;
    std::cout.setf(std::ios::unitbuf);  // 设置单位缓冲（每次操作后刷新）
    std::cout << "现在每次输出都会立即刷新";
    std::cout << "（看不出差别，但确实立即刷新了）" << std::endl;
    
    // 恢复默认缓冲
    std::cout.unsetf(std::ios::unitbuf);
    
    // 文件缓冲演示
    std::cout << "\n文件缓冲演示：" << std::endl;
    std::ofstream file("buffer_demo.txt");
    if (file) {
        file << "第一行数据" << std::endl;
        file << "第二行数据（可能在缓冲区中）" << std::endl;
        
        // 手动刷新到文件
        file.flush();
        std::cout << "数据已刷新到文件" << std::endl;
        
        file << "第三行数据" << std::endl;
        // 文件关闭时自动刷新
        file.close();
        std::cout << "文件关闭，所有数据已写入" << std::endl;
    }
}

// 5. 演示错误处理
void demonstrateErrorHandling() {
    std::cout << "\n=== 错误处理演示 ===" << std::endl;
    
    // 文件打开错误
    std::cout << "\n文件打开错误处理：" << std::endl;
    std::ifstream file("nonexistent_file.txt");
    
    if (!file) {
        std::cout << "文件打开失败！" << std::endl;
        checkStreamState(file, "file");
    }
    
    if (file.fail()) {
        std::cout << "检测到文件流错误" << std::endl;
    }
    
    // 输入格式错误
    std::cout << "\n输入格式错误处理：" << std::endl;
    std::istringstream input("abc123def");
    int number;
    
    std::cout << "尝试从 'abc123def' 读取整数：" << std::endl;
    input >> number;
    
    if (input.fail()) {
        std::cout << "读取失败！" << std::endl;
        checkStreamState(input, "input");
        
        // 清除错误并重置流
        input.clear();
        input.seekg(0);  // 回到开始位置
        
        // 跳过非数字字符
        char ch;
        while (input >> ch && !std::isdigit(ch)) {
            std::cout << "跳过字符: " << ch << std::endl;
        }
        
        if (std::isdigit(ch)) {
            input.putback(ch);  // 放回第一个数字字符
            input >> number;
            if (input.good()) {
                std::cout << "成功读取数字: " << number << std::endl;
            }
        }
    }
    
    // 异常处理方式
    std::cout << "\n异常处理方式：" << std::endl;
    std::istringstream input2("xyz");
    input2.exceptions(std::ios::failbit | std::ios::badbit);
    
    try {
        int val;
        input2 >> val;
    } catch (const std::ios::failure& e) {
        std::cout << "捕获异常: " << e.what() << std::endl;
    }
}

// 6. 演示流的绑定
void demonstrateStreamTying() {
    std::cout << "\n=== 流的绑定演示 ===" << std::endl;
    
    // cout 和 cin 的绑定
    std::cout << "\ncout和cin的绑定：" << std::endl;
    std::ostream* tied = std::cin.tie();
    
    if (tied == &std::cout) {
        std::cout << "cin绑定到cout（默认情况）" << std::endl;
    }
    
    std::cout << "绑定的作用：确保在输入前刷新输出" << std::endl;
    
    // 模拟解绑
    std::cout << "\n解绑演示（仅示例，不实际解绑）：" << std::endl;
    std::cout << "如果解绑，提示信息可能不会立即显示" << std::endl;
    
    // 创建文件流并绑定
    std::cout << "\n自定义流绑定：" << std::endl;
    std::ofstream outfile("tied_output.txt");
    std::ifstream infile("buffer_demo.txt");  // 使用之前创建的文件
    
    if (infile && outfile) {
        // 将输入流绑定到输出流
        infile.tie(&outfile);
        std::cout << "输入流已绑定到输出流" << std::endl;
        
        std::string line;
        while (std::getline(infile, line)) {
            outfile << "复制: " << line << std::endl;
            // 由于绑定，输出会在下次读取前刷新
        }
        
        std::cout << "文件复制完成" << std::endl;
    }
}

// 7. 演示流的同步
void demonstrateStreamSync() {
    std::cout << "\n=== 流同步演示 ===" << std::endl;
    
    // C和C++流的同步
    std::cout << "\nC和C++流同步：" << std::endl;
    std::cout << "默认情况下，C++流与C流同步" << std::endl;
    
    // 检查同步状态
    bool synced = std::ios::sync_with_stdio();
    std::cout << "当前同步状态: " << (synced ? "开启" : "关闭") << std::endl;
    
    std::cout << "\n混合使用C和C++输出：" << std::endl;
    std::cout << "C++输出: Hello ";
    printf("C输出: World ");
    std::cout << "C++输出: !" << std::endl;
    
    // 注意：在实际应用中取消同步可以提高性能
    // 但这里只是演示，不实际取消同步
    std::cout << "\n注意：取消同步可以提高性能，但不能混用C和C++IO" << std::endl;
}

void demonstrateIOBasics() {
    std::cout << "\n=== IO库基础演示 ===" << std::endl;
    
    // 1. 标准输入输出流
    demonstrateStandardStreams();
    
    // 2. 流状态管理
    demonstrateStreamStates();
    
    // 3. 缓冲机制
    demonstrateBuffering();
    
    // 4. 错误处理
    demonstrateErrorHandling();
    
    // 5. 流的绑定
    demonstrateStreamTying();
    
    // 6. 流的同步
    demonstrateStreamSync();
    
    std::cout << "\n=== IO基础演示完成 ===" << std::endl;
}

} // namespace io_basics_demo

int main() {
    io_basics_demo::demonstrateIOBasics();
    return 0;
} 