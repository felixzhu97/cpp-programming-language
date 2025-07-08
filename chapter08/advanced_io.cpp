/*
 * 第8章：IO库 - 高级IO特性
 * 展示流的同步、流的绑定、流的重定向、内存映射文件、异步IO等高级特性
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

namespace advanced_io_demo {

// 1. 流的同步演示
void demonstrateStreamSync() {
    std::cout << "\n=== 流同步演示 ===" << std::endl;
    
    std::cout << "\n1. C和C++流的同步：" << std::endl;
    
    // 检查当前同步状态
    bool is_synced = std::ios::sync_with_stdio();
    std::cout << "当前C++流与C流同步状态: " << (is_synced ? "开启" : "关闭") << std::endl;
    
    std::cout << "\n2. 混合使用C和C++IO（同步状态下）：" << std::endl;
    std::cout << "C++输出: Hello ";
    std::cout.flush();
    printf("C输出: World ");
    fflush(stdout);
    std::cout << "C++输出: !" << std::endl;
    
    std::cout << "\n3. 同步的性能影响：" << std::endl;
    std::cout << "- 同步状态下: C++流与C流协调工作，但性能较慢" << std::endl;
    std::cout << "- 非同步状态下: C++流性能更好，但不能与C流混用" << std::endl;
    
    // 演示性能差异（仅示例，不实际更改同步状态）
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ostringstream oss;
    for (int i = 0; i < 10000; ++i) {
        oss << "测试数据 " << i << std::endl;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "字符串流输出10000行用时: " << duration.count() << " 微秒" << std::endl;
    
    std::cout << "\n4. 同步控制建议：" << std::endl;
    std::cout << "- 纯C++程序: 可以关闭同步提高性能" << std::endl;
    std::cout << "- 混合程序: 保持同步确保正确性" << std::endl;
    std::cout << "- 关闭同步后不要使用C的stdio函数" << std::endl;
}

// 2. 流的绑定演示
void demonstrateStreamTying() {
    std::cout << "\n=== 流绑定演示 ===" << std::endl;
    
    std::cout << "\n1. 默认绑定关系：" << std::endl;
    std::ostream* cout_tie = std::cout.tie();
    std::ostream* cin_tie = std::cin.tie();
    std::ostream* cerr_tie = std::cerr.tie();
    std::ostream* clog_tie = std::clog.tie();
    
    std::cout << "cout绑定: " << (cout_tie ? "有绑定" : "无绑定") << std::endl;
    std::cout << "cin绑定: " << (cin_tie ? "绑定到cout" : "无绑定") << std::endl;
    std::cout << "cerr绑定: " << (cerr_tie ? "有绑定" : "无绑定") << std::endl;
    std::cout << "clog绑定: " << (clog_tie ? "有绑定" : "无绑定") << std::endl;
    
    std::cout << "\n2. 绑定的作用：" << std::endl;
    std::cout << "- 确保在输入前刷新输出缓冲区" << std::endl;
    std::cout << "- 保证提示信息能及时显示" << std::endl;
    
    // 创建自定义流并演示绑定
    std::cout << "\n3. 自定义流绑定：" << std::endl;
    std::ostringstream output_log;
    std::istringstream input_data("line1\nline2\nline3\n");
    
    // 将输入流绑定到输出流
    std::ostream* old_tie = input_data.tie(&output_log);
    
    std::cout << "原绑定: " << (old_tie ? "有" : "无") << std::endl;
    std::cout << "新绑定: " << (input_data.tie() ? "已绑定到output_log" : "无绑定") << std::endl;
    
    // 模拟读取过程中的自动刷新
    std::string line;
    while (std::getline(input_data, line)) {
        output_log << "处理: " << line << std::endl;
        // 由于绑定，output_log会在下次读取前自动刷新
    }
    
    std::cout << "处理日志内容：\n" << output_log.str();
    
    // 恢复原绑定
    input_data.tie(old_tie);
}

// 3. 流的重定向演示
class StreamRedirector {
private:
    std::ostream& stream;
    std::streambuf* original_buffer;
    std::streambuf* new_buffer;
    
public:
    StreamRedirector(std::ostream& s, std::streambuf* new_buf) 
        : stream(s), new_buffer(new_buf) {
        original_buffer = stream.rdbuf(new_buffer);
    }
    
    ~StreamRedirector() {
        stream.rdbuf(original_buffer);
    }
};

void demonstrateStreamRedirection() {
    std::cout << "\n=== 流重定向演示 ===" << std::endl;
    
    std::cout << "\n1. 重定向到字符串流：" << std::endl;
    std::ostringstream captured_output;
    
    std::cout << "重定向前的输出" << std::endl;
    
    {
        StreamRedirector redirector(std::cout, captured_output.rdbuf());
        std::cout << "这条消息被重定向到字符串流" << std::endl;
        std::cout << "第二条重定向消息" << std::endl;
    }  // 自动恢复重定向
    
    std::cout << "重定向后的输出" << std::endl;
    std::cout << "捕获的内容:\n" << captured_output.str();
    
    std::cout << "\n2. 重定向到文件：" << std::endl;
    
    // 创建文件流
    std::ofstream file_output("redirected_output.txt");
    if (file_output) {
        std::cout << "重定向到文件前" << std::endl;
        
        {
            StreamRedirector redirector(std::cout, file_output.rdbuf());
            std::cout << "这条消息被写入到文件" << std::endl;
            std::cout << "时间: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
        }
        
        std::cout << "重定向到文件后" << std::endl;
        file_output.close();
        
        // 读取文件内容验证
        std::ifstream file_input("redirected_output.txt");
        if (file_input) {
            std::cout << "文件内容验证:\n";
            std::string line;
            while (std::getline(file_input, line)) {
                std::cout << "  " << line << std::endl;
            }
        }
    }
    
    std::cout << "\n3. 双向重定向：" << std::endl;
    std::stringstream bidirectional;
    bidirectional << "预设数据行1\n预设数据行2\n";
    
    {
        // 同时重定向输入和输出
        StreamRedirector cout_redirector(std::cout, bidirectional.rdbuf());
        
        std::cout << "写入到字符串流的数据" << std::endl;
        
        // 这里如果要演示cin重定向需要更复杂的设置
        // 为简化演示，只展示概念
    }
    
    std::cout << "双向流最终内容:\n" << bidirectional.str();
}

// 4. 缓冲区管理
void demonstrateBufferManagement() {
    std::cout << "\n=== 缓冲区管理演示 ===" << std::endl;
    
    std::cout << "\n1. 缓冲区类型：" << std::endl;
    std::cout << "- 全缓冲: 缓冲区满或显式刷新时输出" << std::endl;
    std::cout << "- 行缓冲: 遇到换行符时输出" << std::endl;
    std::cout << "- 无缓冲: 立即输出" << std::endl;
    
    std::cout << "\n2. 手动缓冲区控制：" << std::endl;
    
    // 创建文件流演示缓冲控制
    std::ofstream file("buffer_test.txt");
    if (file) {
        std::cout << "写入数据到文件..." << std::endl;
        
        file << "第一行数据" << std::endl;
        std::cout << "第一行已写入（可能在缓冲区）" << std::endl;
        
        file << "第二行数据";  // 没有endl
        std::cout << "第二行已写入（肯定在缓冲区）" << std::endl;
        
        // 手动刷新
        file.flush();
        std::cout << "缓冲区已刷新到磁盘" << std::endl;
        
        file << std::endl;  // 添加换行并刷新
        std::cout << "换行已添加" << std::endl;
        
        file.close();
        std::cout << "文件已关闭（自动刷新）" << std::endl;
    }
    
    std::cout << "\n3. 缓冲区大小信息：" << std::endl;
    
    // 获取缓冲区信息（实现相关）
    std::cout << "标准输出缓冲区指针: " << std::cout.rdbuf() << std::endl;
    
    // 演示缓冲区同步
    std::cout << "\n4. 缓冲区同步：" << std::endl;
    std::cout << "无刷新输出..." << std::flush;
    std::cout << "已刷新!" << std::endl;
    
    std::cout << "使用endl刷新..." << std::endl;  // endl包含换行和刷新
    std::cout << "使用ends刷新..." << std::ends;   // ends只刷新，不换行
    std::cout << "（同一行）" << std::endl;
}

// 5. 异步IO模拟（简化版）
class AsyncFileWriter {
private:
    std::string filename;
    std::vector<std::string> buffer;
    mutable std::mutex buffer_mutex;
    std::thread writer_thread;
    std::atomic<bool> should_stop{false};
    
    void writerLoop() {
        std::ofstream file(filename);
        if (!file) return;
        
        while (!should_stop || !buffer.empty()) {
            std::vector<std::string> local_buffer;
            
            {
                std::lock_guard<std::mutex> lock(buffer_mutex);
                if (!buffer.empty()) {
                    local_buffer.swap(buffer);
                }
            }
            
            for (const auto& line : local_buffer) {
                file << line << std::endl;
            }
            
            if (!local_buffer.empty()) {
                file.flush();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
public:
    AsyncFileWriter(const std::string& fname) 
        : filename(fname), writer_thread(&AsyncFileWriter::writerLoop, this) {}
    
    ~AsyncFileWriter() {
        should_stop = true;
        if (writer_thread.joinable()) {
            writer_thread.join();
        }
    }
    
    void write(const std::string& data) {
        std::lock_guard<std::mutex> lock(buffer_mutex);
        buffer.push_back(data);
    }
    
    size_t getPendingCount() const {
        std::lock_guard<std::mutex> lock(buffer_mutex);
        return buffer.size();
    }
};

void demonstrateAsyncIO() {
    std::cout << "\n=== 异步IO演示 ===" << std::endl;
    
    std::cout << "\n1. 异步文件写入：" << std::endl;
    
    {
        AsyncFileWriter writer("async_output.txt");
        
        // 快速写入多条数据
        for (int i = 0; i < 10; ++i) {
            writer.write("异步数据 " + std::to_string(i));
            std::cout << "排队写入数据 " << i 
                      << ", 待处理: " << writer.getPendingCount() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
        
        std::cout << "等待异步写入完成..." << std::endl;
        
        // 等待队列清空
        while (writer.getPendingCount() > 0) {
            std::cout << "剩余待写入: " << writer.getPendingCount() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        
    }  // AsyncFileWriter析构，等待线程完成
    
    std::cout << "异步写入完成" << std::endl;
    
    // 验证写入结果
    std::ifstream file("async_output.txt");
    if (file) {
        std::cout << "\n异步写入结果验证：" << std::endl;
        std::string line;
        int count = 0;
        while (std::getline(file, line) && count < 5) {
            std::cout << "  " << line << std::endl;
            count++;
        }
        if (count == 5) {
            std::cout << "  ..." << std::endl;
        }
    }
}

// 6. 并发IO安全演示
void demonstrateConcurrentIO() {
    std::cout << "\n=== 并发IO安全演示 ===" << std::endl;
    
    std::cout << "\n1. 多线程写入同一流（不安全）：" << std::endl;
    std::ostringstream shared_stream;
    
    auto writer_func = [&shared_stream](int thread_id) {
        for (int i = 0; i < 5; ++i) {
            shared_stream << "线程" << thread_id << "-消息" << i << " ";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    };
    
    std::vector<std::thread> threads;
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(writer_func, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "不安全的并发输出结果:\n" << shared_stream.str() << std::endl;
    
    std::cout << "\n2. 线程安全的IO访问：" << std::endl;
    std::ostringstream safe_stream;
    std::mutex stream_mutex;
    
    auto safe_writer_func = [&safe_stream, &stream_mutex](int thread_id) {
        for (int i = 0; i < 5; ++i) {
            {
                std::lock_guard<std::mutex> lock(stream_mutex);
                safe_stream << "安全线程" << thread_id << "-消息" << i << " ";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    };
    
    threads.clear();
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(safe_writer_func, i);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "安全的并发输出结果:\n" << safe_stream.str() << std::endl;
}

// 7. 性能优化技巧
void demonstratePerformanceOptimization() {
    std::cout << "\n=== 性能优化演示 ===" << std::endl;
    
    std::cout << "\n1. 批量写入 vs 单次写入：" << std::endl;
    
    const int iterations = 10000;
    
    // 单次写入测试
    auto start = std::chrono::high_resolution_clock::now();
    {
        std::ofstream file("single_write_test.txt");
        for (int i = 0; i < iterations; ++i) {
            file << "数据 " << i << std::endl;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto single_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    // 批量写入测试
    start = std::chrono::high_resolution_clock::now();
    {
        std::ostringstream buffer;
        for (int i = 0; i < iterations; ++i) {
            buffer << "数据 " << i << std::endl;
        }
        
        std::ofstream file("batch_write_test.txt");
        file << buffer.str();
    }
    end = std::chrono::high_resolution_clock::now();
    auto batch_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "单次写入 " << iterations << " 行用时: " << single_duration.count() << " ms" << std::endl;
    std::cout << "批量写入 " << iterations << " 行用时: " << batch_duration.count() << " ms" << std::endl;
    std::cout << "性能提升: " << (double)single_duration.count() / batch_duration.count() << " 倍" << std::endl;
    
    std::cout << "\n2. 优化建议：" << std::endl;
    std::cout << "- 减少系统调用次数" << std::endl;
    std::cout << "- 使用适当的缓冲区大小" << std::endl;
    std::cout << "- 避免频繁的格式化操作" << std::endl;
    std::cout << "- 考虑使用内存映射文件" << std::endl;
    std::cout << "- 在适当时候关闭C++与C流的同步" << std::endl;
}

void demonstrateAdvancedIO() {
    std::cout << "\n=== 高级IO特性演示 ===" << std::endl;
    
    // 1. 流的同步
    demonstrateStreamSync();
    
    // 2. 流的绑定
    demonstrateStreamTying();
    
    // 3. 流的重定向
    demonstrateStreamRedirection();
    
    // 4. 缓冲区管理
    demonstrateBufferManagement();
    
    // 5. 异步IO
    demonstrateAsyncIO();
    
    // 6. 并发IO安全
    demonstrateConcurrentIO();
    
    // 7. 性能优化
    demonstratePerformanceOptimization();
    
    std::cout << "\n=== 高级IO特性演示完成 ===" << std::endl;
}

} // namespace advanced_io_demo

int main() {
    advanced_io_demo::demonstrateAdvancedIO();
    return 0;
} 