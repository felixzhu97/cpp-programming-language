#include "common.h"
#include <limits>

int main() {
    print_separator("基本数据类型示例");
    
    // 整数类型
    cout << "=== 整数类型 ===" << endl;
    short shortVar = 32767;
    int intVar = 2147483647;
    long longVar = 9223372036854775807L;
    long long longlongVar = 9223372036854775807LL;
    
    cout << "short: " << shortVar << " (大小: " << sizeof(short) << " 字节)" << endl;
    cout << "int: " << intVar << " (大小: " << sizeof(int) << " 字节)" << endl;
    cout << "long: " << longVar << " (大小: " << sizeof(long) << " 字节)" << endl;
    cout << "long long: " << longlongVar << " (大小: " << sizeof(long long) << " 字节)" << endl;
    
    // 无符号整数类型
    cout << "\n=== 无符号整数类型 ===" << endl;
    unsigned short ushortVar = 65535U;
    unsigned int uintVar = 4294967295U;
    unsigned long ulongVar = 18446744073709551615UL;
    
    cout << "unsigned short: " << ushortVar << endl;
    cout << "unsigned int: " << uintVar << endl;
    cout << "unsigned long: " << ulongVar << endl;
    
    // 浮点数类型
    cout << "\n=== 浮点数类型 ===" << endl;
    float floatVar = 3.14159f;
    double doubleVar = 3.141592653589793;
    long double longDoubleVar = 3.141592653589793238L;
    
    cout << std::fixed << std::setprecision(10);
    cout << "float: " << floatVar << " (大小: " << sizeof(float) << " 字节)" << endl;
    cout << "double: " << doubleVar << " (大小: " << sizeof(double) << " 字节)" << endl;
    cout << "long double: " << longDoubleVar << " (大小: " << sizeof(long double) << " 字节)" << endl;
    
    // 字符类型
    cout << "\n=== 字符类型 ===" << endl;
    char charVar = 'A';
    wchar_t wcharVar = L'中';
    
    cout << "char: " << charVar << " (ASCII: " << static_cast<int>(charVar) << ")" << endl;
    cout << "wchar_t: " << wcharVar << " (大小: " << sizeof(wchar_t) << " 字节)" << endl;
    
    // 布尔类型
    cout << "\n=== 布尔类型 ===" << endl;
    bool boolVar1 = true;
    bool boolVar2 = false;
    
    cout << std::boolalpha;
    cout << "bool (true): " << boolVar1 << endl;
    cout << "bool (false): " << boolVar2 << endl;
    cout << "bool 大小: " << sizeof(bool) << " 字节" << endl;
    
    // 类型范围信息
    cout << "\n=== 类型范围信息 ===" << endl;
    cout << "int 最小值: " << std::numeric_limits<int>::min() << endl;
    cout << "int 最大值: " << std::numeric_limits<int>::max() << endl;
    cout << "float 最小值: " << std::numeric_limits<float>::min() << endl;
    cout << "float 最大值: " << std::numeric_limits<float>::max() << endl;
    cout << "double 精度: " << std::numeric_limits<double>::digits10 << " 位" << endl;
    
    print_separator("基本数据类型示例完成");
    
    return 0;
} 