#include "common.h"

int main() {
    print_separator("控制流示例");
    
    // if-else 语句
    cout << "=== if-else 示例 ===" << endl;
    int number = 15;
    cout << "数字: " << number << endl;
    
    if (number > 10) {
        cout << "数字大于10" << endl;
    } else if (number > 5) {
        cout << "数字大于5但小于等于10" << endl;
    } else {
        cout << "数字小于等于5" << endl;
    }
    
    // for 循环
    cout << "\n=== for 循环示例 ===" << endl;
    cout << "输出1到5的数字：";
    for (int i = 1; i <= 5; ++i) {
        cout << i << " ";
    }
    cout << endl;
    
    // while 循环
    cout << "\n=== while 循环示例 ===" << endl;
    cout << "倒数计时：";
    int countdown = 5;
    while (countdown > 0) {
        cout << countdown << " ";
        countdown--;
    }
    cout << "发射！" << endl;
    
    // do-while 循环
    cout << "\n=== do-while 循环示例 ===" << endl;
    int choice;
    do {
        cout << "请选择（1-3）: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "您选择了选项1" << endl;
                break;
            case 2:
                cout << "您选择了选项2" << endl;
                break;
            case 3:
                cout << "您选择了选项3" << endl;
                break;
            default:
                cout << "无效选择，请重试" << endl;
        }
    } while (choice < 1 || choice > 3);
    
    // 嵌套循环
    cout << "\n=== 嵌套循环示例 ===" << endl;
    cout << "九九乘法表（前5行）：" << endl;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= i; ++j) {
            cout << j << " × " << i << " = " << i * j << "  ";
        }
        cout << endl;
    }
    
    print_separator("控制流示例完成");
    
    return 0;
} 