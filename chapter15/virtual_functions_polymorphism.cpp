/**
 * @file virtual_functions_polymorphism.cpp
 * @brief 虚函数和多态演示 - 虚函数机制、运行时多态、抽象基类
 */

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <typeinfo>

// 抽象基类 - 图形
class Shape {
protected:
    std::string name;
    double x, y;  // 位置
    
public:
    Shape(const std::string& n, double px = 0, double py = 0) 
        : name(n), x(px), y(py) {
        std::cout << "Shape 构造: " << name << "\n";
    }
    
    virtual ~Shape() {
        std::cout << "Shape 析构: " << name << "\n";
    }
    
    // 纯虚函数 - 使 Shape 成为抽象类
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual void draw() const = 0;
    
    // 虚函数 - 可以有默认实现
    virtual void move(double dx, double dy) {
        x += dx;
        y += dy;
        std::cout << name << " 移动到 (" << x << ", " << y << ")\n";
    }
    
    virtual void display_info() const {
        std::cout << "图形: " << name << " at (" << x << ", " << y << ")\n";
        std::cout << "面积: " << area() << ", 周长: " << perimeter() << "\n";
    }
    
    // 非虚函数
    std::string get_name() const { return name; }
    void set_position(double px, double py) { x = px; y = py; }
    
    // 虚函数 - 用于类型识别
    virtual std::string get_type() const { return "Shape"; }
};

// 圆形类
class Circle : public Shape {
private:
    double radius;
    
public:
    Circle(const std::string& n, double r, double px = 0, double py = 0)
        : Shape(n, px, py), radius(r) {
        std::cout << "Circle 构造: " << name << "\n";
    }
    
    ~Circle() {
        std::cout << "Circle 析构: " << name << "\n";
    }
    
    // 实现纯虚函数
    double area() const override {
        return 3.14159 * radius * radius;
    }
    
    double perimeter() const override {
        return 2 * 3.14159 * radius;
    }
    
    void draw() const override {
        std::cout << "绘制圆形 " << name << ", 半径: " << radius << "\n";
    }
    
    // 重写虚函数
    void move(double dx, double dy) override {
        Shape::move(dx, dy);  // 调用基类版本
        std::cout << "圆形特殊移动效果\n";
    }
    
    std::string get_type() const override { return "Circle"; }
    
    // 圆形特有的方法
    double get_radius() const { return radius; }
    void set_radius(double r) { radius = r; }
};

// 矩形类
class Rectangle : public Shape {
private:
    double width, height;
    
public:
    Rectangle(const std::string& n, double w, double h, double px = 0, double py = 0)
        : Shape(n, px, py), width(w), height(h) {
        std::cout << "Rectangle 构造: " << name << "\n";
    }
    
    ~Rectangle() {
        std::cout << "Rectangle 析构: " << name << "\n";
    }
    
    // 实现纯虚函数
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        std::cout << "绘制矩形 " << name << ", 尺寸: " << width << "x" << height << "\n";
    }
    
    std::string get_type() const override { return "Rectangle"; }
    
    // 矩形特有的方法
    double get_width() const { return width; }
    double get_height() const { return height; }
    void resize(double w, double h) { width = w; height = h; }
};

// 三角形类
class Triangle : public Shape {
private:
    double side1, side2, side3;
    
public:
    Triangle(const std::string& n, double s1, double s2, double s3, 
             double px = 0, double py = 0)
        : Shape(n, px, py), side1(s1), side2(s2), side3(s3) {
        std::cout << "Triangle 构造: " << name << "\n";
    }
    
    ~Triangle() {
        std::cout << "Triangle 析构: " << name << "\n";
    }
    
    // 实现纯虚函数
    double area() const override {
        // 使用海伦公式
        double s = (side1 + side2 + side3) / 2;
        return std::sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }
    
    double perimeter() const override {
        return side1 + side2 + side3;
    }
    
    void draw() const override {
        std::cout << "绘制三角形 " << name << ", 边长: " 
                  << side1 << ", " << side2 << ", " << side3 << "\n";
    }
    
    std::string get_type() const override { return "Triangle"; }
    
    // 三角形特有的方法
    bool is_valid() const {
        return (side1 + side2 > side3) && 
               (side1 + side3 > side2) && 
               (side2 + side3 > side1);
    }
};

// 带虚函数的基类 - 演示虚函数表
class VTableDemo {
public:
    virtual void func1() const { std::cout << "VTableDemo::func1\n"; }
    virtual void func2() const { std::cout << "VTableDemo::func2\n"; }
    virtual void func3() const { std::cout << "VTableDemo::func3\n"; }
    virtual ~VTableDemo() = default;
};

