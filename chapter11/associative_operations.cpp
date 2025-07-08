/**
 * @file associative_operations.cpp
 * @brief 关联容器操作演示 - 插入、删除、查找等操作
 */

#include <iostream>
#include <map>
#include <set>
#include <string>

int main() {
    std::cout << "C++ Primer Chapter 11: 关联容器操作演示\n";
    std::cout << "====================================\n";
    
    // 插入操作演示
    std::cout << "\n=== 插入操作 ===\n";
    std::map<std::string, int> grades;
    
    // 不同的插入方式
    grades.insert({"Alice", 85});
    grades.insert(std::make_pair("Bob", 92));
    grades["Charlie"] = 78;
    auto result = grades.insert({"Alice", 90}); // 重复键，插入失败
    
    std::cout << "插入 Alice(90) " << (result.second ? "成功" : "失败") << "\n";
    
    // 查找操作演示
    std::cout << "\n=== 查找操作 ===\n";
    auto it = grades.find("Bob");
    if (it != grades.end()) {
        std::cout << "Bob 的成绩: " << it->second << "\n";
    }
    
    // 范围查找
    std::cout << "\n=== 范围操作 ===\n";
    std::set<int> numbers{1, 3, 5, 7, 9, 11, 13, 15};
    
    auto lower = numbers.lower_bound(5);
    auto upper = numbers.upper_bound(10);
    
    std::cout << "范围 [5, 10] 中的元素: ";
    for (auto it = lower; it != upper; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // 删除操作
    std::cout << "\n=== 删除操作 ===\n";
    std::cout << "删除前大小: " << grades.size() << "\n";
    grades.erase("Bob");
    std::cout << "删除 Bob 后大小: " << grades.size() << "\n";
    
    std::cout << "\n最终成绩:\n";
    for (const auto& pair : grades) {
        std::cout << "  " << pair.first << ": " << pair.second << "\n";
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 