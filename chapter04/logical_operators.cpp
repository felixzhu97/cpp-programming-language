#include "common.h"

int main() {
    print_separator("逻辑运算符示例");
    
    // 基本逻辑运算符
    cout << "=== 基本逻辑运算符 ===" << endl;
    bool a = true, b = false;
    cout << "a = " << (a ? "true" : "false") << ", b = " << (b ? "true" : "false") << endl;
    
    cout << "逻辑与 (a && b): " << (a && b ? "true" : "false") << endl;
    cout << "逻辑或 (a || b): " << (a || b ? "true" : "false") << endl;
    cout << "逻辑非 (!a): " << (!a ? "true" : "false") << endl;
    cout << "逻辑非 (!b): " << (!b ? "true" : "false") << endl;
    
    // 真值表演示
    cout << "\n=== 逻辑与(&& )真值表 ===" << endl;
    cout << "true  && true  = " << (true && true ? "true" : "false") << endl;
    cout << "true  && false = " << (true && false ? "true" : "false") << endl;
    cout << "false && true  = " << (false && true ? "true" : "false") << endl;
    cout << "false && false = " << (false && false ? "true" : "false") << endl;
    
    cout << "\n=== 逻辑或(||)真值表 ===" << endl;
    cout << "true  || true  = " << (true || true ? "true" : "false") << endl;
    cout << "true  || false = " << (true || false ? "true" : "false") << endl;
    cout << "false || true  = " << (false || true ? "true" : "false") << endl;
    cout << "false || false = " << (false || false ? "true" : "false") << endl;
    
    // 短路求值
    cout << "\n=== 短路求值 ===" << endl;
    int x = 5, y = 0;
    cout << "x = " << x << ", y = " << y << endl;
    
    // 逻辑与的短路求值
    cout << "\n测试短路求值 (&&):" << endl;
    if (y != 0 && x / y > 2) {
        cout << "条件为真" << endl;
    } else {
        cout << "条件为假 (y为0，不会执行除法)" << endl;
    }
    
    // 逻辑或的短路求值
    cout << "\n测试短路求值 (||):" << endl;
    if (x > 0 || x / y > 2) {
        cout << "条件为真 (x > 0，不会执行除法)" << endl;
    } else {
        cout << "条件为假" << endl;
    }
    
    // 比较运算符
    cout << "\n=== 比较运算符 ===" << endl;
    int num1 = 10, num2 = 20, num3 = 10;
    cout << "num1 = " << num1 << ", num2 = " << num2 << ", num3 = " << num3 << endl;
    
    cout << "num1 == num2: " << (num1 == num2 ? "true" : "false") << endl;
    cout << "num1 == num3: " << (num1 == num3 ? "true" : "false") << endl;
    cout << "num1 != num2: " << (num1 != num2 ? "true" : "false") << endl;
    cout << "num1 < num2: " << (num1 < num2 ? "true" : "false") << endl;
    cout << "num1 > num2: " << (num1 > num2 ? "true" : "false") << endl;
    cout << "num1 <= num3: " << (num1 <= num3 ? "true" : "false") << endl;
    cout << "num1 >= num3: " << (num1 >= num3 ? "true" : "false") << endl;
    
    // 逻辑运算符的优先级
    cout << "\n=== 逻辑运算符优先级 ===" << endl;
    bool result;
    
    result = true || false && false;
    cout << "true || false && false = " << (result ? "true" : "false") << " (&&优先级高于||)" << endl;
    
    result = (true || false) && false;
    cout << "(true || false) && false = " << (result ? "true" : "false") << " (括号改变优先级)" << endl;
    
    result = !true || false;
    cout << "!true || false = " << (result ? "true" : "false") << " (!优先级最高)" << endl;
    
    // 数值的布尔转换
    cout << "\n=== 数值的布尔转换 ===" << endl;
    int zero = 0, positive = 42, negative = -5;
    double d_zero = 0.0, d_positive = 3.14;
    
    cout << "整数转布尔:" << endl;
    cout << "0 -> " << (zero ? "true" : "false") << endl;
    cout << "42 -> " << (positive ? "true" : "false") << endl;
    cout << "-5 -> " << (negative ? "true" : "false") << endl;
    
    cout << "浮点数转布尔:" << endl;
    cout << "0.0 -> " << (d_zero ? "true" : "false") << endl;
    cout << "3.14 -> " << (d_positive ? "true" : "false") << endl;
    
    // 指针的布尔转换
    cout << "\n=== 指针的布尔转换 ===" << endl;
    int* null_ptr = nullptr;
    int* valid_ptr = &num1;
    
    cout << "nullptr -> " << (null_ptr ? "true" : "false") << endl;
    cout << "有效指针 -> " << (valid_ptr ? "true" : "false") << endl;
    
    // 复合逻辑表达式
    cout << "\n=== 复合逻辑表达式 ===" << endl;
    int age = 25;
    bool has_license = true;
    bool has_car = false;
    
    cout << "年龄: " << age << ", 有驾照: " << (has_license ? "是" : "否") 
         << ", 有车: " << (has_car ? "是" : "否") << endl;
    
    // 可以开车的条件
    bool can_drive = age >= 18 && has_license;
    cout << "可以开车: " << (can_drive ? "是" : "否") << endl;
    
    // 需要租车的条件
    bool need_rental = can_drive && !has_car;
    cout << "需要租车: " << (need_rental ? "是" : "否") << endl;
    
    // 德摩根定律
    cout << "\n=== 德摩根定律 ===" << endl;
    bool p = true, q = false;
    cout << "p = " << (p ? "true" : "false") << ", q = " << (q ? "true" : "false") << endl;
    
    // !(p && q) == !p || !q
    bool left_side = !(p && q);
    bool right_side = !p || !q;
    cout << "!(p && q) = " << (left_side ? "true" : "false") << endl;
    cout << "!p || !q = " << (right_side ? "true" : "false") << endl;
    cout << "德摩根定律1验证: " << (left_side == right_side ? "成立" : "不成立") << endl;
    
    // !(p || q) == !p && !q
    left_side = !(p || q);
    right_side = !p && !q;
    cout << "!(p || q) = " << (left_side ? "true" : "false") << endl;
    cout << "!p && !q = " << (right_side ? "true" : "false") << endl;
    cout << "德摩根定律2验证: " << (left_side == right_side ? "成立" : "不成立") << endl;
    
    // 三元条件运算符
    cout << "\n=== 三元条件运算符 ===" << endl;
    int score = 85;
    string grade = (score >= 90) ? "优秀" : 
                   (score >= 80) ? "良好" : 
                   (score >= 70) ? "中等" : 
                   (score >= 60) ? "及格" : "不及格";
    
    cout << "分数: " << score << ", 等级: " << grade << endl;
    
    // 条件运算符与if-else的比较
    cout << "\n=== 条件运算符 vs if-else ===" << endl;
    int a_val = 10, b_val = 20;
    
    // 使用条件运算符
    int max_val = (a_val > b_val) ? a_val : b_val;
    cout << "使用条件运算符求最大值: " << max_val << endl;
    
    // 使用if-else
    int max_val2;
    if (a_val > b_val) {
        max_val2 = a_val;
    } else {
        max_val2 = b_val;
    }
    cout << "使用if-else求最大值: " << max_val2 << endl;
    
    // 逻辑运算符的实际应用
    cout << "\n=== 逻辑运算符的实际应用 ===" << endl;
    
    // 范围检查
    int value = 75;
    bool in_range = (value >= 0 && value <= 100);
    cout << "值 " << value << " 在0-100范围内: " << (in_range ? "是" : "否") << endl;
    
    // 字符判断
    char ch = 'A';
    bool is_uppercase = (ch >= 'A' && ch <= 'Z');
    bool is_lowercase = (ch >= 'a' && ch <= 'z');
    bool is_digit = (ch >= '0' && ch <= '9');
    
    cout << "字符 '" << ch << "' 是:" << endl;
    cout << "  大写字母: " << (is_uppercase ? "是" : "否") << endl;
    cout << "  小写字母: " << (is_lowercase ? "是" : "否") << endl;
    cout << "  数字: " << (is_digit ? "是" : "否") << endl;
    
    // 闰年判断
    int year = 2024;
    bool is_leap_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    cout << year << "年是闰年: " << (is_leap_year ? "是" : "否") << endl;
    
    // 输入验证
    cout << "\n=== 输入验证示例 ===" << endl;
    int user_age = 25;
    string user_name = "Alice";
    
    // 验证姓名不为空且年龄在合理范围内
    bool valid_input = !user_name.empty() && user_age > 0 && user_age < 120;
    cout << "用户输入有效: " << (valid_input ? "是" : "否") << endl;
    
    print_separator("逻辑运算符示例完成");
    
    return 0;
} 