#include "common.h"
#include <typeinfo>

// 辅助函数用于演示
int getInt() {
    return 42;
}

double getDouble() {
    return 3.14;
}

int main() {
    print_separator("auto和decltype示例");
    
    // auto基础用法
    cout << "=== auto基础用法 ===" << endl;
    auto intVar = 42;           // 推断为int
    auto doubleVar = 3.14;      // 推断为double
    auto charVar = 'A';         // 推断为char
    auto boolVar = true;        // 推断为bool
    auto stringVar = "Hello";   // 推断为const char*
    
    cout << "auto int: " << intVar << " (type: " << typeid(intVar).name() << ")" << endl;
    cout << "auto double: " << doubleVar << " (type: " << typeid(doubleVar).name() << ")" << endl;
    cout << "auto char: " << charVar << " (type: " << typeid(charVar).name() << ")" << endl;
    cout << "auto bool: " << std::boolalpha << boolVar << " (type: " << typeid(boolVar).name() << ")" << endl;
    cout << "auto string: " << stringVar << " (type: " << typeid(stringVar).name() << ")" << endl;
    
    // auto与指针
    cout << "\n=== auto与指针 ===" << endl;
    int value = 100;
    auto ptr = &value;          // 推断为int*
    auto deref = *ptr;          // 推断为int
    
    cout << "原始值: " << value << endl;
    cout << "auto指针: " << ptr << " (type: " << typeid(ptr).name() << ")" << endl;
    cout << "auto解引用: " << deref << " (type: " << typeid(deref).name() << ")" << endl;
    
    // auto与引用
    cout << "\n=== auto与引用 ===" << endl;
    int original = 200;
    int& ref = original;
    auto autoRef = ref;         // 推断为int（不是引用）
    auto& autoRefRef = ref;     // 显式引用
    
    cout << "原始值: " << original << endl;
    cout << "auto from ref: " << autoRef << " (type: " << typeid(autoRef).name() << ")" << endl;
    cout << "auto& from ref: " << autoRefRef << " (type: " << typeid(autoRefRef).name() << ")" << endl;
    
    // 修改测试
    autoRef = 300;              // 不会影响原始值
    cout << "修改autoRef后，原始值: " << original << endl;
    
    autoRefRef = 400;           // 会影响原始值
    cout << "修改autoRefRef后，原始值: " << original << endl;
    
    // auto与const
    cout << "\n=== auto与const ===" << endl;
    const int constValue = 500;
    auto autoConst = constValue;      // 推断为int（丢失const）
    const auto constAuto = constValue; // 显式const
    
    cout << "const值: " << constValue << endl;
    cout << "auto from const: " << autoConst << " (type: " << typeid(autoConst).name() << ")" << endl;
    cout << "const auto: " << constAuto << " (type: " << typeid(constAuto).name() << ")" << endl;
    
    // auto与函数返回值
    cout << "\n=== auto与函数返回值 ===" << endl;
    auto funcInt = getInt();
    auto funcDouble = getDouble();
    
    cout << "函数返回int: " << funcInt << " (type: " << typeid(funcInt).name() << ")" << endl;
    cout << "函数返回double: " << funcDouble << " (type: " << typeid(funcDouble).name() << ")" << endl;
    
    // auto与容器
    cout << "\n=== auto与容器 ===" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    auto vecSize = vec.size();
    
    cout << "vector大小: " << vecSize << " (type: " << typeid(vecSize).name() << ")" << endl;
    
    // 范围for循环中的auto
    cout << "vector元素（auto）: ";
    for (auto element : vec) {
        cout << element << " ";
    }
    cout << endl;
    
    // decltype基础用法
    cout << "\n=== decltype基础用法 ===" << endl;
    int x = 10;
    double y = 3.14;
    
    decltype(x) declInt = 20;          // 推断为int
    decltype(y) declDouble = 2.71;     // 推断为double
    decltype(x + y) declSum = x + y;   // 推断为double
    
    cout << "decltype(x): " << declInt << " (type: " << typeid(declInt).name() << ")" << endl;
    cout << "decltype(y): " << declDouble << " (type: " << typeid(declDouble).name() << ")" << endl;
    cout << "decltype(x + y): " << declSum << " (type: " << typeid(declSum).name() << ")" << endl;
    
    // decltype与引用
    cout << "\n=== decltype与引用 ===" << endl;
    int a = 30;
    int& refA = a;
    
    decltype(refA) declRefA = a;       // 推断为int&
    cout << "decltype(ref): " << declRefA << " (type: " << typeid(declRefA).name() << ")" << endl;
    
    // decltype与表达式
    cout << "\n=== decltype与表达式 ===" << endl;
    int arr[5] = {1, 2, 3, 4, 5};
    decltype(arr[0]) declArrElement = arr[0];  // 推断为int&
    
    cout << "数组元素: " << declArrElement << " (type: " << typeid(declArrElement).name() << ")" << endl;
    
    // auto与decltype结合
    cout << "\n=== auto与decltype结合 ===" << endl;
    auto autoVar = 42;
    decltype(autoVar) declFromAuto = 100;
    
    cout << "auto变量: " << autoVar << endl;
    cout << "decltype(auto变量): " << declFromAuto << " (type: " << typeid(declFromAuto).name() << ")" << endl;
    
    // 复杂示例
    cout << "\n=== 复杂示例 ===" << endl;
    auto complexAuto = [](int x, int y) -> int {
        return x + y;
    };
    
    auto result = complexAuto(10, 20);
    cout << "lambda结果: " << result << endl;
    
    // 尾置返回类型（C++11）
    cout << "\n=== 类型推断的优势 ===" << endl;
    cout << "1. 简化复杂类型声明" << endl;
    cout << "2. 自动适应类型变化" << endl;
    cout << "3. 提高代码可读性" << endl;
    cout << "4. 减少类型不匹配错误" << endl;
    
    print_separator("auto和decltype示例完成");
    
    return 0;
} 