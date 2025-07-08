/**
 * @file numeric_algorithms.cpp
 * @brief 数值算法演示 - accumulate、inner_product、adjacent_difference 等
 */

#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <functional>

void demonstrate_accumulate() {
    std::cout << "\n=== accumulate 算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5};
    std::cout << "数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 求和
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
    std::cout << "sum: " << sum << "\n";
    
    // 求积
    int product = std::accumulate(numbers.begin(), numbers.end(), 1, std::multiplies<int>());
    std::cout << "product: " << product << "\n";
    
    // 字符串连接
    std::vector<std::string> words{"Hello", " ", "World", "!"};
    std::string sentence = std::accumulate(words.begin(), words.end(), std::string(""));
    std::cout << "连接字符串: \"" << sentence << "\"\n";
}

void demonstrate_inner_product() {
    std::cout << "\n=== inner_product 算法 ===\n";
    
    std::vector<int> vec1{1, 2, 3, 4};
    std::vector<int> vec2{5, 6, 7, 8};
    
    std::cout << "向量1: ";
    for (auto x : vec1) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "向量2: ";
    for (auto x : vec2) std::cout << x << " ";
    std::cout << "\n";
    
    int dot_product = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
    std::cout << "内积: " << dot_product << "\n";
}

void demonstrate_adjacent_difference() {
    std::cout << "\n=== adjacent_difference 算法 ===\n";
    
    std::vector<int> numbers{2, 4, 6, 8, 10};
    std::cout << "原数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    std::vector<int> differences(numbers.size());
    std::adjacent_difference(numbers.begin(), numbers.end(), differences.begin());
    
    std::cout << "相邻差值: ";
    for (auto x : differences) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_partial_sum() {
    std::cout << "\n=== partial_sum 算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5};
    std::cout << "原数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    std::vector<int> sums(numbers.size());
    std::partial_sum(numbers.begin(), numbers.end(), sums.begin());
    
    std::cout << "部分和: ";
    for (auto x : sums) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 10: 数值算法演示\n";
    std::cout << "================================\n";
    
    try {
        demonstrate_accumulate();
        demonstrate_inner_product();
        demonstrate_adjacent_difference();
        demonstrate_partial_sum();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 