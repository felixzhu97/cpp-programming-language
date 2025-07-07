#include "common.h"

int main() {
    print_separator("变量演示");
    
    // 整数类型
    int integer = 42;
    cout << "整数变量: " << integer << endl;
    
    // 浮点数类型
    double decimal = 3.14159;
    cout << "浮点数变量: " << decimal << endl;
    
    // 字符类型
    char character = 'A';
    cout << "字符变量: " << character << endl;
    
    // 布尔类型
    bool isTrue = true;
    cout << "布尔变量: " << std::boolalpha << isTrue << endl;
    
    // 字符串类型
    string text = "Hello, C++!";
    cout << "字符串变量: " << text << endl;
    
    print_separator("变量运算");
    
    // 基本运算
    int a = 10, b = 3;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "a + b = " << a + b << endl;
    cout << "a - b = " << a - b << endl;
    cout << "a * b = " << a * b << endl;
    cout << "a / b = " << a / b << endl;
    cout << "a % b = " << a % b << endl;
    
    // 变量修改
    int counter = 0;
    cout << "\n计数器初始值: " << counter << endl;
    counter++;
    cout << "递增后: " << counter << endl;
    counter += 5;
    cout << "加5后: " << counter << endl;
    
    print_separator("变量演示完成");
    
    return 0;
} 