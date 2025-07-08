#include "common.h"

// 1. 基本函数重载 - 不同参数数量
void print() {
    cout << "无参数的print函数" << endl;
}

void print(int value) {
    cout << "打印整数: " << value << endl;
}

void print(int value1, int value2) {
    cout << "打印两个整数: " << value1 << ", " << value2 << endl;
}

// 2. 不同参数类型的重载
void display(int value) {
    cout << "显示整数: " << value << endl;
}

void display(double value) {
    cout << "显示浮点数: " << value << endl;
}

void display(char value) {
    cout << "显示字符: " << value << endl;
}

void display(const string& value) {
    cout << "显示字符串: " << value << endl;
}

void display(bool value) {
    cout << "显示布尔值: " << (value ? "true" : "false") << endl;
}

// 3. 常量重载（const overloading）
class Container {
private:
    vector<int> data;
    
public:
    Container(initializer_list<int> init) : data(init) {}
    
    // 非常量版本 - 可以修改
    int& get(size_t index) {
        cout << "  调用非常量版本get()" << endl;
        return data[index];
    }
    
    // 常量版本 - 只读访问
    const int& get(size_t index) const {
        cout << "  调用常量版本get()" << endl;
        return data[index];
    }
    
    void print() const {
        cout << "  容器内容: ";
        for (int val : data) {
            cout << val << " ";
        }
        cout << endl;
    }
};

// 4. 引用和指针参数重载
void process(int value) {
    cout << "处理值: " << value << endl;
}

void process(int& value) {
    cout << "处理引用: " << value << " (可修改)" << endl;
    value *= 2;
}

void process(const int& value) {
    cout << "处理常量引用: " << value << " (只读)" << endl;
}

void process(int* value) {
    if (value) {
        cout << "处理指针: " << *value << " (可修改)" << endl;
        *value *= 3;
    } else {
        cout << "处理空指针" << endl;
    }
}

