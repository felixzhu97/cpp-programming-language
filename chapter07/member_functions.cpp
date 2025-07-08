#include "common.h"

// 1. 基本成员函数类型
class MemberFunctionDemo {
private:
    int value;
    mutable int cache;  // mutable成员可以在const函数中修改
    
public:
    MemberFunctionDemo(int v) : value(v), cache(-1) {}
    
    // 1.1 普通成员函数
    void setValue(int v) {
        value = v;
        cache = -1;  // 使缓存失效
        cout << "  设置值: " << value << endl;
    }
    
    // 1.2 const成员函数 - 不修改对象状态
    int getValue() const {
        cout << "  获取值: " << value << endl;
        return value;
    }
    
    // 1.3 const成员函数中修改mutable成员
    int getExpensiveCalculation() const {
        if (cache == -1) {
            cout << "  计算昂贵操作..." << endl;
            cache = value * value + value;  // 模拟复杂计算
        } else {
            cout << "  使用缓存结果" << endl;
        }
        return cache;
    }
    
    // 1.4 内联成员函数
    inline int getSquare() const { return value * value; }
    
    // 1.5 返回引用的成员函数
    int& getValueRef() {
        cout << "  返回值的非const引用" << endl;
        return value;
    }
    
    const int& getValueRef() const {
        cout << "  返回值的const引用" << endl;
        return value;
    }
    
    // 1.6 返回this指针的成员函数（链式调用）
    MemberFunctionDemo& increment() {
        value++;
        cout << "  递增: " << value << endl;
        return *this;
    }
    
    MemberFunctionDemo& multiply(int factor) {
        value *= factor;
        cache = -1;
        cout << "  乘以 " << factor << ": " << value << endl;
        return *this;
    }
    
    MemberFunctionDemo& reset() {
        value = 0;
        cache = -1;
        cout << "  重置: " << value << endl;
        return *this;
    }
    
    void print() const {
        cout << "  当前值: " << value << ", 缓存: " << cache << endl;
    }
};

// 2. 重载成员函数
class OverloadedMethods {
private:
    vector<int> data;
    
public:
    OverloadedMethods() = default;
    
    // 重载的add方法
    void add(int value) {
        data.push_back(value);
        cout << "  添加整数: " << value << endl;
    }
    
    void add(const vector<int>& values) {
        data.insert(data.end(), values.begin(), values.end());
        cout << "  添加向量，大小: " << values.size() << endl;
    }
    
    void add(initializer_list<int> values) {
        data.insert(data.end(), values);
        cout << "  添加初始化列表，大小: " << values.size() << endl;
    }
    
    // 重载的访问方法
    int& at(size_t index) {
        cout << "  非const访问索引: " << index << endl;
        return data.at(index);
    }
    
    const int& at(size_t index) const {
        cout << "  const访问索引: " << index << endl;
        return data.at(index);
    }
    
    // 重载的查找方法
    bool find(int value) const {
        bool found = std::find(data.begin(), data.end(), value) != data.end();
        cout << "  查找值 " << value << ": " << (found ? "找到" : "未找到") << endl;
        return found;
    }
    
    vector<size_t> find(const vector<int>& values) const {
        vector<size_t> indices;
        for (const auto& value : values) {
            auto it = std::find(data.begin(), data.end(), value);
            if (it != data.end()) {
                indices.push_back(it - data.begin());
            }
        }
        cout << "  批量查找，找到 " << indices.size() << " 个" << endl;
        return indices;
    }
    
