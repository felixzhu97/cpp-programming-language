/**
 * @file copy_move_algorithms.cpp
 * @brief 拷贝和移动算法演示 - copy、move、reverse、rotate、unique 等算法
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iterator>

void demonstrate_copy_algorithms() {
    std::cout << "\n=== 拷贝算法 ===\n";
    
    std::vector<int> source{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "源容器: ";
    for (auto x : source) std::cout << x << " ";
    std::cout << "\n";
    
    // 1. copy
    std::vector<int> dest1(source.size());
    std::copy(source.begin(), source.end(), dest1.begin());
    std::cout << "copy(): ";
    for (auto x : dest1) std::cout << x << " ";
    std::cout << "\n";
    
    // 2. copy_if
    std::vector<int> dest2;
    std::copy_if(source.begin(), source.end(), std::back_inserter(dest2),
                [](int x) { return x % 2 == 0; });
    std::cout << "copy_if(偶数): ";
    for (auto x : dest2) std::cout << x << " ";
    std::cout << "\n";
    
    // 3. copy_n
    std::vector<int> dest3(5);
    std::copy_n(source.begin(), 5, dest3.begin());
    std::cout << "copy_n(前5个): ";
    for (auto x : dest3) std::cout << x << " ";
    std::cout << "\n";
    
    // 4. copy_backward
    std::vector<int> dest4(source.size());
    std::copy_backward(source.begin(), source.end(), dest4.end());
    std::cout << "copy_backward(): ";
    for (auto x : dest4) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_move_algorithms() {
    std::cout << "\n=== 移动算法 ===\n";
    
    std::vector<std::string> strings{"apple", "banana", "cherry", "date"};
    std::cout << "原始字符串: ";
    for (const auto& s : strings) std::cout << s << " ";
    std::cout << "\n";
    
    std::vector<std::string> moved_strings(strings.size());
    std::move(strings.begin(), strings.end(), moved_strings.begin());
    
    std::cout << "移动后源容器: ";
    for (const auto& s : strings) std::cout << "\"" << s << "\" ";
    std::cout << "\n";
    
    std::cout << "移动后目标容器: ";
    for (const auto& s : moved_strings) std::cout << s << " ";
    std::cout << "\n";
}

void demonstrate_reverse_algorithms() {
    std::cout << "\n=== 反转算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5};
    std::cout << "原始序列: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 1. reverse - 就地反转
    std::reverse(numbers.begin(), numbers.end());
    std::cout << "reverse(): ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 2. reverse_copy - 拷贝并反转
    std::vector<int> original{1, 2, 3, 4, 5};
    std::vector<int> reversed(original.size());
    std::reverse_copy(original.begin(), original.end(), reversed.begin());
    
    std::cout << "原始: ";
    for (auto x : original) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "reverse_copy(): ";
    for (auto x : reversed) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_rotate_algorithms() {
    std::cout << "\n=== 旋转算法 ===\n";
    
    std::vector<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};
    std::cout << "原始序列: ";
    for (auto c : letters) std::cout << c << " ";
    std::cout << "\n";
    
    // 1. rotate - 就地旋转
    auto mid = letters.begin() + 2; // 以'c'为旋转点
    std::rotate(letters.begin(), mid, letters.end());
    std::cout << "rotate(mid=c): ";
    for (auto c : letters) std::cout << c << " ";
    std::cout << "\n";
    
    // 2. rotate_copy - 拷贝并旋转
    std::vector<char> original2{'a', 'b', 'c', 'd', 'e', 'f'};
    std::vector<char> rotated(original2.size());
    std::rotate_copy(original2.begin(), original2.begin() + 3, 
                    original2.end(), rotated.begin());
    
    std::cout << "原始: ";
    for (auto c : original2) std::cout << c << " ";
    std::cout << "\n";
    std::cout << "rotate_copy(mid=d): ";
    for (auto c : rotated) std::cout << c << " ";
    std::cout << "\n";
}

void demonstrate_unique_algorithms() {
    std::cout << "\n=== 去重算法 ===\n";
    
    std::vector<int> with_duplicates{1, 1, 2, 2, 2, 3, 4, 4, 5};
    std::cout << "原始序列: ";
    for (auto x : with_duplicates) std::cout << x << " ";
    std::cout << "\n";
    
    // 1. unique - 就地去重（需要先排序）
    auto unique_end = std::unique(with_duplicates.begin(), with_duplicates.end());
    with_duplicates.erase(unique_end, with_duplicates.end());
    std::cout << "unique(): ";
    for (auto x : with_duplicates) std::cout << x << " ";
    std::cout << "\n";
    
    // 2. unique_copy - 拷贝去重
    std::vector<int> original3{1, 1, 2, 2, 2, 3, 4, 4, 5};
    std::vector<int> unique_result;
    std::unique_copy(original3.begin(), original3.end(), 
                    std::back_inserter(unique_result));
    
    std::cout << "原始: ";
    for (auto x : original3) std::cout << x << " ";
    std::cout << "\n";
    std::cout << "unique_copy(): ";
    for (auto x : unique_result) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 10: 拷贝和移动算法演示\n";
    std::cout << "=====================================\n";
    
    try {
        demonstrate_copy_algorithms();
        demonstrate_move_algorithms();
        demonstrate_reverse_algorithms();
        demonstrate_rotate_algorithms();
        demonstrate_unique_algorithms();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 