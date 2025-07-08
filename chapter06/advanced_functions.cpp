#include "common.h"
#include <functional>

// 1. Lambda表达式详解
void lambda_examples() {
    cout << "=== Lambda表达式详解 ===" << endl;
    
    // 基本lambda
    auto add = [](int a, int b) { return a + b; };
    cout << "基本lambda: add(5, 3) = " << add(5, 3) << endl;
    
    // 捕获外部变量
    int multiplier = 10;
    auto multiply_by_factor = [multiplier](int x) { return x * multiplier; };
    cout << "值捕获: multiply_by_factor(5) = " << multiply_by_factor(5) << endl;
    
    // 引用捕获
    int counter = 0;
    auto increment = [&counter]() { return ++counter; };
    cout << "引用捕获前: counter = " << counter << endl;
    cout << "increment() = " << increment() << endl;
    cout << "increment() = " << increment() << endl;
    cout << "引用捕获后: counter = " << counter << endl;
    
    // 混合捕获
    int base = 100;
    auto mixed_capture = [base, &counter](int x) mutable {
        base += x;  // mutable允许修改值捕获的变量
        counter += x;
        return base + counter;
    };
    cout << "混合捕获: mixed_capture(5) = " << mixed_capture(5) << endl;
    cout << "counter现在是: " << counter << endl;
    
    // 泛型lambda (C++14)
    auto generic_add = [](auto a, auto b) { return a + b; };
    cout << "泛型lambda: generic_add(1, 2) = " << generic_add(1, 2) << endl;
    cout << "泛型lambda: generic_add(1.5, 2.3) = " << generic_add(1.5, 2.3) << endl;
    
    // 立即调用lambda
    int result = [](int x) { return x * x; }(7);
    cout << "立即调用lambda: " << result << endl;
    
    // 递归lambda
    function<int(int)> factorial = [&factorial](int n) -> int {
        return (n <= 1) ? 1 : n * factorial(n - 1);
    };
    cout << "递归lambda: factorial(5) = " << factorial(5) << endl;
}

// 2. std::function详解
void std_function_examples() {
    cout << "\n=== std::function详解 ===" << endl;
    
    // 存储不同类型的可调用对象
    vector<function<int(int, int)>> operations;
    
    // 普通函数
    operations.push_back([](int a, int b) { return a + b; });
    
    // lambda表达式
    operations.push_back([](int a, int b) { return a - b; });
    
    // 函数对象
    struct Multiplier {
        int operator()(int a, int b) const { return a * b; }
    };
    operations.push_back(Multiplier{});
    
    // 成员函数（通过bind）
    class Calculator {
    public:
        int divide(int a, int b) const { return b != 0 ? a / b : 0; }
    };
    
    Calculator calc;
    operations.push_back(bind(&Calculator::divide, &calc, placeholders::_1, placeholders::_2));
    
    // 执行所有操作
    string names[] = {"加法", "减法", "乘法", "除法"};
    for (size_t i = 0; i < operations.size(); i++) {
        cout << names[i] << ": 12, 3 = " << operations[i](12, 3) << endl;
    }
    
    // 条件回调
    function<void(const string&)> logger;
    
    bool debug_mode = true;
    if (debug_mode) {
        logger = [](const string& msg) { cout << "DEBUG: " << msg << endl; };
    } else {
        logger = [](const string& msg) { cout << "INFO: " << msg << endl; };
    }
    
    logger("这是一条日志消息");
}

// 3. 函数式编程技术
template<typename Container, typename Predicate>
auto filter(const Container& container, Predicate pred) {
    Container result;
    for (const auto& item : container) {
        if (pred(item)) {
            result.push_back(item);
        }
    }
    return result;
}

template<typename Container, typename Transform>
auto map(const Container& container, Transform transform) {
    vector<decltype(transform(*container.begin()))> result;
    for (const auto& item : container) {
        result.push_back(transform(item));
    }
    return result;
}

template<typename Container, typename Accumulator, typename BinaryOp>
auto reduce(const Container& container, Accumulator init, BinaryOp op) {
    auto result = init;
    for (const auto& item : container) {
        result = op(result, item);
    }
    return result;
}

