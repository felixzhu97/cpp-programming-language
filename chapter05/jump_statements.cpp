#include "common.h"

// 演示return语句的函数
int factorial(int n) {
    if (n <= 1) {
        return 1;  // 基础情况，直接返回
    }
    return n * factorial(n - 1);  // 递归调用
}

// 演示多个返回点的函数
string getGrade(int score) {
    if (score >= 90) {
        return "A";  // 早期返回
    }
    if (score >= 80) {
        return "B";
    }
    if (score >= 70) {
        return "C";
    }
    if (score >= 60) {
        return "D";
    }
    return "F";  // 默认返回
}

// 演示void函数的return
void printNumberInfo(int num) {
    if (num < 0) {
        cout << "负数，不处理" << endl;
        return;  // 提前返回，不执行后续代码
    }
    
    cout << "数字: " << num << endl;
    cout << "平方: " << num * num << endl;
    cout << "立方: " << num * num * num << endl;
}

int main() {
    print_separator("跳转语句示例");
    
    // break语句
    cout << "=== break语句 ===" << endl;
    
    // 在for循环中使用break
    cout << "1. 在for循环中使用break:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i == 6) {
            cout << "遇到6，跳出循环" << endl;
            break;
        }
        cout << i << " ";
    }
    cout << "\n循环结束" << endl;
    
    // 在while循环中使用break
    cout << "\n2. 在while循环中使用break:" << endl;
    int count = 0;
    while (true) {  // 无限循环
        count++;
        cout << "计数: " << count << endl;
        if (count >= 5) {
            cout << "达到5次，退出循环" << endl;
            break;
        }
    }
    
    // 在嵌套循环中使用break
    cout << "\n3. 在嵌套循环中使用break:" << endl;
    cout << "寻找第一个乘积大于20的组合:" << endl;
    bool found = false;
    for (int i = 1; i <= 5 && !found; i++) {
        for (int j = 1; j <= 5; j++) {
            int product = i * j;
            cout << i << "×" << j << "=" << product << " ";
            if (product > 20) {
                cout << "(找到了！)" << endl;
                found = true;
                break;  // 只跳出内层循环
            }
        }
        cout << endl;
    }
    
    // 在switch语句中使用break
    cout << "\n4. 在switch语句中使用break:" << endl;
    int choice = 2;
    cout << "菜单选择: " << choice << endl;
    switch (choice) {
        case 1:
            cout << "选择了选项1" << endl;
            break;
        case 2:
            cout << "选择了选项2" << endl;
            break;  // 防止穿透到下一个case
        case 3:
            cout << "选择了选项3" << endl;
            break;
        default:
            cout << "无效选择" << endl;
            break;
    }
    
    // continue语句
    cout << "\n=== continue语句 ===" << endl;
    
    // 在for循环中使用continue
    cout << "1. 在for循环中使用continue - 跳过偶数:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 跳过当前迭代，继续下一次迭代
        }
        cout << i << " ";
    }
    cout << endl;
    
    // 在while循环中使用continue
    cout << "\n2. 在while循环中使用continue - 处理数组:" << endl;
    vector<int> numbers = {1, -2, 3, -4, 5, -6, 7};
    int index = 0;
    cout << "原数组: ";
    for (auto num : numbers) {
        cout << num << " ";
    }
    cout << "\n正数: ";
    
    while (index < numbers.size()) {
        if (numbers[index] < 0) {
            index++;
            continue;  // 跳过负数
        }
        cout << numbers[index] << " ";
        index++;
    }
    cout << endl;
    
    // 嵌套循环中的continue
    cout << "\n3. 嵌套循环中的continue - 跳过对角线:" << endl;
    cout << "3×3矩阵，跳过对角线元素:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                cout << "X ";
                continue;  // 跳过对角线位置
            }
            cout << "O ";
        }
        cout << endl;
    }
    
    // return语句
    cout << "\n=== return语句 ===" << endl;
    
    // 函数中的return
    cout << "1. 函数中的return - 计算阶乘:" << endl;
    for (int n = 1; n <= 6; n++) {
        cout << n << "! = " << factorial(n) << endl;
    }
    
    // 多个返回点
    cout << "\n2. 多个返回点 - 成绩评定:" << endl;
    vector<int> scores = {95, 87, 76, 65, 54};
    for (int score : scores) {
        cout << "分数 " << score << ": " << getGrade(score) << endl;
    }
    
    // void函数的早期返回
    cout << "\n3. void函数的早期返回:" << endl;
    vector<int> test_nums = {-5, 0, 3, 7};
    for (int num : test_nums) {
        printNumberInfo(num);
        cout << "---" << endl;
    }
    
    // goto语句 (不推荐使用)
    cout << "\n=== goto语句 (不推荐使用) ===" << endl;
    cout << "1. goto的基本用法:" << endl;
    int attempts = 0;
    
    retry:  // 标签
    attempts++;
    cout << "尝试第" << attempts << "次" << endl;
    
    if (attempts < 3) {
        goto retry;  // 跳转到retry标签
    }
    cout << "完成3次尝试" << endl;
    
    // goto用于跳出嵌套循环 (不推荐)
    cout << "\n2. 使用goto跳出嵌套循环 (不推荐):" << endl;
    cout << "查找第一个乘积等于12的组合:" << endl;
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            cout << i << "×" << j << "=" << i*j << " ";
            if (i * j == 12) {
                cout << "(找到了！)";
                goto found_product;  // 跳出两层循环
            }
        }
        cout << endl;
    }
    
    found_product:
    cout << "\n查找完成" << endl;
    
    // 更好的替代方案
    cout << "\n3. 更好的替代方案 - 使用函数:" << endl;
    
    auto find_product = [](int target) -> pair<int, int> {
        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <= 6; j++) {
                if (i * j == target) {
                    return make_pair(i, j);  // 使用return代替goto
                }
            }
        }
        return make_pair(-1, -1);  // 未找到
    };
    
    auto result = find_product(12);
    if (result.first != -1) {
        cout << "找到组合: " << result.first << " × " << result.second << " = 12" << endl;
    } else {
        cout << "未找到组合" << endl;
    }
    
    // 跳转语句的实际应用
    cout << "\n=== 跳转语句的实际应用 ===" << endl;
    
    // 1. 输入验证
    cout << "1. 输入验证模拟:" << endl;
    vector<string> inputs = {"abc", "123", "45", "xyz", "67"};
    
    for (const string& input : inputs) {
        cout << "输入: \"" << input << "\" -> ";
        
        // 检查是否为纯数字
        bool is_number = true;
        for (char c : input) {
            if (!isdigit(c)) {
                is_number = false;
                break;  // 发现非数字字符，停止检查
            }
        }
        
        if (!is_number) {
            cout << "无效输入，跳过" << endl;
            continue;  // 跳过当前输入
        }
        
        int number = stoi(input);
        cout << "有效数字: " << number << endl;
    }
    
    // 2. 数据处理
    cout << "\n2. 数据处理 - 统计有效数据:" << endl;
    vector<double> data = {1.5, -2.3, 0.0, 4.7, NAN, 3.2, INFINITY, -1.8};
    double sum = 0.0;
    int valid_count = 0;
    
    cout << "处理数据: ";
    for (auto value : data) {
        cout << value << " ";
        
        // 跳过无效数据
        if (isnan(value) || isinf(value)) {
            continue;
        }
        
        sum += value;
        valid_count++;
    }
    
    cout << "\n有效数据个数: " << valid_count << endl;
    cout << "平均值: " << (valid_count > 0 ? sum / valid_count : 0) << endl;
    
    // 3. 菜单系统
    cout << "\n3. 菜单系统模拟:" << endl;
    vector<int> menu_choices = {1, 3, 5, 2, 4};  // 模拟用户选择
    
    for (int choice : menu_choices) {
        cout << "\n用户选择: " << choice << endl;
        
        switch (choice) {
            case 1:
                cout << "执行操作1: 创建文件" << endl;
                break;
            case 2:
                cout << "执行操作2: 读取文件" << endl;
                break;
            case 3:
                cout << "执行操作3: 删除文件" << endl;
                break;
            case 4:
                cout << "执行操作4: 退出程序" << endl;
                cout << "程序结束" << endl;
                goto menu_end;  // 跳出菜单循环
            default:
                cout << "无效选择，请重试" << endl;
                continue;
        }
    }
    
    menu_end:
    cout << "菜单系统结束" << endl;
    
    // 4. 错误处理
    cout << "\n4. 错误处理示例:" << endl;
    
    auto safe_divide = [](double a, double b) -> double {
        if (b == 0.0) {
            cout << "错误：除数为零！" << endl;
            return NAN;  // 返回NaN表示错误
        }
        return a / b;
    };
    
    vector<pair<double, double>> division_tests = {
        {10.0, 2.0}, {15.0, 0.0}, {8.0, 4.0}, {7.0, 0.0}
    };
    
    for (auto test : division_tests) {
        double result = safe_divide(test.first, test.second);
        if (isnan(result)) {
            continue;  // 跳过错误结果
        }
        cout << test.first << " ÷ " << test.second << " = " << result << endl;
    }
    
    // 5. 搜索算法
    cout << "\n5. 搜索算法 - 线性搜索:" << endl;
    vector<int> search_array = {3, 7, 1, 9, 4, 6, 8, 2, 5};
    int target = 6;
    
    cout << "数组: ";
    for (auto num : search_array) {
        cout << num << " ";
    }
    cout << "\n搜索目标: " << target << endl;
    
    int found_index = -1;
    for (int i = 0; i < search_array.size(); i++) {
        if (search_array[i] == target) {
            found_index = i;
            break;  // 找到目标，停止搜索
        }
    }
    
    if (found_index != -1) {
        cout << "找到目标，位置: " << found_index << endl;
    } else {
        cout << "未找到目标" << endl;
    }
    
    // 跳转语句的最佳实践
    cout << "\n=== 跳转语句的最佳实践 ===" << endl;
    cout << "1. break:" << endl;
    cout << "   - 用于提前退出循环" << endl;
    cout << "   - 在switch中防止穿透" << endl;
    cout << "   - 处理异常或错误条件" << endl;
    
    cout << "\n2. continue:" << endl;
    cout << "   - 跳过当前迭代的剩余代码" << endl;
    cout << "   - 处理特殊值或过滤数据" << endl;
    cout << "   - 简化循环内的条件逻辑" << endl;
    
    cout << "\n3. return:" << endl;
    cout << "   - 从函数中返回值或控制" << endl;
    cout << "   - 实现早期返回优化代码结构" << endl;
    cout << "   - 处理错误条件或边界情况" << endl;
    
    cout << "\n4. goto (避免使用):" << endl;
    cout << "   - 破坏程序结构，难以理解和维护" << endl;
    cout << "   - 可以用函数、循环控制语句替代" << endl;
    cout << "   - 仅在极特殊情况下考虑使用" << endl;
    
    cout << "\n5. 替代goto的方法:" << endl;
    cout << "   - 使用函数封装复杂逻辑" << endl;
    cout << "   - 使用标志变量控制循环" << endl;
    cout << "   - 使用异常处理机制" << endl;
    cout << "   - 重新组织代码结构" << endl;
    
    print_separator("跳转语句示例完成");
    
    return 0;
} 