    void print() const {
        cout << "  数据: [";
        for (size_t i = 0; i < data.size(); i++) {
            cout << data[i];
            if (i < data.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

// 3. 静态成员函数与实例成员函数
class StaticVsInstance {
private:
    int instance_value;
    static int static_value;
    static int instance_count;
    
public:
    StaticVsInstance(int value) : instance_value(value) {
        static_value++;
        instance_count++;
        cout << "  创建实例 #" << instance_count << ", 值: " << value << endl;
    }
    
    ~StaticVsInstance() {
        instance_count--;
        cout << "  销毁实例，剩余: " << instance_count << endl;
    }
    
    // 实例成员函数
    void setInstanceValue(int value) {
        instance_value = value;
        cout << "  设置实例值: " << value << endl;
    }
    
    int getInstanceValue() const {
        return instance_value;
    }
    
    // 静态成员函数
    static void setStaticValue(int value) {
        static_value = value;
        cout << "  设置静态值: " << value << endl;
        // static_value可以访问
        // instance_value不可访问！ // 编译错误
    }
    
    static int getStaticValue() {
        return static_value;
    }
    
    static int getInstanceCount() {
        return instance_count;
    }
    
    // 混合方法 - 实例方法访问静态成员
    void printAll() const {
        cout << "  实例值: " << instance_value 
             << ", 静态值: " << static_value 
             << ", 实例数: " << instance_count << endl;
    }
    
    // 静态工厂方法
    static StaticVsInstance createDefault() {
        cout << "  使用静态工厂方法创建默认对象" << endl;
        return StaticVsInstance(100);
    }
    
    static StaticVsInstance createWithValue(int value) {
        cout << "  使用静态工厂方法创建对象，值: " << value << endl;
        return StaticVsInstance(value);
    }
};

// 静态成员定义
int StaticVsInstance::static_value = 0;
int StaticVsInstance::instance_count = 0;

// 4. 虚成员函数
class Shape {
protected:
    string name;
    
public:
    Shape(const string& n) : name(n) {
        cout << "  Shape构造: " << name << endl;
    }
    
    virtual ~Shape() {
        cout << "  Shape析构: " << name << endl;
    }
    
    // 纯虚函数
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    
    // 虚函数有默认实现
    virtual void print() const {
        cout << "  形状: " << name << ", 面积: " << area() 
             << ", 周长: " << perimeter() << endl;
    }
    
    // 非虚函数
    const string& getName() const { return name; }
    
    // 虚函数中调用其他虚函数
    virtual void describe() const {
        cout << "  这是一个" << name;
        cout << "，面积为" << area();
        cout << "，周长为" << perimeter() << endl;
    }
};

class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(double r) : Shape("圆形"), radius(r) {
        cout << "  Circle构造，半径: " << radius << endl;
    }
    
    ~Circle() {
        cout << "  Circle析构" << endl;
    }
    
    // 实现纯虚函数
    double area() const override {
        cout << "    计算圆形面积" << endl;
        return M_PI * radius * radius;
    }
    
    double perimeter() const override {
        cout << "    计算圆形周长" << endl;
        return 2 * M_PI * radius;
    }
    
    // 重写虚函数
    void print() const override {
        cout << "  " << name << " - 半径: " << radius 
             << ", 面积: " << area() << ", 周长: " << perimeter() << endl;
    }
    
    // 特有方法
    double getRadius() const { return radius; }
};

class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(double w, double h) : Shape("矩形"), width(w), height(h) {
        cout << "  Rectangle构造，尺寸: " << width << "x" << height << endl;
    }
    
    ~Rectangle() {
        cout << "  Rectangle析构" << endl;
    }
    
    double area() const override {
        cout << "    计算矩形面积" << endl;
        return width * height;
    }
    
    double perimeter() const override {
        cout << "    计算矩形周长" << endl;
        return 2 * (width + height);
    }
    
    void describe() const override {
        cout << "  这是一个" << name << "(" << width << "x" << height << ")";
        cout << "，面积为" << area();
        cout << "，周长为" << perimeter() << endl;
    }
    
    double getWidth() const { return width; }
    double getHeight() const { return height; }
};

// 5. 友元函数
class Complex {
private:
    double real, imag;
    
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    
    // 成员函数
    double getReal() const { return real; }
    double getImag() const { return imag; }
    
    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }
    
    // 成员运算符重载
    Complex operator+(const Complex& other) const {
        cout << "  成员函数加法" << endl;
        return Complex(real + other.real, imag + other.imag);
    }
    
    // 友元函数声明
    friend Complex operator-(const Complex& lhs, const Complex& rhs);
    friend Complex operator*(const Complex& lhs, const Complex& rhs);
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
    
    // 友元类声明
    friend class ComplexCalculator;
    
    void print() const {
        cout << "(" << real;
        if (imag >= 0) cout << "+";
        cout << imag << "i)";
    }
};

// 友元函数定义
Complex operator-(const Complex& lhs, const Complex& rhs) {
    cout << "  友元函数减法" << endl;
    return Complex(lhs.real - rhs.real, lhs.imag - rhs.imag);
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
    cout << "  友元函数乘法" << endl;
    return Complex(lhs.real * rhs.real - lhs.imag * rhs.imag,
                   lhs.real * rhs.imag + lhs.imag * rhs.real);
}

ostream& operator<<(ostream& os, const Complex& c) {
    os << "(" << c.real;
    if (c.imag >= 0) os << "+";
    os << c.imag << "i)";
    return os;
}

istream& operator>>(istream& is, Complex& c) {
    cout << "  输入实部: ";
    is >> c.real;
    cout << "  输入虚部: ";
    is >> c.imag;
    return is;
}

// 友元类
class ComplexCalculator {
public:
    static double magnitude(const Complex& c) {
        // 可以直接访问private成员
        return sqrt(c.real * c.real + c.imag * c.imag);
    }
    
