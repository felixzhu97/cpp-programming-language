/**
 * @file regex_demo.cpp
 * @brief 正则表达式和专门库设施演示
 */

#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <random>
#include <chrono>

void demonstrate_regex() {
    std::cout << "\n=== 正则表达式演示 ===\n";
    
    std::string text = "Email: user@example.com, Phone: 123-456-7890";
    
    // 匹配邮箱
    std::regex email_pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    std::smatch email_match;
    
    if (std::regex_search(text, email_match, email_pattern)) {
        std::cout << "找到邮箱: " << email_match[0] << "\n";
    }
    
    // 匹配电话
    std::regex phone_pattern(R"(\d{3}-\d{3}-\d{4})");
    std::smatch phone_match;
    
    if (std::regex_search(text, phone_match, phone_pattern)) {
        std::cout << "找到电话: " << phone_match[0] << "\n";
    }
}

void demonstrate_random() {
    std::cout << "\n=== 随机数生成器演示 ===\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    std::cout << "随机数: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << dis(gen) << " ";
    }
    std::cout << "\n";
}

void demonstrate_chrono() {
    std::cout << "\n=== 时间库演示 ===\n";
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // 模拟一些工作
    int sum = 0;
    for (int i = 0; i < 1000000; ++i) {
        sum += i;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "计算耗时: " << duration.count() << " 微秒\n";
    std::cout << "计算结果: " << sum << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 17: 专门库设施演示\n";
    std::cout << "=================================\n";
    
    demonstrate_regex();
    demonstrate_random();
    demonstrate_chrono();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 