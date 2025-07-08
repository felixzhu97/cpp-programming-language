/**
 * @file set_containers.cpp
 * @brief set 和 multiset 容器演示
 */

#include <iostream>
#include <set>
#include <string>

int main() {
    std::cout << "C++ Primer Chapter 11: set 和 multiset 容器演示\n";
    std::cout << "===========================================\n";
    
    // set 基本操作
    std::cout << "\n=== set 基本操作 ===\n";
    std::set<int> numbers{5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "set 中的元素 (自动排序): ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    // 插入和查找
    numbers.insert(10);
    auto it = numbers.find(5);
    if (it != numbers.end()) {
        std::cout << "找到元素: " << *it << "\n";
    }
    
    // multiset 允许重复元素
    std::cout << "\n=== multiset 演示 ===\n";
    std::multiset<std::string> words{"apple", "banana", "apple", "cherry", "banana"};
    
    std::cout << "multiset 中的元素: ";
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";
    
    std::cout << "apple 出现次数: " << words.count("apple") << "\n";
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 