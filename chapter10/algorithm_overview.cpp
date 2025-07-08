/**
 * @file algorithm_overview.cpp
 * @brief STL 算法概述 - 算法分类、迭代器要求、复杂度分析和异常安全性
 * 
 * STL 提供了丰富的算法库，这些算法与迭代器配合工作，
 * 实现了数据结构与算法的分离。
 */

#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <iterator>
#include <chrono>
#include <random>
#include <functional>

// 可能抛异常的测试类 - 移到全局作用域
class MayThrow {
private:
    int value;
    static int operation_count;
    
public:
    MayThrow(int v = 0) : value(v) {}
    
    MayThrow(const MayThrow& other) : value(other.value) {
        operation_count++;
        if (operation_count % 5 == 0) {
            throw std::runtime_error("Copy constructor failed");
        }
    }
    
    MayThrow& operator=(const MayThrow& other) {
        operation_count++;
        if (operation_count % 7 == 0) {
            throw std::runtime_error("Assignment failed");
        }
        value = other.value;
        return *this;
    }
    
    bool operator<(const MayThrow& other) const {
        operation_count++;
        if (operation_count % 10 == 0) {
            throw std::runtime_error("Comparison failed");
        }
        return value < other.value;
    }
    
    int get_value() const { return value; }
    
    static void reset_count() { operation_count = 0; }
    
    friend std::ostream& operator<<(std::ostream& os, const MayThrow& obj) {
        return os << obj.value;
    }
};

int MayThrow::operation_count = 0;

