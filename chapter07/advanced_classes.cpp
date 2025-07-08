/*
 * 第7章：类 - 高级特性
 * 展示运算符重载、类型转换运算符、抽象类、接口类等高级特性
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace advanced_classes_demo {

// 1. 运算符重载示例 - 复数类
class Complex {
private:
    double real;
    double imag;
    
public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    
    // 算术运算符重载
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(
            real * other.real - imag * other.imag,
            real * other.imag + imag * other.real
        );
    }
    
    // 复合赋值运算符
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    
    // 比较运算符
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }
    
    // 下标运算符（假设索引0为实部，索引1为虚部）
    double& operator[](int index) {
        return index == 0 ? real : imag;
    }
    
    const double& operator[](int index) const {
        return index == 0 ? real : imag;
    }
    
    // 前置递增
    Complex& operator++() {
        ++real;
        return *this;
    }
    
    // 后置递增
    Complex operator++(int) {
        Complex temp(*this);
        ++real;
        return temp;
    }
    
    // 友元函数：输出运算符
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
    friend std::istream& operator>>(std::istream& is, Complex& c);
    
    // 成员函数访问器
    double getReal() const { return real; }
    double getImag() const { return imag; }
    
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }
};

// 友元函数定义
std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i";
    return os;
}

std::istream& operator>>(std::istream& is, Complex& c) {
    std::cout << "输入实部: ";
    is >> c.real;
    std::cout << "输入虚部: ";
    is >> c.imag;
    return is;
}

// 2. 类型转换运算符
class Money {
private:
    double amount;
    std::string currency;
    
public:
    Money(double a = 0.0, const std::string& c = "USD") 
        : amount(a), currency(c) {}
    
    // 隐式类型转换运算符
    operator double() const {
        return amount;
    }
    
    // 显式类型转换运算符
    explicit operator std::string() const {
        return std::to_string(amount) + " " + currency;
    }
    
    // 转换构造函数
    Money(double a) : amount(a), currency("USD") {}
    
    Money operator+(const Money& other) const {
        if (currency == other.currency) {
            return Money(amount + other.amount, currency);
        }
        // 简化处理：假设转换为美元
        return Money(amount + other.amount, "USD");
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Money& m) {
        os << m.amount << " " << m.currency;
        return os;
    }
    
    double getAmount() const { return amount; }
    std::string getCurrency() const { return currency; }
};

// 3. 抽象基类和接口
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;  // 纯虚函数
    virtual void resize(double factor) = 0;
    
    // 非纯虚函数
    virtual void display() const {
        std::cout << "显示图形: ";
        draw();
    }
};

class Colorable {
public:
    virtual ~Colorable() = default;
    virtual void setColor(const std::string& color) = 0;
    virtual std::string getColor() const = 0;
};

// 具体实现类
class Circle : public Drawable, public Colorable {
private:
    double radius;
    std::string color;
    
public:
    Circle(double r, const std::string& c = "black") 
        : radius(r), color(c) {}
    
    void draw() const override {
        std::cout << "绘制半径为 " << radius << " 的" << color << "圆形" << std::endl;
    }
    
    void resize(double factor) override {
        radius *= factor;
        std::cout << "圆形缩放因子: " << factor << ", 新半径: " << radius << std::endl;
    }
    
    void setColor(const std::string& c) override {
        color = c;
    }
    
    std::string getColor() const override {
        return color;
    }
    
    double getRadius() const { return radius; }
};

class Rectangle : public Drawable, public Colorable {
private:
    double width, height;
    std::string color;
    
public:
    Rectangle(double w, double h, const std::string& c = "black") 
        : width(w), height(h), color(c) {}
    
    void draw() const override {
        std::cout << "绘制 " << width << "x" << height << " 的" << color << "矩形" << std::endl;
    }
    
    void resize(double factor) override {
        width *= factor;
        height *= factor;
        std::cout << "矩形缩放因子: " << factor 
                  << ", 新尺寸: " << width << "x" << height << std::endl;
    }
    
    void setColor(const std::string& c) override {
        color = c;
    }
    
    std::string getColor() const override {
        return color;
    }
    
    double getArea() const { return width * height; }
};

// 4. 函数对象（仿函数）
class Comparator {
public:
    bool operator()(int a, int b) const {
        return a < b;
    }
};

class StringLengthComparator {
public:
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length();
    }
};

// 5. RAII资源管理类
template<typename T>
class SmartPtr {
private:
    T* ptr;
    
public:
    explicit SmartPtr(T* p = nullptr) : ptr(p) {}
    
    ~SmartPtr() {
        delete ptr;
        std::cout << "SmartPtr析构，释放资源" << std::endl;
    }
    
    // 禁用拷贝
    SmartPtr(const SmartPtr&) = delete;
    SmartPtr& operator=(const SmartPtr&) = delete;
    
    // 支持移动
    SmartPtr(SmartPtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }
    
    SmartPtr& operator=(SmartPtr&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }
    
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    
    T* get() const { return ptr; }
    
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }
    
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }
    
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

// 6. 特殊成员函数示例
class Resource {
private:
    std::string name;
    int* data;
    size_t size;
    
public:
    // 构造函数
    Resource(const std::string& n, size_t s) 
        : name(n), size(s), data(new int[s]) {
        std::cout << "创建资源: " << name << std::endl;
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
    }
    
    // 析构函数
    ~Resource() {
        delete[] data;
        std::cout << "销毁资源: " << name << std::endl;
    }
    
    // 拷贝构造函数
    Resource(const Resource& other) 
        : name(other.name + "_copy"), size(other.size), data(new int[size]) {
        std::cout << "拷贝构造资源: " << name << std::endl;
        std::copy(other.data, other.data + size, data);
    }
    
    // 拷贝赋值运算符
    Resource& operator=(const Resource& other) {
        if (this != &other) {
            std::cout << "拷贝赋值资源: " << other.name << " -> " << name << std::endl;
            
            // 先释放当前资源
            delete[] data;
            
            // 分配新资源
            name = other.name + "_assigned";
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
        }
        return *this;
    }
    
    // 移动构造函数
    Resource(Resource&& other) noexcept 
        : name(std::move(other.name)), size(other.size), data(other.data) {
        std::cout << "移动构造资源: " << name << std::endl;
        other.data = nullptr;
        other.size = 0;
    }
    
    // 移动赋值运算符
    Resource& operator=(Resource&& other) noexcept {
        if (this != &other) {
            std::cout << "移动赋值资源: " << other.name << " -> " << name << std::endl;
            
            // 释放当前资源
            delete[] data;
            
            // 移动资源
            name = std::move(other.name);
            size = other.size;
            data = other.data;
            
            // 重置源对象
            other.data = nullptr;
            other.size = 0;
        }
        return *this;
    }
    
    void display() const {
        std::cout << "资源 " << name << " (大小: " << size << "): ";
        if (data && size > 0) {
            for (size_t i = 0; i < std::min(size, size_t(5)); ++i) {
                std::cout << data[i] << " ";
            }
            if (size > 5) std::cout << "...";
        }
        std::cout << std::endl;
    }
    
    std::string getName() const { return name; }
};

// 7. 模板类基础
template<typename T>
class Container {
private:
    std::vector<T> data;
    
public:
    void add(const T& item) {
        data.push_back(item);
    }
    
    T& operator[](size_t index) {
        return data[index];
    }
    
    const T& operator[](size_t index) const {
        return data[index];
    }
    
    size_t size() const {
        return data.size();
    }
    
    void display() const {
        std::cout << "容器内容: ";
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    
    // 迭代器支持
    typename std::vector<T>::iterator begin() { return data.begin(); }
    typename std::vector<T>::iterator end() { return data.end(); }
    typename std::vector<T>::const_iterator begin() const { return data.begin(); }
    typename std::vector<T>::const_iterator end() const { return data.end(); }
};

void demonstrateAdvancedClasses() {
    std::cout << "\n=== 高级类特性演示 ===" << std::endl;
    
    // 1. 运算符重载
    std::cout << "\n1. 复数运算符重载：" << std::endl;
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    std::cout << "c1 = " << c1 << std::endl;
    std::cout << "c2 = " << c2 << std::endl;
    
    Complex c3 = c1 + c2;
    std::cout << "c1 + c2 = " << c3 << std::endl;
    
    Complex c4 = c1 * c2;
    std::cout << "c1 * c2 = " << c4 << std::endl;
    
    c1 += c2;
    std::cout << "c1 += c2, c1 = " << c1 << std::endl;
    
    std::cout << "c1[0] (实部) = " << c1[0] << std::endl;
    std::cout << "c1[1] (虚部) = " << c1[1] << std::endl;
    
    Complex c5 = c1++;
    std::cout << "c1++后, c1 = " << c1 << ", c5 = " << c5 << std::endl;
    
    // 2. 类型转换运算符
    std::cout << "\n2. 类型转换运算符：" << std::endl;
    Money m1(100.50, "USD");
    Money m2(50.25, "USD");
    
    std::cout << "m1 = " << m1 << std::endl;
    std::cout << "m2 = " << m2 << std::endl;
    
    Money m3 = m1 + m2;
    std::cout << "m1 + m2 = " << m3 << std::endl;
    
    // 隐式转换
    double amount = m1;  // 调用operator double()
    std::cout << "m1转换为double: " << amount << std::endl;
    
    // 显式转换
    std::string moneyStr = static_cast<std::string>(m1);
    std::cout << "m1转换为string: " << moneyStr << std::endl;
    
    // 3. 抽象类和多态
    std::cout << "\n3. 抽象类和多态：" << std::endl;
    std::vector<std::unique_ptr<Drawable>> shapes;
    shapes.push_back(std::make_unique<Circle>(5.0, "红色"));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0, "蓝色"));
    
    for (auto& shape : shapes) {
        shape->display();
        shape->resize(1.5);
    }
    
    // 接口使用
    Circle circle(3.0, "绿色");
    Colorable* colorable = &circle;
    colorable->setColor("黄色");
    std::cout << "圆形颜色: " << colorable->getColor() << std::endl;
    
    // 4. 函数对象
    std::cout << "\n4. 函数对象（仿函数）：" << std::endl;
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    std::cout << "排序前: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    std::sort(numbers.begin(), numbers.end(), Comparator());
    std::cout << "排序后: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;
    
    std::vector<std::string> words = {"hello", "world", "C++", "programming", "is", "fun"};
    std::sort(words.begin(), words.end(), StringLengthComparator());
    std::cout << "按长度排序的单词: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << std::endl;
    
    // 5. RAII智能指针
    std::cout << "\n5. RAII智能指针：" << std::endl;
    {
        SmartPtr<int> ptr(new int(42));
        std::cout << "智能指针值: " << *ptr << std::endl;
        
        SmartPtr<std::string> strPtr(new std::string("Hello"));
        std::cout << "字符串指针: " << *strPtr << std::endl;
        
        // 移动语义
        SmartPtr<int> ptr2 = std::move(ptr);
        std::cout << "移动后ptr2值: " << *ptr2 << std::endl;
        std::cout << "ptr是否有效: " << static_cast<bool>(ptr) << std::endl;
    }  // 自动释放资源
    
    // 6. 特殊成员函数
    std::cout << "\n6. 特殊成员函数：" << std::endl;
    Resource r1("资源1", 10);
    r1.display();
    
    Resource r2 = r1;  // 拷贝构造
    r2.display();
    
    Resource r3("资源3", 5);
    r3 = r1;  // 拷贝赋值
    r3.display();
    
    Resource r4 = std::move(r1);  // 移动构造
    r4.display();
    r1.display();  // r1应该为空
    
    // 7. 模板类
    std::cout << "\n7. 模板类容器：" << std::endl;
    Container<int> intContainer;
    intContainer.add(1);
    intContainer.add(2);
    intContainer.add(3);
    intContainer.display();
    
    Container<std::string> stringContainer;
    stringContainer.add("Hello");
    stringContainer.add("World");
    stringContainer.add("Template");
    stringContainer.display();
    
    // 使用迭代器
    std::cout << "使用迭代器遍历: ";
    for (auto it = intContainer.begin(); it != intContainer.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

} // namespace advanced_classes_demo

int main() {
    advanced_classes_demo::demonstrateAdvancedClasses();
    return 0;
} 