/**
 * @file map_containers.cpp
 * @brief map 和 multimap 容器演示 - 键值对容器的使用
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

void demonstrate_map_basics() {
    std::cout << "\n=== map 基本操作 ===\n";
    
    // 1. 创建和初始化
    std::map<std::string, int> word_count;
    word_count["apple"] = 5;
    word_count["banana"] = 3;
    word_count["cherry"] = 8;
    
    std::cout << "初始数据:\n";
    for (const auto& pair : word_count) {
        std::cout << "  " << pair.first << ": " << pair.second << "\n";
    }
    
    // 2. 插入操作
    word_count.insert({"date", 2});
    word_count.insert(std::make_pair("elderberry", 6));
    
    // 3. 查找操作
    auto it = word_count.find("banana");
    if (it != word_count.end()) {
        std::cout << "找到 banana: " << it->second << "\n";
    }
    
    // 4. 下标操作
    std::cout << "apple 的数量: " << word_count["apple"] << "\n";
    word_count["fig"] = 4; // 如果不存在会创建
    
    // 5. 统计和删除
    std::cout << "容器大小: " << word_count.size() << "\n";
    word_count.erase("banana");
    std::cout << "删除 banana 后大小: " << word_count.size() << "\n";
    
    std::cout << "最终数据:\n";
    for (const auto& pair : word_count) {
        std::cout << "  " << pair.first << ": " << pair.second << "\n";
    }
}

void demonstrate_multimap() {
    std::cout << "\n=== multimap 演示 ===\n";
    
    // multimap 允许重复键
    std::multimap<std::string, std::string> authors_books;
    
    authors_books.insert({"张三", "C++编程"});
    authors_books.insert({"张三", "Java入门"});
    authors_books.insert({"李四", "Python实战"});
    authors_books.insert({"张三", "算法导论"});
    authors_books.insert({"李四", "机器学习"});
    
    std::cout << "作者-书籍关系:\n";
    for (const auto& pair : authors_books) {
        std::cout << "  " << pair.first << " -> " << pair.second << "\n";
    }
    
    // 查找特定作者的所有书籍
    std::cout << "\n张三的所有书籍:\n";
    auto range = authors_books.equal_range("张三");
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << "  " << it->second << "\n";
    }
    
    // 统计每个作者的书籍数量
    std::cout << "\n各作者书籍数量:\n";
    std::map<std::string, int> author_count;
    for (const auto& pair : authors_books) {
        author_count[pair.first]++;
    }
    for (const auto& pair : author_count) {
        std::cout << "  " << pair.first << ": " << pair.second << " 本\n";
    }
}

void demonstrate_practical_applications() {
    std::cout << "\n=== 实际应用场景 ===\n";
    
    // 1. 学生成绩管理
    std::cout << "\n1. 学生成绩管理:\n";
    std::map<std::string, std::vector<double>> student_scores;
    
    student_scores["Alice"] = {85.5, 92.0, 78.5};
    student_scores["Bob"] = {76.0, 88.5, 91.0};
    student_scores["Charlie"] = {92.5, 85.0, 89.5};
    
    // 计算平均分
    for (const auto& student : student_scores) {
        double sum = 0;
        for (double score : student.second) {
            sum += score;
        }
        double average = sum / student.second.size();
        std::cout << "  " << student.first << " 平均分: " << average << "\n";
    }
    
    // 2. 单词频率统计
    std::cout << "\n2. 单词频率统计:\n";
    std::string text = "hello world hello cpp world programming cpp";
    std::map<std::string, int> word_freq;
    
    // 简单的单词分割（实际应用中会更复杂）
    std::string word;
    for (char c : text) {
        if (c == ' ') {
            if (!word.empty()) {
                word_freq[word]++;
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        word_freq[word]++;
    }
    
    std::cout << "  单词频率:\n";
    for (const auto& pair : word_freq) {
        std::cout << "    " << pair.first << ": " << pair.second << "\n";
    }
    
    // 3. 缓存系统模拟
    std::cout << "\n3. 简单缓存系统:\n";
    std::map<std::string, std::string> cache;
    
    auto get_from_cache = [&](const std::string& key) -> std::string {
        auto it = cache.find(key);
        if (it != cache.end()) {
            std::cout << "    缓存命中: " << key << " -> " << it->second << "\n";
            return it->second;
        } else {
            std::cout << "    缓存未命中: " << key << "\n";
            return "";
        }
    };
    
    auto put_to_cache = [&](const std::string& key, const std::string& value) {
        cache[key] = value;
        std::cout << "    缓存存储: " << key << " -> " << value << "\n";
    };
    
    put_to_cache("user:1001", "Alice");
    put_to_cache("user:1002", "Bob");
    
    get_from_cache("user:1001");
    get_from_cache("user:1003");
    get_from_cache("user:1002");
}

int main() {
    std::cout << "C++ Primer Chapter 11: map 和 multimap 容器演示\n";
    std::cout << "============================================\n";
    
    try {
        demonstrate_map_basics();
        demonstrate_multimap();
        demonstrate_practical_applications();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 