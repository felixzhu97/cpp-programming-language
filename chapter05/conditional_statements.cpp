#include "common.h"

int main() {
    print_separator("条件语句示例");
    
    // 基本if语句
    cout << "=== 基本if语句 ===" << endl;
    int score = 85;
    cout << "学生分数: " << score << endl;
    
    if (score >= 60) {
        cout << "恭喜，您通过了考试！" << endl;
    }
    
    // if-else语句
    cout << "\n=== if-else语句 ===" << endl;
    int age = 17;
    cout << "年龄: " << age << endl;
    
    if (age >= 18) {
        cout << "您已成年，可以投票" << endl;
    } else {
        cout << "您还未成年，不能投票" << endl;
    }
    
    // if-else if-else语句
    cout << "\n=== if-else if-else语句 ===" << endl;
    int temperature = 25;
    cout << "温度: " << temperature << "°C" << endl;
    
    if (temperature < 0) {
        cout << "天气寒冷，注意保暖" << endl;
    } else if (temperature < 20) {
        cout << "天气凉爽，适合户外活动" << endl;
    } else if (temperature < 30) {
        cout << "天气温暖，很舒适" << endl;
    } else {
        cout << "天气炎热，注意防暑" << endl;
    }
    
    // 嵌套if语句
    cout << "\n=== 嵌套if语句 ===" << endl;
    int user_age = 20;
    bool has_license = true;
    bool has_car = false;
    
    cout << "用户年龄: " << user_age << ", 有驾照: " << (has_license ? "是" : "否") 
         << ", 有车: " << (has_car ? "是" : "否") << endl;
    
    if (user_age >= 18) {
        cout << "您已成年" << endl;
        if (has_license) {
            cout << "您有驾照" << endl;
            if (has_car) {
                cout << "您可以开自己的车" << endl;
            } else {
                cout << "您可以租车或借车" << endl;
            }
        } else {
            cout << "建议先考驾照" << endl;
        }
    } else {
        cout << "您还未成年，不能开车" << endl;
    }
    
    // 复杂条件表达式
    cout << "\n=== 复杂条件表达式 ===" << endl;
    int income = 50000;
    int experience = 3;
    bool degree = true;
    
    cout << "收入: " << income << ", 工作经验: " << experience << "年, 有学位: " << (degree ? "是" : "否") << endl;
    
    if ((income > 30000 && experience >= 2) || (degree && income > 20000)) {
        cout << "符合贷款条件" << endl;
    } else {
        cout << "不符合贷款条件" << endl;
    }
    
    // switch语句
    cout << "\n=== switch语句 ===" << endl;
    int day_of_week = 3;
    cout << "今天是星期: " << day_of_week << endl;
    
    switch (day_of_week) {
        case 1:
            cout << "星期一 - 新的一周开始" << endl;
            break;
        case 2:
            cout << "星期二 - 继续努力" << endl;
            break;
        case 3:
            cout << "星期三 - 周中时光" << endl;
            break;
        case 4:
            cout << "星期四 - 快到周末了" << endl;
            break;
        case 5:
            cout << "星期五 - 感谢上帝！" << endl;
            break;
        case 6:
        case 7:
            cout << "周末 - 休息时间" << endl;
            break;
        default:
            cout << "无效的星期" << endl;
            break;
    }
    
    // switch语句的穿透特性
    cout << "\n=== switch语句的穿透特性 ===" << endl;
    char grade = 'B';
    cout << "成绩等级: " << grade << endl;
    
    switch (grade) {
        case 'A':
            cout << "优秀！" << endl;
            break;
        case 'B':
            cout << "良好！" << endl;
            // 故意不加break，演示穿透
        case 'C':
            cout << "需要继续努力" << endl;
            break;
        case 'D':
        case 'F':
            cout << "需要重修" << endl;
            break;
        default:
            cout << "无效等级" << endl;
    }
    
    // 使用switch处理枚举
    cout << "\n=== 使用switch处理枚举 ===" << endl;
    enum Color { RED, GREEN, BLUE, YELLOW };
    Color selected_color = GREEN;
    
    cout << "选择的颜色: ";
    switch (selected_color) {
        case RED:
            cout << "红色 - 热情与活力" << endl;
            break;
        case GREEN:
            cout << "绿色 - 自然与和谐" << endl;
            break;
        case BLUE:
            cout << "蓝色 - 冷静与智慧" << endl;
            break;
        case YELLOW:
            cout << "黄色 - 快乐与温暖" << endl;
            break;
    }
    
    // 现代C++的switch语句
    cout << "\n=== 现代C++的switch语句 ===" << endl;
    enum class Status { ACTIVE, INACTIVE, PENDING, SUSPENDED };
    Status current_status = Status::ACTIVE;
    
    cout << "当前状态: ";
    switch (current_status) {
        case Status::ACTIVE:
            cout << "活跃状态" << endl;
            break;
        case Status::INACTIVE:
            cout << "非活跃状态" << endl;
            break;
        case Status::PENDING:
            cout << "等待状态" << endl;
            break;
        case Status::SUSPENDED:
            cout << "暂停状态" << endl;
            break;
    }
    
    // 条件运算符与if语句的对比
    cout << "\n=== 条件运算符与if语句的对比 ===" << endl;
    int a = 10, b = 20;
    cout << "a = " << a << ", b = " << b << endl;
    
    // 使用if语句
    string result_if;
    if (a > b) {
        result_if = "a更大";
    } else {
        result_if = "b更大或相等";
    }
    cout << "if语句结果: " << result_if << endl;
    
    // 使用条件运算符
    string result_ternary = (a > b) ? "a更大" : "b更大或相等";
    cout << "条件运算符结果: " << result_ternary << endl;
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 用户登录验证
    cout << "1. 用户登录验证:" << endl;
    string username = "admin";
    string password = "123456";
    
    if (username == "admin" && password == "123456") {
        cout << "登录成功！欢迎管理员" << endl;
    } else if (username == "user" && password == "password") {
        cout << "登录成功！欢迎用户" << endl;
    } else {
        cout << "登录失败！用户名或密码错误" << endl;
    }
    
    // 2. 计算器操作
    cout << "\n2. 计算器操作:" << endl;
    double num1 = 10.5, num2 = 3.2;
    char operation = '+';
    
    cout << num1 << " " << operation << " " << num2 << " = ";
    switch (operation) {
        case '+':
            cout << num1 + num2 << endl;
            break;
        case '-':
            cout << num1 - num2 << endl;
            break;
        case '*':
            cout << num1 * num2 << endl;
            break;
        case '/':
            if (num2 != 0) {
                cout << num1 / num2 << endl;
            } else {
                cout << "错误：除数不能为零" << endl;
            }
            break;
        default:
            cout << "不支持的操作" << endl;
    }
    
    // 3. 成绩等级判定
    cout << "\n3. 成绩等级判定:" << endl;
    vector<int> scores = {95, 87, 76, 65, 54, 43};
    
    for (int score : scores) {
        cout << "分数 " << score << ": ";
        if (score >= 90) {
            cout << "A (优秀)" << endl;
        } else if (score >= 80) {
            cout << "B (良好)" << endl;
        } else if (score >= 70) {
            cout << "C (中等)" << endl;
        } else if (score >= 60) {
            cout << "D (及格)" << endl;
        } else {
            cout << "F (不及格)" << endl;
        }
    }
    
    // 4. 交通信号灯控制
    cout << "\n4. 交通信号灯控制:" << endl;
    enum TrafficLight { RED_LIGHT, YELLOW_LIGHT, GREEN_LIGHT };
    TrafficLight current_light = RED_LIGHT;
    
    cout << "当前信号灯: ";
    switch (current_light) {
        case RED_LIGHT:
            cout << "红灯 - 停止" << endl;
            break;
        case YELLOW_LIGHT:
            cout << "黄灯 - 准备" << endl;
            break;
        case GREEN_LIGHT:
            cout << "绿灯 - 通行" << endl;
            break;
    }
    
    // 5. 文件类型判断
    cout << "\n5. 文件类型判断:" << endl;
    string filename = "document.pdf";
    string extension = filename.substr(filename.find_last_of('.') + 1);
    
    cout << "文件: " << filename << ", 扩展名: " << extension << endl;
    
    if (extension == "txt" || extension == "doc" || extension == "docx") {
        cout << "文档文件" << endl;
    } else if (extension == "jpg" || extension == "png" || extension == "gif") {
        cout << "图片文件" << endl;
    } else if (extension == "mp3" || extension == "wav" || extension == "flac") {
        cout << "音频文件" << endl;
    } else if (extension == "mp4" || extension == "avi" || extension == "mkv") {
        cout << "视频文件" << endl;
    } else {
        cout << "未知文件类型" << endl;
    }
    
    // 6. 年龄组分类
    cout << "\n6. 年龄组分类:" << endl;
    vector<int> ages = {5, 12, 18, 25, 35, 45, 65, 75};
    
    for (int age : ages) {
        cout << "年龄 " << age << ": ";
        if (age < 13) {
            cout << "儿童" << endl;
        } else if (age < 18) {
            cout << "青少年" << endl;
        } else if (age < 30) {
            cout << "青年" << endl;
        } else if (age < 50) {
            cout << "中年" << endl;
        } else if (age < 70) {
            cout << "中老年" << endl;
        } else {
            cout << "老年" << endl;
        }
    }
    
    // 条件语句的最佳实践
    cout << "\n=== 条件语句的最佳实践 ===" << endl;
    cout << "1. 使用括号明确条件表达式的优先级" << endl;
    cout << "2. 避免过深的嵌套，考虑使用早期返回" << endl;
    cout << "3. 对于多个相关条件，优先使用else if而不是独立的if" << endl;
    cout << "4. switch语句适合处理离散值的多重选择" << endl;
    cout << "5. 总是在switch的case中使用break，除非有意穿透" << endl;
    cout << "6. 为switch语句添加default分支处理未预期的情况" << endl;
    cout << "7. 复杂条件可以提取为函数，提高代码可读性" << endl;
    
    print_separator("条件语句示例完成");
    
    return 0;
} 