    static double phase(const Complex& c) {
        return atan2(c.imag, c.real);
    }
    
    static Complex conjugate(const Complex& c) {
        return Complex(c.real, -c.imag);
    }
};

// 6. 成员函数指针
class Calculator {
public:
    int add(int a, int b) {
        cout << "  计算: " << a << " + " << b << " = " << (a + b) << endl;
        return a + b;
    }
    
    int multiply(int a, int b) {
        cout << "  计算: " << a << " * " << b << " = " << (a * b) << endl;
        return a * b;
    }
    
    int subtract(int a, int b) {
        cout << "  计算: " << a << " - " << b << " = " << (a - b) << endl;
        return a - b;
    }
    
    void print_result(int result) {
        cout << "  结果: " << result << endl;
    }
};

void demonstrateMemberFunctionBasics() {
    cout << "=== 基本成员函数演示 ===" << endl;
    
    MemberFunctionDemo obj(10);
    obj.print();
    
    cout << "\n链式调用:" << endl;
    obj.increment().multiply(3).increment().print();
    
    cout << "\nconst对象和const成员函数:" << endl;
    const MemberFunctionDemo const_obj(50);
    const_obj.getValue();
    const_obj.getExpensiveCalculation();
    const_obj.getExpensiveCalculation();  // 使用缓存
    
    cout << "\n引用返回:" << endl;
    obj.getValueRef() = 999;  // 修改值
    obj.print();
}

void demonstrateOverloadedMethods() {
    cout << "\n=== 重载成员函数演示 ===" << endl;
    
    OverloadedMethods container;
    
    container.add(1);
    container.add({2, 3, 4});
    container.add(vector<int>{5, 6, 7});
    container.print();
    
    cout << "\n访问元素:" << endl;
    cout << "  元素[2]: " << container.at(2) << endl;
    
    const OverloadedMethods& const_container = container;
    cout << "  const访问[4]: " << const_container.at(4) << endl;
    
    cout << "\n查找方法:" << endl;
    container.find(3);
    container.find({2, 8, 5});
}

void demonstrateStaticVsInstance() {
    cout << "\n=== 静态vs实例成员函数演示 ===" << endl;
    
    cout << "初始状态:" << endl;
    cout << "  静态值: " << StaticVsInstance::getStaticValue() << endl;
    cout << "  实例数: " << StaticVsInstance::getInstanceCount() << endl;
    
    {
        cout << "\n创建实例:" << endl;
        StaticVsInstance obj1(10);
        StaticVsInstance obj2(20);
        
        obj1.printAll();
        obj2.printAll();
        
        cout << "\n修改静态值:" << endl;
        StaticVsInstance::setStaticValue(999);
        obj1.printAll();
        obj2.printAll();
        
        cout << "\n使用工厂方法:" << endl;
        auto obj3 = StaticVsInstance::createDefault();
        auto obj4 = StaticVsInstance::createWithValue(777);
        
        obj3.printAll();
        obj4.printAll();
    }
    
    cout << "\n作用域结束后:" << endl;
    cout << "  实例数: " << StaticVsInstance::getInstanceCount() << endl;
}

void demonstrateVirtualFunctions() {
    cout << "\n=== 虚成员函数演示 ===" << endl;
    
    cout << "创建具体对象:" << endl;
    Circle circle(5.0);
    Rectangle rect(4.0, 6.0);
    
    cout << "\n直接调用:" << endl;
    circle.print();
    rect.print();
    
    cout << "\n多态调用:" << endl;
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<Circle>(3.0));
    shapes.push_back(make_unique<Rectangle>(2.0, 8.0));
    shapes.push_back(make_unique<Circle>(7.0));
    
    for (const auto& shape : shapes) {
        shape->describe();
    }
    
