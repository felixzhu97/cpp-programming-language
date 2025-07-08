/**
 * @file set_algorithms.cpp
 * @brief 集合算法演示 - set_union、set_intersection、set_difference 等
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>

int main() {
    std::cout << "C++ Primer Chapter 10: 集合算法演示\n";
    std::cout << "================================\n";
    
    // 需要有序序列
    std::vector<int> set1{1, 3, 5, 7, 9};
    std::vector<int> set2{2, 3, 6, 7, 10};
    
    std::cout << "集合1: ";
    for (auto x : set1) std::cout << x << " ";
    std::cout << "\n";
    
    std::cout << "集合2: ";
    for (auto x : set2) std::cout << x << " ";
    std::cout << "\n";
    
    // 并集
    std::vector<int> union_result;
    std::set_union(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   std::back_inserter(union_result));
    std::cout << "并集: ";
    for (auto x : union_result) std::cout << x << " ";
    std::cout << "\n";
    
    // 交集
    std::vector<int> intersection_result;
    std::set_intersection(set1.begin(), set1.end(),
                         set2.begin(), set2.end(),
                         std::back_inserter(intersection_result));
    std::cout << "交集: ";
    for (auto x : intersection_result) std::cout << x << " ";
    std::cout << "\n";
    
    // 差集
    std::vector<int> difference_result;
    std::set_difference(set1.begin(), set1.end(),
                       set2.begin(), set2.end(),
                       std::back_inserter(difference_result));
    std::cout << "差集(1-2): ";
    for (auto x : difference_result) std::cout << x << " ";
    std::cout << "\n";
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 