#include "common.h"

int main() {
    print_separator("简单计算器");
    
    double num1, num2;
    char operation;
    
    cout << "请输入第一个数字: ";
    cin >> num1;
    
    cout << "请输入运算符 (+, -, *, /): ";
    cin >> operation;
    
    cout << "请输入第二个数字: ";
    cin >> num2;
    
    double result = 0;
    bool validOperation = true;
    
    switch (operation) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                cout << "错误：除数不能为零！" << endl;
                validOperation = false;
            }
            break;
        default:
            cout << "错误：无效的运算符！" << endl;
            validOperation = false;
    }
    
    if (validOperation) {
        cout << "\n计算结果：" << endl;
        cout << num1 << " " << operation << " " << num2 << " = " << result << endl;
    }
    
    print_separator("计算器演示完成");
    
    return 0;
} 