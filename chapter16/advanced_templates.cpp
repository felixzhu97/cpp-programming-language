/**
 * @file advanced_templates.cpp
 * @brief 高级模板特性演示 - SFINAE、元编程、现代模板特性
 */

#include <iostream>
#include <type_traits>
#include <vector>
#include <string>

// SFINAE 示例
template<typename T>
auto has_size_impl(int) -> decltype(std::declval<T>().size(), std::true_type{});

template<typename T>
auto has_size_impl(...) -> std::false_type;

template<typename T>
constexpr bool has_size = decltype(has_size_impl<T>(0))::value;

// 编译时递归
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// 类型列表
template<typename... Types>
struct TypeList {};

template<typename List>
struct Size;

template<typename... Types>
struct Size<TypeList<Types...>> {
    static constexpr size_t value = sizeof...(Types);
};

// 折叠表达式
template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

template<typename... Args>
void print_all(Args... args) {
    ((std::cout << args << " "), ...);
    std::cout << "\n";
}

// constexpr if
template<typename T>
auto process(T value) {
    if constexpr (std::is_integral_v<T>) {
        return value * 2;
    } else if constexpr (std::is_floating_point_v<T>) {
        return value * 3.14;
    } else {
        return value;
    }
}

void demonstrate_sfinae() {
    std::cout << "\n=== SFINAE 演示 ===\n";
    
    std::cout << "vector 有 size(): " << has_size<std::vector<int>> << "\n";
    std::cout << "int 有 size(): " << has_size<int> << "\n";
    std::cout << "string 有 size(): " << has_size<std::string> << "\n";
}

void demonstrate_metaprogramming() {
    std::cout << "\n=== 模板元编程演示 ===\n";
    
    std::cout << "5! = " << Factorial<5>::value << "\n";
    std::cout << "TypeList<int,double,string> 大小: " 
              << Size<TypeList<int, double, std::string>>::value << "\n";
}

void demonstrate_modern_features() {
    std::cout << "\n=== 现代模板特性演示 ===\n";
    
    std::cout << "折叠表达式求和: " << sum(1, 2, 3, 4, 5) << "\n";
    
    print_all("Hello", 42, 3.14, "World");
    
    std::cout << "constexpr if:\n";
    std::cout << "process(5): " << process(5) << "\n";
    std::cout << "process(2.0): " << process(2.0) << "\n";
    std::cout << "process(\"test\"): " << process(std::string("test")) << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 16: 高级模板特性演示\n";
    std::cout << "====================================\n";
    
    demonstrate_sfinae();
    demonstrate_metaprogramming();
    demonstrate_modern_features();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 