#include "common.h"

int main() {
    print_separator("const限定符示例");
    
    // 基本const变量
    cout << "=== 基本const变量 ===" << endl;
    const int constInt = 100;
    cout << "const int: " << constInt << endl;
    // constInt = 200;  // 编译错误！不能修改const变量
    
    // const与指针
    cout << "\n=== const与指针 ===" << endl;
    
    // 指向常量的指针
    int value1 = 10;
    int value2 = 20;
    const int* ptrToConst = &value1;
    cout << "指向常量的指针: " << *ptrToConst << endl;
    // *ptrToConst = 30;  // 编译错误！不能通过指针修改值
    ptrToConst = &value2;  // 可以改变指针指向
    cout << "改变指向后: " << *ptrToConst << endl;
    
    // 常量指针
    int* const constPtr = &value1;
    cout << "常量指针: " << *constPtr << endl;
    *constPtr = 30;  // 可以修改指向的值
    cout << "修改值后: " << *constPtr << endl;
    // constPtr = &value2;  // 编译错误！不能改变常量指针的指向
    
    // 指向常量的常量指针
    const int* const constPtrToConst = &value1;
    cout << "指向常量的常量指针: " << *constPtrToConst << endl;
    // *constPtrToConst = 40;  // 编译错误！不能修改值
    // constPtrToConst = &value2;  // 编译错误！不能改变指向
    
    // 顶层const和底层const
    cout << "\n=== 顶层const和底层const ===" << endl;
    int i = 42;
    const int ci = i;  // 顶层const
    const int* p1 = &ci;  // 底层const
    int* const p2 = &i;  // 顶层const
    const int* const p3 = &ci;  // 既有顶层const又有底层const
    
    cout << "普通变量 i: " << i << endl;
    cout << "顶层const ci: " << ci << endl;
    cout << "底层const *p1: " << *p1 << endl;
    cout << "顶层const *p2: " << *p2 << endl;
    cout << "顶层+底层const *p3: " << *p3 << endl;
    
    // const与引用
    cout << "\n=== const与引用 ===" << endl;
    int original = 50;
    const int& constRef = original;
    cout << "原始值: " << original << endl;
    cout << "const引用: " << constRef << endl;
    
    original = 60;  // 可以修改原始值
    cout << "修改原始值后: " << original << endl;
    cout << "const引用: " << constRef << endl;
    // constRef = 70;  // 编译错误！不能通过const引用修改值
    
    // 常量表达式
    cout << "\n=== 常量表达式 ===" << endl;
    const int sz = 10;
    const int limit = sz + 1;
    cout << "常量表达式 sz: " << sz << endl;
    cout << "常量表达式 limit: " << limit << endl;
    
    // constexpr（C++11）
    cout << "\n=== constexpr ===" << endl;
    constexpr int maxSize = 100;
    constexpr int doubleMax = maxSize * 2;
    cout << "constexpr maxSize: " << maxSize << endl;
    cout << "constexpr doubleMax: " << doubleMax << endl;
    
    // 数组与const
    cout << "\n=== 数组与const ===" << endl;
    const int arr[5] = {1, 2, 3, 4, 5};
    cout << "const数组: ";
    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    // arr[0] = 10;  // 编译错误！不能修改const数组元素
    
    // const成员函数（在类中使用，这里演示概念）
    cout << "\n=== const的作用 ===" << endl;
    cout << "const关键字的作用：" << endl;
    cout << "1. 防止意外修改变量" << endl;
    cout << "2. 表明程序员的意图" << endl;
    cout << "3. 编译器优化" << endl;
    cout << "4. 函数重载的区分" << endl;
    
    print_separator("const限定符示例完成");
    
    return 0;
} 