#include "common.h"
#include <functional>

// 1. 基本函数定义
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}

int divide(int a, int b) {
    if (b != 0) {
        return a / b;
    }
    return 0;
}

// 2. 不同签名的函数
void print_int(int value) {
    cout << "整数: " << value << endl;
}

void print_double(double value) {
    cout << "浮点数: " << value << endl;
}

bool is_even(int n) {
    return n % 2 == 0;
}

bool is_positive(int n) {
    return n > 0;
}

// 3. 接受函数指针作为参数的函数
int apply_operation(int a, int b, int (*operation)(int, int)) {
    return operation(a, b);
}

void print_result(int value, void (*printer)(int)) {
    printer(value);
}

bool test_condition(int value, bool (*predicate)(int)) {
    return predicate(value);
}

// 4. 返回函数指针的函数
int (*get_operation(char op))(int, int) {
    switch (op) {
        case '+': return add;
        case '-': return subtract;
        case '*': return multiply;
        case '/': return divide;
        default: return nullptr;
    }
}

// 5. 类成员函数指针
class Calculator {
public:
    int add(int a, int b) {
        cout << "  Calculator::add(" << a << ", " << b << ") = ";
        return a + b;
    }
    
    int multiply(int a, int b) {
        cout << "  Calculator::multiply(" << a << ", " << b << ") = ";
        return a * b;
    }
    
    static int static_add(int a, int b) {
        cout << "  Calculator::static_add(" << a << ", " << b << ") = ";
        return a + b;
    }
    
    void print_value(int value) {
        cout << "  Calculator打印值: " << value << endl;
    }
};

// 6. 函数对象（仿函数）
class Adder {
private:
    int offset;
    
public:
    Adder(int offset) : offset(offset) {}
    
    int operator()(int value) {
        return value + offset;
    }
};

class Multiplier {
private:
    int factor;
    
public:
    Multiplier(int factor) : factor(factor) {}
    
    int operator()(int value) {
        return value * factor;
    }
};

// 7. 高阶函数
template<typename Func>
void apply_to_array(int arr[], int size, Func func) {
    cout << "  应用函数到数组: ";
    for (int i = 0; i < size; i++) {
        cout << func(arr[i]) << " ";
    }
    cout << endl;
}

template<typename Func>
int reduce_array(int arr[], int size, int initial, Func func) {
    int result = initial;
    for (int i = 0; i < size; i++) {
        result = func(result, arr[i]);
    }
    return result;
}

// 8. 回调函数示例
typedef void (*ProgressCallback)(int current, int total);

void long_running_task(int steps, ProgressCallback callback) {
    cout << "开始长时间运行的任务..." << endl;
    
    for (int i = 1; i <= steps; i++) {
        // 模拟工作
        this_thread::sleep_for(chrono::milliseconds(100));
        
        // 调用回调函数报告进度
        if (callback) {
            callback(i, steps);
        }
    }
    
    cout << "任务完成!" << endl;
}

void progress_printer(int current, int total) {
    int percentage = (current * 100) / total;
    cout << "  进度: " << current << "/" << total 
         << " (" << percentage << "%)" << endl;
}

// 9. 事件处理系统
enum class EventType {
    CLICK,
    KEY_PRESS,
    MOUSE_MOVE
};

typedef void (*EventHandler)(EventType type, int data);

class EventSystem {
private:
    map<EventType, vector<EventHandler>> handlers;
    
public:
    void register_handler(EventType type, EventHandler handler) {
        handlers[type].push_back(handler);
    }
    
    void trigger_event(EventType type, int data) {
        cout << "触发事件: ";
        switch (type) {
            case EventType::CLICK: cout << "CLICK"; break;
            case EventType::KEY_PRESS: cout << "KEY_PRESS"; break;
            case EventType::MOUSE_MOVE: cout << "MOUSE_MOVE"; break;
        }
        cout << " (数据: " << data << ")" << endl;
        
        if (handlers.find(type) != handlers.end()) {
            for (auto handler : handlers[type]) {
                handler(type, data);
            }
        }
    }
};

void click_handler(EventType type, int data) {
    cout << "  点击处理器: 按钮 " << data << " 被点击" << endl;
}

void key_handler(EventType type, int data) {
    cout << "  按键处理器: 键码 " << data << " 被按下" << endl;
}

void mouse_handler(EventType type, int data) {
    cout << "  鼠标处理器: 移动到位置 " << data << endl;
}

// 10. 函数指针数组和查找表
enum class Operation {
    ADD = 0,
    SUBTRACT = 1,
    MULTIPLY = 2,
    DIVIDE = 3
};

