#include "common.h"

int main() {
    print_separator("指针和引用示例");
    
    // 指针基础
    cout << "=== 指针基础 ===" << endl;
    int value = 42;
    int* ptr = &value;  // 指针指向value的地址
    
    cout << "变量值: " << value << endl;
    cout << "变量地址: " << &value << endl;
    cout << "指针值（地址）: " << ptr << endl;
    cout << "指针解引用: " << *ptr << endl;
    cout << "指针的地址: " << &ptr << endl;
    
    // 通过指针修改值
    cout << "\n=== 通过指针修改值 ===" << endl;
    cout << "修改前: " << value << endl;
    *ptr = 100;
    cout << "修改后: " << value << endl;
    
    // 空指针
    cout << "\n=== 空指针 ===" << endl;
    int* nullPtr = nullptr;  // C++11推荐方式
    int* nullPtr2 = 0;       // 传统方式
    int* nullPtr3 = NULL;    // C风格（需要包含cstdlib）
    
    cout << "nullptr: " << nullPtr << endl;
    cout << "0: " << nullPtr2 << endl;
    cout << "NULL: " << nullPtr3 << endl;
    
    // 指针检查
    if (nullPtr == nullptr) {
        cout << "nullPtr 是空指针" << endl;
    }
    
    // 引用基础
    cout << "\n=== 引用基础 ===" << endl;
    int original = 200;
    int& ref = original;  // 引用必须初始化
    
    cout << "原始值: " << original << endl;
    cout << "引用值: " << ref << endl;
    cout << "原始地址: " << &original << endl;
    cout << "引用地址: " << &ref << endl;
    
    // 通过引用修改值
    cout << "\n=== 通过引用修改值 ===" << endl;
    cout << "修改前: " << original << endl;
    ref = 300;
    cout << "修改后: " << original << endl;
    
    // 指针与引用的区别
    cout << "\n=== 指针与引用的区别 ===" << endl;
    int a = 10, b = 20;
    
    // 指针可以重新指向
    int* p = &a;
    cout << "指针指向a: " << *p << endl;
    p = &b;
    cout << "指针指向b: " << *p << endl;
    
    // 引用不能重新绑定
    int& r = a;
    cout << "引用绑定a: " << r << endl;
    r = b;  // 这是赋值，不是重新绑定
    cout << "赋值后a的值: " << a << endl;
    cout << "赋值后引用值: " << r << endl;
    
    // 指针数组
    cout << "\n=== 指针数组 ===" << endl;
    int val1 = 1, val2 = 2, val3 = 3;
    int* ptrArray[3] = {&val1, &val2, &val3};
    
    cout << "指针数组: ";
    for (int i = 0; i < 3; ++i) {
        cout << *ptrArray[i] << " ";
    }
    cout << endl;
    
    // 数组指针
    cout << "\n=== 数组指针 ===" << endl;
    int arr[3] = {10, 20, 30};
    int (*arrPtr)[3] = &arr;  // 指向数组的指针
    
    cout << "数组: ";
    for (int i = 0; i < 3; ++i) {
        cout << (*arrPtr)[i] << " ";
    }
    cout << endl;
    
    // 指针算术
    cout << "\n=== 指针算术 ===" << endl;
    int numbers[5] = {1, 2, 3, 4, 5};
    int* numPtr = numbers;  // 指向数组首元素
    
    cout << "数组遍历（指针算术）: ";
    for (int i = 0; i < 5; ++i) {
        cout << *(numPtr + i) << " ";
    }
    cout << endl;
    
    // 指针与数组
    cout << "\n=== 指针与数组 ===" << endl;
    cout << "数组名: " << numbers << endl;
    cout << "首元素地址: " << &numbers[0] << endl;
    cout << "指针值: " << numPtr << endl;
    
    // 二级指针
    cout << "\n=== 二级指针 ===" << endl;
    int var = 500;
    int* ptr1 = &var;
    int** ptr2 = &ptr1;
    
    cout << "变量值: " << var << endl;
    cout << "一级指针: " << *ptr1 << endl;
    cout << "二级指针: " << **ptr2 << endl;
    cout << "二级指针指向的地址: " << *ptr2 << endl;
    cout << "二级指针的地址: " << ptr2 << endl;
    
    // 函数指针示例
    cout << "\n=== 函数指针概念 ===" << endl;
    cout << "函数指针可以指向函数，用于回调和动态调用" << endl;
    
    print_separator("指针和引用示例完成");
    
    return 0;
} 