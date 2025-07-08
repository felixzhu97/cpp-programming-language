/**
 * @file function_objects.cpp
 * @brief 函数对象演示 - 函数调用运算符、可调用对象、标准库函数对象
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <string>
#include <numeric>

// 简单的函数对象
class Add {
private:
    int value;
    
public:
    Add(int v) : value(v) {}
    
    // 函数调用运算符
    int operator()(int x) const {
        return x + value;
    }
};

// 通用的比较函数对象
template<typename T>
class GreaterThan {
private:
    T threshold;
    
public:
    GreaterThan(const T& t) : threshold(t) {}
    
    bool operator()(const T& value) const {
        return value > threshold;
    }
};

// 累积器函数对象
class Accumulator {
private:
    int sum;
    
public:
    Accumulator() : sum(0) {}
    
    int operator()(int x) {
        sum += x;
        return sum;
    }
    
    int get_sum() const { return sum; }
};

// 字符串处理函数对象
class StringProcessor {
private:
    std::string prefix;
    
public:
    StringProcessor(const std::string& p) : prefix(p) {}
    
    std::string operator()(const std::string& str) const {
        return prefix + str;
    }
    
    // 重载：处理多个参数
    std::string operator()(const std::string& str1, const std::string& str2) const {
        return prefix + str1 + " " + str2;
    }
};

// 统计函数对象
class Counter {
private:
    mutable int count;  // mutable 允许在 const 函数中修改
    
public:
    Counter() : count(0) {}
    
    bool operator()(int x) const {
        count++;
        return x > 0;
    }
    
    int get_count() const { return count; }
};

// 谓词函数对象
class IsEven {
public:
    bool operator()(int x) const {
        return x % 2 == 0;
    }
};

class IsInRange {
private:
    int min_val, max_val;
    
public:
    IsInRange(int min_v, int max_v) : min_val(min_v), max_val(max_v) {}
    
    bool operator()(int x) const {
        return x >= min_val && x <= max_val;
    }
};

// 函数适配器示例
template<typename Func>
class Negator {
private:
    Func func;
    
public:
    Negator(Func f) : func(f) {}
    
    template<typename... Args>
    auto operator()(Args&&... args) const -> decltype(!func(std::forward<Args>(args)...)) {
        return !func(std::forward<Args>(args)...);
    }
};

template<typename Func>
Negator<Func> make_negator(Func f) {
    return Negator<Func>(f);
}

void demonstrate_basic_function_objects() {
    std::cout << "\n=== 基本函数对象 ===\n";
    
    Add add5(5);
    std::cout << "add5(10) = " << add5(10) << "\n";
    std::cout << "add5(20) = " << add5(20) << "\n";
    
    GreaterThan<int> gt10(10);
    std::cout << "gt10(15) = " << (gt10(15) ? "true" : "false") << "\n";
    std::cout << "gt10(5) = " << (gt10(5) ? "true" : "false") << "\n";
    
    StringProcessor prefix_hello("Hello, ");
    std::cout << "prefix_hello(\"World\") = " << prefix_hello("World") << "\n";
    std::cout << "prefix_hello(\"Alice\", \"Bob\") = " << prefix_hello("Alice", "Bob") << "\n";
}

void demonstrate_function_objects_with_algorithms() {
    std::cout << "\n=== 函数对象与算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "原始数据: ";
    for (int x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 使用函数对象进行变换
    std::vector<int> added(numbers.size());
    std::transform(numbers.begin(), numbers.end(), added.begin(), Add(10));
    std::cout << "每个元素+10: ";
    for (int x : added) std::cout << x << " ";
    std::cout << "\n";
    
    // 使用谓词函数对象进行查找
    auto even_it = std::find_if(numbers.begin(), numbers.end(), IsEven());
    if (even_it != numbers.end()) {
        std::cout << "第一个偶数: " << *even_it << "\n";
    }
    
    // 使用函数对象进行计数
    int even_count = std::count_if(numbers.begin(), numbers.end(), IsEven());
    std::cout << "偶数个数: " << even_count << "\n";
    
    // 使用范围谓词
    IsInRange range_5_8(5, 8);
    int range_count = std::count_if(numbers.begin(), numbers.end(), range_5_8);
    std::cout << "在[5,8]范围内的数字个数: " << range_count << "\n";
    
    // 复制满足条件的元素
    std::vector<int> range_numbers;
    std::copy_if(numbers.begin(), numbers.end(), 
                std::back_inserter(range_numbers), range_5_8);
    std::cout << "范围[5,8]内的数字: ";
    for (int x : range_numbers) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_stateful_function_objects() {
    std::cout << "\n=== 有状态的函数对象 ===\n";
    
    Accumulator acc;
    std::vector<int> numbers{1, 2, 3, 4, 5};
    
    std::cout << "累积过程: ";
    for (int x : numbers) {
        std::cout << acc(x) << " ";
    }
    std::cout << "\n";
    std::cout << "最终累积和: " << acc.get_sum() << "\n";
    
    // 计数器示例
    Counter counter;
    std::vector<int> test_data{-2, -1, 0, 1, 2, 3, -3, 4, 5};
    
    int positive_count = std::count_if(test_data.begin(), test_data.end(), 
                                      std::ref(counter));
    std::cout << "正数个数: " << positive_count << "\n";
    std::cout << "计数器调用次数: " << counter.get_count() << "\n";
}

void demonstrate_standard_function_objects() {
    std::cout << "\n=== 标准库函数对象 ===\n";
    
    std::vector<int> numbers{3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::cout << "原始数据: ";
    for (int x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 使用标准库函数对象排序
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    std::cout << "降序排序: ";
    for (int x : numbers) std::cout << x << " ";
    std::cout << "\n";
    
    // 使用标准库函数对象进行数值计算
    std::vector<int> values1{1, 2, 3, 4, 5};
    std::vector<int> values2{2, 3, 4, 5, 6};
    std::vector<int> products(values1.size());
    
    std::transform(values1.begin(), values1.end(), 
                  values2.begin(), products.begin(), 
                  std::multiplies<int>());
    
    std::cout << "对应元素相乘: ";
    for (int x : products) std::cout << x << " ";
    std::cout << "\n";
    
    // 使用bind创建新的函数对象
    auto multiply_by_3 = std::bind(std::multiplies<int>(), std::placeholders::_1, 3);
    
    std::vector<int> multiplied(values1.size());
    std::transform(values1.begin(), values1.end(), multiplied.begin(), multiply_by_3);
    
    std::cout << "乘以3: ";
    for (int x : multiplied) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_function_adapters() {
    std::cout << "\n=== 函数适配器 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 原始谓词：是偶数
    IsEven is_even;
    int even_count = std::count_if(numbers.begin(), numbers.end(), is_even);
    std::cout << "偶数个数: " << even_count << "\n";
    
    // 取反适配器：是奇数
    auto is_odd = make_negator(is_even);
    int odd_count = std::count_if(numbers.begin(), numbers.end(), is_odd);
    std::cout << "奇数个数: " << odd_count << "\n";
    
    // 使用标准库的not_fn
    int odd_count2 = std::count_if(numbers.begin(), numbers.end(), 
                                  std::not_fn(is_even));
    std::cout << "奇数个数(not_fn): " << odd_count2 << "\n";
    
    // 使用bind适配器
    auto greater_than_5 = std::bind(std::greater<int>(), std::placeholders::_1, 5);
    int greater_count = std::count_if(numbers.begin(), numbers.end(), greater_than_5);
    std::cout << "大于5的数个数: " << greater_count << "\n";
}

void demonstrate_lambda_vs_function_objects() {
    std::cout << "\n=== Lambda 表达式 vs 函数对象 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 函数对象方式
    GreaterThan<int> gt5(5);
    int count1 = std::count_if(numbers.begin(), numbers.end(), gt5);
    std::cout << "函数对象方式 - 大于5的数: " << count1 << "\n";
    
    // Lambda 表达式方式
    int threshold = 5;
    auto lambda_gt5 = [threshold](int x) { return x > threshold; };
    int count2 = std::count_if(numbers.begin(), numbers.end(), lambda_gt5);
    std::cout << "Lambda 方式 - 大于5的数: " << count2 << "\n";
    
    // 复杂的状态管理
    std::cout << "\n有状态的处理:\n";
    
    // 函数对象（可以保持状态）
    Accumulator acc;
    std::for_each(numbers.begin(), numbers.end(), std::ref(acc));
    std::cout << "函数对象累积: " << acc.get_sum() << "\n";
    
    // Lambda 表达式（捕获变量）
    int sum = 0;
    std::for_each(numbers.begin(), numbers.end(), [&sum](int x) { sum += x; });
    std::cout << "Lambda 累积: " << sum << "\n";
}

void demonstrate_performance_considerations() {
    std::cout << "\n=== 性能考虑 ===\n";
    
    std::cout << "1. 函数对象通常可以被内联，性能更好\n";
    std::cout << "2. Lambda 表达式本质上是函数对象的语法糖\n";
    std::cout << "3. 避免在函数对象中进行昂贵的操作\n";
    std::cout << "4. 考虑使用 std::function 进行类型擦除时的开销\n";
    
    // 展示 std::function 的使用
    std::function<bool(int)> predicate = IsEven();
    std::vector<int> test{2, 4, 6, 8};
    bool all_even = std::all_of(test.begin(), test.end(), predicate);
    std::cout << "所有数都是偶数: " << (all_even ? "true" : "false") << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 14: 函数对象演示\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_basic_function_objects();
        demonstrate_function_objects_with_algorithms();
        demonstrate_stateful_function_objects();
        demonstrate_standard_function_objects();
        demonstrate_function_adapters();
        demonstrate_lambda_vs_function_objects();
        demonstrate_performance_considerations();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 