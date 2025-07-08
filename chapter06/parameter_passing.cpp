#include "common.h"

// 1. 按值传递（Pass by Value）
void pass_by_value(int x) {
    cout << "  函数内部 - 接收到的值: " << x << ", 地址: " << &x << endl;
    x = 999;  // 修改不会影响原变量
    cout << "  函数内部 - 修改后的值: " << x << endl;
}

// 2. 按引用传递（Pass by Reference）
void pass_by_reference(int& x) {
    cout << "  函数内部 - 接收到的值: " << x << ", 地址: " << &x << endl;
    x = 999;  // 修改会影响原变量
    cout << "  函数内部 - 修改后的值: " << x << endl;
}

// 3. 按指针传递（Pass by Pointer）
void pass_by_pointer(int* x) {
    cout << "  函数内部 - 指针指向的值: " << *x << ", 指针地址: " << x << endl;
    *x = 999;  // 通过指针修改值
    cout << "  函数内部 - 修改后的值: " << *x << endl;
}

// 4. 按常量引用传递（Pass by Const Reference）
void pass_by_const_reference(const int& x) {
    cout << "  函数内部 - 接收到的常量引用值: " << x << ", 地址: " << &x << endl;
    // x = 999;  // 编译错误：不能修改const引用
    cout << "  函数内部 - 值不能被修改" << endl;
}

// 5. 传递数组参数（数组退化为指针）
void pass_array_as_pointer(int arr[], int size) {
    cout << "  函数内部 - 数组参数大小: " << sizeof(arr) << " (指针大小)" << endl;
    cout << "  数组元素: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 修改数组元素
    arr[0] = 999;
}

// 6. 传递数组引用（保持数组类型）
void pass_array_by_reference(int (&arr)[5]) {
    cout << "  函数内部 - 数组引用大小: " << sizeof(arr) << " (真实数组大小)" << endl;
    cout << "  数组元素: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    arr[1] = 888;
}

