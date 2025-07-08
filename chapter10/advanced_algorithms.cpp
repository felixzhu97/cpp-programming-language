/**
 * @file advanced_algorithms.cpp
 * @brief 高级算法技巧演示 - 自定义算法、算法组合、性能优化
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <numeric>
// #include <execution>  // C++17 并行执行策略（如果支持）

// 自定义算法示例
template<typename Iterator, typename Predicate>
Iterator find_last_if(Iterator first, Iterator last, Predicate pred) {
    Iterator result = last;
    for (auto it = first; it != last; ++it) {
        if (pred(*it)) {
            result = it;
        }
    }
    return result;
}

void demonstrate_custom_algorithms() {
    std::cout << "\n=== 自定义算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 4, 3, 2, 1};
    std::cout << "数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    auto it = find_last_if(numbers.begin(), numbers.end(),
                          [](int x) { return x > 3; });
    if (it != numbers.end()) {
        std::cout << "最后一个>3的元素: " << *it 
                  << "，位置: " << std::distance(numbers.begin(), it) << "\n";
    }
}

void demonstrate_algorithm_composition() {
    std::cout << "\n=== 算法组合 ===\n";
    
    std::vector<std::string> words{
        "apple", "application", "apply", "banana", "band", "can", "candy"
    };
    
    std::cout << "原单词: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << "\n";
    
    // 1. 排序
    std::sort(words.begin(), words.end());
    
    // 2. 去重
    auto unique_end = std::unique(words.begin(), words.end());
    words.erase(unique_end, words.end());
    
    std::cout << "处理后: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << "\n";
}

void demonstrate_performance_optimization() {
    std::cout << "\n=== 性能优化技巧 ===\n";
    
    std::vector<int> large_vec(100000);
    std::iota(large_vec.begin(), large_vec.end(), 1);
    
    // 串行算法演示
    std::sort(large_vec.begin(), large_vec.end(), std::greater<int>());
    std::cout << "大向量排序完成\n";
    
    auto count = std::count_if(large_vec.begin(), large_vec.end(),
                              [](int x) { return x % 1000 == 0; });
    std::cout << "能被1000整除的数: " << count << "\n";
    
    // 算法组合优化示例
    std::vector<int> test_data{5, 2, 8, 1, 9, 3, 7, 4, 6, 2, 8, 1};
    
    // 低效方式：多次遍历
    std::sort(test_data.begin(), test_data.end());
    auto unique_end2 = std::unique(test_data.begin(), test_data.end());
    test_data.erase(unique_end2, test_data.end());
    
    std::cout << "优化后的去重排序结果: ";
    for (auto x : test_data) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 10: 高级算法技巧演示\n";
    std::cout << "====================================\n";
    
    try {
        demonstrate_custom_algorithms();
        demonstrate_algorithm_composition();
        demonstrate_performance_optimization();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 