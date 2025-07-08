#include "common.h"

// 全局变量
int global_var = 100;

// 函数声明
int add(int a, int b);
void print_message(const string& msg);
double calculate_area(double radius);
int factorial(int n);

// 无参数函数
void say_hello() {
    cout << "Hello from say_hello() function!" << endl;
}

// 有参数的函数
int add(int a, int b) {
    cout << "计算 " << a << " + " << b << " = ";
    return a + b;
}

// 传递字符串参数
void print_message(const string& msg) {
    cout << "消息: " << msg << endl;
}

// 返回浮点数的函数
double calculate_area(double radius) {
    const double PI = 3.14159;
    return PI * radius * radius;
}

// 递归函数（简单版本）
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 使用局部变量的函数
void demonstrate_local_variables() {
    cout << "\n=== 局部变量演示 ===" << endl;
    
    int local_var = 10;  // 局部变量
    cout << "局部变量 local_var = " << local_var << endl;
    cout << "全局变量 global_var = " << global_var << endl;
    
    // 局部变量隐藏全局变量
    {
        int global_var = 200;  // 局部变量隐藏同名全局变量
        cout << "在内层作用域中，global_var = " << global_var << " (局部变量)" << endl;
    }
    
    cout << "回到外层作用域，global_var = " << global_var << " (全局变量)" << endl;
}

// 使用静态变量的函数
int get_call_count() {
    static int count = 0;  // 静态局部变量
    count++;
    return count;
}

// 返回多个值的函数（使用引用参数）
void calculate_stats(const vector<int>& numbers, int& sum, double& average) {
    sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    average = static_cast<double>(sum) / numbers.size();
}

// 函数重载的简单示例
void print_value(int value) {
    cout << "整数值: " << value << endl;
}

void print_value(double value) {
    cout << "浮点数值: " << value << endl;
}

void print_value(const string& value) {
    cout << "字符串值: " << value << endl;
}

