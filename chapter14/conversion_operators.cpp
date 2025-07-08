/**
 * @file conversion_operators.cpp
 * @brief 类型转换运算符演示 - 转换构造函数、类型转换运算符、explicit关键字
 */

#include <iostream>
#include <string>
#include <vector>

// 温度类 - 演示转换构造函数和类型转换运算符
class Temperature {
private:
    double celsius;
    
public:
    // 转换构造函数 - 从double隐式转换
    Temperature(double c) : celsius(c) {
        std::cout << "从 double 转换构造 Temperature: " << c << "°C\n";
    }
    
    // 默认构造函数
    Temperature() : celsius(0) {}
    
    // 类型转换运算符 - 转换为double
    operator double() const {
        std::cout << "Temperature 转换为 double: " << celsius << "\n";
        return celsius;
    }
    
    // 转换为华氏度
    double to_fahrenheit() const {
        return celsius * 9.0 / 5.0 + 32;
    }
    
    void set_celsius(double c) { celsius = c; }
    double get_celsius() const { return celsius; }
};

// 安全的温度类 - 使用explicit避免意外转换
class SafeTemperature {
private:
    double celsius;
    
public:
    // explicit 转换构造函数
    explicit SafeTemperature(double c) : celsius(c) {
        std::cout << "explicit 构造 SafeTemperature: " << c << "°C\n";
    }
    
    SafeTemperature() : celsius(0) {}
    
    // explicit 类型转换运算符
    explicit operator double() const {
        std::cout << "explicit 转换为 double: " << celsius << "\n";
        return celsius;
    }
    
    // 明确的转换函数
    double to_celsius() const { return celsius; }
    double to_fahrenheit() const { return celsius * 9.0 / 5.0 + 32; }
    
    void set_celsius(double c) { celsius = c; }
};

// 智能指针类 - 演示bool转换
template<typename T>
class SmartPointer {
private:
    T* ptr;
    
public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}
    
    ~SmartPointer() { delete ptr; }
    
    // 禁用拷贝
    SmartPointer(const SmartPointer&) = delete;
    SmartPointer& operator=(const SmartPointer&) = delete;
    
    // 支持移动
    SmartPointer(SmartPointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // explicit bool 转换 - 用于条件判断
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
};

// 分数类 - 演示多种转换
class Fraction {
private:
    int numerator, denominator;
    
    void simplify() {
        int gcd_val = gcd(abs(numerator), abs(denominator));
        numerator /= gcd_val;
        denominator /= gcd_val;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
    
    int gcd(int a, int b) const {
        return b == 0 ? a : gcd(b, a % b);
    }
    
public:
    Fraction(int num = 0, int den = 1) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw std::invalid_argument("分母不能为0");
        }
        simplify();
    }
    
    // 从double转换构造（可能有精度损失）
    Fraction(double value) {
        // 简单的double到分数转换
        const int precision = 1000000;
        numerator = static_cast<int>(value * precision);
        denominator = precision;
        simplify();
        std::cout << "从 double " << value << " 转换为分数 " 
                  << numerator << "/" << denominator << "\n";
    }
    
    // 转换为double
    operator double() const {
        double result = static_cast<double>(numerator) / denominator;
        std::cout << "分数 " << numerator << "/" << denominator 
                  << " 转换为 double " << result << "\n";
        return result;
    }
    
    // 转换为字符串
    operator std::string() const {
        if (denominator == 1) {
            return std::to_string(numerator);
        }
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
    
    // 算术运算符
    Fraction operator+(const Fraction& other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                       denominator * other.denominator);
    }
    
    Fraction operator*(const Fraction& other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }
    
    // 显示
    void print() const {
        if (denominator == 1) {
            std::cout << numerator;
        } else {
            std::cout << numerator << "/" << denominator;
        }
    }
};

// 容器包装类 - 演示容器转换
template<typename Container>
class ContainerWrapper {
private:
    Container container;
    
public:
    ContainerWrapper() = default;
    
    // 从容器转换构造
    ContainerWrapper(const Container& c) : container(c) {
        std::cout << "从容器转换构造，大小: " << container.size() << "\n";
    }
    
    // 转换为容器
    operator Container() const {
        std::cout << "转换为容器，大小: " << container.size() << "\n";
        return container;
    }
    
    // 添加元素
    void add(const typename Container::value_type& value) {
        container.push_back(value);
    }
    
    size_t size() const { return container.size(); }
    
    // 迭代器支持
    auto begin() { return container.begin(); }
    auto end() { return container.end(); }
    auto begin() const { return container.begin(); }
    auto end() const { return container.end(); }
};