void functional_programming_examples() {
    cout << "\n=== 函数式编程技术 ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    cout << "原始数组: ";
    for (int n : numbers) cout << n << " ";
    cout << endl;
    
    // Filter: 过滤偶数
    auto evens = filter(numbers, [](int n) { return n % 2 == 0; });
    cout << "偶数: ";
    for (int n : evens) cout << n << " ";
    cout << endl;
    
    // Map: 平方
    auto squares = map(numbers, [](int n) { return n * n; });
    cout << "平方: ";
    for (int n : squares) cout << n << " ";
    cout << endl;
    
    // Reduce: 求和
    auto sum = reduce(numbers, 0, [](int acc, int n) { return acc + n; });
    cout << "求和: " << sum << endl;
    
    // 链式操作
    auto result = reduce(
        map(
            filter(numbers, [](int n) { return n % 2 == 1; }),  // 奇数
            [](int n) { return n * n; }                         // 平方
        ),
        0,
        [](int acc, int n) { return acc + n; }                 // 求和
    );
    cout << "奇数平方和: " << result << endl;
}

// 4. 高阶函数
template<typename Func>
auto curry(Func func) {
    return [func](auto first) {
        return [func, first](auto... rest) {
            return func(first, rest...);
        };
    };
}

template<typename Func1, typename Func2>
auto compose(Func1 f, Func2 g) {
    return [f, g](auto x) {
        return f(g(x));
    };
}

template<typename Func>
auto memoize(Func func) {
    return [func](auto... args) mutable {
        static map<tuple<decltype(args)...>, decltype(func(args...))> cache;
        
        auto key = make_tuple(args...);
        if (cache.find(key) != cache.end()) {
            cout << "  从缓存获取结果" << endl;
            return cache[key];
        }
        
        cout << "  计算新结果" << endl;
        auto result = func(args...);
        cache[key] = result;
        return result;
    };
}

void higher_order_functions() {
    cout << "\n=== 高阶函数 ===" << endl;
    
    // 柯里化
    auto add = [](int a, int b, int c) { return a + b + c; };
    auto curried_add = curry(add);
    auto add_5 = curried_add(5);
    auto add_5_3 = add_5(3);
    
    cout << "柯里化: curried_add(5)(3)(2) = " << add_5_3(2) << endl;
    
    // 函数组合
    auto square = [](int x) { return x * x; };
    auto add_one = [](int x) { return x + 1; };
    auto square_then_add_one = compose(add_one, square);
    auto add_one_then_square = compose(square, add_one);
    
    cout << "组合函数1: square_then_add_one(3) = " << square_then_add_one(3) << endl;
    cout << "组合函数2: add_one_then_square(3) = " << add_one_then_square(3) << endl;
    
    // 记忆化
    function<long long(int)> fib = [](int n) -> long long {
        if (n <= 1) return n;
        return fib(n - 1) + fib(n - 2);
    };
    
    auto memo_fib = memoize([](int n) -> long long {
        function<long long(int)> fib_impl = [](int n) -> long long {
            if (n <= 1) return n;
            return fib_impl(n - 1) + fib_impl(n - 2);
        };
        return fib_impl(n);
    });
    
    cout << "记忆化斐波那契:" << endl;
    cout << "memo_fib(10) = " << memo_fib(10) << endl;
    cout << "memo_fib(10) = " << memo_fib(10) << endl;  // 从缓存获取
}

// 5. 异步函数和future
void async_functions() {
    cout << "\n=== 异步函数和future ===" << endl;
    
    // 异步执行函数
    auto long_computation = [](int n) {
        this_thread::sleep_for(chrono::milliseconds(100));
        return n * n;
    };
    
    cout << "启动异步计算..." << endl;
    auto future1 = async(launch::async, long_computation, 5);
    auto future2 = async(launch::async, long_computation, 7);
    auto future3 = async(launch::async, long_computation, 9);
    
    cout << "等待结果..." << endl;
    cout << "5^2 = " << future1.get() << endl;
    cout << "7^2 = " << future2.get() << endl;
    cout << "9^2 = " << future3.get() << endl;
    
    // 使用promise和future
    promise<int> prom;
    future<int> fut = prom.get_future();
    
    thread producer([&prom]() {
        this_thread::sleep_for(chrono::milliseconds(100));
        prom.set_value(42);
    });
    
    cout << "等待producer线程..." << endl;
    cout << "producer结果: " << fut.get() << endl;
    
    producer.join();
}

// 6. 可变参数模板函数
template<typename T>
void print_args(T&& t) {
    cout << t << endl;
}

