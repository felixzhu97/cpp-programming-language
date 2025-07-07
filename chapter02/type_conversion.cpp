#include "common.h"

int main() {
    print_separator("类型转换示例");
    
    // 隐式类型转换
    cout << "=== 隐式类型转换 ===" << endl;
    int intVal = 42;
    double doubleVal = intVal;  // int 到 double
    cout << "int 转 double: " << intVal << " -> " << doubleVal << endl;
    
    double pi = 3.14159;
    int truncated = pi;  // double 到 int（截断）
    cout << "double 转 int: " << pi << " -> " << truncated << endl;
    
    char ch = 'A';
    int asciiVal = ch;  // char 到 int
    cout << "char 转 int: " << ch << " -> " << asciiVal << endl;
    
    // 显式类型转换（C风格）
    cout << "\n=== 显式类型转换（C风格） ===" << endl;
    double val = 123.456;
    int intResult = (int)val;
    cout << "C风格转换: " << val << " -> " << intResult << endl;
    
    // C++风格类型转换
    cout << "\n=== C++风格类型转换 ===" << endl;
    
    // static_cast
    double d = 98.6;
    int i = static_cast<int>(d);
    cout << "static_cast: " << d << " -> " << i << endl;
    
    // const_cast
    const int constInt = 100;
    int* ptr = const_cast<int*>(&constInt);
    cout << "const_cast: 移除const限定符" << endl;
    cout << "原始值: " << constInt << ", 指针指向: " << *ptr << endl;
    
    // reinterpret_cast
    int num = 65;
    char* charPtr = reinterpret_cast<char*>(&num);
    cout << "reinterpret_cast: 重新解释内存" << endl;
    cout << "int值: " << num << ", 作为char: " << *charPtr << endl;
    
    // 类型提升
    cout << "\n=== 类型提升 ===" << endl;
    char c1 = 100;
    char c2 = 50;
    cout << "char + char = " << c1 + c2 << " (结果是int类型)" << endl;
    cout << "sizeof(c1 + c2) = " << sizeof(c1 + c2) << " 字节" << endl;
    
    // 混合运算
    cout << "\n=== 混合运算 ===" << endl;
    int intNum = 5;
    double doubleNum = 2.5;
    auto result = intNum * doubleNum;
    cout << "int * double = " << result << endl;
    cout << "结果类型大小: " << sizeof(result) << " 字节" << endl;
    
    // 布尔转换
    cout << "\n=== 布尔转换 ===" << endl;
    int zero = 0;
    int nonZero = 42;
    bool boolFromZero = zero;
    bool boolFromNonZero = nonZero;
    
    cout << std::boolalpha;
    cout << "0 转布尔: " << boolFromZero << endl;
    cout << "42 转布尔: " << boolFromNonZero << endl;
    
    // 精度损失警告
    cout << "\n=== 精度损失示例 ===" << endl;
    double preciseValue = 123.456789;
    float lessPrec = preciseValue;
    cout << std::fixed << std::setprecision(6);
    cout << "double: " << preciseValue << endl;
    cout << "float:  " << lessPrec << endl;
    cout << "精度损失: " << (preciseValue - lessPrec) << endl;
    
    print_separator("类型转换示例完成");
    
    return 0;
} 