void demonstrate_implicit_conversions() {
    std::cout << "\n=== 隐式类型转换 ===\n";
    
    // 隐式转换构造
    Temperature temp1 = 25.5;  // double -> Temperature
    std::cout << "温度: " << temp1.get_celsius() << "°C\n";
    
    // 隐式类型转换运算符
    double value = temp1;      // Temperature -> double
    std::cout << "转换后的值: " << value << "\n";
    
    // 在表达式中的隐式转换
    double result = temp1 + 10.0;  // Temperature -> double，然后相加
    std::cout << "表达式结果: " << result << "\n";
    
    // 函数参数的隐式转换
    auto add_ten = [](double d) { return d + 10; };
    double func_result = add_ten(temp1);  // Temperature -> double
    std::cout << "函数调用结果: " << func_result << "\n";
}

void demonstrate_explicit_conversions() {
    std::cout << "\n=== 显式类型转换 ===\n";
    
    // explicit 构造函数需要显式调用
    // SafeTemperature temp1 = 25.5;  // 错误：不能隐式转换
    SafeTemperature temp1(25.5);      // 正确：显式构造
    SafeTemperature temp2 = SafeTemperature(30.0);  // 正确：显式构造
    
    // explicit 类型转换运算符需要显式转换
    // double value = temp1;          // 错误：不能隐式转换
    double value = static_cast<double>(temp1);  // 正确：显式转换
    std::cout << "显式转换结果: " << value << "\n";
    
    // 使用明确的转换函数（推荐）
    double celsius = temp1.to_celsius();
    double fahrenheit = temp1.to_fahrenheit();
    std::cout << "摄氏度: " << celsius << ", 华氏度: " << fahrenheit << "\n";
}

void demonstrate_bool_conversion() {
    std::cout << "\n=== bool 类型转换 ===\n";
    
    SmartPointer<int> ptr1(new int(42));
    SmartPointer<int> ptr2;  // 空指针
    
    // explicit bool 转换用于条件判断
    if (ptr1) {
        std::cout << "ptr1 有效，值: " << *ptr1 << "\n";
    }
    
    if (!ptr2) {
        std::cout << "ptr2 为空\n";
    }
    
    // 显式转换
    bool is_valid = static_cast<bool>(ptr1);
    std::cout << "ptr1 有效性: " << (is_valid ? "true" : "false") << "\n";
}

void demonstrate_fraction_conversions() {
    std::cout << "\n=== 分数类型转换 ===\n";
    
    // 从int构造
    Fraction f1(3, 4);
    std::cout << "f1 = ";
    f1.print();
    std::cout << "\n";
    
    // 从double构造
    Fraction f2(0.75);
    std::cout << "f2 = ";
    f2.print();
    std::cout << "\n";
    
    // 转换为double
    double d1 = static_cast<double>(f1);
    std::cout << "f1 转换为 double: " << d1 << "\n";
    
    // 转换为string
    std::string s1 = static_cast<std::string>(f1);
    std::cout << "f1 转换为 string: " << s1 << "\n";
    
    // 运算中的转换
    Fraction f3 = f1 + f2;
    std::cout << "f1 + f2 = ";
    f3.print();
    std::cout << "\n";
}

void demonstrate_container_conversion() {
    std::cout << "\n=== 容器转换 ===\n";
    
    std::vector<int> vec{1, 2, 3, 4, 5};
    
    // 从容器构造
    ContainerWrapper<std::vector<int>> wrapper(vec);
    
    // 添加元素
    wrapper.add(6);
    wrapper.add(7);
    
    // 转换回容器
    std::vector<int> result = static_cast<std::vector<int>>(wrapper);
    
    std::cout << "结果容器: ";
    for (int x : result) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}

void demonstrate_conversion_pitfalls() {
    std::cout << "\n=== 类型转换陷阱 ===\n";
    
    std::cout << "1. 意外的隐式转换:\n";
    // Temperature temp = 100;  // 可能不是预期的行为
    std::cout << "   避免：使用 explicit 构造函数\n";
    
    std::cout << "\n2. 连续转换:\n";
    class A {
    public:
        A(int) { std::cout << "A(int)\n"; }
        operator double() const { std::cout << "A->double\n"; return 1.0; }
    };
    
    class B {
    public:
        B(double) { std::cout << "B(double)\n"; }
    };
    
    A a(1);
    // B b = a;  // A -> double -> B（两次转换，可能意外）
    std::cout << "   避免：限制转换链的长度\n";
    
    std::cout << "\n3. 二义性转换:\n";
    std::cout << "   避免：提供明确的转换函数而非运算符\n";
    
    std::cout << "\n4. 性能问题:\n";
    std::cout << "   注意：频繁的类型转换可能影响性能\n";
}

int main() {
    std::cout << "C++ Primer Chapter 14: 类型转换运算符演示\n";
    std::cout << "=========================================\n";
    
    try {
        demonstrate_implicit_conversions();
        demonstrate_explicit_conversions();
        demonstrate_bool_conversion();
        demonstrate_fraction_conversions();
        demonstrate_container_conversion();
        demonstrate_conversion_pitfalls();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 