class OperationTable {
private:
    static int (*operations[])(int, int);
    static const char* names[];
    
public:
    static int execute(Operation op, int a, int b) {
        int index = static_cast<int>(op);
        if (index >= 0 && index < 4) {
            cout << "  执行操作 " << names[index] << "(" << a << ", " << b << ") = ";
            return operations[index](a, b);
        }
        return 0;
    }
    
    static const char* get_name(Operation op) {
        int index = static_cast<int>(op);
        if (index >= 0 && index < 4) {
            return names[index];
        }
        return "Unknown";
    }
};

// 静态成员定义
int (*OperationTable::operations[])(int, int) = {add, subtract, multiply, divide};
const char* OperationTable::names[] = {"加法", "减法", "乘法", "除法"};

// 11. 排序算法与比较函数
void bubble_sort(int arr[], int size, bool (*compare)(int, int)) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (compare(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

bool ascending(int a, int b) {
    return a > b;  // 如果a > b，需要交换（升序）
}

bool descending(int a, int b) {
    return a < b;  // 如果a < b，需要交换（降序）
}

// 12. 策略模式实现
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double calculate_price(double base_price) = 0;
};

class RegularPricing : public PricingStrategy {
public:
    double calculate_price(double base_price) override {
        return base_price;
    }
};

class DiscountPricing : public PricingStrategy {
private:
    double discount_rate;
    
public:
    DiscountPricing(double rate) : discount_rate(rate) {}
    
    double calculate_price(double base_price) override {
        return base_price * (1.0 - discount_rate);
    }
};

// 使用函数指针实现策略模式
typedef double (*PricingFunction)(double);

double regular_pricing(double base_price) {
    return base_price;
}

double discount_pricing(double base_price) {
    return base_price * 0.8;  // 20% 折扣
}

double premium_pricing(double base_price) {
    return base_price * 1.2;  // 20% 溢价
}

// 13. std::function 使用
void demonstrate_std_function() {
    cout << "=== std::function 演示 ===" << endl;
    
    // 存储普通函数
    function<int(int, int)> op1 = add;
    cout << "std::function存储普通函数: " << op1(5, 3) << endl;
    
    // 存储lambda
    function<int(int, int)> op2 = [](int a, int b) { return a * b; };
    cout << "std::function存储lambda: " << op2(5, 3) << endl;
    
    // 存储函数对象
    Multiplier mult(10);
    function<int(int)> op3 = mult;
    cout << "std::function存储函数对象: " << op3(5) << endl;
    
    // 存储成员函数
    Calculator calc;
    function<int(Calculator*, int, int)> op4 = &Calculator::add;
    cout << "std::function存储成员函数: " << op4(&calc, 5, 3) << endl;
    
    // 使用bind
    function<int(int, int)> op5 = bind(&Calculator::add, &calc, placeholders::_1, placeholders::_2);
    cout << "std::function + bind: " << op5(5, 3) << endl;
}

int main() {
    print_separator("函数指针详解");
    
    // 1. 基本函数指针使用
    cout << "=== 基本函数指针使用 ===" << endl;
    
    // 声明函数指针
    int (*operation)(int, int);
    
    // 赋值和调用
    operation = add;
    cout << "使用add函数: 5 + 3 = " << operation(5, 3) << endl;
    
    operation = multiply;
    cout << "使用multiply函数: 5 * 3 = " << operation(5, 3) << endl;
    
    // 函数指针数组
    cout << "\n函数指针数组:" << endl;
    int (*operations[])(int, int) = {add, subtract, multiply, divide};
    string op_names[] = {"加法", "减法", "乘法", "除法"};
    
    for (int i = 0; i < 4; i++) {
        cout << op_names[i] << ": 12, 4 = " << operations[i](12, 4) << endl;
    }
    
    // 2. 函数指针作为参数
    cout << "\n=== 函数指针作为参数 ===" << endl;
    
    cout << "apply_operation(10, 5, add) = " << apply_operation(10, 5, add) << endl;
    cout << "apply_operation(10, 5, multiply) = " << apply_operation(10, 5, multiply) << endl;
    
    print_result(42, print_int);
    
    cout << "test_condition(4, is_even): " << (test_condition(4, is_even) ? "true" : "false") << endl;
    cout << "test_condition(-5, is_positive): " << (test_condition(-5, is_positive) ? "true" : "false") << endl;
    
    // 3. 返回函数指针
    cout << "\n=== 返回函数指针 ===" << endl;
    
    char ops[] = {'+', '-', '*', '/'};
    for (char op : ops) {
        auto func = get_operation(op);
        if (func) {
            cout << "操作 '" << op << "': 8, 2 = " << func(8, 2) << endl;
        }
    }
    
    // 4. 成员函数指针
    cout << "\n=== 成员函数指针 ===" << endl;
    
    Calculator calc;
    
    // 成员函数指针语法
    int (Calculator::*member_func)(int, int) = &Calculator::add;
    cout << (calc.*member_func)(6, 4) << endl;
    
    member_func = &Calculator::multiply;
    cout << (calc.*member_func)(6, 4) << endl;
    
    // 静态成员函数指针
    int (*static_func)(int, int) = &Calculator::static_add;
    cout << static_func(7, 3) << endl;
    
    // 成员函数指针数组
    cout << "\n成员函数指针数组:" << endl;
    int (Calculator::*member_ops[])(int, int) = {&Calculator::add, &Calculator::multiply};
    string member_names[] = {"成员加法", "成员乘法"};
    
    for (int i = 0; i < 2; i++) {
        cout << member_names[i] << ": ";
        cout << (calc.*member_ops[i])(5, 6) << endl;
    }
    
    // 5. 函数对象
    cout << "\n=== 函数对象（仿函数） ===" << endl;
    
    Adder add10(10);
    Multiplier mult5(5);
    
    cout << "add10(20) = " << add10(20) << endl;
    cout << "mult5(7) = " << mult5(7) << endl;
    
    // 函数对象作为参数
    int arr[] = {1, 2, 3, 4, 5};
    cout << "\n对数组应用函数对象:" << endl;
    apply_to_array(arr, 5, add10);
    apply_to_array(arr, 5, mult5);
    
    // 6. 高阶函数
    cout << "\n=== 高阶函数 ===" << endl;
    
    int numbers[] = {1, 2, 3, 4, 5};
    
    // 使用lambda
    apply_to_array(numbers, 5, [](int x) { return x * x; });
    
    // reduce操作
    int sum = reduce_array(numbers, 5, 0, [](int acc, int val) { return acc + val; });
    cout << "数组求和: " << sum << endl;
    
    int product = reduce_array(numbers, 5, 1, [](int acc, int val) { return acc * val; });
    cout << "数组求积: " << product << endl;
    
    // 7. 回调函数
    cout << "\n=== 回调函数 ===" << endl;
    
    long_running_task(5, progress_printer);
    
    // 使用lambda作为回调
    cout << "\n使用lambda回调:" << endl;
    long_running_task(3, [](int current, int total) {
        cout << "  λ 进度更新: " << current << "/" << total << endl;
    });
    
    // 8. 事件处理系统
    cout << "\n=== 事件处理系统 ===" << endl;
    
    EventSystem event_system;
    
    // 注册事件处理器
    event_system.register_handler(EventType::CLICK, click_handler);
    event_system.register_handler(EventType::KEY_PRESS, key_handler);
    event_system.register_handler(EventType::MOUSE_MOVE, mouse_handler);
    
    // 触发事件
    event_system.trigger_event(EventType::CLICK, 1);
    event_system.trigger_event(EventType::KEY_PRESS, 65);  // 'A'
    event_system.trigger_event(EventType::MOUSE_MOVE, 100);
    
    // 9. 操作查找表
    cout << "\n=== 操作查找表 ===" << endl;
    
    Operation ops_enum[] = {Operation::ADD, Operation::SUBTRACT, Operation::MULTIPLY, Operation::DIVIDE};
    
    for (auto op : ops_enum) {
        int result = OperationTable::execute(op, 15, 3);
        cout << result << endl;
    }
    
    // 10. 排序算法与比较函数
    cout << "\n=== 排序算法与比较函数 ===" << endl;
    
    int sort_arr1[] = {64, 34, 25, 12, 22, 11, 90};
    int sort_arr2[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;
    
    cout << "原始数组: ";
    for (int i = 0; i < size; i++) {
        cout << sort_arr1[i] << " ";
    }
    cout << endl;
    
    bubble_sort(sort_arr1, size, ascending);
    cout << "升序排序: ";
    for (int i = 0; i < size; i++) {
        cout << sort_arr1[i] << " ";
    }
    cout << endl;
    
    bubble_sort(sort_arr2, size, descending);
    cout << "降序排序: ";
    for (int i = 0; i < size; i++) {
        cout << sort_arr2[i] << " ";
    }
    cout << endl;
    
    // 11. 策略模式
    cout << "\n=== 策略模式 ===" << endl;
    
    double base_price = 100.0;
    
    // 使用函数指针实现策略模式
    PricingFunction strategies[] = {regular_pricing, discount_pricing, premium_pricing};
    string strategy_names[] = {"常规定价", "折扣定价", "溢价定价"};
    
    for (int i = 0; i < 3; i++) {
        double price = strategies[i](base_price);
        cout << strategy_names[i] << ": $" << price << endl;
    }
    
    // 12. std::function 演示
    demonstrate_std_function();
    
    // 13. 复杂的函数指针应用
    cout << "\n=== 复杂的函数指针应用 ===" << endl;
    
    // 函数指针的typedef
    typedef int (*BinaryOp)(int, int);
    typedef bool (*Predicate)(int);
    
    // 创建一个函数指针映射
    map<string, BinaryOp> op_map;
    op_map["add"] = add;
    op_map["subtract"] = subtract;
    op_map["multiply"] = multiply;
    op_map["divide"] = divide;
    
    cout << "使用函数指针映射:" << endl;
    for (auto& pair : op_map) {
        cout << "  " << pair.first << "(8, 2) = " << pair.second(8, 2) << endl;
    }
    
    // 组合函数
    auto compose = [](BinaryOp f, BinaryOp g) {
        return [f, g](int a, int b, int c) {
            return f(g(a, b), c);
        };
    };
    
    auto add_then_multiply = compose(multiply, add);
    cout << "\n组合函数 multiply(add(3, 4), 2) = " << add_then_multiply(3, 4, 2) << endl;
    
    // 14. 函数指针的实际应用场景
    cout << "\n=== 函数指针的实际应用场景 ===" << endl;
    
    cout << "1. 插件系统: 动态加载和调用函数" << endl;
    cout << "2. 回调机制: 异步编程和事件处理" << endl;
    cout << "3. 策略模式: 运行时选择算法" << endl;
    cout << "4. 函数表: 快速调度和查找" << endl;
    cout << "5. 模板元编程: 编译时函数选择" << endl;
    cout << "6. 函数式编程: 高阶函数和闭包" << endl;
    cout << "7. 状态机: 状态转换函数" << endl;
    cout << "8. 解释器: 指令执行函数" << endl;
    
    // 15. 性能考虑
    cout << "\n=== 性能考虑 ===" << endl;
    
    const int iterations = 1000000;
    
    // 直接函数调用
    auto start = chrono::high_resolution_clock::now();
    int sum1 = 0;
    for (int i = 0; i < iterations; i++) {
        sum1 += add(i, 1);
    }
    auto mid1 = chrono::high_resolution_clock::now();
    
    // 函数指针调用
    BinaryOp func_ptr = add;
    int sum2 = 0;
    for (int i = 0; i < iterations; i++) {
        sum2 += func_ptr(i, 1);
    }
    auto mid2 = chrono::high_resolution_clock::now();
    
    // std::function调用
    function<int(int, int)> std_func = add;
    int sum3 = 0;
    for (int i = 0; i < iterations; i++) {
        sum3 += std_func(i, 1);
    }
    auto end = chrono::high_resolution_clock::now();
    
    auto time1 = chrono::duration_cast<chrono::microseconds>(mid1 - start);
    auto time2 = chrono::duration_cast<chrono::microseconds>(mid2 - mid1);
    auto time3 = chrono::duration_cast<chrono::microseconds>(end - mid2);
    
    cout << "直接调用时间: " << time1.count() << " 微秒" << endl;
    cout << "函数指针时间: " << time2.count() << " 微秒" << endl;
    cout << "std::function时间: " << time3.count() << " 微秒" << endl;
    
    // 16. 最佳实践
    cout << "\n=== 函数指针最佳实践 ===" << endl;
    cout << "1. 使用typedef简化函数指针类型声明" << endl;
    cout << "2. 优先使用std::function而不是原始函数指针" << endl;
    cout << "3. 检查函数指针是否为nullptr" << endl;
    cout << "4. 考虑使用lambda表达式代替简单函数" << endl;
    cout << "5. 成员函数指针需要对象实例" << endl;
    cout << "6. 注意函数指针的性能开销" << endl;
    cout << "7. 使用auto推导复杂的函数指针类型" << endl;
    cout << "8. 结合模板使用函数指针增强灵活性" << endl;
    cout << "9. 在多线程环境中注意函数指针的安全性" << endl;
    cout << "10. 文档化函数指针的预期行为" << endl;
    
    print_separator("函数指针详解完成");
    
    return 0;
} 