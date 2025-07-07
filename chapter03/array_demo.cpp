#include "common.h"

int main() {
    print_separator("数组操作示例");
    
    // 数组创建和初始化
    cout << "=== 数组创建和初始化 ===" << endl;
    int arr1[5];                        // 未初始化数组
    int arr2[5] = {1, 2, 3, 4, 5};      // 完全初始化
    int arr3[5] = {1, 2};               // 部分初始化，其余为0
    int arr4[] = {1, 2, 3, 4, 5, 6};    // 自动推断大小
    int arr5[5] = {};                   // 所有元素初始化为0
    
    cout << "arr1 (未初始化): ";
    for (int i = 0; i < 5; ++i) {
        cout << arr1[i] << " ";
    }
    cout << endl;
    
    cout << "arr2 (完全初始化): ";
    for (int i = 0; i < 5; ++i) {
        cout << arr2[i] << " ";
    }
    cout << endl;
    
    cout << "arr3 (部分初始化): ";
    for (int i = 0; i < 5; ++i) {
        cout << arr3[i] << " ";
    }
    cout << endl;
    
    cout << "arr4 (自动推断大小): ";
    for (int i = 0; i < 6; ++i) {
        cout << arr4[i] << " ";
    }
    cout << endl;
    
    cout << "arr5 (零初始化): ";
    for (int i = 0; i < 5; ++i) {
        cout << arr5[i] << " ";
    }
    cout << endl;
    
    // 数组大小
    cout << "\n=== 数组大小 ===" << endl;
    int sizeDemo[10] = {1, 2, 3, 4, 5};
    cout << "数组字节大小: " << sizeof(sizeDemo) << endl;
    cout << "数组元素个数: " << sizeof(sizeDemo) / sizeof(sizeDemo[0]) << endl;
    
    // 字符数组
    cout << "\n=== 字符数组 ===" << endl;
    char cstr1[] = "Hello";              // 自动包含'\0'
    char cstr2[10] = "World";            // 指定大小
    char cstr3[6] = {'H', 'e', 'l', 'l', 'o', '\0'};  // 显式指定
    
    cout << "cstr1: " << cstr1 << " (长度: " << strlen(cstr1) << ")" << endl;
    cout << "cstr2: " << cstr2 << " (长度: " << strlen(cstr2) << ")" << endl;
    cout << "cstr3: " << cstr3 << " (长度: " << strlen(cstr3) << ")" << endl;
    
    // 数组遍历
    cout << "\n=== 数组遍历 ===" << endl;
    int traverseDemo[] = {10, 20, 30, 40, 50};
    int arraySize = sizeof(traverseDemo) / sizeof(traverseDemo[0]);
    
    cout << "传统for循环: ";
    for (int i = 0; i < arraySize; ++i) {
        cout << traverseDemo[i] << " ";
    }
    cout << endl;
    
    cout << "范围for循环: ";
    for (int element : traverseDemo) {
        cout << element << " ";
    }
    cout << endl;
    
    // 数组与指针
    cout << "\n=== 数组与指针 ===" << endl;
    int ptrDemo[] = {1, 2, 3, 4, 5};
    int* ptr = ptrDemo;  // 数组名即为指向第一个元素的指针
    
    cout << "数组: ";
    for (int i = 0; i < 5; ++i) {
        cout << ptrDemo[i] << " ";
    }
    cout << endl;
    
    cout << "通过指针访问: ";
    for (int i = 0; i < 5; ++i) {
        cout << *(ptr + i) << " ";
    }
    cout << endl;
    
    cout << "数组首地址: " << ptrDemo << endl;
    cout << "指针值: " << ptr << endl;
    cout << "第一个元素地址: " << &ptrDemo[0] << endl;
    
    // 指针算术
    cout << "\n=== 指针算术 ===" << endl;
    int arithDemo[] = {10, 20, 30, 40, 50};
    int* p = arithDemo;
    
    cout << "p指向: " << *p << endl;
    cout << "p+1指向: " << *(p + 1) << endl;
    cout << "p+2指向: " << *(p + 2) << endl;
    
    p++;  // 移动指针
    cout << "p++后指向: " << *p << endl;
    
    // 数组作为函数参数
    cout << "\n=== 数组作为函数参数 ===" << endl;
    cout << "数组作为参数时退化为指针" << endl;
    cout << "需要同时传递数组大小信息" << endl;
    
    // C++11 array容器
    cout << "\n=== C++11 array容器 ===" << endl;
    std::array<int, 5> stdArray = {1, 2, 3, 4, 5};
    
    cout << "std::array: ";
    for (const auto& element : stdArray) {
        cout << element << " ";
    }
    cout << endl;
    
    cout << "size(): " << stdArray.size() << endl;
    cout << "front(): " << stdArray.front() << endl;
    cout << "back(): " << stdArray.back() << endl;
    cout << "at(2): " << stdArray.at(2) << endl;
    
    // 数组拷贝
    cout << "\n=== 数组拷贝 ===" << endl;
    int source[] = {1, 2, 3, 4, 5};
    int destination[5];
    
    // 使用循环拷贝
    for (int i = 0; i < 5; ++i) {
        destination[i] = source[i];
    }
    
    cout << "源数组: ";
    for (int element : source) {
        cout << element << " ";
    }
    cout << endl;
    
    cout << "目标数组: ";
    for (int element : destination) {
        cout << element << " ";
    }
    cout << endl;
    
    // 使用memcpy拷贝
    int destination2[5];
    memcpy(destination2, source, sizeof(source));
    
    cout << "memcpy拷贝: ";
    for (int element : destination2) {
        cout << element << " ";
    }
    cout << endl;
    
    // 数组比较
    cout << "\n=== 数组比较 ===" << endl;
    int arr_a[] = {1, 2, 3, 4, 5};
    int arr_b[] = {1, 2, 3, 4, 5};
    int arr_c[] = {1, 2, 3, 4, 6};
    
    cout << "arr_a == arr_b (地址): " << (arr_a == arr_b) << endl;
    
    // 内容比较
    bool equal_ab = true;
    bool equal_ac = true;
    
    for (int i = 0; i < 5; ++i) {
        if (arr_a[i] != arr_b[i]) {
            equal_ab = false;
            break;
        }
    }
    
    for (int i = 0; i < 5; ++i) {
        if (arr_a[i] != arr_c[i]) {
            equal_ac = false;
            break;
        }
    }
    
    cout << "arr_a 内容 == arr_b 内容: " << std::boolalpha << equal_ab << endl;
    cout << "arr_a 内容 == arr_c 内容: " << std::boolalpha << equal_ac << endl;
    
    // 动态数组
    cout << "\n=== 动态数组 ===" << endl;
    int size = 5;
    int* dynamicArray = new int[size];
    
    // 初始化动态数组
    for (int i = 0; i < size; ++i) {
        dynamicArray[i] = i * 10;
    }
    
    cout << "动态数组: ";
    for (int i = 0; i < size; ++i) {
        cout << dynamicArray[i] << " ";
    }
    cout << endl;
    
    // 释放内存
    delete[] dynamicArray;
    cout << "动态数组内存已释放" << endl;
    
    // 数组的优缺点
    cout << "\n=== 数组的优缺点 ===" << endl;
    cout << "优点:" << endl;
    cout << "1. 内存连续，访问效率高" << endl;
    cout << "2. 支持随机访问" << endl;
    cout << "3. 内存开销小" << endl;
    cout << "\n缺点:" << endl;
    cout << "1. 大小固定，不能动态调整" << endl;
    cout << "2. 不提供边界检查" << endl;
    cout << "3. 没有大小信息" << endl;
    cout << "4. 不支持拷贝和赋值" << endl;
    
    print_separator("数组操作示例完成");
    
    return 0;
} 