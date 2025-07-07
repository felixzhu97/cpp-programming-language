#include "common.h"

int main() {
    print_separator("输入输出示例");
    
    // 基本输出
    cout << "欢迎来到C++世界！" << endl;
    cout << "让我们学习基本的输入输出操作。" << endl;
    
    // 获取用户输入
    string name;
    cout << "\n请输入您的姓名: ";
    cin >> name;
    cout << "您好，" << name << "！" << endl;
    
    // 获取数字输入
    int age;
    cout << "请输入您的年龄: ";
    cin >> age;
    cout << "您今年" << age << "岁了。" << endl;
    
    // 计算明年的年龄
    cout << "明年您将" << age + 1 << "岁。" << endl;
    
    // 使用getline获取包含空格的字符串
    cin.ignore(); // 忽略前面留下的换行符
    string fullName;
    cout << "请输入您的全名（可包含空格）: ";
    getline(cin, fullName);
    cout << "您的全名是：" << fullName << endl;
    
    print_separator("输入输出演示完成");
    
    return 0;
} 