template<typename T, typename... Args>
void print_args(T&& t, Args&&... args) {
    cout << t << " ";
    print_args(args...);
}

template<typename... Args>
auto sum_all(Args... args) {
    return (args + ...);  // C++17折叠表达式
}

template<typename... Args>
void call_all(Args... functions) {
    (functions(), ...);  // C++17折叠表达式
}

void variadic_templates() {
    cout << "\n=== 可变参数模板函数 ===" << endl;
    
    cout << "打印多个参数: ";
    print_args(1, 2.5, "hello", 'c');
    
    cout << "求和: sum_all(1, 2, 3, 4, 5) = " << sum_all(1, 2, 3, 4, 5) << endl;
    
    cout << "调用多个函数:" << endl;
    call_all(
        []() { cout << "  函数1执行" << endl; },
        []() { cout << "  函数2执行" << endl; },
        []() { cout << "  函数3执行" << endl; }
    );
}

// 7. SFINAE和概念
template<typename T>
typename enable_if<is_integral<T>::value, T>::type
safe_divide(T a, T b) {
    cout << "  整数除法: ";
    return b != 0 ? a / b : 0;
}

template<typename T>
typename enable_if<is_floating_point<T>::value, T>::type
safe_divide(T a, T b) {
    cout << "  浮点除法: ";
    return b != 0.0 ? a / b : 0.0;
}

// C++20 概念 (如果支持)
#if __cplusplus >= 202002L
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric T>
T concept_safe_divide(T a, T b) {
    cout << "  概念约束除法: ";
    return b != 0 ? a / b : 0;
}
#endif

void sfinae_concepts() {
    cout << "\n=== SFINAE和概念 ===" << endl;
    
    cout << "SFINAE示例:" << endl;
    cout << "safe_divide(10, 3) = " << safe_divide(10, 3) << endl;
    cout << "safe_divide(10.0, 3.0) = " << safe_divide(10.0, 3.0) << endl;
    
#if __cplusplus >= 202002L
    cout << "\nC++20概念示例:" << endl;
    cout << "concept_safe_divide(15, 4) = " << concept_safe_divide(15, 4) << endl;
#else
    cout << "\nC++20概念需要更新的编译器支持" << endl;
#endif
}

// 8. 函数对象和仿函数
class Accumulator {
private:
    int total;
    
public:
    Accumulator(int init = 0) : total(init) {}
    
    int operator()(int value) {
        total += value;
        return total;
    }
    
    int get_total() const { return total; }
};

template<typename Op>
class BinaryOperation {
private:
    Op operation;
    
public:
    BinaryOperation(Op op) : operation(op) {}
    
    template<typename T>
    auto operator()(T a, T b) -> decltype(operation(a, b)) {
        return operation(a, b);
    }
};

void function_objects() {
    cout << "\n=== 函数对象和仿函数 ===" << endl;
    
    Accumulator acc(10);
    cout << "累加器初值: " << acc.get_total() << endl;
    cout << "acc(5) = " << acc(5) << ", 总计: " << acc.get_total() << endl;
    cout << "acc(3) = " << acc(3) << ", 总计: " << acc.get_total() << endl;
    cout << "acc(7) = " << acc(7) << ", 总计: " << acc.get_total() << endl;
    
    // 泛型函数对象
    auto multiply_op = [](auto a, auto b) { return a * b; };
    BinaryOperation multiply(multiply_op);
    
    cout << "\n泛型函数对象:" << endl;
    cout << "multiply(3, 4) = " << multiply(3, 4) << endl;
    cout << "multiply(2.5, 3.0) = " << multiply(2.5, 3.0) << endl;
}

// 9. 完美转发
template<typename Func, typename... Args>
auto perfect_forward(Func&& func, Args&&... args) 
    -> decltype(func(forward<Args>(args)...)) {
    cout << "  完美转发调用" << endl;
    return func(forward<Args>(args)...);
}

void perfect_forwarding() {
    cout << "\n=== 完美转发 ===" << endl;
    
    auto test_func = [](const string& s) {
        cout << "  接收到字符串: " << s << endl;
        return s.length();
    };
    
    string str = "Hello World";
    cout << "完美转发结果: " << perfect_forward(test_func, str) << endl;
    cout << "完美转发结果: " << perfect_forward(test_func, "Temporary") << endl;
}

