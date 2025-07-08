#include "common.h"

int main() {
    print_separator("简单语句示例");
    
    // 表达式语句
    cout << "=== 表达式语句 ===" << endl;
    
    // 赋值语句
    cout << "1. 赋值语句:" << endl;
    int a = 10;
    int b = 20;
    cout << "a = " << a << ", b = " << b << endl;
    
    // 赋值操作本身是表达式
    int c = (a = b + 5);  // 先计算b + 5，赋值给a，然后赋值给c
    cout << "执行 c = (a = b + 5) 后: a = " << a << ", c = " << c << endl;
    
    // 算术表达式语句
    cout << "\n2. 算术表达式语句:" << endl;
    int x = 5;
    int y = 3;
    cout << "x = " << x << ", y = " << y << endl;
    
    x + y;  // 这是一个表达式语句，但结果被丢弃
    cout << "x + y; 执行后，x = " << x << ", y = " << y << " (值未改变)" << endl;
    
    x += y;  // 这会修改x的值
    cout << "x += y; 执行后，x = " << x << ", y = " << y << endl;
    
    // 函数调用语句
    cout << "\n3. 函数调用语句:" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5};
    cout << "原始vector大小: " << numbers.size() << endl;
    
    numbers.push_back(6);  // 函数调用语句
    cout << "push_back(6)后vector大小: " << numbers.size() << endl;
    
    // 前缀和后缀运算符
    cout << "\n4. 前缀和后缀运算符:" << endl;
    int counter = 0;
    cout << "初始counter: " << counter << endl;
    
    counter++;  // 后缀自增语句
    cout << "counter++后: " << counter << endl;
    
    ++counter;  // 前缀自增语句
    cout << "++counter后: " << counter << endl;
    
    // 在表达式中的差异
    int val1 = 10;
    int val2 = 10;
    cout << "val1 = " << val1 << ", val2 = " << val2 << endl;
    
    int result1 = val1++;  // 后缀：先赋值，后自增
    int result2 = ++val2;  // 前缀：先自增，后赋值
    cout << "result1 = val1++ 得到 " << result1 << ", val1 = " << val1 << endl;
    cout << "result2 = ++val2 得到 " << result2 << ", val2 = " << val2 << endl;
    
    // 空语句
    cout << "\n=== 空语句 ===" << endl;
    cout << "空语句演示:" << endl;
    
    // 空语句在循环中的应用
    string text = "hello";
    size_t pos = 0;
    
    // 寻找第一个'l'的位置
    while (pos < text.length() && text[pos] != 'l') {
        pos++;  // 这里可以简化为空语句
    }
    
    if (pos < text.length()) {
        cout << "在位置 " << pos << " 找到字符 'l'" << endl;
    }
    
    // 使用空语句的简化版本
    pos = 0;
    while (pos < text.length() && text[pos] != 'l')
        pos++;  // 循环体为空，工作在条件检查中完成
    
    cout << "使用空语句循环，找到位置: " << pos << endl;
    
    // 复合语句（块语句）
    cout << "\n=== 复合语句（块语句) ===" << endl;
    cout << "复合语句演示:" << endl;
    
    {
        // 这是一个块语句
        int local_var = 100;
        cout << "块内变量: " << local_var << endl;
        
        {
            // 嵌套块
            int nested_var = 200;
            cout << "嵌套块内变量: " << nested_var << endl;
            cout << "可以访问外层变量: " << local_var << endl;
        }
        // nested_var 在这里不可访问
        cout << "回到外层块，local_var = " << local_var << endl;
    }
    // local_var 在这里不可访问
    
    // 变量作用域
    cout << "\n=== 变量作用域 ===" << endl;
    int global_var = 50;
    cout << "全局变量: " << global_var << endl;
    
    {
        int local_var = 60;
        cout << "局部变量: " << local_var << endl;
        cout << "可以访问全局变量: " << global_var << endl;
        
        // 变量隐藏
        int global_var = 70;  // 隐藏外层的global_var
        cout << "隐藏外层变量: " << global_var << endl;
    }
    
    cout << "回到外层，global_var = " << global_var << endl;
    
    // 声明语句
    cout << "\n=== 声明语句 ===" << endl;
    cout << "声明语句演示:" << endl;
    
    // 变量声明
    int var1;  // 声明但未初始化
    int var2 = 42;  // 声明并初始化
    int var3(33);  // 直接初始化
    int var4{44};  // 列表初始化（C++11）
    
    var1 = 11;  // 赋值
    cout << "var1 = " << var1 << ", var2 = " << var2 
         << ", var3 = " << var3 << ", var4 = " << var4 << endl;
    
    // 多变量声明
    int a1, a2 = 10, a3;
    a1 = 1;
    a3 = 3;
    cout << "多变量声明: a1 = " << a1 << ", a2 = " << a2 << ", a3 = " << a3 << endl;
    
    // 常量声明
    const int MAX_SIZE = 100;
    const double PI = 3.14159;
    cout << "常量: MAX_SIZE = " << MAX_SIZE << ", PI = " << PI << endl;
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 变量交换
    cout << "1. 变量交换:" << endl;
    int num1 = 10, num2 = 20;
    cout << "交换前: num1 = " << num1 << ", num2 = " << num2 << endl;
    
    // 使用第三个变量交换
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    cout << "交换后: num1 = " << num1 << ", num2 = " << num2 << endl;
    
    // 不使用第三个变量交换（数值方法）
    cout << "再次交换（不使用第三个变量）:" << endl;
    num1 = num1 + num2;
    num2 = num1 - num2;
    num1 = num1 - num2;
    cout << "交换后: num1 = " << num1 << ", num2 = " << num2 << endl;
    
    // 2. 累加器模式
    cout << "\n2. 累加器模式:" << endl;
    vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int sum = 0;
    
    cout << "数组: ";
    for (int val : values) {
        cout << val << " ";
        sum += val;  // 累加语句
    }
    cout << "\n总和: " << sum << endl;
    
    // 3. 计数器模式
    cout << "\n3. 计数器模式:" << endl;
    string sentence = "Hello World! How are you?";
    int vowel_count = 0;
    
    cout << "句子: \"" << sentence << "\"" << endl;
    for (char c : sentence) {
        char lower_c = tolower(c);
        if (lower_c == 'a' || lower_c == 'e' || lower_c == 'i' || 
            lower_c == 'o' || lower_c == 'u') {
            vowel_count++;  // 计数语句
        }
    }
    cout << "元音字母个数: " << vowel_count << endl;
    
    // 4. 状态更新
    cout << "\n4. 状态更新:" << endl;
    bool is_logged_in = false;
    int login_attempts = 0;
    const int MAX_ATTEMPTS = 3;
    
    cout << "模拟登录过程:" << endl;
    while (!is_logged_in && login_attempts < MAX_ATTEMPTS) {
        login_attempts++;  // 增加尝试次数
        cout << "登录尝试 " << login_attempts << "..." << endl;
        
        // 模拟登录成功（第3次尝试）
        if (login_attempts == 3) {
            is_logged_in = true;  // 状态更新语句
            cout << "登录成功！" << endl;
        } else {
            cout << "登录失败，请重试" << endl;
        }
    }
    
    // 5. 数据处理链
    cout << "\n5. 数据处理链:" << endl;
    vector<double> raw_data = {1.2, 3.4, 5.6, 7.8, 9.0};
    vector<double> processed_data;
    
    cout << "原始数据: ";
    for (double val : raw_data) {
        cout << val << " ";
    }
    cout << endl;
    
    // 数据处理：平方并加1
    for (double val : raw_data) {
        double processed = val * val + 1;  // 处理语句
        processed_data.push_back(processed);  // 存储语句
    }
    
    cout << "处理后数据: ";
    for (double val : processed_data) {
        cout << val << " ";
    }
    cout << endl;
    
    // 6. 条件设置
    cout << "\n6. 条件设置:" << endl;
    int score = 85;
    string grade;
    bool passed;
    
    cout << "分数: " << score << endl;
    
    // 条件设置语句
    if (score >= 90) {
        grade = "A";
        passed = true;
    } else if (score >= 80) {
        grade = "B";
        passed = true;
    } else if (score >= 70) {
        grade = "C";
        passed = true;
    } else if (score >= 60) {
        grade = "D";
        passed = true;
    } else {
        grade = "F";
        passed = false;
    }
    
    cout << "等级: " << grade << ", 是否通过: " << (passed ? "是" : "否") << endl;
    
    // 语句最佳实践
    cout << "\n=== 语句最佳实践 ===" << endl;
    cout << "1. 每个语句应该做一件事情" << endl;
    cout << "2. 使用适当的变量名，提高代码可读性" << endl;
    cout << "3. 避免过于复杂的表达式语句" << endl;
    cout << "4. 合理使用空语句，但要谨慎" << endl;
    cout << "5. 使用块语句控制变量作用域" << endl;
    cout << "6. 初始化变量，避免使用未初始化的变量" << endl;
    cout << "7. 使用const声明不会改变的变量" << endl;
    cout << "8. 合理使用复合赋值运算符（+=, -=等）" << endl;
    
    print_separator("简单语句示例完成");
    
    return 0;
} 