/**
 * @file copy_control.cpp
 * @brief 拷贝控制演示 - 拷贝构造函数、拷贝赋值运算符、析构函数、移动语义
 */

#include <iostream>
#include <memory>
#include <string>
#include <utility>

// 基本的拷贝控制示例
class BasicCopyControl {
private:
    std::string* data;
    
public:
    // 构造函数
    BasicCopyControl(const std::string& str = "") : data(new std::string(str)) {
        std::cout << "构造 BasicCopyControl: " << *data << "\n";
    }
    
    // 拷贝构造函数
    BasicCopyControl(const BasicCopyControl& other) : data(new std::string(*other.data)) {
        std::cout << "拷贝构造 BasicCopyControl: " << *data << "\n";
    }
    
    // 拷贝赋值运算符
    BasicCopyControl& operator=(const BasicCopyControl& other) {
        if (this != &other) {
            delete data;
            data = new std::string(*other.data);
            std::cout << "拷贝赋值 BasicCopyControl: " << *data << "\n";
        }
        return *this;
    }
    
    // 析构函数
    ~BasicCopyControl() {
        std::cout << "析构 BasicCopyControl: " << *data << "\n";
        delete data;
    }
    
    const std::string& get_data() const { return *data; }
};

// 移动语义示例
class MoveSemanticsExample {
private:
    std::string* data;
    size_t size;
    
public:
    // 构造函数
    MoveSemanticsExample(const std::string& str = "") 
        : data(new std::string(str)), size(str.size()) {
        std::cout << "构造 MoveSemanticsExample: " << *data << "\n";
    }
    
    // 拷贝构造函数
    MoveSemanticsExample(const MoveSemanticsExample& other) 
        : data(new std::string(*other.data)), size(other.size) {
        std::cout << "拷贝构造 MoveSemanticsExample: " << *data << "\n";
    }
    
    // 移动构造函数
    MoveSemanticsExample(MoveSemanticsExample&& other) noexcept 
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "移动构造 MoveSemanticsExample\n";
    }
    
    // 拷贝赋值运算符
    MoveSemanticsExample& operator=(const MoveSemanticsExample& other) {
        if (this != &other) {
            delete data;
            data = new std::string(*other.data);
            size = other.size;
            std::cout << "拷贝赋值 MoveSemanticsExample: " << *data << "\n";
        }
        return *this;
    }
    
    // 移动赋值运算符
    MoveSemanticsExample& operator=(MoveSemanticsExample&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "移动赋值 MoveSemanticsExample\n";
        }
        return *this;
    }
    
    // 析构函数
    ~MoveSemanticsExample() {
        if (data) {
            std::cout << "析构 MoveSemanticsExample: " << *data << "\n";
            delete data;
        } else {
            std::cout << "析构 MoveSemanticsExample: (已移动)\n";
        }
    }
    
    const std::string& get_data() const { 
        return data ? *data : *(new std::string("(empty)"));
    }
};

// 三法则/五法则演示
class RuleOfFive {
private:
    int* data;
    size_t size;
    
public:
    // 1. 析构函数
    ~RuleOfFive() {
        std::cout << "析构 RuleOfFive\n";
        delete[] data;
    }
    
    // 2. 拷贝构造函数
    RuleOfFive(const RuleOfFive& other) : size(other.size) {
        data = new int[size];
        std::copy(other.data, other.data + size, data);
        std::cout << "拷贝构造 RuleOfFive\n";
    }
    
    // 3. 拷贝赋值运算符
    RuleOfFive& operator=(const RuleOfFive& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            std::copy(other.data, other.data + size, data);
            std::cout << "拷贝赋值 RuleOfFive\n";
        }
        return *this;
    }
    
    // 4. 移动构造函数
    RuleOfFive(RuleOfFive&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        std::cout << "移动构造 RuleOfFive\n";
    }
    
    // 5. 移动赋值运算符
    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
            std::cout << "移动赋值 RuleOfFive\n";
        }
        return *this;
    }
    
    // 构造函数
    RuleOfFive(size_t s = 10) : size(s), data(new int[s]) {
        std::cout << "构造 RuleOfFive，大小: " << size << "\n";
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
    }
    
    void print() const {
        std::cout << "RuleOfFive 数据: ";
        for (size_t i = 0; i < size && i < 5; ++i) {
            std::cout << data[i] << " ";
        }
        if (size > 5) std::cout << "...";
        std::cout << "\n";
    }
};

void demonstrate_basic_copy_control() {
    std::cout << "\n=== 基本拷贝控制 ===\n";
    
    BasicCopyControl obj1("Hello");
    BasicCopyControl obj2 = obj1;  // 拷贝构造
    BasicCopyControl obj3;
    obj3 = obj1;  // 拷贝赋值
    
    std::cout << "obj1: " << obj1.get_data() << "\n";
    std::cout << "obj2: " << obj2.get_data() << "\n";
    std::cout << "obj3: " << obj3.get_data() << "\n";
}

void demonstrate_move_semantics() {
    std::cout << "\n=== 移动语义演示 ===\n";
    
    MoveSemanticsExample obj1("World");
    MoveSemanticsExample obj2 = std::move(obj1);  // 移动构造
    
    MoveSemanticsExample obj3;
    obj3 = std::move(obj2);  // 移动赋值
    
    std::cout << "移动后的对象状态检查完成\n";
}

void demonstrate_rule_of_five() {
    std::cout << "\n=== 五法则演示 ===\n";
    
    RuleOfFive obj1(5);
    obj1.print();
    
    RuleOfFive obj2 = obj1;  // 拷贝构造
    obj2.print();
    
    RuleOfFive obj3 = std::move(obj1);  // 移动构造
    obj3.print();
    
    RuleOfFive obj4(3);
    obj4 = obj2;  // 拷贝赋值
    obj4.print();
    
    obj4 = std::move(obj3);  // 移动赋值
    obj4.print();
}

int main() {
    std::cout << "C++ Primer Chapter 13: 拷贝控制演示\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_basic_copy_control();
        demonstrate_move_semantics();
        demonstrate_rule_of_five();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 