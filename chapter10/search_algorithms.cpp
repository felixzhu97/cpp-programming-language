/**
 * @file search_algorithms.cpp
 * @brief 查找算法演示 - find、search、binary_search、lower_bound 等算法
 * 
 * 查找算法是最常用的STL算法之一，包括线性查找和二分查找等。
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iterator>
#include <functional>

// 演示基本查找算法
void demonstrate_basic_find() {
    std::cout << "\n=== 基本查找算法 ===\n";
    
    std::vector<int> numbers{5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    std::cout << "测试数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 1. find - 查找特定值
    std::cout << "\n1. find() 算法：\n";
    
    auto it = std::find(numbers.begin(), numbers.end(), 7);
    if (it != numbers.end()) {
        std::cout << "   找到 7，位置: " << std::distance(numbers.begin(), it) << "\n";
    } else {
        std::cout << "   未找到 7\n";
    }
    
    it = std::find(numbers.begin(), numbers.end(), 10);
    if (it != numbers.end()) {
        std::cout << "   找到 10，位置: " << std::distance(numbers.begin(), it) << "\n";
    } else {
        std::cout << "   未找到 10\n";
    }
    
    // 2. find_if - 按条件查找
    std::cout << "\n2. find_if() 算法：\n";
    
    auto it_even = std::find_if(numbers.begin(), numbers.end(),
                               [](int x) { return x % 2 == 0; });
    if (it_even != numbers.end()) {
        std::cout << "   找到第一个偶数: " << *it_even 
                  << "，位置: " << std::distance(numbers.begin(), it_even) << "\n";
    }
    
    auto it_large = std::find_if(numbers.begin(), numbers.end(),
                                [](int x) { return x > 8; });
    if (it_large != numbers.end()) {
        std::cout << "   找到第一个>8的数: " << *it_large 
                  << "，位置: " << std::distance(numbers.begin(), it_large) << "\n";
    }
    
    // 3. find_if_not - 查找不满足条件的元素
    std::cout << "\n3. find_if_not() 算法：\n";
    
    std::vector<int> even_numbers{2, 4, 6, 8, 9, 10, 12};
    auto it_not_even = std::find_if_not(even_numbers.begin(), even_numbers.end(),
                                       [](int x) { return x % 2 == 0; });
    if (it_not_even != even_numbers.end()) {
        std::cout << "   找到第一个非偶数: " << *it_not_even 
                  << "，位置: " << std::distance(even_numbers.begin(), it_not_even) << "\n";
    }
    
    // 4. find_first_of - 查找任一匹配的元素
    std::cout << "\n4. find_first_of() 算法：\n";
    
    std::vector<int> targets{3, 7, 11};
    auto it_first = std::find_first_of(numbers.begin(), numbers.end(),
                                      targets.begin(), targets.end());
    if (it_first != numbers.end()) {
        std::cout << "   找到第一个目标元素: " << *it_first 
                  << "，位置: " << std::distance(numbers.begin(), it_first) << "\n";
    }
    
    // 5. adjacent_find - 查找相邻的重复元素
    std::cout << "\n5. adjacent_find() 算法：\n";
    
    std::vector<int> with_adjacent{1, 2, 3, 3, 4, 5, 6, 6, 7};
    auto it_adj = std::adjacent_find(with_adjacent.begin(), with_adjacent.end());
    if (it_adj != with_adjacent.end()) {
        std::cout << "   找到相邻重复元素: " << *it_adj 
                  << "，位置: " << std::distance(with_adjacent.begin(), it_adj) << "\n";
    }
    
    // 使用自定义比较函数
    auto it_adj_custom = std::adjacent_find(numbers.begin(), numbers.end(),
                                           [](int a, int b) { return a > b; });
    if (it_adj_custom != numbers.end()) {
        std::cout << "   找到第一个递减对: " << *it_adj_custom 
                  << " > " << *(it_adj_custom + 1) << "\n";
    }
}

// 演示序列查找算法
void demonstrate_sequence_search() {
    std::cout << "\n=== 序列查找算法 ===\n";
    
    std::vector<int> text{1, 2, 3, 4, 5, 3, 4, 6, 7, 8, 3, 4, 5};
    std::vector<int> pattern{3, 4, 5};
    
    std::cout << "文本序列: ";
    for (auto x : text) std::cout << x << " ";
    std::cout << "\n";
    
    std::cout << "查找模式: ";
    for (auto x : pattern) std::cout << x << " ";
    std::cout << "\n";
    
    // 1. search - 查找子序列
    std::cout << "\n1. search() 算法：\n";
    
    auto it = std::search(text.begin(), text.end(),
                         pattern.begin(), pattern.end());
    if (it != text.end()) {
        std::cout << "   找到模式，起始位置: " 
                  << std::distance(text.begin(), it) << "\n";
    }
    
    // 2. search_n - 查找连续的n个相同元素
    std::cout << "\n2. search_n() 算法：\n";
    
    std::vector<int> repeated{1, 2, 3, 3, 3, 4, 5, 6, 6, 7};
    auto it_n = std::search_n(repeated.begin(), repeated.end(), 3, 3);
    if (it_n != repeated.end()) {
        std::cout << "   找到连续3个3，起始位置: " 
                  << std::distance(repeated.begin(), it_n) << "\n";
    } else {
        std::cout << "   未找到连续3个3\n";
    }
    
    it_n = std::search_n(repeated.begin(), repeated.end(), 2, 6);
    if (it_n != repeated.end()) {
        std::cout << "   找到连续2个6，起始位置: " 
                  << std::distance(repeated.begin(), it_n) << "\n";
    } else {
        std::cout << "   未找到连续2个6\n";
    }
    
    // 3. find_end - 查找最后出现的子序列
    std::cout << "\n3. find_end() 算法：\n";
    
    auto it_last = std::find_end(text.begin(), text.end(),
                                pattern.begin(), pattern.end());
    if (it_last != text.end()) {
        std::cout << "   最后一次出现的位置: " 
                  << std::distance(text.begin(), it_last) << "\n";
    }
    
    // 4. 字符串搜索示例
    std::cout << "\n4. 字符串搜索示例：\n";
    
    std::string text_str = "Hello world, this is a wonderful world!";
    std::string pattern_str = "world";
    
    std::cout << "   文本: \"" << text_str << "\"\n";
    std::cout << "   模式: \"" << pattern_str << "\"\n";
    
    auto str_it = std::search(text_str.begin(), text_str.end(),
                             pattern_str.begin(), pattern_str.end());
    if (str_it != text_str.end()) {
        std::cout << "   第一次出现位置: " 
                  << std::distance(text_str.begin(), str_it) << "\n";
    }
    
    auto str_it_last = std::find_end(text_str.begin(), text_str.end(),
                                    pattern_str.begin(), pattern_str.end());
    if (str_it_last != text_str.end()) {
        std::cout << "   最后一次出现位置: " 
                  << std::distance(text_str.begin(), str_it_last) << "\n";
    }
}

// 演示二分查找算法（需要有序序列）
void demonstrate_binary_search() {
    std::cout << "\n=== 二分查找算法 ===\n";
    
    std::vector<int> sorted_vec{1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    
    std::cout << "有序序列: ";
    for (auto x : sorted_vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 1. binary_search - 判断元素是否存在
    std::cout << "\n1. binary_search() 算法：\n";
    
    bool found_7 = std::binary_search(sorted_vec.begin(), sorted_vec.end(), 7);
    std::cout << "   查找 7: " << (found_7 ? "存在" : "不存在") << "\n";
    
    bool found_8 = std::binary_search(sorted_vec.begin(), sorted_vec.end(), 8);
    std::cout << "   查找 8: " << (found_8 ? "存在" : "不存在") << "\n";
    
    // 2. lower_bound - 查找第一个不小于目标值的位置
    std::cout << "\n2. lower_bound() 算法：\n";
    
    auto lb_7 = std::lower_bound(sorted_vec.begin(), sorted_vec.end(), 7);
    std::cout << "   lower_bound(7): 位置 " 
              << std::distance(sorted_vec.begin(), lb_7);
    if (lb_7 != sorted_vec.end()) {
        std::cout << "，值 " << *lb_7;
    }
    std::cout << "\n";
    
    auto lb_8 = std::lower_bound(sorted_vec.begin(), sorted_vec.end(), 8);
    std::cout << "   lower_bound(8): 位置 " 
              << std::distance(sorted_vec.begin(), lb_8);
    if (lb_8 != sorted_vec.end()) {
        std::cout << "，值 " << *lb_8;
    }
    std::cout << "\n";
    
    // 3. upper_bound - 查找第一个大于目标值的位置
    std::cout << "\n3. upper_bound() 算法：\n";
    
    auto ub_7 = std::upper_bound(sorted_vec.begin(), sorted_vec.end(), 7);
    std::cout << "   upper_bound(7): 位置 " 
              << std::distance(sorted_vec.begin(), ub_7);
    if (ub_7 != sorted_vec.end()) {
        std::cout << "，值 " << *ub_7;
    }
    std::cout << "\n";
    
    auto ub_8 = std::upper_bound(sorted_vec.begin(), sorted_vec.end(), 8);
    std::cout << "   upper_bound(8): 位置 " 
              << std::distance(sorted_vec.begin(), ub_8);
    if (ub_8 != sorted_vec.end()) {
        std::cout << "，值 " << *ub_8;
    }
    std::cout << "\n";
    
    // 4. equal_range - 查找等于目标值的范围
    std::cout << "\n4. equal_range() 算法：\n";
    
    auto range_7 = std::equal_range(sorted_vec.begin(), sorted_vec.end(), 7);
    std::cout << "   equal_range(7): [" 
              << std::distance(sorted_vec.begin(), range_7.first)
              << ", " << std::distance(sorted_vec.begin(), range_7.second) 
              << ")\n";
    
    auto range_8 = std::equal_range(sorted_vec.begin(), sorted_vec.end(), 8);
    std::cout << "   equal_range(8): [" 
              << std::distance(sorted_vec.begin(), range_8.first)
              << ", " << std::distance(sorted_vec.begin(), range_8.second) 
              << ")\n";
    
    // 5. 处理重复元素
    std::cout << "\n5. 处理重复元素：\n";
    
    std::vector<int> with_duplicates{1, 3, 5, 7, 7, 7, 9, 11, 13};
    std::cout << "   带重复元素的序列: ";
    for (auto x : with_duplicates) std::cout << x << " ";
    std::cout << "\n";
    
    auto dup_range = std::equal_range(with_duplicates.begin(), with_duplicates.end(), 7);
    std::cout << "   equal_range(7): [" 
              << std::distance(with_duplicates.begin(), dup_range.first)
              << ", " << std::distance(with_duplicates.begin(), dup_range.second) 
              << ")，共 " << std::distance(dup_range.first, dup_range.second) 
              << " 个元素\n";
    
    // 6. 自定义比较函数
    std::cout << "\n6. 自定义比较函数：\n";
    
    std::vector<std::string> words{"apple", "banana", "cherry", "date", "elderberry"};
    std::cout << "   单词列表: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << "\n";
    
    // 按长度查找
    auto length_comp = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };
    
    // 注意：这里假设按长度已经排序，实际中需要先排序
    std::string target = "test"; // 长度为4
    auto word_lb = std::lower_bound(words.begin(), words.end(), target, length_comp);
    if (word_lb != words.end()) {
        std::cout << "   第一个长度>=4的单词: " << *word_lb << "\n";
    }
}

// 演示计数算法
void demonstrate_count_algorithms() {
    std::cout << "\n=== 计数算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 2, 4, 2, 5, 6, 2, 7};
    
    std::cout << "测试数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 1. count - 计算特定值的出现次数
    std::cout << "\n1. count() 算法：\n";
    
    auto count_2 = std::count(numbers.begin(), numbers.end(), 2);
    std::cout << "   数字 2 出现次数: " << count_2 << "\n";
    
    auto count_8 = std::count(numbers.begin(), numbers.end(), 8);
    std::cout << "   数字 8 出现次数: " << count_8 << "\n";
    
    // 2. count_if - 计算满足条件的元素个数
    std::cout << "\n2. count_if() 算法：\n";
    
    auto count_even = std::count_if(numbers.begin(), numbers.end(),
                                   [](int x) { return x % 2 == 0; });
    std::cout << "   偶数个数: " << count_even << "\n";
    
    auto count_greater_3 = std::count_if(numbers.begin(), numbers.end(),
                                        [](int x) { return x > 3; });
    std::cout << "   大于3的数个数: " << count_greater_3 << "\n";
    
    // 3. 字符串计数示例
    std::cout << "\n3. 字符串计数示例：\n";
    
    std::string text = "Hello World! How are you?";
    std::cout << "   文本: \"" << text << "\"\n";
    
    auto vowel_count = std::count_if(text.begin(), text.end(),
                                    [](char c) {
                                        c = std::tolower(c);
                                        return c == 'a' || c == 'e' || c == 'i' || 
                                               c == 'o' || c == 'u';
                                    });
    std::cout << "   元音字母个数: " << vowel_count << "\n";
    
    auto space_count = std::count(text.begin(), text.end(), ' ');
    std::cout << "   空格个数: " << space_count << "\n";
}

// 演示实际应用场景
void demonstrate_practical_applications() {
    std::cout << "\n=== 实际应用场景 ===\n";
    
    // 1. 在学生成绩中查找
    std::cout << "\n1. 学生成绩查找：\n";
    
    struct Student {
        std::string name;
        int score;
        
        Student(const std::string& n, int s) : name(n), score(s) {}
    };
    
    std::vector<Student> students{
        {"Alice", 85}, {"Bob", 92}, {"Charlie", 78}, 
        {"David", 95}, {"Eve", 88}, {"Frank", 82}
    };
    
    // 查找特定姓名的学生
    auto student_it = std::find_if(students.begin(), students.end(),
                                  [](const Student& s) {
                                      return s.name == "Charlie";
                                  });
    if (student_it != students.end()) {
        std::cout << "   找到学生 " << student_it->name 
                  << "，成绩: " << student_it->score << "\n";
    }
    
    // 查找第一个及格的学生
    auto pass_it = std::find_if(students.begin(), students.end(),
                               [](const Student& s) {
                                   return s.score >= 60;
                               });
    if (pass_it != students.end()) {
        std::cout << "   第一个及格学生: " << pass_it->name 
                  << "，成绩: " << pass_it->score << "\n";
    }
    
    // 统计优秀学生数量
    auto excellent_count = std::count_if(students.begin(), students.end(),
                                        [](const Student& s) {
                                            return s.score >= 90;
                                        });
    std::cout << "   优秀学生(>=90分)数量: " << excellent_count << "\n";
    
    // 2. 在有序序列中快速查找
    std::cout << "\n2. 有序序列快速查找：\n";
    
    std::vector<int> inventory_ids{1001, 1005, 1010, 1015, 1020, 1025, 1030};
    std::cout << "   库存ID: ";
    for (auto id : inventory_ids) std::cout << id << " ";
    std::cout << "\n";
    
    // 检查特定ID是否存在
    int search_id = 1015;
    bool exists = std::binary_search(inventory_ids.begin(), inventory_ids.end(), search_id);
    std::cout << "   ID " << search_id << (exists ? " 存在" : " 不存在") << "\n";
    
    // 找到插入新ID的合适位置
    int new_id = 1018;
    auto insert_pos = std::lower_bound(inventory_ids.begin(), inventory_ids.end(), new_id);
    std::cout << "   新ID " << new_id << " 应插入位置: " 
              << std::distance(inventory_ids.begin(), insert_pos) << "\n";
    
    // 3. 文本处理
    std::cout << "\n3. 文本处理应用：\n";
    
    std::vector<std::string> document{
        "The", "quick", "brown", "fox", "jumps", "over", 
        "the", "lazy", "dog", "in", "the", "garden"
    };
    
    std::cout << "   文档: ";
    for (const auto& word : document) std::cout << word << " ";
    std::cout << "\n";
    
    // 查找特定单词
    std::string target_word = "fox";
    auto word_it = std::find(document.begin(), document.end(), target_word);
    if (word_it != document.end()) {
        std::cout << "   找到单词 \"" << target_word 
                  << "\"，位置: " << std::distance(document.begin(), word_it) << "\n";
    }
    
    // 统计定冠词
    auto the_count = std::count(document.begin(), document.end(), "the");
    std::cout << "   \"the\" 出现次数: " << the_count << "\n";
    
    // 查找长单词
    auto long_word = std::find_if(document.begin(), document.end(),
                                 [](const std::string& word) {
                                     return word.length() > 5;
                                 });
    if (long_word != document.end()) {
        std::cout << "   第一个长单词(>5字母): \"" << *long_word << "\"\n";
    }
    
    // 4. 邻近查找应用
    std::cout << "\n4. 邻近查找应用：\n";
    
    std::vector<int> temperatures{20, 22, 25, 25, 23, 21, 19, 19, 18};
    std::cout << "   温度记录: ";
    for (auto temp : temperatures) std::cout << temp << " ";
    std::cout << "\n";
    
    // 查找连续相同的温度
    auto same_temp = std::adjacent_find(temperatures.begin(), temperatures.end());
    if (same_temp != temperatures.end()) {
        std::cout << "   发现连续相同温度: " << *same_temp 
                  << "，位置: " << std::distance(temperatures.begin(), same_temp) << "\n";
    }
    
    // 查找温度急剧下降（差值>=5度）
    auto temp_drop = std::adjacent_find(temperatures.begin(), temperatures.end(),
                                       [](int a, int b) {
                                           return a - b >= 5;
                                       });
    if (temp_drop != temperatures.end()) {
        std::cout << "   发现温度急降: " << *temp_drop 
                  << " -> " << *(temp_drop + 1) << "\n";
    }
}

int main() {
    std::cout << "C++ Primer Chapter 10: 查找算法演示\n";
    std::cout << "==================================\n";
    
    try {
        // 1. 基本查找算法
        demonstrate_basic_find();
        
        // 2. 序列查找算法
        demonstrate_sequence_search();
        
        // 3. 二分查找算法
        demonstrate_binary_search();
        
        // 4. 计数算法
        demonstrate_count_algorithms();
        
        // 5. 实际应用场景
        demonstrate_practical_applications();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 