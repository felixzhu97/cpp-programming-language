#include "common.h"

// 1. 基本内联函数
inline int add(int a, int b) {
    return a + b;
}

inline int square(int x) {
    return x * x;
}

inline double max_value(double a, double b) {
    return (a > b) ? a : b;
}

// 2. 内联vs非内联对比
int regular_multiply(int a, int b) {
    return a * b;
}

inline int inline_multiply(int a, int b) {
    return a * b;
}

// 3. 复杂内联函数（编译器可能拒绝内联）
inline int complex_calculation(int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result += i * j;
        }
    }
    return result;
}

// 4. 递归内联函数（通常不会被内联）
inline int factorial_inline(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial_inline(n - 1);
}

// 5. 模板内联函数
template<typename T>
inline T min_value(T a, T b) {
    return (a < b) ? a : b;
}

template<typename T>
inline void swap_values(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 6. 类中的内联函数
class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // 类内定义的成员函数默认为内联
    double getX() const { return x; }
    double getY() const { return y; }
    
    void setX(double new_x) { x = new_x; }
    void setY(double new_y) { y = new_y; }
    
    // 内联成员函数
    inline double distance_from_origin() const {
        return sqrt(x * x + y * y);
    }
    
    // 类外定义的内联函数
    inline double distance_to(const Point& other) const;
    
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

// 类外内联函数定义
inline double Point::distance_to(const Point& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return sqrt(dx * dx + dy * dy);
}

// 7. 内联函数的访问器和修改器
class Rectangle {
private:
    double width, height;
    
public:
    Rectangle(double w = 0, double h = 0) : width(w), height(h) {}
    
    // 内联访问器
    inline double get_width() const { return width; }
    inline double get_height() const { return height; }
    inline double get_area() const { return width * height; }
    inline double get_perimeter() const { return 2 * (width + height); }
    
    // 内联修改器
    inline void set_width(double w) { 
        if (w >= 0) width = w; 
    }
    
    inline void set_height(double h) { 
        if (h >= 0) height = h; 
    }
    
    inline void resize(double w, double h) {
        set_width(w);
        set_height(h);
    }
    
    inline bool is_square() const {
        return width == height;
    }
};

// 8. 条件内联（C++17 if constexpr）
template<typename T>
inline T conditional_abs(T value) {
    if constexpr (std::is_unsigned_v<T>) {
        return value;  // 无符号类型直接返回
    } else {
        return (value < 0) ? -value : value;  // 有符号类型取绝对值
    }
}

// 9. 强制内联（编译器特定）
#ifdef _MSC_VER
    #define FORCE_INLINE __forceinline
#elif defined(__GNUC__)
    #define FORCE_INLINE __attribute__((always_inline)) inline
#else
    #define FORCE_INLINE inline
#endif

FORCE_INLINE int force_inline_add(int a, int b) {
    return a + b;
}

// 10. 性能关键的内联函数
class Vector2D {
private:
    double x, y;
    
public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}
    
    // 性能关键的内联运算符
    inline Vector2D operator+(const Vector2D& other) const {
        return Vector2D(x + other.x, y + other.y);
    }
    
    inline Vector2D operator-(const Vector2D& other) const {
        return Vector2D(x - other.x, y - other.y);
    }
    
    inline Vector2D operator*(double scalar) const {
        return Vector2D(x * scalar, y * scalar);
    }
    
    inline double dot(const Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    
    inline double magnitude() const {
        return sqrt(x * x + y * y);
    }
    
    inline Vector2D normalized() const {
        double mag = magnitude();
        return (mag > 0) ? Vector2D(x / mag, y / mag) : Vector2D(0, 0);
    }
    
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

// 11. 数学内联函数库
namespace MathUtils {
    inline double deg_to_rad(double degrees) {
        return degrees * M_PI / 180.0;
    }
    
    inline double rad_to_deg(double radians) {
        return radians * 180.0 / M_PI;
    }
    
    inline double clamp(double value, double min_val, double max_val) {
        return (value < min_val) ? min_val : (value > max_val) ? max_val : value;
    }
    
    inline double lerp(double a, double b, double t) {
        return a + t * (b - a);
    }
    
    inline bool is_power_of_two(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
    
    inline int next_power_of_two(int n) {
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return n + 1;
    }
}

// 12. 内联函数的性能测试
void performance_test() {
    const int iterations = 10000000;
    
    cout << "=== 内联函数性能测试 ===" << endl;
    cout << "测试迭代次数: " << iterations << endl;
    
    // 测试1: 内联vs非内联函数调用
    auto start = chrono::high_resolution_clock::now();
    
    volatile int sum1 = 0;  // volatile防止编译器优化
    for (int i = 0; i < iterations; i++) {
        sum1 += regular_multiply(i, 2);
    }
    
    auto mid = chrono::high_resolution_clock::now();
    
    volatile int sum2 = 0;
    for (int i = 0; i < iterations; i++) {
        sum2 += inline_multiply(i, 2);
    }
    
    auto end = chrono::high_resolution_clock::now();
    
    auto regular_time = chrono::duration_cast<chrono::microseconds>(mid - start);
    auto inline_time = chrono::duration_cast<chrono::microseconds>(end - mid);
    
    cout << "常规函数时间: " << regular_time.count() << " 微秒" << endl;
    cout << "内联函数时间: " << inline_time.count() << " 微秒" << endl;
    cout << "性能提升: " << (double)regular_time.count() / inline_time.count() << "x" << endl;
    
    // 测试2: 复杂运算的性能
    cout << "\n复杂运算性能测试:" << endl;
    
    start = chrono::high_resolution_clock::now();
    
    volatile double result1 = 0;
    for (int i = 0; i < 100000; i++) {
        double x = i * 0.1;
        double y = i * 0.2;
        result1 += sqrt(x * x + y * y);  // 直接计算
    }
    
    mid = chrono::high_resolution_clock::now();
    
    volatile double result2 = 0;
    for (int i = 0; i < 100000; i++) {
        Vector2D v(i * 0.1, i * 0.2);
        result2 += v.magnitude();  // 内联成员函数
    }
    
    end = chrono::high_resolution_clock::now();
    
    auto direct_time = chrono::duration_cast<chrono::microseconds>(mid - start);
    auto inline_class_time = chrono::duration_cast<chrono::microseconds>(end - mid);
    
    cout << "直接计算时间: " << direct_time.count() << " 微秒" << endl;
    cout << "内联类函数时间: " << inline_class_time.count() << " 微秒" << endl;
    cout << "开销比例: " << (double)inline_class_time.count() / direct_time.count() << "x" << endl;
}

// 13. 内联函数的调试考虑
inline void debug_inline_function(int value) {
    cout << "  调试内联函数: 输入值 = " << value << endl;
    
    // 在调试模式下，内联函数可能不会被内联
    // 这有助于调试，但会影响性能测试的准确性
    
    #ifdef DEBUG
        cout << "  调试模式: 函数可能未被内联" << endl;
    #endif
    
    cout << "  处理后的值 = " << value * 2 << endl;
}

// 14. 内联函数的最佳实践示例
class Timer {
private:
    chrono::high_resolution_clock::time_point start_time;
    
public:
    // 简单的内联函数适合内联
    inline void start() {
        start_time = chrono::high_resolution_clock::now();
    }
    
    inline double elapsed_ms() const {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000.0;
    }
    
    // 复杂的函数不应该内联
    void detailed_report() const {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
        
        cout << "详细时间报告:" << endl;
        cout << "  开始时间: " << start_time.time_since_epoch().count() << endl;
        cout << "  结束时间: " << end_time.time_since_epoch().count() << endl;
        cout << "  持续时间: " << duration.count() << " 微秒" << endl;
        cout << "  持续时间: " << duration.count() / 1000.0 << " 毫秒" << endl;
        cout << "  持续时间: " << duration.count() / 1000000.0 << " 秒" << endl;
    }
};

int main() {
    print_separator("内联函数详解");
    
    // 1. 基本内联函数使用
    cout << "=== 基本内联函数使用 ===" << endl;
    
    int a = 5, b = 3;
    cout << "add(" << a << ", " << b << ") = " << add(a, b) << endl;
    cout << "square(" << a << ") = " << square(a) << endl;
    cout << "max_value(3.14, 2.71) = " << max_value(3.14, 2.71) << endl;
    
    // 2. 模板内联函数
    cout << "\n=== 模板内联函数 ===" << endl;
    
    cout << "min_value(10, 20) = " << min_value(10, 20) << endl;
    cout << "min_value(3.14, 2.71) = " << min_value(3.14, 2.71) << endl;
    cout << "min_value('a', 'z') = " << min_value('a', 'z') << endl;
    
    int x = 10, y = 20;
    cout << "交换前: x=" << x << ", y=" << y << endl;
    swap_values(x, y);
    cout << "交换后: x=" << x << ", y=" << y << endl;
    
    // 3. 类内联函数
    cout << "\n=== 类内联函数 ===" << endl;
    
    Point p1(3, 4);
    Point p2(6, 8);
    
    cout << "点p1: ";
    p1.print();
    cout << ", 距离原点: " << p1.distance_from_origin() << endl;
    
    cout << "点p2: ";
    p2.print();
    cout << ", 距离原点: " << p2.distance_from_origin() << endl;
    
    cout << "p1到p2的距离: " << p1.distance_to(p2) << endl;
    
    // 4. 矩形类内联函数
    cout << "\n=== 矩形类内联函数 ===" << endl;
    
    Rectangle rect(5, 3);
    cout << "矩形: 宽=" << rect.get_width() << ", 高=" << rect.get_height() << endl;
    cout << "面积: " << rect.get_area() << endl;
    cout << "周长: " << rect.get_perimeter() << endl;
    cout << "是正方形: " << (rect.is_square() ? "是" : "否") << endl;
    
    rect.resize(4, 4);
    cout << "\n调整后矩形: 宽=" << rect.get_width() << ", 高=" << rect.get_height() << endl;
    cout << "是正方形: " << (rect.is_square() ? "是" : "否") << endl;
    
    // 5. 条件内联函数
    cout << "\n=== 条件内联函数 ===" << endl;
    
    cout << "conditional_abs(-5) = " << conditional_abs(-5) << endl;
    cout << "conditional_abs(5u) = " << conditional_abs(5u) << endl;
    cout << "conditional_abs(-3.14) = " << conditional_abs(-3.14) << endl;
    
    // 6. 向量类内联运算
    cout << "\n=== 向量类内联运算 ===" << endl;
    
    Vector2D v1(3, 4);
    Vector2D v2(1, 2);
    
    cout << "向量v1: ";
    v1.print();
    cout << ", 模长: " << v1.magnitude() << endl;
    
    cout << "向量v2: ";
    v2.print();
    cout << ", 模长: " << v2.magnitude() << endl;
    
    Vector2D v3 = v1 + v2;
    cout << "v1 + v2 = ";
    v3.print();
    cout << endl;
    
    Vector2D v4 = v1 - v2;
    cout << "v1 - v2 = ";
    v4.print();
    cout << endl;
    
    cout << "v1 · v2 = " << v1.dot(v2) << endl;
    
    Vector2D v5 = v1 * 2.0;
    cout << "v1 * 2 = ";
    v5.print();
    cout << endl;
    
    Vector2D v6 = v1.normalized();
    cout << "v1归一化 = ";
    v6.print();
    cout << ", 模长: " << v6.magnitude() << endl;
    
    // 7. 数学工具函数
    cout << "\n=== 数学工具内联函数 ===" << endl;
    
    cout << "90度转弧度: " << MathUtils::deg_to_rad(90) << endl;
    cout << "π弧度转角度: " << MathUtils::rad_to_deg(M_PI) << endl;
    cout << "clamp(15, 10, 20): " << MathUtils::clamp(15, 10, 20) << endl;
    cout << "clamp(5, 10, 20): " << MathUtils::clamp(5, 10, 20) << endl;
    cout << "lerp(0, 10, 0.5): " << MathUtils::lerp(0, 10, 0.5) << endl;
    cout << "is_power_of_two(8): " << (MathUtils::is_power_of_two(8) ? "是" : "否") << endl;
    cout << "is_power_of_two(6): " << (MathUtils::is_power_of_two(6) ? "是" : "否") << endl;
    cout << "next_power_of_two(6): " << MathUtils::next_power_of_two(6) << endl;
    
    // 8. 性能测试
    performance_test();
    
    // 9. 调试内联函数
    cout << "\n=== 调试内联函数 ===" << endl;
    
    debug_inline_function(42);
    
    // 10. 计时器类使用
    cout << "\n=== 计时器类使用 ===" << endl;
    
    Timer timer;
    timer.start();
    
    // 模拟一些工作
    this_thread::sleep_for(chrono::milliseconds(100));
    
    cout << "经过时间: " << timer.elapsed_ms() << " 毫秒" << endl;
    
    timer.detailed_report();
    
    // 11. 复杂内联函数测试
    cout << "\n=== 复杂内联函数测试 ===" << endl;
    
    cout << "复杂计算(5): " << complex_calculation(5) << endl;
    cout << "内联阶乘(5): " << factorial_inline(5) << endl;
    
    // 12. 内联函数的优缺点总结
    cout << "\n=== 内联函数优缺点总结 ===" << endl;
    cout << "优点:" << endl;
    cout << "1. 消除函数调用开销，提高性能" << endl;
    cout << "2. 保持函数封装的同时获得宏的性能" << endl;
    cout << "3. 编译器可以进行更好的优化" << endl;
    cout << "4. 类型安全（相比宏）" << endl;
    cout << "5. 遵循作用域规则" << endl;
    
    cout << "\n缺点:" << endl;
    cout << "1. 可能增加代码大小" << endl;
    cout << "2. 编译时间可能增加" << endl;
    cout << "3. 调试可能更困难" << endl;
    cout << "4. 过度使用可能适得其反" << endl;
    cout << "5. 递归函数通常不能内联" << endl;
    
    // 13. 内联函数使用指南
    cout << "\n=== 内联函数使用指南 ===" << endl;
    cout << "适合内联的函数:" << endl;
    cout << "1. 简短的函数（1-5行代码）" << endl;
    cout << "2. 频繁调用的函数" << endl;
    cout << "3. 访问器和修改器函数" << endl;
    cout << "4. 简单的数学运算函数" << endl;
    cout << "5. 模板函数" << endl;
    
    cout << "\n不适合内联的函数:" << endl;
    cout << "1. 复杂的函数（大量代码）" << endl;
    cout << "2. 递归函数" << endl;
    cout << "3. 包含循环的函数" << endl;
    cout << "4. 很少调用的函数" << endl;
    cout << "5. 包含静态变量的函数" << endl;
    
    // 14. 编译器内联行为
    cout << "\n=== 编译器内联行为 ===" << endl;
    cout << "1. inline关键字只是建议，编译器可能忽略" << endl;
    cout << "2. 编译器可能内联未标记inline的函数" << endl;
    cout << "3. 优化级别影响内联决策" << endl;
    cout << "4. 不同编译器有不同的内联策略" << endl;
    cout << "5. 链接时优化(LTO)可以跨文件内联" << endl;
    
    // 15. 最佳实践
    cout << "\n=== 内联函数最佳实践 ===" << endl;
    cout << "1. 在头文件中定义内联函数" << endl;
    cout << "2. 保持内联函数简短" << endl;
    cout << "3. 优先考虑性能关键路径" << endl;
    cout << "4. 使用编译器优化选项" << endl;
    cout << "5. 测量实际性能影响" << endl;
    cout << "6. 避免过早优化" << endl;
    cout << "7. 考虑模板替代内联" << endl;
    cout << "8. 注意调试版本的性能差异" << endl;
    cout << "9. 使用profiler工具分析热点" << endl;
    cout << "10. 平衡代码大小和执行速度" << endl;
    
    print_separator("内联函数详解完成");
    
    return 0;
} 