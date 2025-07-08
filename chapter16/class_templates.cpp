/**
 * @file class_templates.cpp
 * @brief 类模板演示 - 类模板基础、成员模板、友元、特化
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <type_traits>

// 基础类模板
template<typename T>
class Stack {
private:
    std::vector<T> data;
    
public:
    Stack() = default;
    
    void push(const T& item) {
        data.push_back(item);
        std::cout << "压入: " << item << "\n";
    }
    
    void push(T&& item) {
        std::cout << "移动压入: " << item << "\n";
        data.push_back(std::move(item));
    }
    
    T pop() {
        if (empty()) {
            throw std::runtime_error("栈为空");
        }
        T item = std::move(data.back());
        data.pop_back();
        std::cout << "弹出: " << item << "\n";
        return item;
    }
    
    const T& top() const {
        if (empty()) {
            throw std::runtime_error("栈为空");
        }
        return data.back();
    }
    
    bool empty() const {
        return data.empty();
    }
    
    size_t size() const {
        return data.size();
    }
    
    // 友元函数模板
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Stack<U>& stack);
};

// 友元函数实现
template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& stack) {
    os << "Stack[";
    for (size_t i = 0; i < stack.data.size(); ++i) {
        if (i > 0) os << ", ";
        os << stack.data[i];
    }
    os << "]";
    return os;
}

// 类模板特化
template<>
class Stack<bool> {
private:
    std::vector<bool> data;
    
public:
    void push(bool item) {
        data.push_back(item);
        std::cout << "bool特化压入: " << std::boolalpha << item << "\n";
    }
    
    bool pop() {
        if (empty()) {
            throw std::runtime_error("bool栈为空");
        }
        bool item = data.back();
        data.pop_back();
        std::cout << "bool特化弹出: " << std::boolalpha << item << "\n";
        return item;
    }
    
    bool top() const {
        if (empty()) {
            throw std::runtime_error("bool栈为空");
        }
        return data.back();
    }
    
    bool empty() const {
        return data.empty();
    }
    
    size_t size() const {
        return data.size();
    }
};

// 多个模板参数的类模板
template<typename K, typename V, size_t MaxSize = 100>
class SimpleMap {
private:
    std::pair<K, V> data[MaxSize];
    size_t current_size;
    
public:
    SimpleMap() : current_size(0) {}
    
    bool insert(const K& key, const V& value) {
        if (current_size >= MaxSize) {
            return false;
        }
        data[current_size++] = std::make_pair(key, value);
        return true;
    }
    
    V* find(const K& key) {
        for (size_t i = 0; i < current_size; ++i) {
            if (data[i].first == key) {
                return &data[i].second;
            }
        }
        return nullptr;
    }
    
    size_t size() const { return current_size; }
    size_t capacity() const { return MaxSize; }
    
    void display() const {
        std::cout << "SimpleMap (" << current_size << "/" << MaxSize << "):\n";
        for (size_t i = 0; i < current_size; ++i) {
            std::cout << "  " << data[i].first << " -> " << data[i].second << "\n";
        }
    }
};

// 成员模板
template<typename T>
class Container {
private:
    T data;
    
public:
    Container(const T& d) : data(d) {}
    
    // 成员函数模板
    template<typename U>
    bool compare(const U& other) const {
        return data == other;
    }
    
    // 成员函数模板 - 类型转换
    template<typename U>
    Container<U> convert() const {
        return Container<U>(static_cast<U>(data));
    }
    
    // 成员类模板
    template<typename U>
    class Converter {
    public:
        static U convert(const T& value) {
            return static_cast<U>(value);
        }
    };
    
    T get_data() const { return data; }
    void set_data(const T& d) { data = d; }
};

// 类模板的偏特化
template<typename T>
class SmartPointer {
private:
    T* ptr;
    
public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}
    
    ~SmartPointer() {
        delete ptr;
        std::cout << "SmartPointer 析构\n";
    }
    
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    
    T* get() const { return ptr; }
    
    void display_type() const {
        std::cout << "通用 SmartPointer<T>\n";
    }
};

// 偏特化：数组类型
template<typename T>
class SmartPointer<T[]> {
private:
    T* ptr;
    
public:
    explicit SmartPointer(T* p = nullptr) : ptr(p) {}
    
    ~SmartPointer() {
        delete[] ptr;
        std::cout << "SmartPointer<T[]> 析构\n";
    }
    
    T& operator[](size_t index) const { return ptr[index]; }
    
    T* get() const { return ptr; }
    
    void display_type() const {
        std::cout << "偏特化 SmartPointer<T[]>\n";
    }
};

// 可变参数模板类
template<typename... Args>
class Tuple;

// 递归特化
template<>
class Tuple<> {
public:
    void print() const {
        std::cout << "()\n";
    }
    
    static constexpr size_t size() { return 0; }
};

template<typename Head, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...> {
private:
    Head head;
    
public:
    Tuple(const Head& h, const Tail&... t) : Tuple<Tail...>(t...), head(h) {}
    
    Head& get_head() { return head; }
    const Head& get_head() const { return head; }
    
    Tuple<Tail...>& get_tail() { return static_cast<Tuple<Tail...>&>(*this); }
    const Tuple<Tail...>& get_tail() const { return static_cast<const Tuple<Tail...>&>(*this); }
    
    void print() const {
        std::cout << "(" << head;
        print_tail();
        std::cout << ")\n";
    }
    
    static constexpr size_t size() { return 1 + sizeof...(Tail); }

private:
    void print_tail() const {
        if constexpr (sizeof...(Tail) > 0) {
            std::cout << ", ";
            get_tail().print_without_parens();
        }
    }
    
    void print_without_parens() const {
        std::cout << head;
        if constexpr (sizeof...(Tail) > 0) {
            std::cout << ", ";
            get_tail().print_without_parens();
        }
    }
};

// 模板模板参数
template<template<typename> class Container, typename T>
class Wrapper {
private:
    Container<T> container;
    
public:
    void add(const T& item) {
        container.push(item);
    }
    
    T remove() {
        return container.pop();
    }
    
    bool empty() const {
        return container.empty();
    }
    
    void display() const {
        std::cout << "Wrapper contains: " << container << "\n";
    }
};

// CRTP (Curiously Recurring Template Pattern)
template<typename Derived>
class Base {
public:
    void interface() {
        static_cast<Derived*>(this)->implementation();
    }
    
    void common_functionality() {
        std::cout << "Base 的通用功能\n";
    }
};

class Derived1 : public Base<Derived1> {
public:
    void implementation() {
        std::cout << "Derived1 的实现\n";
    }
};

class Derived2 : public Base<Derived2> {
public:
    void implementation() {
        std::cout << "Derived2 的实现\n";
    }
};

void demonstrate_basic_class_templates() {
    std::cout << "\n=== 基础类模板演示 ===\n";
    
    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    
    std::cout << "栈内容: " << int_stack << "\n";
    std::cout << "栈大小: " << int_stack.size() << "\n";
    
    while (!int_stack.empty()) {
        int_stack.pop();
    }
    
    Stack<std::string> string_stack;
    string_stack.push("hello");
    string_stack.push("world");
    std::cout << "字符串栈: " << string_stack << "\n";
}

void demonstrate_class_template_specialization() {
    std::cout << "\n=== 类模板特化演示 ===\n";
    
    Stack<bool> bool_stack;
    bool_stack.push(true);
    bool_stack.push(false);
    bool_stack.push(true);
    
    std::cout << "bool栈大小: " << bool_stack.size() << "\n";
    
    while (!bool_stack.empty()) {
        bool_stack.pop();
    }
}

void demonstrate_multiple_template_parameters() {
    std::cout << "\n=== 多模板参数演示 ===\n";
    
    SimpleMap<std::string, int, 5> map;
    map.insert("one", 1);
    map.insert("two", 2);
    map.insert("three", 3);
    
    map.display();
    
    auto* value = map.find("two");
    if (value) {
        std::cout << "找到 'two': " << *value << "\n";
    }
    
    // 使用默认参数
    SimpleMap<int, std::string> large_map;
    large_map.insert(100, "hundred");
    large_map.display();
}

void demonstrate_member_templates() {
    std::cout << "\n=== 成员模板演示 ===\n";
    
    Container<int> int_container(42);
    Container<double> double_container(3.14);
    
    // 成员函数模板
    bool result1 = int_container.compare(42);
    bool result2 = int_container.compare(3.14);
    
    std::cout << "int_container.compare(42): " << std::boolalpha << result1 << "\n";
    std::cout << "int_container.compare(3.14): " << result2 << "\n";
    
    // 类型转换
    auto double_from_int = int_container.convert<double>();
    std::cout << "转换结果: " << double_from_int.get_data() << "\n";
    
    // 成员类模板
    auto converted = Container<int>::Converter<double>::convert(100);
    std::cout << "成员类转换: " << converted << "\n";
}

void demonstrate_partial_specialization() {
    std::cout << "\n=== 偏特化演示 ===\n";
    
    SmartPointer<int> ptr1(new int(42));
    ptr1.display_type();
    std::cout << "值: " << *ptr1 << "\n";
    
    SmartPointer<int[]> ptr2(new int[3]{1, 2, 3});
    ptr2.display_type();
    std::cout << "数组元素: " << ptr2[0] << ", " << ptr2[1] << ", " << ptr2[2] << "\n";
}

void demonstrate_variadic_class_templates() {
    std::cout << "\n=== 可变参数类模板演示 ===\n";
    
    Tuple<> empty_tuple;
    empty_tuple.print();
    std::cout << "空元组大小: " << empty_tuple.size() << "\n";
    
    Tuple<int> single_tuple(42);
    single_tuple.print();
    std::cout << "单元素元组大小: " << single_tuple.size() << "\n";
    
    Tuple<int, std::string, double> multi_tuple(1, "hello", 3.14);
    multi_tuple.print();
    std::cout << "多元素元组大小: " << multi_tuple.size() << "\n";
    
    std::cout << "第一个元素: " << multi_tuple.get_head() << "\n";
}

void demonstrate_template_template_parameters() {
    std::cout << "\n=== 模板模板参数演示 ===\n";
    
    Wrapper<Stack, int> wrapper;
    wrapper.add(10);
    wrapper.add(20);
    wrapper.add(30);
    
    wrapper.display();
    
    while (!wrapper.empty()) {
        wrapper.remove();
    }
}

void demonstrate_crtp() {
    std::cout << "\n=== CRTP 演示 ===\n";
    
    Derived1 d1;
    Derived2 d2;
    
    d1.interface();
    d1.common_functionality();
    
    d2.interface();
    d2.common_functionality();
    
    // 静态多态
    Base<Derived1>* ptr1 = &d1;
    Base<Derived2>* ptr2 = &d2;
    
    ptr1->interface();  // 编译时解析
    ptr2->interface();  // 编译时解析
}

void demonstrate_template_metaprogramming() {
    std::cout << "\n=== 模板元编程示例 ===\n";
    
    std::cout << "编译时计算:\n";
    std::cout << "Tuple<int, string, double> 大小: " 
              << Tuple<int, std::string, double>::size() << "\n";
    
    std::cout << "\n类型特性:\n";
    std::cout << "int 是整数类型: " << std::is_integral<int>::value << "\n";
    std::cout << "double 是浮点类型: " << std::is_floating_point<double>::value << "\n";
    std::cout << "string 是类类型: " << std::is_class<std::string>::value << "\n";
}

void demonstrate_template_guidelines() {
    std::cout << "\n=== 类模板设计指导原则 ===\n";
    
    std::cout << "1. 类模板设计原则:\n";
    std::cout << "   - 尽量使模板参数独立\n";
    std::cout << "   - 提供合理的默认参数\n";
    std::cout << "   - 考虑特化的需要\n";
    
    std::cout << "\n2. 成员模板使用:\n";
    std::cout << "   - 增加类的灵活性\n";
    std::cout << "   - 支持类型转换和比较\n";
    std::cout << "   - 注意模板参数推导\n";
    
    std::cout << "\n3. 特化策略:\n";
    std::cout << "   - 完全特化用于特殊类型\n";
    std::cout << "   - 偏特化用于类型模式\n";
    std::cout << "   - 考虑性能和功能需求\n";
    
    std::cout << "\n4. 编译和链接:\n";
    std::cout << "   - 模板定义通常在头文件中\n";
    std::cout << "   - 注意模板实例化的控制\n";
    std::cout << "   - 避免不必要的代码膨胀\n";
}

int main() {
    std::cout << "C++ Primer Chapter 16: 类模板演示\n";
    std::cout << "===============================\n";
    
    try {
        demonstrate_basic_class_templates();
        demonstrate_class_template_specialization();
        demonstrate_multiple_template_parameters();
        demonstrate_member_templates();
        demonstrate_partial_specialization();
        demonstrate_variadic_class_templates();
        demonstrate_template_template_parameters();
        demonstrate_crtp();
        demonstrate_template_metaprogramming();
        demonstrate_template_guidelines();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 