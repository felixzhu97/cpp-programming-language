/*
 * 第8章：IO库 - 流的继承体系
 * 展示iostream类层次、虚继承的使用、流的多态性、自定义流类
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

namespace stream_hierarchy_demo {

// 1. 演示流类层次结构
void demonstrateStreamHierarchy() {
    std::cout << "\n=== 流类层次结构演示 ===" << std::endl;
    
    std::cout << "\n1. 基础流类型信息：" << std::endl;
    
    // ios_base 是所有流的基类
    std::cout << "ios_base 类型ID: " << typeid(std::ios_base).name() << std::endl;
    
    // ios 继承自 ios_base
    std::cout << "ios 类型ID: " << typeid(std::ios).name() << std::endl;
    
    // 输入流
    std::cout << "istream 类型ID: " << typeid(std::istream).name() << std::endl;
    std::cout << "ifstream 类型ID: " << typeid(std::ifstream).name() << std::endl;
    std::cout << "istringstream 类型ID: " << typeid(std::istringstream).name() << std::endl;
    
    // 输出流
    std::cout << "ostream 类型ID: " << typeid(std::ostream).name() << std::endl;
    std::cout << "ofstream 类型ID: " << typeid(std::ofstream).name() << std::endl;
    std::cout << "ostringstream 类型ID: " << typeid(std::ostringstream).name() << std::endl;
    
    // 双向流
    std::cout << "iostream 类型ID: " << typeid(std::iostream).name() << std::endl;
    std::cout << "fstream 类型ID: " << typeid(std::fstream).name() << std::endl;
    std::cout << "stringstream 类型ID: " << typeid(std::stringstream).name() << std::endl;
    
    std::cout << "\n2. 标准流对象信息：" << std::endl;
    std::cout << "cout 类型: " << typeid(std::cout).name() << std::endl;
    std::cout << "cin 类型: " << typeid(std::cin).name() << std::endl;
    std::cout << "cerr 类型: " << typeid(std::cerr).name() << std::endl;
    std::cout << "clog 类型: " << typeid(std::clog).name() << std::endl;
}

// 2. 演示虚继承的使用
void demonstrateVirtualInheritance() {
    std::cout << "\n=== 虚继承演示 ===" << std::endl;
    
    std::cout << "\n1. iostream的虚继承结构：" << std::endl;
    std::cout << "iostream 同时继承自 istream 和 ostream" << std::endl;
    std::cout << "istream 和 ostream 都虚继承自 ios" << std::endl;
    std::cout << "这样避免了菱形继承问题" << std::endl;
    
    // 创建一个stringstream对象来演示
    std::stringstream ss;
    
    // 可以作为输入流使用
    std::istream* input = &ss;
    // 可以作为输出流使用
    std::ostream* output = &ss;
    // 可以作为双向流使用
    std::iostream* both = &ss;
    
    std::cout << "\n2. 多态性演示：" << std::endl;
    *output << "Hello, ";
    *output << "World!";
    
    std::string word;
    *input >> word;
    std::cout << "从输入流读取: " << word << std::endl;
    
    // 通过iostream接口使用
    both->seekg(0);  // 重置读位置
    std::string line;
    std::getline(*both, line);
    std::cout << "从双向流读取整行: " << line << std::endl;
    
    std::cout << "\n3. 同一对象的不同接口：" << std::endl;
    std::cout << "input指针地址: " << input << std::endl;
    std::cout << "output指针地址: " << output << std::endl;
    std::cout << "both指针地址: " << both << std::endl;
    std::cout << "ss对象地址: " << &ss << std::endl;
}

// 3. 流的多态性应用
void processStream(std::ostream& os, const std::string& data) {
    os << "处理数据: " << data << std::endl;
}

void readFromStream(std::istream& is) {
    std::string line;
    std::cout << "从流中读取的内容：" << std::endl;
    while (std::getline(is, line)) {
        std::cout << "  " << line << std::endl;
    }
}

void demonstratePolymorphism() {
    std::cout << "\n=== 流的多态性演示 ===" << std::endl;
    
    std::cout << "\n1. 统一的输出接口：" << std::endl;
    
    // 写入到标准输出
    processStream(std::cout, "标准输出");
    
    // 写入到字符串流
    std::ostringstream oss;
    processStream(oss, "字符串流");
    std::cout << "字符串流内容: " << oss.str();
    
    // 写入到文件流
    std::ofstream file("stream_test.txt");
    if (file) {
        processStream(file, "文件流");
        file.close();
        std::cout << "数据已写入文件" << std::endl;
    }
    
    std::cout << "\n2. 统一的输入接口：" << std::endl;
    
    // 从字符串流读取
    std::istringstream iss("第一行\n第二行\n第三行");
    std::cout << "从字符串流读取：" << std::endl;
    readFromStream(iss);
    
    // 从文件流读取
    std::ifstream infile("stream_test.txt");
    if (infile) {
        std::cout << "从文件流读取：" << std::endl;
        readFromStream(infile);
    }
}

// 4. 自定义流缓冲区
class UppercaseBuffer : public std::streambuf {
private:
    std::streambuf* original;
    
protected:
    int_type overflow(int_type ch) override {
        if (ch != traits_type::eof()) {
            char upper_ch = std::toupper(static_cast<char>(ch));
            return original->sputc(upper_ch);
        }
        return ch;
    }
    
public:
    UppercaseBuffer(std::streambuf* orig) : original(orig) {}
};

class NumberedLineBuffer : public std::streambuf {
private:
    std::streambuf* original;
    int line_number;
    bool at_line_start;
    
protected:
    int_type overflow(int_type ch) override {
        if (ch != traits_type::eof()) {
            if (at_line_start) {
                std::string line_prefix = "[" + std::to_string(line_number++) + "] ";
                for (char c : line_prefix) {
                    original->sputc(c);
                }
                at_line_start = false;
            }
            
            if (ch == '\n') {
                at_line_start = true;
            }
            
            return original->sputc(static_cast<char>(ch));
        }
        return ch;
    }
    
public:
    NumberedLineBuffer(std::streambuf* orig) 
        : original(orig), line_number(1), at_line_start(true) {}
};

// 5. 自定义流类
class UppercaseStream : public std::ostream {
private:
    UppercaseBuffer buffer;
    
public:
    UppercaseStream(std::ostream& os) 
        : std::ostream(&buffer), buffer(os.rdbuf()) {}
};

class NumberedLineStream : public std::ostream {
private:
    NumberedLineBuffer buffer;
    
public:
    NumberedLineStream(std::ostream& os) 
        : std::ostream(&buffer), buffer(os.rdbuf()) {}
};

class TeeStream : public std::ostream {
private:
    class TeeBuffer : public std::streambuf {
    private:
        std::streambuf* buf1;
        std::streambuf* buf2;
        
    protected:
        int_type overflow(int_type ch) override {
            if (ch != traits_type::eof()) {
                buf1->sputc(static_cast<char>(ch));
                buf2->sputc(static_cast<char>(ch));
            }
            return ch;
        }
        
    public:
        TeeBuffer(std::streambuf* b1, std::streambuf* b2) : buf1(b1), buf2(b2) {}
    };
    
    TeeBuffer buffer;
    
public:
    TeeStream(std::ostream& os1, std::ostream& os2) 
        : std::ostream(&buffer), buffer(os1.rdbuf(), os2.rdbuf()) {}
};

void demonstrateCustomStreams() {
    std::cout << "\n=== 自定义流类演示 ===" << std::endl;
    
    std::cout << "\n1. 大写转换流：" << std::endl;
    UppercaseStream upper(std::cout);
    upper << "hello world! this will be uppercase." << std::endl;
    
    std::cout << "\n2. 行号添加流：" << std::endl;
    NumberedLineStream numbered(std::cout);
    numbered << "第一行内容" << std::endl;
    numbered << "第二行内容" << std::endl;
    numbered << "第三行内容" << std::endl;
    
    std::cout << "\n3. 双重输出流（Tee流）：" << std::endl;
    std::ostringstream memory_stream;
    TeeStream tee(std::cout, memory_stream);
    
    tee << "这条消息会同时输出到控制台和内存流" << std::endl;
    tee << "第二条消息" << std::endl;
    
    std::cout << "\n内存流中的内容：" << std::endl;
    std::cout << memory_stream.str();
}

// 6. 流的状态和错误处理
void demonstrateStreamStates() {
    std::cout << "\n=== 流状态管理演示 ===" << std::endl;
    
    // 基类指针指向不同的流对象
    std::vector<std::unique_ptr<std::iostream>> streams;
    streams.push_back(std::make_unique<std::stringstream>("123 456 abc"));
    streams.push_back(std::make_unique<std::stringstream>("789 xyz 012"));
    
    for (size_t i = 0; i < streams.size(); ++i) {
        std::cout << "\n流 " << (i + 1) << " 的状态检查：" << std::endl;
        std::iostream& stream = *streams[i];
        
        int num1, num2;
        std::string str;
        
        // 尝试读取数据
        stream >> num1;
        std::cout << "读取第一个数字: " << num1 
                  << " (good: " << stream.good() << ")" << std::endl;
        
        stream >> num2;
        std::cout << "读取第二个数字: " << num2 
                  << " (good: " << stream.good() << ")" << std::endl;
        
        stream >> str;
        std::cout << "读取字符串: " << str 
                  << " (good: " << stream.good() << ")" << std::endl;
        
        // 尝试读取更多数据
        int num3;
        stream >> num3;
        std::cout << "尝试读取第三个数字: " << num3 
                  << " (fail: " << stream.fail() 
                  << ", eof: " << stream.eof() << ")" << std::endl;
        
        // 重置流状态
        stream.clear();
        stream.seekg(0);
        std::cout << "重置后状态 (good: " << stream.good() << ")" << std::endl;
    }
}

// 7. 流的RAII管理
class StreamStateGuard {
private:
    std::ios& stream;
    std::ios::fmtflags flags;
    std::streamsize precision;
    char fill;
    
public:
    StreamStateGuard(std::ios& s) : stream(s) {
        flags = stream.flags();
        precision = stream.precision();
        fill = stream.fill();
    }
    
    ~StreamStateGuard() {
        stream.flags(flags);
        stream.precision(precision);
        stream.fill(fill);
    }
};

void demonstrateRAII() {
    std::cout << "\n=== 流的RAII管理演示 ===" << std::endl;
    
    double number = 3.14159265;
    
    std::cout << "\nRAII前格式: " << number << std::endl;
    
    {
        StreamStateGuard guard(std::cout);
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "RAII中格式: " << number << std::endl;
    }  // guard析构，自动恢复格式
    
    std::cout << "RAII后格式: " << number << std::endl;
}

void demonstrateStreamHierarchyComplete() {
    std::cout << "\n=== 流继承体系完整演示 ===" << std::endl;
    
    // 1. 流类层次结构
    demonstrateStreamHierarchy();
    
    // 2. 虚继承
    demonstrateVirtualInheritance();
    
    // 3. 多态性
    demonstratePolymorphism();
    
    // 4. 自定义流
    demonstrateCustomStreams();
    
    // 5. 流状态
    demonstrateStreamStates();
    
    // 6. RAII管理
    demonstrateRAII();
    
    std::cout << "\n=== 流继承体系演示完成 ===" << std::endl;
}

} // namespace stream_hierarchy_demo

int main() {
    stream_hierarchy_demo::demonstrateStreamHierarchyComplete();
    return 0;
} 