// 7. 传递vector参数
void pass_vector_by_value(vector<int> vec) {
    cout << "  按值传递vector (复制): ";
    vec.push_back(100);  // 不影响原vector
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

void pass_vector_by_reference(vector<int>& vec) {
    cout << "  按引用传递vector: ";
    vec.push_back(200);  // 影响原vector
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

void pass_vector_by_const_reference(const vector<int>& vec) {
    cout << "  按常量引用传递vector: ";
    // vec.push_back(300);  // 编译错误：不能修改const引用
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

// 8. 传递结构体
struct Point {
    double x, y;
    
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

void pass_struct_by_value(Point p) {
    cout << "  按值传递结构体: ";
    p.print();
    p.x = 999;  // 不影响原结构体
    cout << " -> 修改后: ";
    p.print();
    cout << endl;
}

void pass_struct_by_reference(Point& p) {
    cout << "  按引用传递结构体: ";
    p.print();
    p.x = 999;  // 影响原结构体
    cout << " -> 修改后: ";
    p.print();
    cout << endl;
}

void pass_struct_by_const_reference(const Point& p) {
    cout << "  按常量引用传递结构体: ";
    p.print();
    // p.x = 999;  // 编译错误
    cout << " (不能修改)" << endl;
}

// 9. 传递函数指针
int add_func(int a, int b) {
    return a + b;
}

int multiply_func(int a, int b) {
    return a * b;
}

void pass_function_pointer(int (*func)(int, int), int x, int y) {
    cout << "  函数指针调用结果: " << func(x, y) << endl;
}

// 10. 可变参数函数（C风格）
#include <cstdarg>

void print_ints(int count, ...) {
    va_list args;
    va_start(args, count);
    
    cout << "  C风格可变参数: ";
    for (int i = 0; i < count; i++) {
        int value = va_arg(args, int);
        cout << value << " ";
    }
    cout << endl;
    
    va_end(args);
}

// 11. C++11 可变参数模板
template<typename T>
void print_variadic_single(T&& value) {
    cout << value << " ";
}

template<typename T, typename... Args>
void print_variadic(T&& first, Args&&... rest) {
    cout << first << " ";
    print_variadic(rest...);
}

// 基础版本（递归终止）
void print_variadic() {
    cout << endl;
}

// 12. 完美转发示例
template<typename T>
void forward_to_function(T&& param) {
    // 使用std::forward保持参数的值类别
    pass_by_reference(std::forward<T>(param));
}

// 13. 返回多个值的方法
// 方法1：使用引用参数
void get_min_max_by_reference(const vector<int>& vec, int& min_val, int& max_val) {
    if (vec.empty()) return;
    
    min_val = max_val = vec[0];
    for (int val : vec) {
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }
}

// 方法2：使用pair
pair<int, int> get_min_max_by_pair(const vector<int>& vec) {
    if (vec.empty()) return {0, 0};
    
    int min_val = vec[0], max_val = vec[0];
    for (int val : vec) {
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
    }
    return {min_val, max_val};
}

// 方法3：使用tuple
tuple<int, int, double> get_stats(const vector<int>& vec) {
    if (vec.empty()) return {0, 0, 0.0};
    
    int min_val = vec[0], max_val = vec[0], sum = 0;
    for (int val : vec) {
        if (val < min_val) min_val = val;
        if (val > max_val) max_val = val;
        sum += val;
    }
    double average = static_cast<double>(sum) / vec.size();
    return {min_val, max_val, average};
}

// 14. 参数验证函数
bool validate_parameters(int value, int min_val = 0, int max_val = 100) {
    return value >= min_val && value <= max_val;
}

void safe_divide(double a, double b, double& result, bool& success) {
    if (b == 0.0) {
        success = false;
        result = 0.0;
        cout << "  错误: 除数不能为零" << endl;
    } else {
        success = true;
        result = a / b;
        cout << "  " << a << " / " << b << " = " << result << endl;
    }
}

// 15. 字符串参数处理
void process_string_by_value(string str) {
    cout << "  按值传递字符串 (复制开销): " << str << endl;
    str += " [修改]";  // 不影响原字符串
    cout << "  函数内修改: " << str << endl;
}

void process_string_by_reference(string& str) {
    cout << "  按引用传递字符串: " << str << endl;
    str += " [修改]";  // 影响原字符串
    cout << "  函数内修改: " << str << endl;
}

void process_string_by_const_reference(const string& str) {
    cout << "  按常量引用传递字符串 (高效): " << str << endl;
    // str += " [修改]";  // 编译错误
}

// 16. 大对象传递测试
struct LargeObject {
    vector<int> data;
    
    LargeObject() : data(1000, 42) {
        cout << "    LargeObject构造函数调用" << endl;
    }
    
    LargeObject(const LargeObject& other) : data(other.data) {
        cout << "    LargeObject拷贝构造函数调用 (性能开销!)" << endl;
    }
    
    ~LargeObject() {
        cout << "    LargeObject析构函数调用" << endl;
    }
    
    size_t size() const { return data.size(); }
};

void process_large_object_by_value(LargeObject obj) {
    cout << "  大对象按值传递，大小: " << obj.size() << endl;
}

void process_large_object_by_reference(LargeObject& obj) {
    cout << "  大对象按引用传递，大小: " << obj.size() << endl;
}

void process_large_object_by_const_reference(const LargeObject& obj) {
    cout << "  大对象按常量引用传递，大小: " << obj.size() << endl;
}

int main() {
    print_separator("参数传递方式详解");
    
    // 1. 基本参数传递方式对比
    cout << "=== 基本参数传递方式对比 ===" << endl;
    
    int original_value = 42;
    cout << "原始值: " << original_value << ", 地址: " << &original_value << endl;
    
    cout << "\n1. 按值传递:" << endl;
    pass_by_value(original_value);
    cout << "函数调用后，原始值: " << original_value << endl;
    
    cout << "\n2. 按引用传递:" << endl;
    original_value = 42;  // 重置值
    pass_by_reference(original_value);
    cout << "函数调用后，原始值: " << original_value << endl;
    
    cout << "\n3. 按指针传递:" << endl;
    original_value = 42;  // 重置值
    pass_by_pointer(&original_value);
    cout << "函数调用后，原始值: " << original_value << endl;
    
    cout << "\n4. 按常量引用传递:" << endl;
    original_value = 42;  // 重置值
    pass_by_const_reference(original_value);
    cout << "函数调用后，原始值: " << original_value << endl;
    
    // 2. 数组参数传递
    cout << "\n=== 数组参数传递 ===" << endl;
    
    int arr[5] = {1, 2, 3, 4, 5};
    cout << "原始数组: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\n1. 数组作为指针传递:" << endl;
    pass_array_as_pointer(arr, 5);
    cout << "函数调用后，数组: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\n2. 数组引用传递:" << endl;
    pass_array_by_reference(arr);
    cout << "函数调用后，数组: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
    
    // 3. vector参数传递
    cout << "\n=== Vector参数传递 ===" << endl;
    
    vector<int> vec = {10, 20, 30};
    cout << "原始vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\n1. 按值传递vector:" << endl;
    pass_vector_by_value(vec);
    cout << "函数调用后，原始vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\n2. 按引用传递vector:" << endl;
    pass_vector_by_reference(vec);
    cout << "函数调用后，原始vector: ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\n3. 按常量引用传递vector:" << endl;
    pass_vector_by_const_reference(vec);
    
    // 4. 结构体参数传递
    cout << "\n=== 结构体参数传递 ===" << endl;
    
    Point point = {3.14, 2.71};
    cout << "原始点: ";
    point.print();
    cout << endl;
    
    cout << "\n1. 按值传递结构体:" << endl;
    pass_struct_by_value(point);
    cout << "函数调用后，原始点: ";
    point.print();
    cout << endl;
    
    cout << "\n2. 按引用传递结构体:" << endl;
    point = {3.14, 2.71};  // 重置
    pass_struct_by_reference(point);
    cout << "函数调用后，原始点: ";
    point.print();
    cout << endl;
    
    cout << "\n3. 按常量引用传递结构体:" << endl;
    point = {3.14, 2.71};  // 重置
    pass_struct_by_const_reference(point);
    
    // 5. 函数指针参数
    cout << "\n=== 函数指针参数 ===" << endl;
    
    cout << "传递不同函数指针:" << endl;
    pass_function_pointer(add_func, 10, 5);
    pass_function_pointer(multiply_func, 10, 5);
    
    // 6. 可变参数函数
    cout << "\n=== 可变参数函数 ===" << endl;
    
    cout << "C风格可变参数:" << endl;
    print_ints(5, 1, 2, 3, 4, 5);
    print_ints(3, 10, 20, 30);
    
    cout << "\nC++11可变参数模板:" << endl;
    cout << "  ";
    print_variadic(1, 2.5, "hello", 'c', 42);
    cout << "  ";
    print_variadic("只有", "两个", "参数");
    
    // 7. 返回多个值的方法
    cout << "\n=== 返回多个值的方法 ===" << endl;
    
    vector<int> test_vec = {5, 2, 8, 1, 9, 3};
    
    cout << "测试数据: ";
    for (int val : test_vec) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\n1. 使用引用参数返回多个值:" << endl;
    int min_val, max_val;
    get_min_max_by_reference(test_vec, min_val, max_val);
    cout << "  最小值: " << min_val << ", 最大值: " << max_val << endl;
    
    cout << "\n2. 使用pair返回多个值:" << endl;
    auto [min_val2, max_val2] = get_min_max_by_pair(test_vec);  // C++17结构化绑定
    cout << "  最小值: " << min_val2 << ", 最大值: " << max_val2 << endl;
    
    cout << "\n3. 使用tuple返回多个值:" << endl;
    auto [min_val3, max_val3, avg] = get_stats(test_vec);
    cout << "  最小值: " << min_val3 << ", 最大值: " << max_val3 << ", 平均值: " << avg << endl;
    
    // 8. 参数验证
    cout << "\n=== 参数验证 ===" << endl;
    
    cout << "参数验证测试:" << endl;
    cout << "  validate_parameters(50): " << (validate_parameters(50) ? "有效" : "无效") << endl;
    cout << "  validate_parameters(150): " << (validate_parameters(150) ? "有效" : "无效") << endl;
    cout << "  validate_parameters(75, 50, 100): " << (validate_parameters(75, 50, 100) ? "有效" : "无效") << endl;
    
    cout << "\n安全除法函数:" << endl;
    double result;
    bool success;
    
    safe_divide(10.0, 2.0, result, success);
    safe_divide(10.0, 0.0, result, success);
    
    // 9. 字符串参数处理
    cout << "\n=== 字符串参数处理 ===" << endl;
    
    string test_str = "Hello World";
    cout << "原始字符串: " << test_str << endl;
    
    cout << "\n1. 按值传递字符串:" << endl;
    process_string_by_value(test_str);
    cout << "函数调用后，原始字符串: " << test_str << endl;
    
    cout << "\n2. 按引用传递字符串:" << endl;
    test_str = "Hello World";  // 重置
    process_string_by_reference(test_str);
    cout << "函数调用后，原始字符串: " << test_str << endl;
    
    cout << "\n3. 按常量引用传递字符串:" << endl;
    test_str = "Hello World";  // 重置
    process_string_by_const_reference(test_str);
    
    // 10. 大对象传递性能测试
    cout << "\n=== 大对象传递性能测试 ===" << endl;
    
    cout << "创建大对象:" << endl;
    LargeObject large_obj;
    
    cout << "\n1. 按值传递大对象 (会触发拷贝构造):" << endl;
    process_large_object_by_value(large_obj);
    
    cout << "\n2. 按引用传递大对象 (无拷贝开销):" << endl;
    process_large_object_by_reference(large_obj);
    
    cout << "\n3. 按常量引用传递大对象 (无拷贝开销，不能修改):" << endl;
    process_large_object_by_const_reference(large_obj);
    
    // 11. 参数传递最佳实践总结
    cout << "\n=== 参数传递最佳实践 ===" << endl;
    cout << "1. 基本类型（int, double等）：按值传递" << endl;
    cout << "2. 大对象（string, vector等）：按常量引用传递（如果不需要修改）" << endl;
    cout << "3. 需要修改参数：按引用传递" << endl;
    cout << "4. 可选的输出参数：使用指针传递（可以为nullptr）" << endl;
    cout << "5. 数组参数：使用容器（vector）或传递指针+大小" << endl;
    cout << "6. 函数参数：使用函数指针或std::function" << endl;
    cout << "7. 多个返回值：使用tuple、pair或结构体" << endl;
    cout << "8. 避免不必要的拷贝：优先使用const引用" << endl;
    cout << "9. 参数验证：在函数开始时检查参数有效性" << endl;
    cout << "10. 异常安全：确保参数传递不会导致资源泄漏" << endl;
    
    // 12. 性能对比示例
    cout << "\n=== 性能对比示例 ===" << endl;
    
    string large_string(10000, 'x');
    
    cout << "大字符串长度: " << large_string.length() << endl;
    
    auto start = chrono::high_resolution_clock::now();
    
    // 测试按值传递（会产生拷贝）
    for (int i = 0; i < 1000; i++) {
        process_string_by_value(large_string);
    }
    
    auto mid = chrono::high_resolution_clock::now();
    
    // 测试按常量引用传递（无拷贝）
    for (int i = 0; i < 1000; i++) {
        process_string_by_const_reference(large_string);
    }
    
    auto end = chrono::high_resolution_clock::now();
    
    auto duration1 = chrono::duration_cast<chrono::microseconds>(mid - start);
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - mid);
    
    cout << "按值传递1000次耗时: " << duration1.count() << " 微秒" << endl;
    cout << "按常量引用传递1000次耗时: " << duration2.count() << " 微秒" << endl;
    cout << "性能提升: " << (duration1.count() / (double)duration2.count()) << " 倍" << endl;
    
    print_separator("参数传递方式详解完成");
    
    return 0;
} 