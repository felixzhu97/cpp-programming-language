/**
 * @file modifying_algorithms.cpp
 * @brief 修改算法演示 - transform、replace、fill、generate、partition 等
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>

void demonstrate_transform() {
    std::cout << "\n=== transform 算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5};
    std::cout << "原数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 每个元素乘以2
    std::vector<int> doubled(numbers.size());
    std::transform(numbers.begin(), numbers.end(), doubled.begin(),
                  [](int x) { return x * 2; });
    
    std::cout << "doubled: ";
    for (auto x : doubled) std::cout << x << " ";
    std::cout << "\n";
    
    // 字符串转大写
    std::vector<std::string> words{"hello", "world", "cpp"};
    std::transform(words.begin(), words.end(), words.begin(),
                  [](std::string s) {
                      std::transform(s.begin(), s.end(), s.begin(), ::toupper);
                      return s;
                  });
    
    std::cout << "大写: ";
    for (const auto& s : words) std::cout << s << " ";
    std::cout << "\n";
}

void demonstrate_replace() {
    std::cout << "\n=== replace 算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 2, 4, 2, 5};
    std::cout << "原数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 替换所有的2为99
    std::replace(numbers.begin(), numbers.end(), 2, 99);
    std::cout << "replace(2->99): ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // replace_if 示例
    std::vector<int> numbers2{1, 2, 3, 4, 5, 6, 7, 8};
    std::replace_if(numbers2.begin(), numbers2.end(),
                   [](int x) { return x % 2 == 0; }, 0);
    std::cout << "replace_if(偶数->0): ";
    for (auto x : numbers2) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_fill() {
    std::cout << "\n=== fill 算法 ===\n";
    
    std::vector<int> vec(10);
    std::fill(vec.begin(), vec.end(), 42);
    std::cout << "fill(42): ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";
    
    // fill_n
    std::vector<int> vec2(10, 0);
    std::fill_n(vec2.begin(), 5, 99);
    std::cout << "fill_n(前5个99): ";
    for (auto x : vec2) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_generate() {
    std::cout << "\n=== generate 算法 ===\n";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    std::vector<int> random_vec(10);
    std::generate(random_vec.begin(), random_vec.end(),
                 [&]() { return dis(gen); });
    
    std::cout << "generate(随机数): ";
    for (auto x : random_vec) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_partition() {
    std::cout << "\n=== partition 算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "原数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    auto partition_point = std::partition(numbers.begin(), numbers.end(),
                                         [](int x) { return x % 2 == 0; });
    
    std::cout << "partition(偶数): ";
    for (auto it = numbers.begin(); it != partition_point; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "| ";
    for (auto it = partition_point; it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 10: 修改算法演示\n";
    std::cout << "================================\n";
    
    try {
        demonstrate_transform();
        demonstrate_replace();
        demonstrate_fill();
        demonstrate_generate();
        demonstrate_partition();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 