class DerivedDemo : public VTableDemo {
public:
    void func1() const override { std::cout << "DerivedDemo::func1\n"; }
    // func2 使用基类版本
    void func3() const override { std::cout << "DerivedDemo::func3\n"; }
    virtual void func4() const { std::cout << "DerivedDemo::func4\n"; }  // 新虚函数
};

// 多层继承的虚函数
class Vehicle {
public:
    virtual void start() const { std::cout << "Vehicle 启动\n"; }
    virtual void stop() const { std::cout << "Vehicle 停止\n"; }
    virtual void display() const { std::cout << "这是一个交通工具\n"; }
    virtual ~Vehicle() = default;
};

class Car : public Vehicle {
public:
    void start() const override { std::cout << "Car 启动引擎\n"; }
    void display() const override { std::cout << "这是一辆汽车\n"; }
    virtual void honk() const { std::cout << "汽车鸣笛\n"; }
};

class ElectricCar : public Car {
public:
    void start() const override { std::cout << "ElectricCar 静音启动\n"; }
    void display() const override { std::cout << "这是一辆电动汽车\n"; }
    virtual void charge() const { std::cout << "电动汽车充电\n"; }
};

// 抽象工厂模式示例
class ShapeFactory {
public:
    enum ShapeType { CIRCLE, RECTANGLE, TRIANGLE };
    
    static std::unique_ptr<Shape> create_shape(ShapeType type, 
                                               const std::string& name) {
        switch (type) {
            case CIRCLE:
                return std::make_unique<Circle>(name, 5.0);
            case RECTANGLE:
                return std::make_unique<Rectangle>(name, 4.0, 6.0);
            case TRIANGLE:
                return std::make_unique<Triangle>(name, 3.0, 4.0, 5.0);
        }
        return nullptr;
    }
};

void demonstrate_basic_polymorphism() {
    std::cout << "\n=== 基本多态演示 ===\n";
    
    // 创建不同类型的图形
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>("圆1", 3.0, 1.0, 1.0));
    shapes.push_back(std::make_unique<Rectangle>("矩形1", 4.0, 5.0, 2.0, 2.0));
    shapes.push_back(std::make_unique<Triangle>("三角形1", 3.0, 4.0, 5.0, 3.0, 3.0));
    
    std::cout << "\n通过基类指针调用虚函数:\n";
    for (const auto& shape : shapes) {
        shape->display_info();
        shape->draw();
        shape->move(1.0, 1.0);
        std::cout << "类型: " << shape->get_type() << "\n";
        std::cout << "---\n";
    }
    
    std::cout << "\n计算总面积:\n";
    double total_area = 0;
    for (const auto& shape : shapes) {
        total_area += shape->area();
    }
    std::cout << "所有图形的总面积: " << total_area << "\n";
}

void demonstrate_virtual_function_override() {
    std::cout << "\n=== 虚函数重写演示 ===\n";
    
    VTableDemo* base_ptr = new DerivedDemo();
    
    std::cout << "通过基类指针调用虚函数:\n";
    base_ptr->func1();  // 调用 DerivedDemo::func1
    base_ptr->func2();  // 调用 VTableDemo::func2
    base_ptr->func3();  // 调用 DerivedDemo::func3
    
    // 需要转换才能调用派生类特有的虚函数
    if (auto* derived_ptr = dynamic_cast<DerivedDemo*>(base_ptr)) {
        derived_ptr->func4();
    }
    
    delete base_ptr;
}

void demonstrate_multilevel_inheritance() {
    std::cout << "\n=== 多层继承虚函数演示 ===\n";
    
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    vehicles.push_back(std::make_unique<Vehicle>());
    vehicles.push_back(std::make_unique<Car>());
    vehicles.push_back(std::make_unique<ElectricCar>());
    
    for (const auto& vehicle : vehicles) {
        vehicle->display();
        vehicle->start();
        vehicle->stop();
        std::cout << "---\n";
    }
    
    std::cout << "\n特定类型的行为:\n";
    auto car = std::make_unique<Car>();
    auto e_car = std::make_unique<ElectricCar>();
    
    car->honk();
    e_car->charge();
}