// 5. 数组参数重载
void analyze(int arr[], int size) {
    cout << "分析C风格数组，大小: " << size << endl;
    cout << "  元素: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void analyze(const vector<int>& arr) {
    cout << "分析vector，大小: " << arr.size() << endl;
    cout << "  元素: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

void analyze(const array<int, 5>& arr) {
    cout << "分析std::array<int, 5>" << endl;
    cout << "  元素: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

// 6. 模板函数重载
template<typename T>
void calculate(T value) {
    cout << "模板函数: 计算 " << value << " 的平方 = " << value * value << endl;
}

// 特化版本
void calculate(const string& value) {
    cout << "特化版本: 字符串 \"" << value << "\" 的长度 = " << value.length() << endl;
}

// 7. 重载运算符函数
class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // 成员函数运算符重载
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
    
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
    
    Point& operator+=(const Point& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
    
    double getX() const { return x; }
    double getY() const { return y; }
};

// 友元函数运算符重载
Point operator*(const Point& p, double scalar) {
    return Point(p.getX() * scalar, p.getY() * scalar);
}

Point operator*(double scalar, const Point& p) {
    return Point(p.getX() * scalar, p.getY() * scalar);
}

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.getX() << ", " << p.getY() << ")";
    return os;
}

// 8. 函数对象重载（仿函数）
class Multiplier {
private:
    double factor;
    
public:
    Multiplier(double f) : factor(f) {}
    
    // 重载函数调用运算符
    double operator()(double value) const {
        return value * factor;
    }
    
    int operator()(int value) const {
        return static_cast<int>(value * factor);
    }
    
    string operator()(const string& str) const {
        string result;
        for (int i = 0; i < static_cast<int>(factor); i++) {
            result += str;
        }
        return result;
    }
};

// 9. 重载解析优先级演示
class OverloadDemo {
public:
    void func(int x) {
        cout << "  func(int): " << x << endl;
    }
    
    void func(double x) {
        cout << "  func(double): " << x << endl;
    }
    
    void func(const char* x) {
        cout << "  func(const char*): " << x << endl;
    }
    
    void func(const string& x) {
        cout << "  func(const string&): " << x << endl;
    }
    
    template<typename T>
    void func(T x) {
        cout << "  func(template T): " << x << endl;
    }
};

// 10. 重载的最佳匹配规则演示
void match_test(int value) {
    cout << "  匹配到: int版本, 值: " << value << endl;
}

void match_test(long value) {
    cout << "  匹配到: long版本, 值: " << value << endl;
}

void match_test(double value) {
    cout << "  匹配到: double版本, 值: " << value << endl;
}

// 11. 构造函数重载
class Rectangle {
private:
    double width, height;
    
public:
    // 默认构造函数
    Rectangle() : width(1.0), height(1.0) {
        cout << "  默认构造函数: 1x1 矩形" << endl;
    }
    
    // 单参数构造函数（正方形）
    Rectangle(double side) : width(side), height(side) {
        cout << "  单参数构造函数: " << side << "x" << side << " 正方形" << endl;
    }
    
    // 双参数构造函数
    Rectangle(double w, double h) : width(w), height(h) {
        cout << "  双参数构造函数: " << w << "x" << h << " 矩形" << endl;
    }
    
    // 拷贝构造函数
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {
        cout << "  拷贝构造函数: 复制 " << width << "x" << height << " 矩形" << endl;
    }
    
    double area() const {
        return width * height;
    }
    
    void print() const {
        cout << "  矩形: " << width << "x" << height << ", 面积: " << area() << endl;
    }
};

// 12. 重载的常见错误示例
class OverloadErrors {
public:
    // 正确的重载
    void correct1(int x) { cout << "correct1(int)" << endl; }
    void correct1(double x) { cout << "correct1(double)" << endl; }
    
    // 错误示例1：仅返回类型不同（编译错误）
    // int error1(int x) { return x; }
    // double error1(int x) { return x; }  // 错误！
    
    // 错误示例2：参数名不同不算重载（编译错误）
    // void error2(int x) { }
    // void error2(int y) { }  // 错误！
    
    // 错误示例3：const位置不同的重载
    void const_demo(int x) { cout << "const_demo(int)" << endl; }
    void const_demo(const int x) { cout << "const_demo(const int)" << endl; }  // 实际上不是重载
    
    // 正确的const重载
    void correct_const(int& x) { cout << "correct_const(int&)" << endl; }
    void correct_const(const int& x) { cout << "correct_const(const int&)" << endl; }
};

// 13. 重载与模板的交互
template<typename T>
void template_overload(T value) {
    cout << "  模板版本: " << value << endl;
}

void template_overload(int value) {
    cout << "  特化版本(int): " << value << endl;
}

void template_overload(double value) {
    cout << "  特化版本(double): " << value << endl;
}

int main() {
    print_separator("函数重载详解");
    
    // 1. 基本函数重载
    cout << "=== 基本函数重载 ===" << endl;
    
    print();
    print(42);
    print(10, 20);
    
    // 2. 不同类型参数重载
    cout << "\n=== 不同类型参数重载 ===" << endl;
    
    display(100);
    display(3.14);
    display('A');
    display("Hello World");
    display(true);
    
    // 3. 常量重载
    cout << "\n=== 常量重载 ===" << endl;
    
    Container container{1, 2, 3, 4, 5};
    const Container const_container{10, 20, 30};
    
    cout << "非常量对象访问:" << endl;
    int& ref = container.get(0);
    ref = 999;
    container.print();
    
    cout << "常量对象访问:" << endl;
    const int& const_ref = const_container.get(0);
    cout << "  获取到的值: " << const_ref << endl;
    
    // 4. 引用和指针参数重载
    cout << "\n=== 引用和指针参数重载 ===" << endl;
    
    int value = 10;
    const int const_value = 20;
    
    cout << "处理不同类型的参数:" << endl;
    process(5);           // 按值传递
    process(value);       // 按引用传递
    process(const_value); // 按常量引用传递
    process(&value);      // 按指针传递
    process(nullptr);     // 空指针
    
    cout << "修改后的value: " << value << endl;
    
    // 5. 数组参数重载
    cout << "\n=== 数组参数重载 ===" << endl;
    
    int c_array[] = {1, 2, 3, 4, 5};
    vector<int> vector_array = {6, 7, 8, 9, 10};
    array<int, 5> std_array = {11, 12, 13, 14, 15};
    
    analyze(c_array, 5);
    analyze(vector_array);
    analyze(std_array);
    
    // 6. 模板函数重载
    cout << "\n=== 模板函数重载 ===" << endl;
    
    calculate(5);
    calculate(3.14);
    calculate(string("Hello"));
    
    // 7. 运算符重载
    cout << "\n=== 运算符重载 ===" << endl;
    
    Point p1(3, 4);
    Point p2(1, 2);
    
    cout << "点p1: " << p1 << endl;
    cout << "点p2: " << p2 << endl;
    
    Point p3 = p1 + p2;
    cout << "p1 + p2 = " << p3 << endl;
    
    Point p4 = p1 - p2;
    cout << "p1 - p2 = " << p4 << endl;
    
    p1 += p2;
    cout << "p1 += p2 后，p1 = " << p1 << endl;
    
    Point p5 = p2 * 2.0;
    cout << "p2 * 2.0 = " << p5 << endl;
    
    Point p6 = 3.0 * p2;
    cout << "3.0 * p2 = " << p6 << endl;
    
    cout << "p2 == p2: " << (p2 == p2 ? "true" : "false") << endl;
    cout << "p1 == p2: " << (p1 == p2 ? "true" : "false") << endl;
    
    // 8. 函数对象重载
    cout << "\n=== 函数对象重载 ===" << endl;
    
    Multiplier doubler(2.0);
    Multiplier tripler(3.0);
    
    cout << "doubler(5.5) = " << doubler(5.5) << endl;
    cout << "doubler(10) = " << doubler(10) << endl;
    cout << "doubler(\"Hi\") = " << doubler("Hi") << endl;
    
    cout << "tripler(4.2) = " << tripler(4.2) << endl;
    cout << "tripler(7) = " << tripler(7) << endl;
    cout << "tripler(\"Test\") = " << tripler("Test") << endl;
    
    // 9. 重载解析优先级
    cout << "\n=== 重载解析优先级 ===" << endl;
    
    OverloadDemo demo;
    
    cout << "调用不同参数类型:" << endl;
    demo.func(42);        // int
    demo.func(3.14);      // double
    demo.func("hello");   // const char*
    demo.func(string("world")); // const string&
    demo.func('c');       // 模板版本（因为没有char重载）
    
    // 10. 最佳匹配规则
    cout << "\n=== 最佳匹配规则 ===" << endl;
    
    cout << "调用match_test()函数:" << endl;
    match_test(10);        // 精确匹配 int
    match_test(10L);       // 精确匹配 long
    match_test(10.5);      // 精确匹配 double
    match_test(10.5f);     // 提升为 double
    // match_test('A');    // 歧义：可以转换为int或long
    
    // 11. 构造函数重载
    cout << "\n=== 构造函数重载 ===" << endl;
    
    Rectangle r1;           // 默认构造
    Rectangle r2(5.0);      // 单参数构造（正方形）
    Rectangle r3(3.0, 4.0); // 双参数构造
    Rectangle r4(r2);       // 拷贝构造
    
    r1.print();
    r2.print();
    r3.print();
    r4.print();
    
    // 12. 重载与模板的交互
    cout << "\n=== 重载与模板的交互 ===" << endl;
    
    cout << "模板与特化函数的选择:" << endl;
    template_overload(42);      // 选择int特化版本
    template_overload(3.14);    // 选择double特化版本
    template_overload('A');     // 选择模板版本
    template_overload(string("test")); // 选择模板版本
    
    // 13. 重载的实际应用案例
    cout << "\n=== 重载的实际应用案例 ===" << endl;
    
    // 案例1：日志系统
    auto log = [](const string& message) {
        cout << "  LOG: " << message << endl;
    };
    
    auto log_with_level = [](const string& level, const string& message) {
        cout << "  " << level << ": " << message << endl;
    };
    
    auto log_with_details = [](const string& level, const string& component, const string& message) {
        cout << "  [" << component << "] " << level << ": " << message << endl;
    };
    
    cout << "日志系统重载演示:" << endl;
    log("简单日志消息");
    log_with_level("ERROR", "发生错误");
    log_with_details("INFO", "Database", "连接成功");
    
    // 案例2：数学计算库
    auto calculate_area = [](double radius) -> double {
        return 3.14159 * radius * radius;  // 圆面积
    };
    
    auto calculate_area_rect = [](double width, double height) -> double {
        return width * height;  // 矩形面积
    };
    
    auto calculate_area_triangle = [](double base, double height, bool is_triangle) -> double {
        return 0.5 * base * height;  // 三角形面积
    };
    
    cout << "\n数学计算库重载演示:" << endl;
    cout << "  圆面积(半径5): " << calculate_area(5.0) << endl;
    cout << "  矩形面积(3x4): " << calculate_area_rect(3.0, 4.0) << endl;
    cout << "  三角形面积(底6高4): " << calculate_area_triangle(6.0, 4.0, true) << endl;
    
    // 14. 重载的最佳实践
    cout << "\n=== 重载的最佳实践 ===" << endl;
    cout << "1. 重载函数应该执行相似的操作" << endl;
    cout << "2. 避免仅仅因为参数类型不同就重载" << endl;
    cout << "3. 优先考虑默认参数而不是重载" << endl;
    cout << "4. 重载函数应该有一致的行为" << endl;
    cout << "5. 避免过度重载，保持代码清晰" << endl;
    cout << "6. 注意隐式类型转换可能导致的歧义" << endl;
    cout << "7. 使用const重载来区分只读和修改操作" << endl;
    cout << "8. 运算符重载应该直观且符合习惯" << endl;
    cout << "9. 模板特化优于函数重载" << endl;
    cout << "10. 文档化重载函数的不同用途" << endl;
    
    // 15. 常见错误和解决方案
    cout << "\n=== 常见错误和解决方案 ===" << endl;
    
    cout << "错误1：重载解析歧义" << endl;
    cout << "  解决方案：显式类型转换或重新设计函数签名" << endl;
    
    cout << "错误2：仅返回类型不同" << endl;
    cout << "  解决方案：改变函数名或参数列表" << endl;
    
    cout << "错误3：过度依赖隐式转换" << endl;
    cout << "  解决方案：使用explicit关键字或提供明确的重载" << endl;
    
    cout << "错误4：const不一致" << endl;
    cout << "  解决方案：为const和非const版本都提供重载" << endl;
    
    print_separator("函数重载详解完成");
    
    return 0;
} 