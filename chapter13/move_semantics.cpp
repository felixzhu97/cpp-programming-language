/**
 * @file move_semantics.cpp
 * @brief 移动语义演示 - 右值引用、移动构造、完美转发
 */

#include <iostream>
#include <string>
#include <vector>
#include <utility>

// 简单的移动示例
class MoveExample {
private:
    std::string data;
    
public:
    MoveExample(std::string s = "") : data(std::move(s)) {
        std::cout << "构造 MoveExample: " << data << "\n";
    }
    
    MoveExample(const MoveExample& other) : data(other.data) {
        std::cout << "拷贝构造 MoveExample: " << data << "\n";
    }
    
    MoveExample(MoveExample&& other) noexcept : data(std::move(other.data)) {
        std::cout << "移动构造 MoveExample: " << data << "\n";
    }
    
    MoveExample& operator=(const MoveExample& other) {
        if (this != &other) {
            data = other.data;
            std::cout << "拷贝赋值 MoveExample: " << data << "\n";
        }
        return *this;
    }
    
    MoveExample& operator=(MoveExample&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            std::cout << "移动赋值 MoveExample: " << data << "\n";
        }
        return *this;
    }
    
    const std::string& get_data() const { return data; }
};

// 演示右值引用
void demonstrate_rvalue_references() {
    std::cout << "\n=== 右值引用演示 ===\n";
    
    std::string str = "Hello";
    std::string& lref = str;           // 左值引用
    std::string&& rref = std::move(str); // 右值引用
    
    std::cout << "原字符串: " << str << "\n";
    std::cout << "左值引用: " << lref << "\n";
    std::cout << "右值引用: " << rref << "\n";
    
    // 右值引用绑定到临时对象
    std::string&& rref2 = std::string("World");
    std::cout << "临时对象的右值引用: " << rref2 << "\n";
}

// 演示移动构造和移动赋值
void demonstrate_move_operations() {
    std::cout << "\n=== 移动操作演示 ===\n";
    
    MoveExample obj1("Original");
    
    // 移动构造
    MoveExample obj2 = std::move(obj1);
    std::cout << "移动后 obj1: \"" << obj1.get_data() << "\"\n";
    std::cout << "移动后 obj2: \"" << obj2.get_data() << "\"\n";
    
    // 移动赋值
    MoveExample obj3;
    obj3 = std::move(obj2);
    std::cout << "移动后 obj2: \"" << obj2.get_data() << "\"\n";
    std::cout << "移动后 obj3: \"" << obj3.get_data() << "\"\n";
}

// 完美转发示例
template<typename T>
void process_value(T&& arg) {
    std::cout << "处理值: " << arg << "\n";
}

template<typename T>
void perfect_forward(T&& arg) {
    std::cout << "完美转发: ";
    process_value(std::forward<T>(arg));
}

void demonstrate_perfect_forwarding() {
    std::cout << "\n=== 完美转发演示 ===\n";
    
    std::string str = "forwarded";
    
    perfect_forward(str);                    // 左值
    perfect_forward(std::move(str));         // 右值
    perfect_forward(std::string("temp"));    // 临时对象
}

// 容器中的移动语义
void demonstrate_container_move() {
    std::cout << "\n=== 容器移动语义 ===\n";
    
    std::vector<MoveExample> vec;
    
    std::cout << "添加元素到容器:\n";
    vec.emplace_back("Element1");           // 直接构造
    vec.push_back(MoveExample("Element2")); // 移动构造
    
    MoveExample obj("Element3");
    vec.push_back(std::move(obj));          // 移动到容器
    
    std::cout << "容器大小: " << vec.size() << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 13: 移动语义演示\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_rvalue_references();
        demonstrate_move_operations();
        demonstrate_perfect_forwarding();
        demonstrate_container_move();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 