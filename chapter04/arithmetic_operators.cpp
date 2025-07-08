#include "common.h"

int main() {
    print_separator("算术运算符示例");
    
    // 基本算术运算符
    cout << "=== 基本算术运算符 ===" << endl;
    int a = 15, b = 4;
    cout << "a = " << a << ", b = " << b << endl;
    
    cout << "加法 (a + b): " << a + b << endl;
    cout << "减法 (a - b): " << a - b << endl;
    cout << "乘法 (a * b): " << a * b << endl;
    cout << "除法 (a / b): " << a / b << endl;
    cout << "取模 (a % b): " << a % b << endl;
    
    // 浮点数运算
    cout << "\n=== 浮点数运算 ===" << endl;
    double x = 15.0, y = 4.0;
    cout << "x = " << x << ", y = " << y << endl;
    
    cout << "浮点除法 (x / y): " << x / y << endl;
    cout << "整数除法 vs 浮点除法: " << a / b << " vs " << x / y << endl;
    
    // 一元运算符
    cout << "\n=== 一元运算符 ===" << endl;
    int num = 10;
    cout << "原始值: " << num << endl;
    cout << "正号 (+num): " << +num << endl;
    cout << "负号 (-num): " << -num << endl;
    
    // 自增自减运算符
    cout << "\n=== 自增自减运算符 ===" << endl;
    int counter = 5;
    cout << "初始值: " << counter << endl;
    
    cout << "前置自增 (++counter): " << ++counter << endl;
    cout << "counter现在为: " << counter << endl;
    
    cout << "后置自增 (counter++): " << counter++ << endl;
    cout << "counter现在为: " << counter << endl;
    
    cout << "前置自减 (--counter): " << --counter << endl;
    cout << "counter现在为: " << counter << endl;
    
    cout << "后置自减 (counter--): " << counter-- << endl;
    cout << "counter现在为: " << counter << endl;
    
    // 前置vs后置的区别
    cout << "\n=== 前置vs后置的区别 ===" << endl;
    int val1 = 5, val2 = 5;
    int result1 = ++val1 * 2;  // 先自增，再计算
    int result2 = val2++ * 2;  // 先计算，再自增
    
    cout << "++val1 * 2 = " << result1 << ", val1 = " << val1 << endl;
    cout << "val2++ * 2 = " << result2 << ", val2 = " << val2 << endl;
    
    // 复合赋值运算符
    cout << "\n=== 复合赋值运算符 ===" << endl;
    int compound = 10;
    cout << "初始值: " << compound << endl;
    
    compound += 5;
    cout << "compound += 5: " << compound << endl;
    
    compound -= 3;
    cout << "compound -= 3: " << compound << endl;
    
    compound *= 2;
    cout << "compound *= 2: " << compound << endl;
    
    compound /= 4;
    cout << "compound /= 4: " << compound << endl;
    
    compound %= 3;
    cout << "compound %= 3: " << compound << endl;
    
    // 运算符优先级示例
    cout << "\n=== 运算符优先级示例 ===" << endl;
    int result;
    
    result = 2 + 3 * 4;
    cout << "2 + 3 * 4 = " << result << " (乘法优先)" << endl;
    
    result = (2 + 3) * 4;
    cout << "(2 + 3) * 4 = " << result << " (括号改变优先级)" << endl;
    
    result = 10 / 2 * 3;
    cout << "10 / 2 * 3 = " << result << " (从左到右)" << endl;
    
    // 整数除法的注意事项
    cout << "\n=== 整数除法的注意事项 ===" << endl;
    int dividend = 7, divisor = 3;
    cout << "整数除法 " << dividend << " / " << divisor << " = " << dividend / divisor << endl;
    cout << "余数 " << dividend << " % " << divisor << " = " << dividend % divisor << endl;
    
    double precise_result = static_cast<double>(dividend) / divisor;
    cout << "精确除法 " << dividend << " / " << divisor << " = " << precise_result << endl;
    
    // 除零检查
    cout << "\n=== 除零检查 ===" << endl;
    int zero_divisor = 0;
    cout << "检查除数: " << zero_divisor << endl;
    
    if (zero_divisor != 0) {
        cout << "10 / " << zero_divisor << " = " << 10 / zero_divisor << endl;
    } else {
        cout << "错误：除数不能为零！" << endl;
    }
    
    // 溢出示例
    cout << "\n=== 溢出示例 ===" << endl;
    int max_int = std::numeric_limits<int>::max();
    cout << "int最大值: " << max_int << endl;
    cout << "max_int + 1 = " << max_int + 1 << " (溢出)" << endl;
    
    unsigned int u_max = std::numeric_limits<unsigned int>::max();
    cout << "unsigned int最大值: " << u_max << endl;
    cout << "u_max + 1 = " << u_max + 1 << " (溢出回绕到0)" << endl;
    
    // 浮点数特殊值
    cout << "\n=== 浮点数特殊值 ===" << endl;
    double pos_inf = 1.0 / 0.0;
    double neg_inf = -1.0 / 0.0;
    double not_a_number = 0.0 / 0.0;
    
    cout << "正无穷: " << pos_inf << endl;
    cout << "负无穷: " << neg_inf << endl;
    cout << "NaN: " << not_a_number << endl;
    
    cout << "isinf(pos_inf): " << std::isinf(pos_inf) << endl;
    cout << "isnan(not_a_number): " << std::isnan(not_a_number) << endl;
    
    // 混合类型运算
    cout << "\n=== 混合类型运算 ===" << endl;
    int int_val = 5;
    double double_val = 2.5;
    float float_val = 1.5f;
    
    auto mixed_result1 = int_val + double_val;
    auto mixed_result2 = double_val * float_val;
    
    cout << "int + double: " << int_val << " + " << double_val << " = " << mixed_result1 << endl;
    cout << "结果类型大小: " << sizeof(mixed_result1) << " 字节" << endl;
    
    cout << "double * float: " << double_val << " * " << float_val << " = " << mixed_result2 << endl;
    cout << "结果类型大小: " << sizeof(mixed_result2) << " 字节" << endl;
    
    print_separator("算术运算符示例完成");
    
    return 0;
} 