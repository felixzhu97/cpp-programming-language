#include "common.h"

int main() {
    print_separator("运算符优先级示例");
    
    // 算术运算符优先级
    cout << "=== 算术运算符优先级 ===" << endl;
    int a = 2, b = 3, c = 4, d = 5;
    int result;
    
    // 乘除法优先于加减法
    result = a + b * c;
    cout << "a + b * c = " << a << " + " << b << " * " << c << " = " << result << endl;
    cout << "等价于: " << a << " + (" << b << " * " << c << ") = " << a + (b * c) << endl;
    
    result = a * b + c;
    cout << "a * b + c = " << a << " * " << b << " + " << c << " = " << result << endl;
    cout << "等价于: (" << a << " * " << b << ") + " << c << " = " << (a * b) + c << endl;
    
    // 同级运算符从左到右
    result = a + b - c;
    cout << "a + b - c = " << a << " + " << b << " - " << c << " = " << result << endl;
    cout << "等价于: (" << a << " + " << b << ") - " << c << " = " << (a + b) - c << endl;
    
    result = a * b / c;
    cout << "a * b / c = " << a << " * " << b << " / " << c << " = " << result << endl;
    cout << "等价于: (" << a << " * " << b << ") / " << c << " = " << (a * b) / c << endl;
    
    // 括号改变优先级
    cout << "\n=== 括号改变优先级 ===" << endl;
    result = (a + b) * c;
    cout << "(a + b) * c = (" << a << " + " << b << ") * " << c << " = " << result << endl;
    
    result = a * (b + c);
    cout << "a * (b + c) = " << a << " * (" << b << " + " << c << ") = " << result << endl;
    
    // 一元运算符优先级
    cout << "\n=== 一元运算符优先级 ===" << endl;
    int x = 5;
    cout << "x = " << x << endl;
    
    result = -x * 2;
    cout << "-x * 2 = " << result << " (一元负号优先级高)" << endl;
    
    result = -(x * 2);
    cout << "-(x * 2) = " << result << " (用括号明确顺序)" << endl;
    
    // 逻辑运算符优先级
    cout << "\n=== 逻辑运算符优先级 ===" << endl;
    bool p = true, q = false, r = true;
    cout << "p = " << (p ? "true" : "false") << ", q = " << (q ? "true" : "false") 
         << ", r = " << (r ? "true" : "false") << endl;
    
    // &&优先级高于||
    bool logic_result = p || q && r;
    cout << "p || q && r = " << (logic_result ? "true" : "false") << endl;
    cout << "等价于: p || (q && r) = " << (p || (q && r) ? "true" : "false") << endl;
    
    logic_result = (p || q) && r;
    cout << "(p || q) && r = " << (logic_result ? "true" : "false") << endl;
    
    // 比较运算符优先级
    cout << "\n=== 比较运算符优先级 ===" << endl;
    int val1 = 10, val2 = 20, val3 = 30;
    
    // 比较运算符优先级相同，从左到右
    logic_result = val1 < val2 < val3;
    cout << "val1 < val2 < val3 = " << (logic_result ? "true" : "false") << endl;
    cout << "注意：这可能不是你想要的结果！" << endl;
    cout << "实际计算: (val1 < val2) < val3 = " << ((val1 < val2) < val3 ? "true" : "false") << endl;
    cout << "即: " << (val1 < val2) << " < " << val3 << " = " << ((val1 < val2) < val3 ? "true" : "false") << endl;
    
    // 正确的范围比较
    logic_result = (val1 < val2) && (val2 < val3);
    cout << "正确的范围比较: (val1 < val2) && (val2 < val3) = " << (logic_result ? "true" : "false") << endl;
    
    // 赋值运算符优先级
    cout << "\n=== 赋值运算符优先级 ===" << endl;
    int m = 10, n = 20, o = 30;
    
    // 赋值运算符是右结合的
    m = n = o;
    cout << "m = n = o: m = " << m << ", n = " << n << ", o = " << o << endl;
    cout << "等价于: m = (n = o)" << endl;
    
    // 赋值运算符优先级低于算术运算符
    m = 5;
    n = 3;
    m += n * 2;
    cout << "m += n * 2: m = " << m << " (等价于 m = m + (n * 2))" << endl;
    
    // 条件运算符优先级
    cout << "\n=== 条件运算符优先级 ===" << endl;
    int score = 85;
    
    // 条件运算符优先级低于比较运算符
    string grade = score >= 90 ? "A" : score >= 80 ? "B" : "C";
    cout << "分数 " << score << " 的等级: " << grade << endl;
    
    // 逗号运算符优先级最低
    cout << "\n=== 逗号运算符优先级 ===" << endl;
    int comma_result = (x = 1, y = 2, x + y);
    cout << "逗号运算符: (x = 1, y = 2, x + y) = " << comma_result << endl;
    cout << "x = " << x << ", y = " << y << endl;
    
    // 混合运算符优先级
    cout << "\n=== 混合运算符优先级 ===" << endl;
    int complex_expr = 10 + 5 * 2 - 3 / 1;
    cout << "10 + 5 * 2 - 3 / 1 = " << complex_expr << endl;
    cout << "计算顺序: 10 + (5 * 2) - (3 / 1) = " << 10 + (5 * 2) - (3 / 1) << endl;
    
    // 更复杂的表达式
    logic_result = 10 > 5 && 20 < 30 || 40 == 50;
    cout << "10 > 5 && 20 < 30 || 40 == 50 = " << (logic_result ? "true" : "false") << endl;
    cout << "计算顺序: ((10 > 5) && (20 < 30)) || (40 == 50) = " 
         << (((10 > 5) && (20 < 30)) || (40 == 50) ? "true" : "false") << endl;
    
    // 位运算符优先级
    cout << "\n=== 位运算符优先级 ===" << endl;
    unsigned int bit_a = 12, bit_b = 10, bit_c = 5;  // 12=1100, 10=1010, 5=0101
    
    // 位运算符优先级：& > ^ > |
    unsigned int bit_result = bit_a | bit_b & bit_c;
    cout << "bit_a | bit_b & bit_c = " << bit_a << " | " << bit_b << " & " << bit_c << " = " << bit_result << endl;
    cout << "等价于: bit_a | (bit_b & bit_c) = " << bit_a << " | (" << bit_b << " & " << bit_c << ") = " 
         << (bit_a | (bit_b & bit_c)) << endl;
    
    // 自增自减运算符优先级
    cout << "\n=== 自增自减运算符优先级 ===" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    int* ptr = arr;
    
    cout << "数组: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 后置自增优先级高于解引用
    cout << "*ptr++ = " << *ptr++ << " (先解引用，再自增指针)" << endl;
    cout << "现在ptr指向: " << *ptr << endl;
    
    // 前置自增优先级高于解引用
    ptr = arr;  // 重置指针
    cout << "*++ptr = " << *++ptr << " (先自增指针，再解引用)" << endl;
    
    // 运算符优先级表（部分）
    cout << "\n=== 运算符优先级表（从高到低） ===" << endl;
    cout << "1. 后置自增/自减 (++/--)、函数调用 ()、数组下标 []" << endl;
    cout << "2. 前置自增/自减 (++/--)、一元运算符 (+/-/!/~)、解引用 (*)、取地址 (&)" << endl;
    cout << "3. 乘除模 (*//%)" << endl;
    cout << "4. 加减 (+/-)" << endl;
    cout << "5. 移位 (<</>>) " << endl;
    cout << "6. 关系运算符 (</<=/>/>=)" << endl;
    cout << "7. 相等运算符 (==/!=)" << endl;
    cout << "8. 位与 (&)" << endl;
    cout << "9. 位异或 (^)" << endl;
    cout << "10. 位或 (|)" << endl;
    cout << "11. 逻辑与 (&&)" << endl;
    cout << "12. 逻辑或 (||)" << endl;
    cout << "13. 条件运算符 (?:)" << endl;
    cout << "14. 赋值运算符 (=/+=/等)" << endl;
    cout << "15. 逗号运算符 (,)" << endl;
    
    // 实际应用中的优先级问题
    cout << "\n=== 实际应用中的优先级问题 ===" << endl;
    
    // 1. 函数调用中的优先级
    cout << "1. 函数调用中的优先级:" << endl;
    auto multiply = [](int a, int b) { return a * b; };
    result = multiply(3 + 2, 4);
    cout << "multiply(3 + 2, 4) = " << result << endl;
    
    // 2. 数组访问中的优先级
    cout << "2. 数组访问中的优先级:" << endl;
    int index = 2;
    cout << "arr[index++] = " << arr[index++] << ", index现在为: " << index << endl;
    
    // 3. 结构体成员访问
    cout << "3. 结构体成员访问:" << endl;
    struct Point {
        int x, y;
    };
    Point point = {10, 20};
    Point* pPoint = &point;
    
    cout << "(*pPoint).x = " << (*pPoint).x << endl;
    cout << "pPoint->x = " << pPoint->x << " (-> 等价于 (*pPoint).)" << endl;
    
    // 推荐的做法
    cout << "\n=== 推荐的做法 ===" << endl;
    cout << "1. 使用括号明确表达式的计算顺序" << endl;
    cout << "2. 复杂表达式拆分成多个简单表达式" << endl;
    cout << "3. 一行代码只做一件事" << endl;
    cout << "4. 避免依赖运算符优先级，除非是最常用的情况" << endl;
    
    print_separator("运算符优先级示例完成");
    
    return 0;
} 