/**
 * @file thread_demo.cpp
 * @brief 多线程和特殊工具演示
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <atomic>

std::mutex cout_mutex;
std::atomic<int> counter{0};

void worker_function(int id) {
    for (int i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "线程 " << id << " 执行第 " << i + 1 << " 次\n";
        }
        
        counter++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void demonstrate_threads() {
    std::cout << "\n=== 多线程演示 ===\n";
    
    std::vector<std::thread> threads;
    
    // 创建多个线程
    for (int i = 0; i < 3; ++i) {
        threads.emplace_back(worker_function, i + 1);
    }
    
    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "计数器最终值: " << counter.load() << "\n";
}

void demonstrate_atomic() {
    std::cout << "\n=== 原子操作演示 ===\n";
    
    std::cout << "原子变量确保线程安全的读写操作\n";
    std::cout << "当前计数器值: " << counter.load() << "\n";
    
    counter.store(100);
    std::cout << "设置后计数器值: " << counter.load() << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 19: 特殊工具和技术演示\n";
    std::cout << "=====================================\n";
    
    demonstrate_threads();
    demonstrate_atomic();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 