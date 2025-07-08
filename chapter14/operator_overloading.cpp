/**
 * @file operator_overloading.cpp
 * @brief 运算符重载演示 - 算术、比较、特殊运算符的重载
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 复数类 - 演示算术运算符重载
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // 访问器
    double get_real() const { return real; }
    double get_imag() const { return imag; }
    
    // 算术运算符重载（成员函数）
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    // 复合赋值运算符
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    Complex& operator-=(const Complex& other) {
        real -= other.real;
        imag -= other.imag;
        return *this;
    }
    
    // 比较运算符
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // 前缀递增
    Complex& operator++() {
        ++real;
        return *this;
    }
    
    // 后缀递增
    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        return temp;
    }
    
    // 下标运算符
    double& operator[](int index) {
        return index == 0 ? real : imag;
    }
    
    const double& operator[](int index) const {
        return index == 0 ? real : imag;
    }
    
    // 流插入运算符（友元函数）
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real;
        if (c.imag >= 0) os << " + ";
        else os << " - ";
        os << std::abs(c.imag) << "i)";
        return os;
    }
    
    // 流提取运算符（友元函数）
    friend std::istream& operator>>(std::istream& is, Complex& c) {
        is >> c.real >> c.imag;
        return is;
    }
};

// 智能指针类 - 演示指针相关运算符重载
template<typename T>
class SmartPtr {
private:
    T* ptr;
    
public:
    explicit SmartPtr(T* p = nullptr) : ptr(p) {}
    
    ~SmartPtr() {
        delete ptr;
    }
    
    // 禁用拷贝构造和拷贝赋值
    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;
    
    // 移动构造
    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    // 移动赋值
    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    // 解引用运算符
    T& operator*() const {
        return *ptr;
    }
    
    // 成员访问运算符
    T* operator->() const {
        return ptr;
    }
    
    // 布尔转换运算符
    explicit operator bool() const {
        return ptr != nullptr;
    }
    
    // 获取原始指针
    T* get() const {
        return ptr;
    }
    
    // 释放所有权
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    // 重置指针
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
};

// 动态数组类 - 演示下标和比较运算符
class DynamicArray {
private:
    int* data;
    size_t size;
    size_t capacity;
    
    void resize_if_needed() {
        if (size >= capacity) {
            capacity = capacity == 0 ? 1 : capacity * 2;
            int* new_data = new int[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
    }
    
public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}
    
    ~DynamicArray() {
        delete[] data;
    }
    
    // 拷贝构造函数
    DynamicArray(const DynamicArray& other) 
        : size(other.size), capacity(other.capacity) {
        data = new int[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // 拷贝赋值运算符
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new int[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // 下标运算符
    int& operator[](size_t index) {
        return data[index];
    }
    
    const int& operator[](size_t index) const {
        return data[index];
    }
    
    // 添加元素
    void push_back(int value) {
        resize_if_needed();
        data[size++] = value;
    }
    
    // 获取大小
    size_t get_size() const {
        return size;
    }
    
    // 比较运算符
    bool operator==(const DynamicArray& other) const {
        if (size != other.size) return false;
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }
    
    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }
    
    // 流插入运算符
    friend std::ostream& operator<<(std::ostream& os, const DynamicArray& arr) {
        os << "[";
        for (size_t i = 0; i < arr.size; ++i) {
            if (i > 0) os << ", ";
            os << arr.data[i];
        }
        os << "]";
        return os;
    }
};

// 字符串类 - 演示各种运算符重载
class MyString {
private:
    char* data;
    size_t len;
    
public:
    MyString(const char* str = "") {
        len = std::strlen(str);
        data = new char[len + 1];
        std::strcpy(data, str);
    }
    
    ~MyString() {
        delete[] data;
    }
    
    // 拷贝构造
    MyString(const MyString& other) : len(other.len) {
        data = new char[len + 1];
        std::strcpy(data, other.data);
    }
    
    // 拷贝赋值
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            len = other.len;
            data = new char[len + 1];
            std::strcpy(data, other.data);
        }
        return *this;
    }
    
    // 字符串连接
    MyString operator+(const MyString& other) const {
        MyString result;
        result.len = len + other.len;
        result.data = new char[result.len + 1];
        std::strcpy(result.data, data);
        std::strcat(result.data, other.data);
        return result;
    }
    
    // 复合赋值
    MyString& operator+=(const MyString& other) {
        char* new_data = new char[len + other.len + 1];
        std::strcpy(new_data, data);
        std::strcat(new_data, other.data);
        delete[] data;
        data = new_data;
        len += other.len;
        return *this;
    }
    
    // 比较运算符
    bool operator==(const MyString& other) const {
        return std::strcmp(data, other.data) == 0;
    }
    
    bool operator<(const MyString& other) const {
        return std::strcmp(data, other.data) < 0;
    }
    
    bool operator>(const MyString& other) const {
        return std::strcmp(data, other.data) > 0;
    }
    
    // 下标运算符
    char& operator[](size_t index) {
        return data[index];
    }
    
    const char& operator[](size_t index) const {
        return data[index];
    }
    
    // 获取C字符串
    const char* c_str() const {
        return data;
    }
    
    size_t length() const {
        return len;
    }
    
    // 流运算符
    friend std::ostream& operator<<(std::ostream& os, const MyString& str) {
        os << str.data;
        return os;
    }
};

void demonstrate_complex_operators() {
    std::cout << "\n=== 复数类运算符重载 ===\n";
    
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    std::cout << "c1 = " << c1 << "\n";
    std::cout << "c2 = " << c2 << "\n";
    
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << "\n";
    
    Complex c4 = c1 * c2;
    std::cout << "c1 * c2 = " << c4 << "\n";
    
    c1 += c2;
    std::cout << "c1 += c2: " << c1 << "\n";
    
    std::cout << "c1 == c2: " << (c1 == c2 ? "true" : "false") << "\n";
    
    // 前缀和后缀递增
    Complex c5 = ++c1;
    std::cout << "++c1 = " << c5 << ", c1 = " << c1 << "\n";
    
    Complex c6 = c1++;
    std::cout << "c1++ = " << c6 << ", c1 = " << c1 << "\n";
    
    // 下标访问
    std::cout << "c1[0] (实部) = " << c1[0] << "\n";
    std::cout << "c1[1] (虚部) = " << c1[1] << "\n";
}

void demonstrate_smart_pointer() {
    std::cout << "\n=== 智能指针运算符重载 ===\n";
    
    SmartPtr<std::string> ptr(new std::string("Hello World"));
    
    // 解引用运算符
    std::cout << "解引用: " << *ptr << "\n";
    
    // 成员访问运算符
    std::cout << "长度: " << ptr->length() << "\n";
    
    // 布尔转换
    if (ptr) {
        std::cout << "指针有效\n";
    }
    
    // 释放所有权
    std::string* raw_ptr = ptr.release();
    std::cout << "释放后，原始指针: " << *raw_ptr << "\n";
    
    if (!ptr) {
        std::cout << "智能指针现在为空\n";
    }
    
    delete raw_ptr; // 手动删除
}

void demonstrate_dynamic_array() {
    std::cout << "\n=== 动态数组运算符重载 ===\n";
    
    DynamicArray arr1;
    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);
    
    std::cout << "arr1 = " << arr1 << "\n";
    
    DynamicArray arr2 = arr1; // 拷贝构造
    std::cout << "arr2 (拷贝) = " << arr2 << "\n";
    
    // 下标访问
    arr2[1] = 99;
    std::cout << "修改 arr2[1] = 99: " << arr2 << "\n";
    
    // 比较
    std::cout << "arr1 == arr2: " << (arr1 == arr2 ? "true" : "false") << "\n";
    std::cout << "arr1 != arr2: " << (arr1 != arr2 ? "true" : "false") << "\n";
}

void demonstrate_string_operators() {
    std::cout << "\n=== 自定义字符串运算符重载 ===\n";
    
    MyString str1("Hello");
    MyString str2(" World");
    
    std::cout << "str1 = " << str1 << "\n";
    std::cout << "str2 = " << str2 << "\n";
    
    // 字符串连接
    MyString str3 = str1 + str2;
    std::cout << "str1 + str2 = " << str3 << "\n";
    
    // 复合赋值
    str1 += str2;
    std::cout << "str1 += str2: " << str1 << "\n";
    
    // 比较
    MyString str4("Hello World");
    std::cout << "str1 == str4: " << (str1 == str4 ? "true" : "false") << "\n";
    
    // 下标访问
    std::cout << "str1[0] = " << str1[0] << "\n";
    str1[0] = 'h';
    std::cout << "修改 str1[0] = 'h': " << str1 << "\n";
    
    // 比较运算
    MyString str5("Apple");
    MyString str6("Banana");
    std::cout << "\"Apple\" < \"Banana\": " << (str5 < str6 ? "true" : "false") << "\n";
}

void demonstrate_operator_guidelines() {
    std::cout << "\n=== 运算符重载指导原则 ===\n";
    
    std::cout << "1. 保持运算符的常规含义\n";
    std::cout << "2. 对称的运算符应该有对称的行为\n";
    std::cout << "3. 复合赋值运算符应该返回 *this 的引用\n";
    std::cout << "4. 前缀递增/递减返回引用，后缀返回值\n";
    std::cout << "5. 比较运算符应该定义传递性关系\n";
    std::cout << "6. 流运算符应该为非成员函数\n";
    std::cout << "7. 下标运算符应该有 const 和非 const 版本\n";
    std::cout << "8. 不要重载 &&、||、逗号运算符\n";
    std::cout << "9. 优先使用成员函数重载赋值类运算符\n";
    std::cout << "10. 优先使用非成员函数重载对称运算符\n";
}

int main() {
    std::cout << "C++ Primer Chapter 14: 运算符重载演示\n";
    std::cout << "====================================\n";
    
    try {
        demonstrate_complex_operators();
        demonstrate_smart_pointer();
        demonstrate_dynamic_array();
        demonstrate_string_operators();
        demonstrate_operator_guidelines();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 