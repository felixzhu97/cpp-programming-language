#include "common.h"

int main() {
    print_separator("条件运算符示例");
    
    // 基本条件运算符
    cout << "=== 基本条件运算符 ===" << endl;
    int a = 10, b = 20;
    cout << "a = " << a << ", b = " << b << endl;
    
    // 基本用法: condition ? value_if_true : value_if_false
    int max_val = (a > b) ? a : b;
    cout << "较大值: " << max_val << endl;
    
    int min_val = (a < b) ? a : b;
    cout << "较小值: " << min_val << endl;
    
    // 字符串条件运算符
    cout << "\n=== 字符串条件运算符 ===" << endl;
    int score = 85;
    string result = (score >= 60) ? "及格" : "不及格";
    cout << "分数 " << score << ": " << result << endl;
    
    // 嵌套条件运算符
    cout << "\n=== 嵌套条件运算符 ===" << endl;
    string grade = (score >= 90) ? "优秀" : 
                   (score >= 80) ? "良好" : 
                   (score >= 70) ? "中等" : 
                   (score >= 60) ? "及格" : "不及格";
    cout << "分数 " << score << " 的等级: " << grade << endl;
    
    // 不同数据类型
    cout << "\n=== 不同数据类型的条件运算符 ===" << endl;
    double temperature = 25.5;
    string weather = (temperature > 30) ? "炎热" : 
                     (temperature > 20) ? "温暖" : 
                     (temperature > 10) ? "凉爽" : "寒冷";
    cout << "温度 " << temperature << "°C: " << weather << endl;
    
    // 布尔条件运算符
    bool is_weekend = true;
    string activity = is_weekend ? "休息" : "工作";
    cout << "今天是" << (is_weekend ? "周末" : "工作日") << ": " << activity << endl;
    
    // 数值计算中的条件运算符
    cout << "\n=== 数值计算中的条件运算符 ===" << endl;
    int x = 5, y = -3;
    int abs_x = (x >= 0) ? x : -x;
    int abs_y = (y >= 0) ? y : -y;
    cout << "x = " << x << ", |x| = " << abs_x << endl;
    cout << "y = " << y << ", |y| = " << abs_y << endl;
    
    // 符号判断
    char sign_x = (x > 0) ? '+' : (x < 0) ? '-' : '0';
    char sign_y = (y > 0) ? '+' : (y < 0) ? '-' : '0';
    cout << "x的符号: " << sign_x << ", y的符号: " << sign_y << endl;
    
    // 数组和指针中的条件运算符
    cout << "\n=== 数组和指针中的条件运算符 ===" << endl;
    int arr[] = {1, 2, 3, 4, 5};
    int index = 2;
    
    // 安全的数组访问
    int safe_value = (index >= 0 && index < 5) ? arr[index] : 0;
    cout << "安全访问arr[" << index << "] = " << safe_value << endl;
    
    // 指针条件运算符
    int* ptr = (index < 5) ? &arr[index] : nullptr;
    cout << "指针值: " << (ptr ? *ptr : 0) << endl;
    
    // 函数返回值的条件运算符
    cout << "\n=== 函数返回值的条件运算符 ===" << endl;
    auto get_message = [](bool success) {
        return success ? "操作成功" : "操作失败";
    };
    
    cout << "操作结果: " << get_message(true) << endl;
    cout << "操作结果: " << get_message(false) << endl;
    
    // 类型转换中的条件运算符
    cout << "\n=== 类型转换中的条件运算符 ===" << endl;
    int int_val = 42;
    double double_val = 3.14;
    
    // 注意：条件运算符的两个分支必须是相同类型或可转换类型
    double result_val = (int_val > 40) ? int_val : double_val;
    cout << "结果: " << result_val << " (类型为double)" << endl;
    
    // 复杂表达式中的条件运算符
    cout << "\n=== 复杂表达式中的条件运算符 ===" << endl;
    int num1 = 10, num2 = 20, num3 = 15;
    
    // 找出三个数中的最大值
    int max_of_three = (num1 > num2) ? 
                       ((num1 > num3) ? num1 : num3) : 
                       ((num2 > num3) ? num2 : num3);
    cout << "三个数 " << num1 << ", " << num2 << ", " << num3 << " 中的最大值: " << max_of_three << endl;
    
    // 条件运算符 vs if-else语句
    cout << "\n=== 条件运算符 vs if-else语句 ===" << endl;
    
    // 使用条件运算符
    cout << "使用条件运算符:" << endl;
    string status1 = (score >= 60) ? "通过" : "未通过";
    cout << "考试结果: " << status1 << endl;
    
    // 使用if-else语句
    cout << "使用if-else语句:" << endl;
    string status2;
    if (score >= 60) {
        status2 = "通过";
    } else {
        status2 = "未通过";
    }
    cout << "考试结果: " << status2 << endl;
    
    // 条件运算符的优势：简洁性
    cout << "\n=== 条件运算符的优势 ===" << endl;
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    cout << "数组元素的奇偶性:" << endl;
    for (int num : numbers) {
        cout << num << " 是 " << (num % 2 == 0 ? "偶数" : "奇数") << endl;
    }
    
    // 条件运算符与逻辑运算符结合
    cout << "\n=== 条件运算符与逻辑运算符结合 ===" << endl;
    int age = 25;
    bool has_license = true;
    
    string can_drive = (age >= 18 && has_license) ? "可以开车" : "不能开车";
    cout << "年龄: " << age << ", 有驾照: " << (has_license ? "是" : "否") << endl;
    cout << "结论: " << can_drive << endl;
    
    // 范围检查
    int test_score = 95;
    string performance = (test_score >= 90 && test_score <= 100) ? "优秀" : 
                        (test_score >= 80 && test_score < 90) ? "良好" : 
                        (test_score >= 70 && test_score < 80) ? "一般" : 
                        (test_score >= 60 && test_score < 70) ? "及格" : "不及格";
    cout << "测试分数: " << test_score << ", 表现: " << performance << endl;
    
    // 条件运算符的陷阱
    cout << "\n=== 条件运算符的陷阱 ===" << endl;
    
    // 1. 类型不匹配的问题
    cout << "1. 类型不匹配的问题:" << endl;
    int int_result = 10;
    double double_result = 3.14;
    
    // 结果将是double类型
    auto mixed_result = (int_result > 5) ? int_result : double_result;
    cout << "混合类型结果: " << mixed_result << " (类型大小: " << sizeof(mixed_result) << " 字节)" << endl;
    
    // 2. 优先级问题
    cout << "2. 优先级问题:" << endl;
    bool condition = true;
    int val1 = 10, val2 = 20;
    
    // 赋值运算符优先级低于条件运算符
    int assignment_result = condition ? val1 : val2;
    cout << "assignment_result = " << assignment_result << endl;
    
    // 3. 副作用问题
    cout << "3. 副作用问题:" << endl;
    int counter = 0;
    int side_effect_result = (counter++ > 0) ? counter : counter + 10;
    cout << "side_effect_result = " << side_effect_result << ", counter = " << counter << endl;
    
    // 实际应用场景
    cout << "\n=== 实际应用场景 ===" << endl;
    
    // 1. 参数验证
    cout << "1. 参数验证:" << endl;
    auto safe_divide = [](double a, double b) {
        return (b != 0) ? a / b : 0.0;
    };
    cout << "10 / 2 = " << safe_divide(10, 2) << endl;
    cout << "10 / 0 = " << safe_divide(10, 0) << " (安全除法)" << endl;
    
    // 2. 默认值设置
    cout << "2. 默认值设置:" << endl;
    string user_name = "";
    string display_name = user_name.empty() ? "匿名用户" : user_name;
    cout << "显示名称: " << display_name << endl;
    
    // 3. 状态标志
    cout << "3. 状态标志:" << endl;
    bool is_online = false;
    string status_icon = is_online ? "🟢" : "🔴";
    cout << "用户状态: " << status_icon << " " << (is_online ? "在线" : "离线") << endl;
    
    // 4. 数据格式化
    cout << "4. 数据格式化:" << endl;
    int file_size = 1024 * 1024 + 512;
    string size_format = (file_size >= 1024 * 1024) ? 
                         to_string(file_size / (1024 * 1024)) + " MB" :
                         (file_size >= 1024) ? 
                         to_string(file_size / 1024) + " KB" :
                         to_string(file_size) + " 字节";
    cout << "文件大小: " << size_format << endl;
    
    // 5. 配置选择
    cout << "5. 配置选择:" << endl;
    bool debug_mode = true;
    int log_level = debug_mode ? 0 : 2;  // 0=详细, 1=正常, 2=仅错误
    cout << "日志级别: " << (log_level == 0 ? "详细" : log_level == 1 ? "正常" : "仅错误") << endl;
    
    print_separator("条件运算符示例完成");
    
    return 0;
} 