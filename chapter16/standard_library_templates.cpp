/**
 * @file standard_library_templates.cpp
 * @brief 标准库模板演示 - STL容器、算法、迭代器模板
 */

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>

void demonstrate_container_templates() {
    std::cout << "\n=== 容器模板演示 ===\n";
    
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::map<std::string, int> m{{"one", 1}, {"two", 2}};
    
    std::cout << "vector 大小: " << vec.size() << "\n";
    std::cout << "map 大小: " << m.size() << "\n";
    
    // 迭代器模板
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

void demonstrate_algorithm_templates() {
    std::cout << "\n=== 算法模板演示 ===\n";
    
    std::vector<int> vec{5, 2, 8, 1, 9};
    
    std::sort(vec.begin(), vec.end());
    std::cout << "排序后: ";
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
    
    auto it = std::find(vec.begin(), vec.end(), 8);
    if (it != vec.end()) {
        std::cout << "找到元素: " << *it << "\n";
    }
}

void demonstrate_smart_pointers() {
    std::cout << "\n=== 智能指针模板演示 ===\n";
    
    auto ptr = std::make_unique<int>(42);
    std::cout << "unique_ptr 值: " << *ptr << "\n";
    
    auto shared1 = std::make_shared<std::string>("Hello");
    auto shared2 = shared1;
    std::cout << "shared_ptr 引用计数: " << shared1.use_count() << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 16: 标准库模板演示\n";
    std::cout << "=================================\n";
    
    demonstrate_container_templates();
    demonstrate_algorithm_templates();
    demonstrate_smart_pointers();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 