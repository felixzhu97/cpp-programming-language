/**
 * @file sorting_algorithms.cpp
 * @brief 排序算法演示 - sort、stable_sort、partial_sort、nth_element 等算法
 * 
 * 排序算法是数据处理中最重要的算法之一，STL提供了多种排序算法。
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <functional>
#include <iomanip>

// 用于演示的学生类
struct Student {
    std::string name;
    int age;
    double score;
    
    Student(const std::string& n, int a, double s) 
        : name(n), age(a), score(s) {}
        
    friend std::ostream& operator<<(std::ostream& os, const Student& s) {
        return os << s.name << "(" << s.age << "," << std::fixed 
                  << std::setprecision(1) << s.score << ")";
    }
};

// 用于稳定性演示的Item类
struct Item {
    char letter;
    int number;
    
    Item(char l, int n) : letter(l), number(n) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        return os << item.letter << item.number;
    }
};

// 商品类
struct Product {
    std::string name;
    double price;
    double rating;
    int sales;
    
    Product(const std::string& n, double p, double r, int s)
        : name(n), price(p), rating(r), sales(s) {}
        
    friend std::ostream& operator<<(std::ostream& os, const Product& p) {
        return os << p.name << "($" << std::fixed << std::setprecision(1) 
                  << p.price << ",★" << p.rating << "," << p.sales << "销量)";
    }
};

// 任务类
struct Task {
    int id;
    int priority;
    int estimated_time;
    
    Task(int i, int p, int t) : id(i), priority(p), estimated_time(t) {}
    
    friend std::ostream& operator<<(std::ostream& os, const Task& t) {
        return os << "T" << t.id << "(P" << t.priority << ",T" << t.estimated_time << ")";
    }
};

// 演示基本排序算法
void demonstrate_basic_sorting() {
    std::cout << "\n=== 基本排序算法 ===\n";
    
    // 1. sort - 默认升序排序
    std::cout << "\n1. sort() 算法：\n";
    
    std::vector<int> numbers{5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::cout << "   原始数据: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    std::sort(numbers.begin(), numbers.end());
    std::cout << "   升序排序: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 降序排序
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    std::cout << "   降序排序: ";
    for (auto x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 2. stable_sort - 稳定排序
    std::cout << "\n2. stable_sort() 算法：\n";
    
    std::vector<Student> students{
        Student("Alice", 20, 85.5),
        Student("Bob", 22, 90.0),
        Student("Charlie", 20, 78.5),
        Student("David", 21, 92.0),
        Student("Eve", 20, 88.0)
    };
    
    std::cout << "   原始学生数据: ";
    for (const auto& s : students) std::cout << s << " ";
    std::cout << "\n";
    
    // 按年龄稳定排序
    std::stable_sort(students.begin(), students.end(),
                    [](const Student& a, const Student& b) {
                        return a.age < b.age;
                    });
    std::cout << "   按年龄稳定排序: ";
    for (const auto& s : students) std::cout << s << " ";
    std::cout << "\n";
    
    // 3. partial_sort - 部分排序
    std::cout << "\n3. partial_sort() 算法：\n";
    
    std::vector<int> large_data{15, 3, 9, 1, 12, 7, 18, 5, 11, 2, 14, 8, 6, 13, 10};
    std::cout << "   原始数据: ";
    for (auto x : large_data) std::cout << x << " ";
    std::cout << "\n";
    
    // 只排序前5个最小的元素
    std::partial_sort(large_data.begin(), large_data.begin() + 5, large_data.end());
    std::cout << "   前5小元素: ";
    for (int i = 0; i < 5; ++i) std::cout << large_data[i] << " ";
    std::cout << "| 其余元素: ";
    for (int i = 5; i < large_data.size(); ++i) std::cout << large_data[i] << " ";
    std::cout << "\n";
    
    // 4. nth_element - 找第n个元素
    std::cout << "\n4. nth_element() 算法：\n";
    
    std::vector<int> nth_data{15, 3, 9, 1, 12, 7, 18, 5, 11, 2, 14, 8, 6, 13, 10};
    std::cout << "   原始数据: ";
    for (auto x : nth_data) std::cout << x << " ";
    std::cout << "\n";
    
    // 找中位数（第7小的元素，索引6）
    int nth = 6;
    std::nth_element(nth_data.begin(), nth_data.begin() + nth, nth_data.end());
    std::cout << "   第" << (nth + 1) << "小的元素: " << nth_data[nth] << "\n";
    std::cout << "   分区结果: ";
    for (int i = 0; i <= nth; ++i) std::cout << nth_data[i] << " ";
    std::cout << "| " << nth_data[nth] << " | ";
    for (int i = nth + 1; i < nth_data.size(); ++i) std::cout << nth_data[i] << " ";
    std::cout << "\n";
}

// 演示自定义比较函数
void demonstrate_custom_comparators() {
    std::cout << "\n=== 自定义比较函数 ===\n";
    
    std::vector<std::string> words{"apple", "Banana", "cherry", "Date", "elderberry"};
    std::cout << "原始单词: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << "\n";
    
    // 1. 按长度排序
    std::cout << "\n1. 按长度排序：\n";
    std::vector<std::string> by_length = words;
    std::sort(by_length.begin(), by_length.end(),
             [](const std::string& a, const std::string& b) {
                 return a.length() < b.length();
             });
    std::cout << "   按长度排序: ";
    for (const auto& word : by_length) std::cout << word << " ";
    std::cout << "\n";
    
    // 2. 忽略大小写排序
    std::cout << "\n2. 忽略大小写排序：\n";
    std::vector<std::string> case_insensitive = words;
    std::sort(case_insensitive.begin(), case_insensitive.end(),
             [](const std::string& a, const std::string& b) {
                 std::string lower_a = a;
                 std::string lower_b = b;
                 std::transform(lower_a.begin(), lower_a.end(), lower_a.begin(), ::tolower);
                 std::transform(lower_b.begin(), lower_b.end(), lower_b.begin(), ::tolower);
                 return lower_a < lower_b;
             });
    std::cout << "   忽略大小写: ";
    for (const auto& word : case_insensitive) std::cout << word << " ";
    std::cout << "\n";
    
    // 3. 复合条件排序
    std::cout << "\n3. 复合条件排序：\n";
    
    std::vector<Student> students{
        Student("Alice", 20, 85.5),
        Student("Bob", 20, 90.0),
        Student("Charlie", 22, 78.5),
        Student("David", 20, 92.0),
        Student("Eve", 22, 88.0)
    };
    
    std::cout << "   原始数据: ";
    for (const auto& s : students) std::cout << s << " ";
    std::cout << "\n";
    
    // 先按年龄排序，年龄相同时按成绩降序
    std::sort(students.begin(), students.end(),
             [](const Student& a, const Student& b) {
                 if (a.age != b.age) {
                     return a.age < b.age;
                 }
                 return a.score > b.score; // 成绩降序
             });
    std::cout << "   年龄升序+成绩降序: ";
    for (const auto& s : students) std::cout << s << " ";
    std::cout << "\n";
    
    // 4. 使用函数对象
    std::cout << "\n4. 使用函数对象：\n";
    
    struct ScoreComparator {
        bool ascending;
        
        ScoreComparator(bool asc = true) : ascending(asc) {}
        
        bool operator()(const Student& a, const Student& b) const {
            return ascending ? (a.score < b.score) : (a.score > b.score);
        }
    };
    
    std::vector<Student> score_sorted = students;
    std::sort(score_sorted.begin(), score_sorted.end(), ScoreComparator(false));
    std::cout << "   成绩降序(函数对象): ";
    for (const auto& s : score_sorted) std::cout << s << " ";
    std::cout << "\n";
}

// 演示稳定性差异
void demonstrate_stability() {
    std::cout << "\n=== 排序稳定性演示 ===\n";
    
    std::vector<Item> items{
        Item('B', 1), Item('A', 2), Item('B', 3), 
        Item('A', 4), Item('C', 5), Item('B', 6)
    };
    
    std::cout << "原始数据: ";
    for (const auto& item : items) std::cout << item << " ";
    std::cout << "\n";
    
    // 1. 使用 sort（不稳定）
    std::cout << "\n1. sort()（不稳定）：\n";
    std::vector<Item> unstable_sorted = items;
    std::sort(unstable_sorted.begin(), unstable_sorted.end(),
             [](const Item& a, const Item& b) {
                 return a.letter < b.letter;
             });
    std::cout << "   结果: ";
    for (const auto& item : unstable_sorted) std::cout << item << " ";
    std::cout << "\n   注意: 相同字母的数字顺序可能改变\n";
    
    // 2. 使用 stable_sort（稳定）
    std::cout << "\n2. stable_sort()（稳定）：\n";
    std::vector<Item> stable_sorted = items;
    std::stable_sort(stable_sorted.begin(), stable_sorted.end(),
                    [](const Item& a, const Item& b) {
                        return a.letter < b.letter;
                    });
    std::cout << "   结果: ";
    for (const auto& item : stable_sorted) std::cout << item << " ";
    std::cout << "\n   注意: 相同字母保持原始顺序\n";
    
    // 3. 多级排序演示稳定性的重要性
    std::cout << "\n3. 多级排序应用：\n";
    
    std::vector<Student> multi_students{
        Student("Alice", 20, 85.0),
        Student("Bob", 20, 85.0),
        Student("Charlie", 21, 85.0),
        Student("David", 20, 90.0),
        Student("Eve", 21, 90.0)
    };
    
    std::cout << "   原始数据: ";
    for (const auto& s : multi_students) std::cout << s << " ";
    std::cout << "\n";
    
    // 先按成绩排序
    std::stable_sort(multi_students.begin(), multi_students.end(),
                    [](const Student& a, const Student& b) {
                        return a.score > b.score;
                    });
    std::cout << "   第一步-按成绩降序: ";
    for (const auto& s : multi_students) std::cout << s << " ";
    std::cout << "\n";
    
    // 再按年龄排序（稳定排序保持成绩顺序）
    std::stable_sort(multi_students.begin(), multi_students.end(),
                    [](const Student& a, const Student& b) {
                        return a.age < b.age;
                    });
    std::cout << "   第二步-按年龄升序: ";
    for (const auto& s : multi_students) std::cout << s << " ";
    std::cout << "\n   结果: 年龄相同时保持成绩降序\n";
}

// 演示部分排序的应用
void demonstrate_partial_sorting_applications() {
    std::cout << "\n=== 部分排序应用 ===\n";
    
    // 1. Top-K 问题
    std::cout << "\n1. Top-K 问题（查找前K个最大值）：\n";
    
    std::vector<int> scores{78, 92, 85, 67, 95, 88, 73, 91, 82, 89, 76, 94, 87, 69, 93};
    std::cout << "   成绩数据: ";
    for (auto score : scores) std::cout << score << " ";
    std::cout << "\n";
    
    const int K = 5;
    std::vector<int> top_k = scores;
    
    // 使用 partial_sort 找前K个最大值
    std::partial_sort(top_k.begin(), top_k.begin() + K, top_k.end(), 
                     std::greater<int>());
    
    std::cout << "   前" << K << "个最高分: ";
    for (int i = 0; i < K; ++i) std::cout << top_k[i] << " ";
    std::cout << "\n";
    
    // 2. 中位数查找
    std::cout << "\n2. 中位数查找：\n";
    
    std::vector<double> data{3.2, 1.8, 4.7, 2.1, 5.9, 3.8, 2.5, 4.1, 1.3, 5.2};
    std::cout << "   数据: ";
    for (auto x : data) std::cout << std::fixed << std::setprecision(1) << x << " ";
    std::cout << "\n";
    
    std::vector<double> median_data = data;
    size_t mid = median_data.size() / 2;
    
    if (median_data.size() % 2 == 1) {
        // 奇数个元素
        std::nth_element(median_data.begin(), median_data.begin() + mid, median_data.end());
        std::cout << "   中位数: " << std::fixed << std::setprecision(1) 
                  << median_data[mid] << "\n";
    } else {
        // 偶数个元素，需要两个中间值的平均
        std::nth_element(median_data.begin(), median_data.begin() + mid - 1, median_data.end());
        double lower_mid = median_data[mid - 1];
        std::nth_element(median_data.begin() + mid, median_data.begin() + mid, median_data.end());
        double upper_mid = median_data[mid];
        std::cout << "   中位数: " << std::fixed << std::setprecision(1) 
                  << (lower_mid + upper_mid) / 2.0 << "\n";
    }
    
    // 3. 百分位数计算
    std::cout << "\n3. 百分位数计算：\n";
    
    std::vector<int> test_scores{65, 70, 75, 78, 80, 82, 85, 87, 89, 90, 92, 94, 96, 98, 100};
    std::cout << "   测试成绩: ";
    for (auto score : test_scores) std::cout << score << " ";
    std::cout << "\n";
    
    // 计算75%百分位数
    auto calculate_percentile = [](std::vector<int> data, double percentile) {
        if (data.empty()) return 0;
        
        double index = (percentile / 100.0) * (data.size() - 1);
        size_t lower_index = static_cast<size_t>(index);
        size_t upper_index = std::min(lower_index + 1, data.size() - 1);
        
        std::nth_element(data.begin(), data.begin() + lower_index, data.end());
        int lower_value = data[lower_index];
        
        if (lower_index == upper_index) {
            return lower_value;
        }
        
        std::nth_element(data.begin() + upper_index, data.begin() + upper_index, data.end());
        int upper_value = data[upper_index];
        
        double weight = index - lower_index;
        return static_cast<int>(lower_value + weight * (upper_value - lower_value));
    };
    
    int p75 = calculate_percentile(test_scores, 75.0);
    int p90 = calculate_percentile(test_scores, 90.0);
    
    std::cout << "   75%百分位数: " << p75 << "\n";
    std::cout << "   90%百分位数: " << p90 << "\n";
}

// 演示性能比较
void demonstrate_performance_comparison() {
    std::cout << "\n=== 性能比较 ===\n";
    
    const int N = 100000;
    
    auto measure_time = [](auto func, const std::string& desc) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "   " << desc << ": " << duration.count() << " μs\n";
        return duration.count();
    };
    
    // 生成随机数据
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, N);
    
    std::vector<int> base_data(N);
    for (auto& x : base_data) {
        x = dis(gen);
    }
    
    std::cout << "\n数据规模: " << N << " 个随机整数\n";
    
    // 1. 完全排序 vs 部分排序
    std::cout << "\n1. 完全排序 vs 部分排序（前1000个）：\n";
    
    std::vector<int> full_sort_data = base_data;
    measure_time([&]() {
        std::sort(full_sort_data.begin(), full_sort_data.end());
    }, "完全排序");
    
    std::vector<int> partial_sort_data = base_data;
    measure_time([&]() {
        std::partial_sort(partial_sort_data.begin(), 
                         partial_sort_data.begin() + 1000, 
                         partial_sort_data.end());
    }, "部分排序(前1000)");
    
    // 2. nth_element vs 完全排序（查找中位数）
    std::cout << "\n2. nth_element vs 完全排序（查找中位数）：\n";
    
    std::vector<int> nth_data = base_data;
    measure_time([&]() {
        std::nth_element(nth_data.begin(), 
                        nth_data.begin() + N/2, 
                        nth_data.end());
    }, "nth_element查找中位数");
    
    std::vector<int> sort_median_data = base_data;
    measure_time([&]() {
        std::sort(sort_median_data.begin(), sort_median_data.end());
        volatile auto median = sort_median_data[N/2]; // 防止优化
    }, "完全排序后取中位数");
    
    // 3. sort vs stable_sort
    std::cout << "\n3. sort vs stable_sort：\n";
    
    std::vector<int> sort_data = base_data;
    measure_time([&]() {
        std::sort(sort_data.begin(), sort_data.end());
    }, "sort()");
    
    std::vector<int> stable_sort_data = base_data;
    measure_time([&]() {
        std::stable_sort(stable_sort_data.begin(), stable_sort_data.end());
    }, "stable_sort()");
}

// 演示实际应用场景
void demonstrate_real_world_applications() {
    std::cout << "\n=== 实际应用场景 ===\n";
    
    // 1. 成绩排名系统
    std::cout << "\n1. 成绩排名系统：\n";
    
    std::vector<Student> class_students{
        Student("Alice", 20, 92.5),
        Student("Bob", 19, 88.0),
        Student("Charlie", 21, 95.0),
        Student("David", 20, 87.5),
        Student("Eve", 19, 91.0),
        Student("Frank", 22, 89.5),
        Student("Grace", 20, 94.0),
        Student("Henry", 21, 86.0)
    };
    
    std::cout << "   班级学生: ";
    for (const auto& s : class_students) std::cout << s << " ";
    std::cout << "\n";
    
    // 按成绩降序排列
    std::sort(class_students.begin(), class_students.end(),
             [](const Student& a, const Student& b) {
                 return a.score > b.score;
             });
    
    std::cout << "   成绩排名:\n";
    for (size_t i = 0; i < class_students.size(); ++i) {
        std::cout << "     " << (i + 1) << ". " << class_students[i] << "\n";
    }
    
    // 查找前30%的学生
    size_t top_30_percent = static_cast<size_t>(class_students.size() * 0.3);
    std::cout << "   前30%学生: ";
    for (size_t i = 0; i < top_30_percent; ++i) {
        std::cout << class_students[i].name << " ";
    }
    std::cout << "\n";
    
    // 2. 电商商品排序
    std::cout << "\n2. 电商商品排序：\n";
    
    std::vector<Product> products{
        Product("手机A", 999.9, 4.5, 1200),
        Product("手机B", 799.9, 4.8, 800),
        Product("手机C", 1299.9, 4.3, 600),
        Product("手机D", 699.9, 4.6, 1500),
        Product("手机E", 1199.9, 4.7, 900)
    };
    
    std::cout << "   商品列表: ";
    for (const auto& p : products) std::cout << p << " ";
    std::cout << "\n";
    
    // 按综合评分排序（评分权重60%，销量权重40%）
    std::sort(products.begin(), products.end(),
             [](const Product& a, const Product& b) {
                 double score_a = a.rating * 0.6 + (a.sales / 1000.0) * 0.4;
                 double score_b = b.rating * 0.6 + (b.sales / 1000.0) * 0.4;
                 return score_a > score_b;
             });
    
    std::cout << "   综合排序: ";
    for (const auto& p : products) std::cout << p.name << " ";
    std::cout << "\n";
    
    // 3. 任务调度系统
    std::cout << "\n3. 任务调度系统：\n";
    
    std::vector<Task> tasks{
        Task(1, 3, 10), Task(2, 1, 15), Task(3, 2, 5),
        Task(4, 3, 8), Task(5, 1, 20), Task(6, 2, 12)
    };
    
    std::cout << "   任务列表: ";
    for (const auto& t : tasks) std::cout << t << " ";
    std::cout << "\n";
    
    // 优先级调度：优先级高的先执行，同优先级按时间短的先执行
    std::stable_sort(tasks.begin(), tasks.end(),
                    [](const Task& a, const Task& b) {
                        if (a.priority != b.priority) {
                            return a.priority < b.priority; // 优先级数字小的优先级高
                        }
                        return a.estimated_time < b.estimated_time; // 时间短的优先
                    });
    
    std::cout << "   执行顺序: ";
    for (const auto& t : tasks) std::cout << t << " ";
    std::cout << "\n";
    
    // 使用 nth_element 找到最紧急的前3个任务
    std::vector<Task> urgent_tasks = tasks;
    std::nth_element(urgent_tasks.begin(), urgent_tasks.begin() + 2, urgent_tasks.end(),
                    [](const Task& a, const Task& b) {
                        return a.priority < b.priority;
                    });
    
    std::cout << "   最紧急的3个任务: ";
    for (int i = 0; i < 3; ++i) std::cout << urgent_tasks[i] << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 10: 排序算法演示\n";
    std::cout << "==================================\n";
    
    try {
        // 1. 基本排序算法
        demonstrate_basic_sorting();
        
        // 2. 自定义比较函数
        demonstrate_custom_comparators();
        
        // 3. 稳定性演示
        demonstrate_stability();
        
        // 4. 部分排序应用
        demonstrate_partial_sorting_applications();
        
        // 5. 性能比较
        demonstrate_performance_comparison();
        
        // 6. 实际应用场景
        demonstrate_real_world_applications();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 