    cout << "\n虚函数调用链:" << endl;
    Shape* shape_ptr = new Circle(4.0);
    shape_ptr->print();  // 调用Circle::print
    delete shape_ptr;
}

void demonstrateFriendFunctions() {
    cout << "\n=== 友元函数演示 ===" << endl;
    
    Complex c1(3, 4);
    Complex c2(1, 2);
    
    cout << "复数c1: " << c1 << endl;
    cout << "复数c2: " << c2 << endl;
    
    cout << "\n运算:" << endl;
    Complex c3 = c1 + c2;  // 成员函数
    cout << "c1 + c2 = " << c3 << endl;
    
    Complex c4 = c1 - c2;  // 友元函数
    cout << "c1 - c2 = " << c4 << endl;
    
    Complex c5 = c1 * c2;  // 友元函数
    cout << "c1 * c2 = " << c5 << endl;
    
    cout << "\n友元类方法:" << endl;
    cout << "c1的模长: " << ComplexCalculator::magnitude(c1) << endl;
    cout << "c1的相位: " << ComplexCalculator::phase(c1) << endl;
    cout << "c1的共轭: " << ComplexCalculator::conjugate(c1) << endl;
}

void demonstrateMemberFunctionPointers() {
    cout << "\n=== 成员函数指针演示 ===" << endl;
    
    Calculator calc;
    
    // 成员函数指针语法
    int (Calculator::*operation)(int, int) = &Calculator::add;
    
    cout << "使用成员函数指针:" << endl;
    int result = (calc.*operation)(10, 5);
    
    // 成员函数指针数组
    int (Calculator::*operations[])(int, int) = {
        &Calculator::add,
        &Calculator::multiply,
        &Calculator::subtract
    };
    
    string names[] = {"加法", "乘法", "减法"};
    
    cout << "\n使用函数指针数组:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << names[i] << ": ";
        (calc.*operations[i])(12, 3);
    }
    
    // 成员函数指针与std::function
    function<int(Calculator*, int, int)> func_ptr = &Calculator::multiply;
    cout << "\n使用std::function包装成员函数指针:" << endl;
    func_ptr(&calc, 7, 8);
    
    // 使用bind
    auto bound_func = bind(&Calculator::add, &calc, placeholders::_1, placeholders::_2);
    cout << "\n使用bind绑定对象:" << endl;
    bound_func(15, 25);
}

int main() {
    print_separator("成员函数详解");
    
    // 1. 基本成员函数
    demonstrateMemberFunctionBasics();
    
    // 2. 重载成员函数
    demonstrateOverloadedMethods();
    
    // 3. 静态vs实例成员函数
    demonstrateStaticVsInstance();
    
    // 4. 虚成员函数
    demonstrateVirtualFunctions();
    
    // 5. 友元函数
    demonstrateFriendFunctions();
    
    // 6. 成员函数指针
    demonstrateMemberFunctionPointers();
    
    // 7. 成员函数最佳实践
    cout << "\n=== 成员函数最佳实践 ===" << endl;
    cout << "1. const正确性:" << endl;
    cout << "   - 不修改对象状态的方法声明为const" << endl;
    cout << "   - 提供const和非const版本的访问器" << endl;
    cout << "   - 使用mutable关键字处理缓存等情况" << endl;
    
    cout << "\n2. 访问控制:" << endl;
    cout << "   - 最小化公共接口" << endl;
    cout << "   - 将实现细节放在private中" << endl;
    cout << "   - 合理使用protected给派生类" << endl;
    
    cout << "\n3. 虚函数使用:" << endl;
    cout << "   - 基类析构函数应该是虚函数" << endl;
    cout << "   - 使用override关键字明确重写意图" << endl;
    cout << "   - 考虑纯虚函数定义接口" << endl;
    
    cout << "\n4. 性能考虑:" << endl;
    cout << "   - 频繁调用的简单函数考虑内联" << endl;
    cout << "   - 返回引用避免不必要拷贝" << endl;
    cout << "   - 使用移动语义优化参数传递" << endl;
    
    cout << "\n5. 设计原则:" << endl;
    cout << "   - 函数功能单一且明确" << endl;
    cout << "   - 链式调用返回引用" << endl;
    cout << "   - 异常安全保证" << endl;
    cout << "   - 考虑线程安全性" << endl;
    
    print_separator("成员函数详解完成");
    
    return 0;
} 