// 演示算法分类
void demonstrate_algorithm_classification() {
    std::cout << "\n=== STL 算法分类 ===\n";
    
    std::vector<int> vec{5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::vector<int> result;
    
    // 1. 非修改序列算法 (Non-modifying sequence algorithms)
    std::cout << "\n1. 非修改序列算法：\n";
    std::cout << "   原始序列: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 查找算法
    auto it = std::find(vec.begin(), vec.end(), 5);
    std::cout << "   find(5): " << (it != vec.end() ? "找到" : "未找到") << "\n";
    
    // 计数算法
    auto count_greater_5 = std::count_if(vec.begin(), vec.end(), 
                                        [](int x) { return x > 5; });
    std::cout << "   count_if(>5): " << count_greater_5 << "\n";
    
    // 比较算法
    std::vector<int> vec2{5, 2, 8, 1, 9, 3, 7, 4, 6};
    bool is_equal = std::equal(vec.begin(), vec.end(), vec2.begin());
    std::cout << "   equal(): " << std::boolalpha << is_equal << "\n";
    
    // 2. 修改序列算法 (Modifying sequence algorithms)
    std::cout << "\n2. 修改序列算法：\n";
    std::vector<int> vec_copy = vec;
    
    // 拷贝算法
    result.resize(vec.size());
    std::copy(vec.begin(), vec.end(), result.begin());
    std::cout << "   copy(): ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";
    
    // 变换算法
    std::transform(vec_copy.begin(), vec_copy.end(), vec_copy.begin(),
                   [](int x) { return x * 2; });
    std::cout << "   transform(*2): ";
    for (auto x : vec_copy) std::cout << x << " ";
    std::cout << "\n";
    
    // 填充算法
    std::vector<int> fill_vec(5);
    std::fill(fill_vec.begin(), fill_vec.end(), 42);
    std::cout << "   fill(42): ";
    for (auto x : fill_vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 3. 排序和相关算法 (Sorting and related algorithms)
    std::cout << "\n3. 排序和相关算法：\n";
    std::vector<int> sort_vec = vec;
    
    // 排序
    std::sort(sort_vec.begin(), sort_vec.end());
    std::cout << "   sort(): ";
    for (auto x : sort_vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 二分查找
    bool found = std::binary_search(sort_vec.begin(), sort_vec.end(), 5);
    std::cout << "   binary_search(5): " << found << "\n";
    
    // 部分排序
    std::vector<int> partial_vec = vec;
    std::partial_sort(partial_vec.begin(), partial_vec.begin() + 3, partial_vec.end());
    std::cout << "   partial_sort(3): ";
    for (auto x : partial_vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 4. 数值算法 (Numeric algorithms)
    std::cout << "\n4. 数值算法：\n";
    
    // 累积
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "   accumulate(): " << sum << "\n";
    
    // 内积
    int inner_prod = std::inner_product(vec.begin(), vec.begin() + 3,
                                       vec.begin() + 3, 0);
    std::cout << "   inner_product(): " << inner_prod << "\n";
    
    // 相邻差值
    std::vector<int> diff_result(vec.size());
    std::adjacent_difference(vec.begin(), vec.end(), diff_result.begin());
    std::cout << "   adjacent_difference(): ";
    for (auto x : diff_result) std::cout << x << " ";
    std::cout << "\n";
    
    // 5. 集合算法 (Set algorithms - 要求有序序列)
    std::cout << "\n5. 集合算法：\n";
    std::vector<int> set1{1, 3, 5, 7, 9};
    std::vector<int> set2{2, 3, 6, 7, 10};
    std::vector<int> union_result;
    
    std::set_union(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   std::back_inserter(union_result));
    std::cout << "   set_union(): ";
    for (auto x : union_result) std::cout << x << " ";
    std::cout << "\n";
    
    std::vector<int> intersection_result;
    std::set_intersection(set1.begin(), set1.end(),
                         set2.begin(), set2.end(),
                         std::back_inserter(intersection_result));
    std::cout << "   set_intersection(): ";
    for (auto x : intersection_result) std::cout << x << " ";
    std::cout << "\n";
}

// 演示迭代器要求
void demonstrate_iterator_requirements() {
    std::cout << "\n=== 迭代器要求 ===\n";
    
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::list<int> lst{1, 2, 3, 4, 5};
    
    // 1. 输入迭代器 (Input Iterator) - 只读，单次遍历
    std::cout << "\n1. 输入迭代器算法：\n";
    
    // find 只需要输入迭代器
    auto vec_it = std::find(vec.begin(), vec.end(), 3);
    auto lst_it = std::find(lst.begin(), lst.end(), 3);
    std::cout << "   find() 适用于 vector 和 list\n";
    
    // count 只需要输入迭代器
    auto vec_count = std::count(vec.begin(), vec.end(), 3);
    auto lst_count = std::count(lst.begin(), lst.end(), 3);
    std::cout << "   count() 适用于 vector 和 list\n";
    
    // 2. 输出迭代器 (Output Iterator) - 只写
    std::cout << "\n2. 输出迭代器算法：\n";
    
    std::vector<int> output_vec(5);
    std::fill(output_vec.begin(), output_vec.end(), 99);
    std::cout << "   fill() 需要输出迭代器: ";
    for (auto x : output_vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 3. 前向迭代器 (Forward Iterator) - 可读写，多次遍历
    std::cout << "\n3. 前向迭代器算法：\n";
    
    std::vector<int> forward_vec{1, 1, 2, 2, 3, 3};
    std::list<int> forward_lst{1, 1, 2, 2, 3, 3};
    
    // unique 需要前向迭代器
    auto vec_end = std::unique(forward_vec.begin(), forward_vec.end());
    forward_vec.erase(vec_end, forward_vec.end());
    std::cout << "   unique() on vector: ";
    for (auto x : forward_vec) std::cout << x << " ";
    std::cout << "\n";
    
    forward_lst.unique(); // list 有自己的 unique 方法
    std::cout << "   unique() on list: ";
    for (auto x : forward_lst) std::cout << x << " ";
    std::cout << "\n";
    
    // 4. 双向迭代器 (Bidirectional Iterator) - 可前向和后向
    std::cout << "\n4. 双向迭代器算法：\n";
    
    std::vector<int> bidir_vec{1, 2, 3, 4, 5};
    std::list<int> bidir_lst{1, 2, 3, 4, 5};
    
    // reverse 需要双向迭代器
    std::reverse(bidir_vec.begin(), bidir_vec.end());
    std::cout << "   reverse() on vector: ";
    for (auto x : bidir_vec) std::cout << x << " ";
    std::cout << "\n";
    
    std::reverse(bidir_lst.begin(), bidir_lst.end());
    std::cout << "   reverse() on list: ";
    for (auto x : bidir_lst) std::cout << x << " ";
    std::cout << "\n";
    
    // 5. 随机访问迭代器 (Random Access Iterator) - 可随机访问
    std::cout << "\n5. 随机访问迭代器算法：\n";
    
    std::vector<int> random_vec{5, 2, 8, 1, 9, 3, 7, 4, 6};
    // std::deque 也支持随机访问迭代器
    std::deque<int> random_deq{5, 2, 8, 1, 9, 3, 7, 4, 6};
    
    // sort 需要随机访问迭代器
    std::sort(random_vec.begin(), random_vec.end());
    std::cout << "   sort() on vector: ";
    for (auto x : random_vec) std::cout << x << " ";
    std::cout << "\n";
    
    std::sort(random_deq.begin(), random_deq.end());
    std::cout << "   sort() on deque: ";
    for (auto x : random_deq) std::cout << x << " ";
    std::cout << "\n";
    
    // list 不支持随机访问，所以不能用 std::sort
    std::list<int> list_for_sort{5, 2, 8, 1, 9, 3, 7, 4, 6};
    list_for_sort.sort(); // 使用 list 自己的 sort 方法
    std::cout << "   list.sort(): ";
    for (auto x : list_for_sort) std::cout << x << " ";
    std::cout << "\n";
    
    // nth_element 也需要随机访问迭代器
    std::vector<int> nth_vec{5, 2, 8, 1, 9, 3, 7, 4, 6};
    std::nth_element(nth_vec.begin(), nth_vec.begin() + 4, nth_vec.end());
    std::cout << "   nth_element(4): 第5小的元素是 " << nth_vec[4] << "\n";
}

// 演示算法复杂度
void demonstrate_algorithm_complexity() {
    std::cout << "\n=== 算法复杂度分析 ===\n";
    
    const int N = 100000;
    std::vector<int> large_vec(N);
    std::iota(large_vec.begin(), large_vec.end(), 1); // 1, 2, 3, ..., N
    
    auto measure_time = [](auto func, const std::string& desc) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "   " << desc << ": " << duration.count() << " μs\n";
        return duration.count();
    };
    
    // 1. O(n) 线性算法
    std::cout << "\n1. O(n) 线性算法：\n";
    
    measure_time([&]() {
        auto it = std::find(large_vec.begin(), large_vec.end(), N/2);
        volatile auto dummy = it; // 防止优化
    }, "find() - O(n)");
    
    measure_time([&]() {
        auto count = std::count_if(large_vec.begin(), large_vec.end(),
                                  [](int x) { return x % 2 == 0; });
        volatile auto dummy = count;
    }, "count_if() - O(n)");
    
    measure_time([&]() {
        auto sum = std::accumulate(large_vec.begin(), large_vec.end(), 0LL);
        volatile auto dummy = sum;
    }, "accumulate() - O(n)");
    
    // 2. O(log n) 对数算法 (需要有序序列)
    std::cout << "\n2. O(log n) 对数算法：\n";
    
    // 确保序列有序
    std::vector<int> sorted_vec = large_vec; // 已经有序
    
    measure_time([&]() {
        bool found = std::binary_search(sorted_vec.begin(), sorted_vec.end(), N/2);
        volatile auto dummy = found;
    }, "binary_search() - O(log n)");
    
    measure_time([&]() {
        auto it = std::lower_bound(sorted_vec.begin(), sorted_vec.end(), N/2);
        volatile auto dummy = it;
    }, "lower_bound() - O(log n)");
    
    // 3. O(n log n) 准线性算法
    std::cout << "\n3. O(n log n) 准线性算法：\n";
    
    std::vector<int> unsorted_vec = large_vec;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(unsorted_vec.begin(), unsorted_vec.end(), gen);
    
    measure_time([&]() {
        std::sort(unsorted_vec.begin(), unsorted_vec.end());
    }, "sort() - O(n log n)");
    
    // 重新打乱
    std::shuffle(unsorted_vec.begin(), unsorted_vec.end(), gen);
    measure_time([&]() {
        std::stable_sort(unsorted_vec.begin(), unsorted_vec.end());
    }, "stable_sort() - O(n log n)");
    
    // 4. O(n) 线性排序算法 (特殊情况)
    std::cout << "\n4. O(n) 线性选择算法：\n";
    
    std::vector<int> nth_vec = large_vec;
    std::shuffle(nth_vec.begin(), nth_vec.end(), gen);
    
    measure_time([&]() {
        std::nth_element(nth_vec.begin(), nth_vec.begin() + N/2, nth_vec.end());
    }, "nth_element() - O(n) 平均");
    
    // 5. 不同大小的性能对比
    std::cout << "\n5. 规模对性能的影响：\n";
    
    for (int size : {1000, 10000, 100000}) {
        std::vector<int> test_vec(size);
        std::iota(test_vec.begin(), test_vec.end(), 1);
        
        auto time = measure_time([&]() {
            auto sum = std::accumulate(test_vec.begin(), test_vec.end(), 0LL);
            volatile auto dummy = sum;
        }, "accumulate() size=" + std::to_string(size));
    }
}

// 演示异常安全性
void demonstrate_exception_safety() {
    std::cout << "\n=== 异常安全性 ===\n";
    
    std::cout << "\n1. 算法的异常安全保证：\n";
    
    // 测试 copy 的异常安全性
    std::vector<MayThrow> source;
    for (int i = 1; i <= 10; ++i) {
        source.emplace_back(i);
    }
    
    std::vector<MayThrow> dest(10);
    
    try {
        std::cout << "   尝试 copy() 操作...\n";
        std::copy(source.begin(), source.end(), dest.begin());
        std::cout << "   copy() 成功完成\n";
    } catch (const std::exception& e) {
        std::cout << "   copy() 异常: " << e.what() << "\n";
        std::cout << "   目标容器可能处于部分修改状态\n";
    }
    
    // 测试 sort 的异常安全性
    std::vector<MayThrow> sort_vec;
    for (int i = 10; i >= 1; --i) {
        sort_vec.emplace_back(i);
    }
    
    try {
        std::cout << "\n   尝试 sort() 操作...\n";
        MayThrow::reset_count(); // 重置计数器
        std::sort(sort_vec.begin(), sort_vec.end());
        std::cout << "   sort() 成功完成\n";
        std::cout << "   排序结果: ";
        for (const auto& item : sort_vec) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cout << "   sort() 异常: " << e.what() << "\n";
        std::cout << "   容器可能处于未完全排序状态\n";
        std::cout << "   当前状态: ";
        for (const auto& item : sort_vec) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\n2. 异常安全的编程实践：\n";
    std::cout << "   - 使用异常安全的容器操作\n";
    std::cout << "   - 在算法执行前保存状态\n";
    std::cout << "   - 使用 RAII 和智能指针\n";
    std::cout << "   - 选择提供强异常安全保证的算法\n";
    std::cout << "   - 避免在算法中使用可能抛异常的操作\n";
}

// 演示算法的实际应用
void demonstrate_practical_usage() {
    std::cout << "\n=== 算法实际应用 ===\n";
    
    // 1. 数据分析场景
    std::cout << "\n1. 数据分析场景：\n";
    
    std::vector<double> sales_data{1200.5, 980.3, 1450.7, 876.2, 2100.8, 
                                  1890.4, 1344.6, 967.1, 1678.9, 2345.2};
    
    std::cout << "   销售数据: ";
    for (auto x : sales_data) std::cout << x << " ";
    std::cout << "\n";
    
    // 计算总销售额
    double total = std::accumulate(sales_data.begin(), sales_data.end(), 0.0);
    std::cout << "   总销售额: " << total << "\n";
    
    // 计算平均值
    double average = total / sales_data.size();
    std::cout << "   平均销售额: " << average << "\n";
    
    // 找到最大和最小销售额
    auto max_it = std::max_element(sales_data.begin(), sales_data.end());
    auto min_it = std::min_element(sales_data.begin(), sales_data.end());
    std::cout << "   最大销售额: " << *max_it << "\n";
    std::cout << "   最小销售额: " << *min_it << "\n";
    
    // 计算高于平均值的销售数量
    auto above_avg = std::count_if(sales_data.begin(), sales_data.end(),
                                  [average](double x) { return x > average; });
    std::cout << "   高于平均值的销售数量: " << above_avg << "\n";
    
    // 排序获取销售排名
    std::vector<double> sorted_sales = sales_data;
    std::sort(sorted_sales.rbegin(), sorted_sales.rend()); // 降序
    std::cout << "   销售排名 (前5): ";
    for (int i = 0; i < std::min(5, static_cast<int>(sorted_sales.size())); ++i) {
        std::cout << sorted_sales[i] << " ";
    }
    std::cout << "\n";
    
    // 2. 字符串处理场景
    std::cout << "\n2. 字符串处理场景：\n";
    
    std::vector<std::string> words{"hello", "world", "algorithm", "standard", 
                                  "library", "cpp", "programming", "language"};
    
    std::cout << "   原始单词: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << "\n";
    
    // 转换为大写
    std::vector<std::string> upper_words = words;
    std::for_each(upper_words.begin(), upper_words.end(),
                 [](std::string& word) {
                     std::transform(word.begin(), word.end(), word.begin(),
                                   [](char c) { return std::toupper(c); });
                 });
    
    std::cout << "   大写转换: ";
    for (const auto& word : upper_words) std::cout << word << " ";
    std::cout << "\n";
    
    // 按长度排序
    std::vector<std::string> sorted_words = words;
    std::sort(sorted_words.begin(), sorted_words.end(),
             [](const std::string& a, const std::string& b) {
                 return a.length() < b.length();
             });
    
    std::cout << "   按长度排序: ";
    for (const auto& word : sorted_words) std::cout << word << " ";
    std::cout << "\n";
    
    // 查找特定长度的单词
    auto long_words = std::count_if(words.begin(), words.end(),
                                   [](const std::string& word) {
                                       return word.length() > 6;
                                   });
    std::cout << "   长度>6的单词数量: " << long_words << "\n";
    
    // 3. 容器操作场景
    std::cout << "\n3. 容器操作场景：\n";
    
    std::vector<int> vec1{1, 3, 5, 7, 9};
    std::vector<int> vec2{2, 4, 6, 8, 10};
    std::vector<int> merged;
    
    // 合并两个有序序列
    std::merge(vec1.begin(), vec1.end(),
              vec2.begin(), vec2.end(),
              std::back_inserter(merged));
    
    std::cout << "   合并结果: ";
    for (auto x : merged) std::cout << x << " ";
    std::cout << "\n";
    
    // 去除重复元素
    std::vector<int> with_duplicates{1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    auto unique_end = std::unique(with_duplicates.begin(), with_duplicates.end());
    with_duplicates.erase(unique_end, with_duplicates.end());
    
    std::cout << "   去重结果: ";
    for (auto x : with_duplicates) std::cout << x << " ";
    std::cout << "\n";
    
    // 分区操作
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto partition_point = std::partition(numbers.begin(), numbers.end(),
                                         [](int x) { return x % 2 == 0; });
    
    std::cout << "   偶数分区: ";
    for (auto it = numbers.begin(); it != partition_point; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "| 奇数分区: ";
    for (auto it = partition_point; it != numbers.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 10: 泛型算法概述\n";
    std::cout << "==================================\n";
    
    try {
        // 1. 算法分类演示
        demonstrate_algorithm_classification();
        
        // 2. 迭代器要求演示  
        demonstrate_iterator_requirements();
        
        // 3. 算法复杂度分析
        demonstrate_algorithm_complexity();
        
        // 4. 异常安全性
        demonstrate_exception_safety();
        
        // 5. 实际应用
        demonstrate_practical_usage();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 