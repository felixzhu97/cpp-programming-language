/**
 * @file lambda_expressions.cpp
 * @brief Lambda 表达式高级演示 - 捕获、泛型 lambda、实用技巧
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <string>
#include <memory>
#include <numeric>

void demonstrate_basic_lambdas() {
    std::cout << "\n=== 基本 Lambda 表达式 ===\n";
    
    // 最简单的 lambda
    auto simple = []() { 
        std::cout << "Hello from lambda!\n"; 
    };
    simple();
    
    // 带参数的 lambda
    auto add = [](int a, int b) { 
        return a + b; 
    };
    std::cout << "add(3, 4) = " << add(3, 4) << "\n";
    
    // 带返回类型的 lambda
    auto divide = [](double a, double b) -> double {
        if (b != 0) return a / b;
        throw std::invalid_argument("除零错误");
    };
    std::cout << "divide(10.0, 3.0) = " << divide(10.0, 3.0) << "\n";
    
    // 在算法中使用 lambda
    std::vector<int> numbers{5, 2, 8, 1, 9, 3};
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a > b;  // 降序排序
    });
    
    std::cout << "降序排序: ";
    for (int x : numbers) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_capture_by_value() {
    std::cout << "\n=== 按值捕获 ===\n";
    
    int multiplier = 10;
    std::string prefix = "结果: ";
    
    // 按值捕获单个变量
    auto multiply_by_value = [multiplier](int x) {
        return x * multiplier;
    };
    
    std::cout << "multiply_by_value(5) = " << multiply_by_value(5) << "\n";
    
    // 修改外部变量不影响 lambda 内部的副本
    multiplier = 20;
    std::cout << "修改 multiplier 后: multiply_by_value(5) = " 
              << multiply_by_value(5) << "\n";
    
    // 按值捕获多个变量
    auto format_result = [prefix, multiplier](int x) {
        return prefix + std::to_string(x * multiplier);
    };
    
    std::cout << format_result(3) << "\n";
    
    // 按值捕获所有变量
    int base = 100;
    auto capture_all = [=](int x) {
        return prefix + std::to_string(base + multiplier * x);
    };
    
    std::cout << capture_all(2) << "\n";
}

void demonstrate_capture_by_reference() {
    std::cout << "\n=== 按引用捕获 ===\n";
    
    int counter = 0;
    std::vector<int> results;
    
    // 按引用捕获单个变量
    auto increment_counter = [&counter]() {
        return ++counter;
    };
    
    std::cout << "计数器: " << increment_counter() << "\n";
    std::cout << "计数器: " << increment_counter() << "\n";
    std::cout << "外部计数器值: " << counter << "\n";
    
    // 按引用捕获多个变量
    auto add_to_results = [&counter, &results](int value) {
        results.push_back(counter + value);
        counter++;
    };
    
    add_to_results(10);
    add_to_results(20);
    add_to_results(30);
    
    std::cout << "结果向量: ";
    for (int x : results) std::cout << x << " ";
    std::cout << "\n计数器最终值: " << counter << "\n";
    
    // 按引用捕获所有变量
    std::string message = "当前状态";
    auto print_status = [&]() {
        std::cout << message << ": counter=" << counter 
                  << ", results_size=" << results.size() << "\n";
    };
    
    print_status();
}

void demonstrate_mixed_capture() {
    std::cout << "\n=== 混合捕获 ===\n";
    
    int x = 10;
    int y = 20;
    std::string name = "测试";
    
    // 混合捕获：x 按值，y 按引用
    auto mixed = [x, &y, name](int delta) {
        y += delta;  // 修改外部的 y
        return name + ": x=" + std::to_string(x) + ", y=" + std::to_string(y);
    };
    
    std::cout << "调用前 y = " << y << "\n";
    std::cout << mixed(5) << "\n";
    std::cout << "调用后 y = " << y << "\n";
    
    // 广义捕获（C++14）
    auto generalized = [value = x * 2, &ref = y](int add) {
        ref += add;
        return value + ref;
    };
    
    std::cout << "广义捕获结果: " << generalized(3) << "\n";
    std::cout << "最终 y = " << y << "\n";
}

void demonstrate_mutable_lambdas() {
    std::cout << "\n=== 可变 Lambda ===\n";
    
    int captured_value = 100;
    
    // 不使用 mutable（编译错误）
    // auto non_mutable = [captured_value]() {
    //     captured_value++;  // 错误：不能修改按值捕获的变量
    //     return captured_value;
    // };
    
    // 使用 mutable
    auto mutable_lambda = [captured_value](int delta) mutable {
        captured_value += delta;  // 可以修改捕获的副本
        return captured_value;
    };
    
    std::cout << "第一次调用: " << mutable_lambda(10) << "\n";
    std::cout << "第二次调用: " << mutable_lambda(20) << "\n";
    std::cout << "外部变量未变: " << captured_value << "\n";
    
    // 实际应用：状态累积器
    auto accumulator = [sum = 0](int value) mutable {
        sum += value;
        return sum;
    };
    
    std::vector<int> values{1, 2, 3, 4, 5};
    std::cout << "累积过程: ";
    for (int val : values) {
        std::cout << accumulator(val) << " ";
    }
    std::cout << "\n";
}

void demonstrate_generic_lambdas() {
    std::cout << "\n=== 泛型 Lambda (C++14) ===\n";
    
    // 泛型 lambda
    auto generic_add = [](auto a, auto b) {
        return a + b;
    };
    
    std::cout << "int + int: " << generic_add(3, 4) << "\n";
    std::cout << "double + double: " << generic_add(3.14, 2.86) << "\n";
    std::cout << "string + string: " << generic_add(std::string("Hello "), std::string("World")) << "\n";
    
    // 更复杂的泛型 lambda
    auto print_pair = [](const auto& first, const auto& second) {
        std::cout << "(" << first << ", " << second << ")\n";
    };
    
    print_pair(1, 2);
    print_pair("key", "value");
    print_pair(3.14, true);
    
    // 在算法中使用泛型 lambda
    std::vector<std::string> words{"apple", "banana", "cherry"};
    std::vector<size_t> lengths(words.size());
    
    std::transform(words.begin(), words.end(), lengths.begin(),
                  [](const auto& str) { return str.length(); });
    
    std::cout << "字符串长度: ";
    for (size_t len : lengths) std::cout << len << " ";
    std::cout << "\n";
}

void demonstrate_lambda_with_algorithms() {
    std::cout << "\n=== Lambda 与 STL 算法 ===\n";
    
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // 查找第一个偶数
    auto even_it = std::find_if(numbers.begin(), numbers.end(),
                               [](int x) { return x % 2 == 0; });
    if (even_it != numbers.end()) {
        std::cout << "第一个偶数: " << *even_it << "\n";
    }
    
    // 计算满足条件的元素数量
    int count_gt_5 = std::count_if(numbers.begin(), numbers.end(),
                                  [](int x) { return x > 5; });
    std::cout << "大于5的数字个数: " << count_gt_5 << "\n";
    
    // 变换元素
    std::vector<int> squares(numbers.size());
    std::transform(numbers.begin(), numbers.end(), squares.begin(),
                  [](int x) { return x * x; });
    
    std::cout << "平方数: ";
    for (int sq : squares) std::cout << sq << " ";
    std::cout << "\n";
    
    // 累积操作
    int sum = std::accumulate(numbers.begin(), numbers.end(), 0,
                             [](int acc, int x) { return acc + x * x; });
    std::cout << "平方和: " << sum << "\n";
    
    // 分区操作
    std::vector<int> data = numbers;  // 复制数据
    auto partition_point = std::partition(data.begin(), data.end(),
                                         [](int x) { return x % 2 == 0; });
    
    std::cout << "分区后（偶数在前）: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_lambda_recursion() {
    std::cout << "\n=== Lambda 递归 ===\n";
    
    // 使用 std::function 实现递归 lambda
    std::function<int(int)> factorial = [&factorial](int n) -> int {
        return n <= 1 ? 1 : n * factorial(n - 1);
    };
    
    std::cout << "5! = " << factorial(5) << "\n";
    
    // 斐波那契数列
    std::function<int(int)> fibonacci = [&fibonacci](int n) -> int {
        return n <= 1 ? n : fibonacci(n - 1) + fibonacci(n - 2);
    };
    
    std::cout << "斐波那契数列前10项: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << fibonacci(i) << " ";
    }
    std::cout << "\n";
}

void demonstrate_lambda_utilities() {
    std::cout << "\n=== Lambda 实用技巧 ===\n";
    
    // IIFE (Immediately Invoked Function Expression)
    auto result = [](int x, int y) {
        std::cout << "立即执行的 lambda\n";
        return x * y + 10;
    }(3, 4);
    std::cout << "IIFE 结果: " << result << "\n";
    
    // Lambda 作为初始化器
    auto complex_init = []{
        std::vector<int> vec;
        for (int i = 0; i < 5; ++i) {
            vec.push_back(i * i);
        }
        return vec;
    }();
    
    std::cout << "复杂初始化结果: ";
    for (int x : complex_init) std::cout << x << " ";
    std::cout << "\n";
    
    // 条件编译的 lambda
    auto debug_print = [](const auto& msg) {
        #ifdef DEBUG
        std::cout << "DEBUG: " << msg << "\n";
        #else
        // 在非调试模式下什么都不做
        #endif
    };
    
    debug_print("这是调试信息");
    
    // Lambda 作为比较器
    std::vector<std::pair<std::string, int>> people{
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}
    };
    
    // 按年龄排序
    std::sort(people.begin(), people.end(),
             [](const auto& a, const auto& b) {
                 return a.second < b.second;
             });
    
    std::cout << "按年龄排序: ";
    for (const auto& person : people) {
        std::cout << "(" << person.first << "," << person.second << ") ";
    }
    std::cout << "\n";
}

void demonstrate_lambda_performance() {
    std::cout << "\n=== Lambda 性能考虑 ===\n";
    
    std::cout << "1. Lambda 通常会被内联，性能很好\n";
    std::cout << "2. 避免捕获大对象，优先使用引用\n";
    std::cout << "3. 注意 std::function 的开销\n";
    std::cout << "4. 简单的 lambda 比函数指针快\n";
    
    // 示例：避免不必要的拷贝
    std::vector<std::string> large_strings(1000, "This is a large string");
    
    // 不好：按值捕获大容器
    // auto bad_lambda = [large_strings](int index) {
    //     return large_strings[index];
    // };
    
    // 好：按引用捕获
    auto good_lambda = [&large_strings](int index) {
        return large_strings[index];
    };
    
    std::cout << "良好的捕获方式: " << good_lambda(0).substr(0, 10) << "...\n";
}

int main() {
    std::cout << "C++ Primer Chapter 14: Lambda 表达式高级演示\n";
    std::cout << "==========================================\n";
    
    try {
        demonstrate_basic_lambdas();
        demonstrate_capture_by_value();
        demonstrate_capture_by_reference();
        demonstrate_mixed_capture();
        demonstrate_mutable_lambdas();
        demonstrate_generic_lambdas();
        demonstrate_lambda_with_algorithms();
        demonstrate_lambda_recursion();
        demonstrate_lambda_utilities();
        demonstrate_lambda_performance();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 