void demonstrate_dynamic_cast() {
    std::cout << "\n=== dynamic_cast 演示 ===\n";
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>("动态圆", 2.0));
    shapes.push_back(std::make_unique<Rectangle>("动态矩形", 3.0, 4.0));
    shapes.push_back(std::make_unique<Triangle>("动态三角形", 2.0, 3.0, 4.0));
    
    for (const auto& shape : shapes) {
        std::cout << "\n检查类型: " << shape->get_name() << "\n";
        
        // 尝试转换为 Circle
        if (auto* circle = dynamic_cast<Circle*>(shape.get())) {
            std::cout << "这是圆形，半径: " << circle->get_radius() << "\n";
        }
        // 尝试转换为 Rectangle
        else if (auto* rect = dynamic_cast<Rectangle*>(shape.get())) {
            std::cout << "这是矩形，尺寸: " << rect->get_width() 
                      << "x" << rect->get_height() << "\n";
        }
        // 尝试转换为 Triangle
        else if (auto* tri = dynamic_cast<Triangle*>(shape.get())) {
            std::cout << "这是三角形，有效性: " 
                      << (tri->is_valid() ? "有效" : "无效") << "\n";
        }
    }
}

void demonstrate_typeid() {
    std::cout << "\n=== typeid 演示 ===\n";
    
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>("typeid圆", 1.0));
    shapes.push_back(std::make_unique<Rectangle>("typeid矩形", 2.0, 3.0));
    
    for (const auto& shape : shapes) {
        std::cout << "对象类型: " << typeid(*shape).name() << "\n";
        std::cout << "是否为Circle: " << (typeid(*shape) == typeid(Circle) ? "是" : "否") << "\n";
        std::cout << "是否为Rectangle: " << (typeid(*shape) == typeid(Rectangle) ? "是" : "否") << "\n";
    }
}

void demonstrate_abstract_factory() {
    std::cout << "\n=== 抽象工厂模式演示 ===\n";
    
    std::vector<std::unique_ptr<Shape>> factory_shapes;
    
    // 使用工厂创建不同类型的图形
    factory_shapes.push_back(
        ShapeFactory::create_shape(ShapeFactory::CIRCLE, "工厂圆"));
    factory_shapes.push_back(
        ShapeFactory::create_shape(ShapeFactory::RECTANGLE, "工厂矩形"));
    factory_shapes.push_back(
        ShapeFactory::create_shape(ShapeFactory::TRIANGLE, "工厂三角形"));
    
    std::cout << "工厂创建的图形:\n";
    for (const auto& shape : factory_shapes) {
        shape->display_info();
        shape->draw();
    }
}

void demonstrate_virtual_function_costs() {
    std::cout << "\n=== 虚函数性能考虑 ===\n";
    
    std::cout << "1. 虚函数调用的开销:\n";
    std::cout << "   - 间接调用（通过虚函数表）\n";
    std::cout << "   - 阻止某些编译器优化\n";
    std::cout << "   - 每个对象都有虚函数表指针\n";
    
    std::cout << "\n2. 使用建议:\n";
    std::cout << "   - 需要多态时才使用虚函数\n";
    std::cout << "   - 析构函数在继承中应为虚函数\n";
    std::cout << "   - 避免在构造/析构函数中调用虚函数\n";
    
    // 展示对象大小的差异
    class NonVirtual { int data; };
    class WithVirtual { int data; virtual void func() {} };
    
    std::cout << "\n对象大小比较:\n";
    std::cout << "无虚函数类大小: " << sizeof(NonVirtual) << " 字节\n";
    std::cout << "有虚函数类大小: " << sizeof(WithVirtual) << " 字节\n";
}

void demonstrate_pure_virtual_functions() {
    std::cout << "\n=== 纯虚函数演示 ===\n";
    
    std::cout << "Shape 是抽象类，不能实例化:\n";
    // Shape shape;  // 编译错误
    
    std::cout << "必须在派生类中实现所有纯虚函数:\n";
    Circle circle("纯虚圆", 1.0);
    circle.area();      // 必须实现
    circle.perimeter(); // 必须实现
    circle.draw();      // 必须实现
    
    std::cout << "抽象类可以有非纯虚函数和数据成员\n";
}

int main() {
    std::cout << "C++ Primer Chapter 15: 虚函数和多态演示\n";
    std::cout << "=====================================\n";
    
    try {
        demonstrate_basic_polymorphism();
        demonstrate_virtual_function_override();
        demonstrate_multilevel_inheritance();
        demonstrate_dynamic_cast();
        demonstrate_typeid();
        demonstrate_abstract_factory();
        demonstrate_virtual_function_costs();
        demonstrate_pure_virtual_functions();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 