// 默认参数函数
void print_rectangle_info(int width, int height = 10, char border = '*') {
    cout << "矩形信息: 宽度=" << width << ", 高度=" << height << ", 边框字符=" << border << endl;
    
    // 绘制简单的矩形边框
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cout << border;
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// 可变参数函数（C++11风格）
template<typename... Args>
void print_all(Args... args) {
    cout << "打印所有参数: ";
    ((cout << args << " "), ...);  // C++17 fold expression
    cout << endl;
}

// 函数模板简单示例
template<typename T>
T get_max(T a, T b) {
    return (a > b) ? a : b;
}

// 内联函数示例
inline int square(int x) {
    return x * x;
}

// 返回引用的函数
int& get_array_element(vector<int>& arr, size_t index) {
    return arr[index];
}

// 函数指针的基本使用
int multiply(int a, int b) {
    return a * b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    print_separator("函数基础示例");
    
    // 基本函数调用
    cout << "=== 基本函数调用 ===" << endl;
    
    say_hello();
    
    int result = add(5, 3);
    cout << result << endl;
    
    print_message("这是一个测试消息");
    
    double area = calculate_area(5.0);
    cout << "半径为5的圆面积: " << area << endl;
    
    // 递归函数调用
    cout << "\n=== 递归函数调用 ===" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << "! = " << factorial(i) << endl;
    }
    
    // 局部变量和作用域
    demonstrate_local_variables();
    
    // 静态变量
    cout << "\n=== 静态变量演示 ===" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "函数调用次数: " << get_call_count() << endl;
    }
    
    // 返回多个值
    cout << "\n=== 返回多个值 ===" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum;
    double average;
    
    calculate_stats(numbers, sum, average);
    cout << "数组统计: 总和=" << sum << ", 平均值=" << average << endl;
    
    // 函数重载
    cout << "\n=== 函数重载 ===" << endl;
    print_value(42);
    print_value(3.14);
    print_value("Hello World");
    
    // 默认参数
    cout << "\n=== 默认参数 ===" << endl;
    print_rectangle_info(5);
    cout << endl;
    print_rectangle_info(8, 4);
    cout << endl;
    print_rectangle_info(6, 3, '#');
    
    // 可变参数模板
    cout << "\n=== 可变参数模板 ===" << endl;
    print_all(1, 2.5, "hello", 'c');
    print_all("只有一个参数");
    print_all(10, 20, 30, 40, 50);
    
    // 函数模板
    cout << "\n=== 函数模板 ===" << endl;
    cout << "max(10, 20) = " << get_max(10, 20) << endl;
    cout << "max(3.5, 2.8) = " << get_max(3.5, 2.8) << endl;
    cout << "max('a', 'z') = " << get_max('a', 'z') << endl;
    
    // 内联函数
    cout << "\n=== 内联函数 ===" << endl;
    cout << "square(5) = " << square(5) << endl;
    cout << "square(7) = " << square(7) << endl;
    
    // 返回引用
    cout << "\n=== 返回引用 ===" << endl;
    vector<int> arr = {10, 20, 30, 40, 50};
    cout << "原始数组: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
    
    // 通过引用修改数组元素
    get_array_element(arr, 2) = 999;
    cout << "修改后数组: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
    
    // 函数指针基础
    cout << "\n=== 函数指针基础 ===" << endl;
    
    // 声明函数指针
    int (*operation)(int, int);
    
    // 使用函数指针
    operation = add;
    cout << "使用add函数: 5 + 3 = " << operation(5, 3) << endl;
    
    operation = multiply;
    cout << "使用multiply函数: 5 * 3 = " << operation(5, 3) << endl;
    
    operation = subtract;
    cout << "使用subtract函数: 5 - 3 = " << operation(5, 3) << endl;
    
    // 函数指针数组
    cout << "\n函数指针数组:" << endl;
    int (*operations[])(int, int) = {add, multiply, subtract};
    string op_names[] = {"加法", "乘法", "减法"};
    
    for (int i = 0; i < 3; i++) {
        cout << op_names[i] << ": 8, 4 = " << operations[i](8, 4) << endl;
    }
    
    // 函数生命周期和作用域
    cout << "\n=== 函数生命周期和作用域 ===" << endl;
    
    auto demo_scope = []() {
        int local_var = 42;
        cout << "函数内局部变量: " << local_var << endl;
        
        // 局部函数（lambda）
        auto inner_func = [local_var]() {
            cout << "内部函数访问外部变量: " << local_var << endl;
        };
        
        inner_func();
        return local_var;
    };
    
    int returned_value = demo_scope();
    cout << "函数返回值: " << returned_value << endl;
    
    // 函数作为参数
    cout << "\n=== 函数作为参数 ===" << endl;
    
    auto apply_operation = [](int x, int y, int (*func)(int, int)) {
        return func(x, y);
    };
    
    cout << "apply_operation(6, 4, add) = " << apply_operation(6, 4, add) << endl;
    cout << "apply_operation(6, 4, multiply) = " << apply_operation(6, 4, multiply) << endl;
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 数学函数库
    cout << "1. 数学函数库:" << endl;
    
    auto power = [](double base, int exponent) -> double {
        double result = 1.0;
        for (int i = 0; i < exponent; i++) {
            result *= base;
        }
        return result;
    };
    
    auto is_prime = [](int n) -> bool {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    };
    
    cout << "2^10 = " << power(2.0, 10) << endl;
    cout << "3^4 = " << power(3.0, 4) << endl;
    
    cout << "质数检查:" << endl;
    for (int i = 2; i <= 20; i++) {
        if (is_prime(i)) {
            cout << i << " ";
        }
    }
    cout << endl;
    
    // 2. 字符串处理函数
    cout << "\n2. 字符串处理函数:" << endl;
    
    auto to_upper = [](string str) -> string {
        for (char& c : str) {
            c = toupper(c);
        }
        return str;
    };
    
    auto word_count = [](const string& text) -> int {
        int count = 0;
        bool in_word = false;
        for (char c : text) {
            if (isalnum(c)) {
                if (!in_word) {
                    count++;
                    in_word = true;
                }
            } else {
                in_word = false;
            }
        }
        return count;
    };
    
    string text = "Hello World! This is a test.";
    cout << "原始文本: " << text << endl;
    cout << "转大写: " << to_upper(text) << endl;
    cout << "单词数量: " << word_count(text) << endl;
    
    // 函数最佳实践
    cout << "\n=== 函数最佳实践 ===" << endl;
    cout << "1. 函数应该有单一职责" << endl;
    cout << "2. 函数名应该描述其功能" << endl;
    cout << "3. 避免函数过长（一般不超过50行）" << endl;
    cout << "4. 优先使用const参数保护数据" << endl;
    cout << "5. 合理使用默认参数" << endl;
    cout << "6. 注意函数的异常安全性" << endl;
    cout << "7. 使用适当的返回类型" << endl;
    cout << "8. 避免全局变量，使用参数传递" << endl;
    
    print_separator("函数基础示例完成");
    
    return 0;
} 