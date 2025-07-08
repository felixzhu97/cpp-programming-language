#include "common.h"

// 递归函数示例
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// 尾递归优化版本
int fibonacciTail(int n, int a = 0, int b = 1) {
    if (n == 0) return a;
    if (n == 1) return b;
    return fibonacciTail(n - 1, b, a + b);
}

// 函数指针示例
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }
int subtract(int a, int b) { return a - b; }

int main() {
    print_separator("高级控制流示例");
    
    // 递归控制流
    cout << "=== 递归控制流 ===" << endl;
    
    cout << "1. 基本递归 - 斐波那契数列:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "F(" << i << ") = " << fibonacci(i) << endl;
    }
    
    cout << "\n2. 尾递归优化版本:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "F(" << i << ") = " << fibonacciTail(i) << endl;
    }
    
    // 阶乘递归
    cout << "\n3. 阶乘递归:" << endl;
    function<int(int)> factorial = [&](int n) -> int {
        if (n <= 1) return 1;
        return n * factorial(n - 1);
    };
    
    for (int i = 1; i <= 6; i++) {
        cout << i << "! = " << factorial(i) << endl;
    }
    
    // 函数指针和回调
    cout << "\n=== 函数指针和回调 ===" << endl;
    
    // 函数指针数组
    int (*operations[])(int, int) = {add, multiply, subtract};
    string op_names[] = {"加法", "乘法", "减法"};
    
    int a = 10, b = 3;
    cout << "操作数: a = " << a << ", b = " << b << endl;
    
    for (int i = 0; i < 3; i++) {
        int result = operations[i](a, b);
        cout << op_names[i] << ": " << result << endl;
    }
    
    // 回调函数示例
    cout << "\n回调函数示例:" << endl;
    
    auto processArray = [](const vector<int>& arr, function<void(int)> callback) {
        cout << "处理数组:" << endl;
        for (int val : arr) {
            callback(val);
        }
    };
    
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // 使用lambda作为回调
    processArray(numbers, [](int x) {
        cout << "处理元素: " << x << ", 平方: " << x * x << endl;
    });
    
    // Lambda表达式
    cout << "\n=== Lambda表达式 ===" << endl;
    
    // 基本lambda
    cout << "1. 基本lambda表达式:" << endl;
    auto square = [](int x) { return x * x; };
    cout << "5的平方: " << square(5) << endl;
    
    // 捕获变量
    cout << "\n2. 捕获变量:" << endl;
    int multiplier = 3;
    
    // 按值捕获
    auto multiplyByValue = [multiplier](int x) { return x * multiplier; };
    
    // 按引用捕获
    auto multiplyByRef = [&multiplier](int x) { return x * multiplier; };
    
    cout << "按值捕获: 4 * " << multiplier << " = " << multiplyByValue(4) << endl;
    
    multiplier = 5;
    cout << "修改multiplier后:" << endl;
    cout << "按值捕获: 4 * " << multiplier << " = " << multiplyByValue(4) << " (仍使用旧值3)" << endl;
    cout << "按引用捕获: 4 * " << multiplier << " = " << multiplyByRef(4) << " (使用新值5)" << endl;
    
    // 捕获所有变量
    cout << "\n3. 捕获所有变量:" << endl;
    int x = 10, y = 20;
    
    auto captureAll = [=]() { return x + y; };  // 按值捕获所有
    auto captureAllRef = [&]() { return x + y; };  // 按引用捕获所有
    
    cout << "原始值: x = " << x << ", y = " << y << endl;
    cout << "按值捕获所有: " << captureAll() << endl;
    cout << "按引用捕获所有: " << captureAllRef() << endl;
    
    x = 30; y = 40;
    cout << "修改后: x = " << x << ", y = " << y << endl;
    cout << "按值捕获所有: " << captureAll() << " (仍使用旧值)" << endl;
    cout << "按引用捕获所有: " << captureAllRef() << " (使用新值)" << endl;
    
    // 可变lambda
    cout << "\n4. 可变lambda:" << endl;
    int counter = 0;
    auto incrementer = [counter]() mutable {
        return ++counter;
    };
    
    cout << "第1次调用: " << incrementer() << endl;
    cout << "第2次调用: " << incrementer() << endl;
    cout << "第3次调用: " << incrementer() << endl;
    cout << "外部counter仍为: " << counter << endl;
    
    // 函数对象和仿函数
    cout << "\n=== 函数对象和仿函数 ===" << endl;
    
    // 函数对象类
    class Adder {
    private:
        int value;
    public:
        Adder(int v) : value(v) {}
        int operator()(int x) const {
            return x + value;
        }
    };
    
    Adder add10(10);
    cout << "函数对象: 5 + 10 = " << add10(5) << endl;
    
    // STL中的函数对象
    cout << "\nSTL函数对象:" << endl;
    vector<int> data = {5, 2, 8, 1, 9, 3};
    
    cout << "原始数据: ";
    for (int val : data) {
        cout << val << " ";
    }
    cout << endl;
    
    // 使用greater函数对象进行降序排序
    sort(data.begin(), data.end(), greater<int>());
    cout << "降序排序: ";
    for (int val : data) {
        cout << val << " ";
    }
    cout << endl;
    
    // 高阶函数
    cout << "\n=== 高阶函数 ===" << endl;
    
    // map函数
    auto mapFunction = [](const vector<int>& input, function<int(int)> func) {
        vector<int> result;
        for (int val : input) {
            result.push_back(func(val));
        }
        return result;
    };
    
    vector<int> original = {1, 2, 3, 4, 5};
    cout << "原始数组: ";
    for (int val : original) {
        cout << val << " ";
    }
    cout << endl;
    
    auto doubled = mapFunction(original, [](int x) { return x * 2; });
    cout << "翻倍后: ";
    for (int val : doubled) {
        cout << val << " ";
    }
    cout << endl;
    
    // filter函数
    auto filterFunction = [](const vector<int>& input, function<bool(int)> predicate) {
        vector<int> result;
        for (int val : input) {
            if (predicate(val)) {
                result.push_back(val);
            }
        }
        return result;
    };
    
    auto evens = filterFunction(original, [](int x) { return x % 2 == 0; });
    cout << "偶数筛选: ";
    for (int val : evens) {
        cout << val << " ";
    }
    cout << endl;
    
    // reduce函数
    auto reduceFunction = [](const vector<int>& input, function<int(int, int)> func, int initial) {
        int result = initial;
        for (int val : input) {
            result = func(result, val);
        }
        return result;
    };
    
    int sum = reduceFunction(original, [](int acc, int x) { return acc + x; }, 0);
    cout << "数组求和: " << sum << endl;
    
    // 控制流组合
    cout << "\n=== 控制流组合 ===" << endl;
    
    // 短路评估
    cout << "1. 短路评估:" << endl;
    
    auto expensiveFunction = [](int x) {
        cout << "执行昂贵计算: " << x << endl;
        return x > 5;
    };
    
    bool condition1 = false;
    bool condition2 = true;
    
    cout << "测试 false && expensiveFunction(10):" << endl;
    bool result1 = condition1 && expensiveFunction(10);  // expensiveFunction不会被调用
    cout << "结果: " << (result1 ? "true" : "false") << endl;
    
    cout << "\n测试 true || expensiveFunction(10):" << endl;
    bool result2 = condition2 || expensiveFunction(10);  // expensiveFunction不会被调用
    cout << "结果: " << (result2 ? "true" : "false") << endl;
    
    // 条件链
    cout << "\n2. 条件链:" << endl;
    
    auto processValue = [](int value) {
        cout << "处理值: " << value << " -> ";
        
        if (value < 0) {
            cout << "负数，转为正数" << endl;
            return -value;
        } else if (value == 0) {
            cout << "零值，设为1" << endl;
            return 1;
        } else if (value > 100) {
            cout << "过大，限制为100" << endl;
            return 100;
        } else {
            cout << "正常值，保持不变" << endl;
            return value;
        }
    };
    
    vector<int> test_values = {-5, 0, 50, 150};
    for (int val : test_values) {
        int processed = processValue(val);
        cout << "结果: " << processed << endl;
    }
    
    // 状态机
    cout << "\n=== 状态机 ===" << endl;
    
    enum class State {
        IDLE,
        PROCESSING,
        COMPLETED,
        ERROR
    };
    
    class StateMachine {
    private:
        State current_state;
        
    public:
        StateMachine() : current_state(State::IDLE) {}
        
        void transition(const string& event) {
            State old_state = current_state;
            
            switch (current_state) {
                case State::IDLE:
                    if (event == "start") {
                        current_state = State::PROCESSING;
                    }
                    break;
                    
                case State::PROCESSING:
                    if (event == "complete") {
                        current_state = State::COMPLETED;
                    } else if (event == "error") {
                        current_state = State::ERROR;
                    }
                    break;
                    
                case State::COMPLETED:
                    if (event == "reset") {
                        current_state = State::IDLE;
                    }
                    break;
                    
                case State::ERROR:
                    if (event == "reset") {
                        current_state = State::IDLE;
                    }
                    break;
            }
            
            if (old_state != current_state) {
                cout << "状态转换: " << stateToString(old_state) 
                     << " -> " << stateToString(current_state) << endl;
            } else {
                cout << "无效转换: 在" << stateToString(current_state) 
                     << "状态下收到事件'" << event << "'" << endl;
            }
        }
        
        string stateToString(State state) {
            switch (state) {
                case State::IDLE: return "空闲";
                case State::PROCESSING: return "处理中";
                case State::COMPLETED: return "已完成";
                case State::ERROR: return "错误";
                default: return "未知";
            }
        }
        
        State getState() const { return current_state; }
    };
    
    StateMachine sm;
    vector<string> events = {"start", "complete", "reset", "start", "error", "reset"};
    
    cout << "初始状态: " << sm.stateToString(sm.getState()) << endl;
    
    for (const string& event : events) {
        cout << "事件: " << event << " -> ";
        sm.transition(event);
    }
    
    // 协程风格的控制流模拟
    cout << "\n=== 协程风格控制流模拟 ===" << endl;
    
    class Generator {
    private:
        int current;
        int max_val;
        
    public:
        Generator(int max) : current(0), max_val(max) {}
        
        optional<int> next() {
            if (current < max_val) {
                return current++;
            }
            return nullopt;
        }
        
        bool hasNext() const {
            return current < max_val;
        }
    };
    
    cout << "生成器示例:" << endl;
    Generator gen(5);
    
    while (gen.hasNext()) {
        auto value = gen.next();
        if (value) {
            cout << "生成值: " << *value << endl;
        }
    }
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 算法策略模式
    cout << "1. 排序策略模式:" << endl;
    
    using SortStrategy = function<void(vector<int>&)>;
    
    auto bubbleSort = [](vector<int>& arr) {
        cout << "使用冒泡排序" << endl;
        for (size_t i = 0; i < arr.size() - 1; i++) {
            for (size_t j = 0; j < arr.size() - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    };
    
    auto selectionSort = [](vector<int>& arr) {
        cout << "使用选择排序" << endl;
        for (size_t i = 0; i < arr.size() - 1; i++) {
            size_t minIdx = i;
            for (size_t j = i + 1; j < arr.size(); j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            swap(arr[i], arr[minIdx]);
        }
    };
    
    auto sorter = [](vector<int> data, SortStrategy strategy) {
        cout << "排序前: ";
        for (int val : data) {
            cout << val << " ";
        }
        cout << endl;
        
        strategy(data);
        
        cout << "排序后: ";
        for (int val : data) {
            cout << val << " ";
        }
        cout << endl;
    };
    
    vector<int> data1 = {64, 34, 25, 12, 22};
    vector<int> data2 = {64, 34, 25, 12, 22};
    
    sorter(data1, bubbleSort);
    sorter(data2, selectionSort);
    
    // 2. 函数式编程风格
    cout << "\n2. 函数式编程风格:" << endl;
    
    auto pipeline = [](vector<int> data) {
        // 链式操作
        auto result = data;
        
        // 过滤偶数
        result.erase(
            remove_if(result.begin(), result.end(), [](int x) { return x % 2 != 0; }),
            result.end()
        );
        
        // 翻倍
        transform(result.begin(), result.end(), result.begin(), [](int x) { return x * 2; });
        
        // 排序
        sort(result.begin(), result.end());
        
        return result;
    };
    
    vector<int> input = {5, 2, 8, 1, 9, 4, 6, 3, 7};
    cout << "输入: ";
    for (int val : input) {
        cout << val << " ";
    }
    cout << endl;
    
    auto output = pipeline(input);
    cout << "处理后（保留偶数->翻倍->排序）: ";
    for (int val : output) {
        cout << val << " ";
    }
    cout << endl;
    
    // 高级控制流总结
    cout << "\n=== 高级控制流总结 ===" << endl;
    cout << "1. 递归：解决自相似问题，注意栈溢出风险" << endl;
    cout << "2. 函数指针：实现回调和策略模式" << endl;
    cout << "3. Lambda表达式：简洁的匿名函数，支持闭包" << endl;
    cout << "4. 函数对象：可重用的函数逻辑封装" << endl;
    cout << "5. 高阶函数：操作其他函数的函数" << endl;
    cout << "6. 短路评估：提高条件判断效率" << endl;
    cout << "7. 状态机：管理复杂的状态转换" << endl;
    cout << "8. 函数式编程：声明式的编程范式" << endl;
    
    print_separator("高级控制流示例完成");
    
    return 0;
} 