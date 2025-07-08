/**
 * @file function_templates.cpp
 * @brief 函数模板演示 - 模板基础、参数推导、重载、特化
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <type_traits>

// 基础函数模板
template<typename T>
T max_value(T a, T b) {
    std::cout << "通用 max_value 模板被调用\n";
    return a > b ? a : b;
}

// 函数模板重载
template<typename T>
T max_value(T a, T b, T c) {
    std::cout << "三参数 max_value 模板被调用\n";
    return max_value(max_value(a, b), c);
}

// 函数模板特化
template<>
const char* max_value<const char*>(const char* a, const char* b) {
    std::cout << "const char* 特化版本被调用\n";
    return std::strcmp(a, b) > 0 ? a : b;
}

// 带默认模板参数的函数模板
template<typename T = int, typename U = double>
auto add_values(T a, U b = U{}) -> decltype(a + b) {
    std::cout << "add_values 模板被调用\n";
    return a + b;
}

// 非类型模板参数
template<int N>
int factorial() {
    std::cout << "编译时计算 " << N << "! = ";
    return N * factorial<N-1>();
}

// 特化：递归终止条件
template<>
int factorial<0>() {
    return 1;
}

template<>
int factorial<1>() {
    return 1;
}

// 多个模板参数
template<typename T, typename U>
struct Pair {
    T first;
    U second;
    
    Pair(T f, U s) : first(f), second(s) {}
    
    void display() const {
        std::cout << "Pair: (" << first << ", " << second << ")\n";
    }
};

// 模板函数创建器
template<typename T, typename U>
Pair<T, U> make_pair(T first, U second) {
    return Pair<T, U>(first, second);
}

// 高级模板技术：SFINAE
template<typename T>
auto print_if_integral(T value) -> typename std::enable_if<std::is_integral<T>::value, void>::type {
    std::cout << "整数类型: " << value << "\n";
}

template<typename T>
auto print_if_floating(T value) -> typename std::enable_if<std::is_floating_point<T>::value, void>::type {
    std::cout << "浮点类型: " << value << "\n";
}

// 函数模板与auto
template<typename T>
auto square(T value) {
    return value * value;
}

// 前向声明
void process_value(int& value);
void process_value(const int& value);
void process_value(int&& value);

// 完美转发
template<typename T>
void wrapper(T&& arg) {
    std::cout << "包装器调用: ";
    process_value(std::forward<T>(arg));
}

void process_value(int& value) {
    std::cout << "处理左值引用: " << value << "\n";
    value++;
}

void process_value(const int& value) {
    std::cout << "处理const引用: " << value << "\n";
}

void process_value(int&& value) {
    std::cout << "处理右值引用: " << value << "\n";
}

// 可变参数模板函数
template<typename... Args>
void print_values(Args... args) {
    std::cout << "参数个数: " << sizeof...(args) << "\n";
    ((std::cout << args << " "), ...);  // C++17 折叠表达式
    std::cout << "\n";
}

// 递归可变参数模板（C++11/14方式）
template<typename T>
void print_recursive(T&& t) {
    std::cout << t << "\n";
}

template<typename T, typename... Args>
void print_recursive(T&& t, Args&&... args) {
    std::cout << t << " ";
    print_recursive(args...);
}

// 模板匹配和重载解析
template<typename T>
void overload_test(T value) {
    std::cout << "通用模板: " << value << "\n";
}

template<typename T>
void overload_test(T* value) {
    std::cout << "指针特化: " << *value << "\n";
}

void overload_test(int value) {
    std::cout << "非模板函数: " << value << "\n";
}

// 模板类型推导辅助
template<typename Container>
auto get_size(const Container& container) -> decltype(container.size()) {
    return container.size();
}

// 通用比较函数模板
template<typename T>
bool less_than(const T& a, const T& b) {
    return a < b;
}

// 为std::string特化
template<>
bool less_than<std::string>(const std::string& a, const std::string& b) {
    std::cout << "字符串比较特化版本\n";
    return a.length() < b.length();  // 按长度比较而非字典序
}

void demonstrate_basic_templates() {
    std::cout << "\n=== 基础函数模板演示 ===\n";
    
    // 模板参数推导
    int max_int = max_value(10, 20);
    std::cout << "max_value(10, 20) = " << max_int << "\n";
    
    double max_double = max_value(3.14, 2.71);
    std::cout << "max_value(3.14, 2.71) = " << max_double << "\n";
    
    // 显式指定模板参数
    auto max_explicit = max_value<long>(100L, 200L);
    std::cout << "max_value<long>(100L, 200L) = " << max_explicit << "\n";
    
    // 三参数版本
    int max_three = max_value(5, 15, 10);
    std::cout << "max_value(5, 15, 10) = " << max_three << "\n";
}

void demonstrate_template_specialization() {
    std::cout << "\n=== 模板特化演示 ===\n";
    
    // 使用特化版本
    const char* str1 = "hello";
    const char* str2 = "world";
    const char* max_str = max_value(str1, str2);
    std::cout << "max_value(\"hello\", \"world\") = " << max_str << "\n";
    
    // 字符串长度比较特化
    std::string s1 = "short";
    std::string s2 = "verylongstring";
    bool result = less_than(s1, s2);
    std::cout << "less_than(\"short\", \"verylongstring\") = " << std::boolalpha << result << "\n";
    
    // 普通类型比较
    bool int_result = less_than(10, 20);
    std::cout << "less_than(10, 20) = " << int_result << "\n";
}

void demonstrate_template_parameters() {
    std::cout << "\n=== 模板参数演示 ===\n";
    
    // 默认模板参数
    auto result1 = add_values(5);  // T=int, U=double
    std::cout << "add_values(5) = " << result1 << "\n";
    
    auto result2 = add_values(3.14f, 2.71);
    std::cout << "add_values(3.14f, 2.71) = " << result2 << "\n";
    
    // 非类型模板参数
    std::cout << factorial<5>() << "\n";
    std::cout << factorial<0>() << "\n";
    
    // 多个模板参数
    auto pair1 = make_pair(42, "hello");
    pair1.display();
    
    auto pair2 = make_pair(3.14, 100);
    pair2.display();
}

void demonstrate_sfinae() {
    std::cout << "\n=== SFINAE 演示 ===\n";
    
    print_if_integral(42);
    print_if_integral(static_cast<long>(100));
    print_if_floating(3.14);
    print_if_floating(2.71f);
    
    // 编译时不会出错，因为SFINAE
    // print_if_integral(3.14);  // 如果取消注释，编译器会忽略这个重载
}

void demonstrate_auto_and_decltype() {
    std::cout << "\n=== auto 和 decltype 演示 ===\n";
    
    auto squared_int = square(5);
    std::cout << "square(5) = " << squared_int << "\n";
    
    auto squared_double = square(3.14);
    std::cout << "square(3.14) = " << squared_double << "\n";
    
    // 类型推导
    std::vector<int> vec{1, 2, 3, 4, 5};
    auto size = get_size(vec);
    std::cout << "vector size = " << size << "\n";
    
    std::string str = "Hello";
    auto str_size = get_size(str);
    std::cout << "string size = " << str_size << "\n";
}

void demonstrate_perfect_forwarding() {
    std::cout << "\n=== 完美转发演示 ===\n";
    
    int x = 42;
    const int y = 100;
    
    wrapper(x);        // 左值
    wrapper(y);        // const左值
    wrapper(99);       // 右值
    
    std::cout << "x after wrapper: " << x << "\n";
}

void demonstrate_variadic_templates() {
    std::cout << "\n=== 可变参数模板演示 ===\n";
    
    // C++17 折叠表达式
    print_values(1, 2, 3, "hello", 3.14);
    print_values();
    print_values(42);
    
    std::cout << "\n递归版本:\n";
    print_recursive(1, 2, 3, "world", 2.71);
    print_recursive("single");
}

void demonstrate_overload_resolution() {
    std::cout << "\n=== 重载解析演示 ===\n";
    
    int value = 42;
    int* ptr = &value;
    double dval = 3.14;
    
    overload_test(value);    // 非模板函数优先
    overload_test(ptr);      // 指针特化
    overload_test(dval);     // 通用模板
    overload_test(&dval);    // 指针特化
}

void demonstrate_template_deduction_guides() {
    std::cout << "\n=== 模板推导指南演示 ===\n";
    
    // C++17 之前需要显式指定类型
    Pair<int, std::string> pair1(42, "hello");
    pair1.display();
    
    // 使用make函数进行推导
    auto pair2 = make_pair(3.14, 100);
    pair2.display();
    
    std::cout << "注意：C++17有类模板参数推导，可以直接写 Pair pair(42, \"hello\")\n";
}

void demonstrate_template_instantiation() {
    std::cout << "\n=== 模板实例化演示 ===\n";
    
    std::cout << "编译器会为使用过的模板参数类型生成代码:\n";
    std::cout << "- max_value<int>\n";
    std::cout << "- max_value<double>\n";
    std::cout << "- max_value<const char*> (特化版本)\n";
    std::cout << "- factorial<5>, factorial<4>, ..., factorial<0>\n";
    
    std::cout << "\n模板只有在使用时才会实例化\n";
    std::cout << "这叫做懒惰实例化(lazy instantiation)\n";
}

void demonstrate_template_compilation_model() {
    std::cout << "\n=== 模板编译模型 ===\n";
    
    std::cout << "1. 包含模型:\n";
    std::cout << "   - 模板定义通常放在头文件中\n";
    std::cout << "   - 每个使用模板的翻译单元都会实例化\n";
    std::cout << "   - 链接器需要合并重复的实例化\n";
    
    std::cout << "\n2. 显式实例化:\n";
    std::cout << "   - template int max_value<int>(int, int);\n";
    std::cout << "   - 在特定翻译单元中强制实例化\n";
    
    std::cout << "\n3. 外部模板:\n";
    std::cout << "   - extern template int max_value<int>(int, int);\n";
    std::cout << "   - 抑制当前翻译单元的实例化\n";
}

int main() {
    std::cout << "C++ Primer Chapter 16: 函数模板演示\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_basic_templates();
        demonstrate_template_specialization();
        demonstrate_template_parameters();
        demonstrate_sfinae();
        demonstrate_auto_and_decltype();
        demonstrate_perfect_forwarding();
        demonstrate_variadic_templates();
        demonstrate_overload_resolution();
        demonstrate_template_deduction_guides();
        demonstrate_template_instantiation();
        demonstrate_template_compilation_model();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 