// 10. 实际应用：事件系统
class EventManager {
private:
    map<string, vector<function<void(const string&)>>> handlers;
    
public:
    void subscribe(const string& event, function<void(const string&)> handler) {
        handlers[event].push_back(handler);
    }
    
    void publish(const string& event, const string& data) {
        cout << "发布事件: " << event << " 数据: " << data << endl;
        if (handlers.find(event) != handlers.end()) {
            for (auto& handler : handlers[event]) {
                handler(data);
            }
        }
    }
    
    template<typename... Args>
    void subscribe_multiple(const string& event, Args... handlers) {
        (subscribe(event, handlers), ...);
    }
};

void practical_event_system() {
    cout << "\n=== 实际应用：事件系统 ===" << endl;
    
    EventManager em;
    
    // 订阅事件
    em.subscribe("user_login", [](const string& data) {
        cout << "  日志处理器: 用户登录 - " << data << endl;
    });
    
    em.subscribe("user_login", [](const string& data) {
        cout << "  统计处理器: 记录登录统计 - " << data << endl;
    });
    
    em.subscribe("user_login", [](const string& data) {
        cout << "  安全处理器: 检查登录安全 - " << data << endl;
    });
    
    // 一次订阅多个处理器
    em.subscribe_multiple("user_logout",
        [](const string& data) { cout << "  清理会话: " << data << endl; },
        [](const string& data) { cout << "  更新状态: " << data << endl; }
    );
    
    // 发布事件
    em.publish("user_login", "user123");
    em.publish("user_logout", "user123");
}

int main() {
    print_separator("高级函数特性详解");
    
    // 1. Lambda表达式
    lambda_examples();
    
    // 2. std::function
    std_function_examples();
    
    // 3. 函数式编程
    functional_programming_examples();
    
    // 4. 高阶函数
    higher_order_functions();
    
    // 5. 异步函数
    async_functions();
    
    // 6. 可变参数模板
    variadic_templates();
    
    // 7. SFINAE和概念
    sfinae_concepts();
    
    // 8. 函数对象
    function_objects();
    
    // 9. 完美转发
    perfect_forwarding();
    
    // 10. 实际应用
    practical_event_system();
    
    // 总结：高级函数特性的优势
    cout << "\n=== 高级函数特性总结 ===" << endl;
    cout << "1. Lambda表达式:" << endl;
    cout << "   - 简洁的就地函数定义" << endl;
    cout << "   - 灵活的变量捕获机制" << endl;
    cout << "   - 支持泛型和模板特性" << endl;
    
    cout << "\n2. std::function:" << endl;
    cout << "   - 统一的可调用对象接口" << endl;
    cout << "   - 类型擦除技术" << endl;
    cout << "   - 支持函数指针、lambda、仿函数" << endl;
    
    cout << "\n3. 函数式编程:" << endl;
    cout << "   - 不可变性和纯函数" << endl;
    cout << "   - 高阶函数和函数组合" << endl;
    cout << "   - 声明式编程风格" << endl;
    
    cout << "\n4. 模板元编程:" << endl;
    cout << "   - 编译时计算和优化" << endl;
    cout << "   - 类型安全的泛型编程" << endl;
    cout << "   - SFINAE和概念约束" << endl;
    
    cout << "\n5. 异步编程:" << endl;
    cout << "   - 并发和并行执行" << endl;
    cout << "   - future和promise模式" << endl;
    cout << "   - 非阻塞式编程" << endl;
    
    // 最佳实践建议
    cout << "\n=== 最佳实践建议 ===" << endl;
    cout << "1. 适度使用lambda，避免过度复杂" << endl;
    cout << "2. 优先使用标准库算法而不是手写循环" << endl;
    cout << "3. 合理使用函数式编程提高代码可读性" << endl;
    cout << "4. 注意性能开销，特别是std::function" << endl;
    cout << "5. 利用编译器优化和内联" << endl;
    cout << "6. 保持函数的单一职责原则" << endl;
    cout << "7. 使用类型推导减少冗余代码" << endl;
    cout << "8. 在合适场景使用异步编程" << endl;
    cout << "9. 文档化复杂的函数接口" << endl;
    cout << "10. 持续学习新的C++标准特性" << endl;
    
    print_separator("高级函数特性详解完成");
    
    return 0;
} 