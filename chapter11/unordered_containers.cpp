/**
 * @file unordered_containers.cpp
 * @brief 无序容器演示 - unordered_map 和 unordered_set
 */

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

int main() {
    std::cout << "C++ Primer Chapter 11: 无序容器演示\n";
    std::cout << "================================\n";
    
    // unordered_map 演示
    std::cout << "\n=== unordered_map 演示 ===\n";
    std::unordered_map<std::string, int> word_count;
    
    word_count["hello"] = 5;
    word_count["world"] = 3;
    word_count["cpp"] = 8;
    
    std::cout << "单词计数:\n";
    for (const auto& pair : word_count) {
        std::cout << "  " << pair.first << ": " << pair.second << "\n";
    }
    
    // unordered_set 演示
    std::cout << "\n=== unordered_set 演示 ===\n";
    std::unordered_set<int> unique_numbers{1, 2, 3, 2, 4, 3, 5};
    
    std::cout << "唯一数字: ";
    for (int n : unique_numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    // 哈希信息
    std::cout << "\n=== 哈希信息 ===\n";
    std::cout << "桶数量: " << word_count.bucket_count() << "\n";
    std::cout << "负载因子: " << word_count.load_factor() << "\n";
    std::cout << "最大负载因子: " << word_count.max_load_factor() << "\n";
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 