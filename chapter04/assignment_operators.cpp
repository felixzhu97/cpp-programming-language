#include "common.h"

int main() {
    print_separator("赋值运算符示例");
    
    // 基本赋值运算符
    cout << "=== 基本赋值运算符 ===" << endl;
    int a = 10;
    int b = 20;
    cout << "初始值: a = " << a << ", b = " << b << endl;
    
    // 简单赋值
    a = b;
    cout << "a = b 后: a = " << a << ", b = " << b << endl;
    
    // 链式赋值
    int c, d, e;
    c = d = e = 100;
    cout << "链式赋值 c = d = e = 100: c = " << c << ", d = " << d << ", e = " << e << endl;
    
    // 复合赋值运算符
    cout << "\n=== 复合赋值运算符 ===" << endl;
    int num = 50;
    cout << "初始值: " << num << endl;
    
    // 算术复合赋值
    num += 10;
    cout << "num += 10: " << num << endl;
    
    num -= 5;
    cout << "num -= 5: " << num << endl;
    
    num *= 2;
    cout << "num *= 2: " << num << endl;
    
    num /= 3;
    cout << "num /= 3: " << num << endl;
    
    num %= 10;
    cout << "num %= 10: " << num << endl;
    
    // 位运算复合赋值
    cout << "\n=== 位运算复合赋值 ===" << endl;
    unsigned int bits = 12;  // 12 = 1100 in binary
    cout << "初始值: " << bits << " (二进制: " << bitset<8>(bits) << ")" << endl;
    
    bits &= 10;  // 10 = 1010 in binary
    cout << "bits &= 10: " << bits << " (二进制: " << bitset<8>(bits) << ")" << endl;
    
    bits |= 5;   // 5 = 0101 in binary
    cout << "bits |= 5: " << bits << " (二进制: " << bitset<8>(bits) << ")" << endl;
    
    bits ^= 3;   // 3 = 0011 in binary
    cout << "bits ^= 3: " << bits << " (二进制: " << bitset<8>(bits) << ")" << endl;
    
    bits <<= 2;
    cout << "bits <<= 2: " << bits << " (二进制: " << bitset<8>(bits) << ")" << endl;
    
    bits >>= 1;
    cout << "bits >>= 1: " << bits << " (二进制: " << bitset<8>(bits) << ")" << endl;
    
    // 赋值运算符的返回值
    cout << "\n=== 赋值运算符的返回值 ===" << endl;
    int x = 5, y = 10;
    cout << "x = " << x << ", y = " << y << endl;
    
    // 赋值运算符返回左操作数的引用
    int z = (x = y);
    cout << "z = (x = y): x = " << x << ", y = " << y << ", z = " << z << endl;
    
    // 在条件表达式中使用赋值
    int input = 0;
    cout << "模拟输入处理:" << endl;
    if ((input = 42) != 0) {
        cout << "输入值 " << input << " 非零" << endl;
    }
    
    // 自增自减运算符
    cout << "\n=== 自增自减运算符 ===" << endl;
    int counter = 10;
    cout << "初始值: " << counter << endl;
    
    cout << "前置自增 ++counter: " << ++counter << ", counter = " << counter << endl;
    cout << "后置自增 counter++: " << counter++ << ", counter = " << counter << endl;
    
    cout << "前置自减 --counter: " << --counter << ", counter = " << counter << endl;
    cout << "后置自减 counter--: " << counter-- << ", counter = " << counter << endl;
    
    // 前置与后置的区别
    cout << "\n=== 前置与后置的区别 ===" << endl;
    int val1 = 5, val2 = 5;
    
    // 前置：先增加，再使用
    int result1 = ++val1 * 2;
    cout << "++val1 * 2 = " << result1 << ", val1 = " << val1 << endl;
    
    // 后置：先使用，再增加
    int result2 = val2++ * 2;
    cout << "val2++ * 2 = " << result2 << ", val2 = " << val2 << endl;
    
    // 在循环中的应用
    cout << "\n=== 在循环中的应用 ===" << endl;
    cout << "使用后置自增的for循环:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "i = " << i << " ";
    }
    cout << endl;
    
    cout << "使用前置自增的for循环:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "i = " << i << " ";
    }
    cout << endl;
    
    // 数组和指针的赋值
    cout << "\n=== 数组和指针的赋值 ===" << endl;
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr = arr;
    
    cout << "数组元素: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 通过指针修改数组元素
    *ptr = 10;
    *(ptr + 1) = 20;
    cout << "修改后: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 指针自增
    cout << "指针自增遍历:" << endl;
    ptr = arr;  // 重新指向数组开头
    for (int i = 0; i < 5; i++) {
        cout << "*ptr = " << *ptr << ", ptr地址: " << ptr << endl;
        ptr++;
    }
    
    // 字符串赋值
    cout << "\n=== 字符串赋值 ===" << endl;
    string str1 = "Hello";
    string str2 = "World";
    cout << "str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" << endl;
    
    str1 = str2;
    cout << "str1 = str2 后: str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" << endl;
    
    // 字符串复合赋值
    str1 += " C++";
    cout << "str1 += \" C++\": str1 = \"" << str1 << "\"" << endl;
    
    // 结构体赋值
    cout << "\n=== 结构体赋值 ===" << endl;
    struct Point {
        int x, y;
    };
    
    Point p1 = {10, 20};
    Point p2 = {30, 40};
    cout << "p1 = (" << p1.x << ", " << p1.y << ")" << endl;
    cout << "p2 = (" << p2.x << ", " << p2.y << ")" << endl;
    
    p1 = p2;  // 结构体赋值
    cout << "p1 = p2 后: p1 = (" << p1.x << ", " << p1.y << ")" << endl;
    
    // 赋值运算符的优先级
    cout << "\n=== 赋值运算符的优先级 ===" << endl;
    int m = 10, n = 20, p = 30;
    
    // 赋值运算符是右结合的
    m = n = p;
    cout << "m = n = p: m = " << m << ", n = " << n << ", p = " << p << endl;
    
    // 赋值运算符的优先级低于算术运算符
    int result = m + n;
    cout << "result = m + n: " << result << endl;
    
    // 括号改变优先级
    p = 5;
    result = (m = p) + n;
    cout << "result = (m = p) + n: result = " << result << ", m = " << m << endl;
    
    // 常见错误：在条件中使用赋值
    cout << "\n=== 常见错误示例 ===" << endl;
    int test_val = 5;
    
    // 错误示例（但在这里是故意的）
    if (test_val = 0) {  // 赋值而不是比较
        cout << "这行不会执行" << endl;
    } else {
        cout << "test_val被赋值为0: " << test_val << endl;
    }
    
    // 正确的比较
    test_val = 5;
    if (test_val == 0) {  // 比较
        cout << "test_val等于0" << endl;
    } else {
        cout << "test_val不等于0，值为: " << test_val << endl;
    }
    
    // 避免错误的方法：使用常量在左边
    if (0 == test_val) {  // 如果误写成=会产生编译错误
        cout << "test_val等于0" << endl;
    } else {
        cout << "使用常量在左边的比较" << endl;
    }
    
    // 赋值运算符的实际应用
    cout << "\n=== 赋值运算符的实际应用 ===" << endl;
    
    // 累加器
    int sum = 0;
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    cout << "使用+=累加:" << endl;
    for (int num : numbers) {
        sum += num;
        cout << "当前和: " << sum << endl;
    }
    
    // 计数器
    int count = 0;
    for (int num : numbers) {
        if (num % 2 == 0) {
            count++;
        }
    }
    cout << "偶数个数: " << count << endl;
    
    // 位操作应用
    cout << "\n位操作应用:" << endl;
    unsigned int flags = 0;
    const unsigned int FLAG_A = 1;
    const unsigned int FLAG_B = 2;
    const unsigned int FLAG_C = 4;
    
    flags |= FLAG_A;  // 设置标志A
    cout << "设置标志A: " << bitset<8>(flags) << endl;
    
    flags |= FLAG_C;  // 设置标志C
    cout << "设置标志C: " << bitset<8>(flags) << endl;
    
    flags &= ~FLAG_A;  // 清除标志A
    cout << "清除标志A: " << bitset<8>(flags) << endl;
    
    print_separator("赋值运算符示例完成");
    
    return 0;
} 