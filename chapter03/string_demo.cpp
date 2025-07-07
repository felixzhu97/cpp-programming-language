#include "common.h"
#include <cctype>

int main() {
    print_separator("字符串操作示例");
    
    // 字符串创建和初始化
    cout << "=== 字符串创建和初始化 ===" << endl;
    string str1;                        // 空字符串
    string str2 = "Hello";              // 直接初始化
    string str3("World");               // 直接初始化
    string str4(5, 'A');                // 5个'A'
    string str5 = str2;                 // 拷贝初始化
    
    cout << "空字符串: '" << str1 << "'" << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl;
    cout << "str5: " << str5 << endl;
    
    // 字符串大小和容量
    cout << "\n=== 字符串大小和容量 ===" << endl;
    string text = "Hello, C++!";
    cout << "字符串: " << text << endl;
    cout << "size(): " << text.size() << endl;
    cout << "length(): " << text.length() << endl;
    cout << "empty(): " << std::boolalpha << text.empty() << endl;
    cout << "capacity(): " << text.capacity() << endl;
    
    // 字符串拼接
    cout << "\n=== 字符串拼接 ===" << endl;
    string first = "Hello";
    string second = "World";
    string combined = first + ", " + second + "!";
    cout << "拼接结果: " << combined << endl;
    
    // 使用+=运算符
    string greeting = "Hello";
    greeting += ", ";
    greeting += "C++";
    greeting += "!";
    cout << "使用+=: " << greeting << endl;
    
    // 字符串比较
    cout << "\n=== 字符串比较 ===" << endl;
    string s1 = "apple";
    string s2 = "banana";
    string s3 = "apple";
    
    cout << "s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << endl;
    cout << "s1 == s2: " << (s1 == s2) << endl;
    cout << "s1 == s3: " << (s1 == s3) << endl;
    cout << "s1 < s2: " << (s1 < s2) << endl;
    cout << "s1 > s2: " << (s1 > s2) << endl;
    
    // 字符串访问
    cout << "\n=== 字符串访问 ===" << endl;
    string sample = "Programming";
    cout << "字符串: " << sample << endl;
    cout << "第一个字符: " << sample[0] << endl;
    cout << "最后一个字符: " << sample[sample.size() - 1] << endl;
    cout << "使用at(): " << sample.at(3) << endl;
    
    // 范围for循环遍历
    cout << "逐字符输出: ";
    for (char c : sample) {
        cout << c << " ";
    }
    cout << endl;
    
    // 字符串修改
    cout << "\n=== 字符串修改 ===" << endl;
    string modifiable = "hello";
    cout << "原字符串: " << modifiable << endl;
    
    modifiable[0] = 'H';  // 修改第一个字符
    cout << "修改首字母: " << modifiable << endl;
    
    // 字符串查找
    cout << "\n=== 字符串查找 ===" << endl;
    string sentence = "The quick brown fox jumps over the lazy dog";
    cout << "句子: " << sentence << endl;
    
    auto pos = sentence.find("fox");
    if (pos != string::npos) {
        cout << "找到'fox'在位置: " << pos << endl;
    }
    
    pos = sentence.find("cat");
    if (pos == string::npos) {
        cout << "没有找到'cat'" << endl;
    }
    
    // 字符串替换
    cout << "\n=== 字符串替换 ===" << endl;
    string original = "Hello, World!";
    cout << "原字符串: " << original << endl;
    
    string replaced = original;
    size_t pos_replace = replaced.find("World");
    if (pos_replace != string::npos) {
        replaced.replace(pos_replace, 5, "C++");
    }
    cout << "替换后: " << replaced << endl;
    
    // 子字符串
    cout << "\n=== 子字符串 ===" << endl;
    string fullString = "Hello, World!";
    string sub1 = fullString.substr(0, 5);      // "Hello"
    string sub2 = fullString.substr(7);         // "World!"
    string sub3 = fullString.substr(7, 5);      // "World"
    
    cout << "原字符串: " << fullString << endl;
    cout << "substr(0, 5): " << sub1 << endl;
    cout << "substr(7): " << sub2 << endl;
    cout << "substr(7, 5): " << sub3 << endl;
    
    // 字符串插入和删除
    cout << "\n=== 字符串插入和删除 ===" << endl;
    string editable = "Hello World";
    cout << "原字符串: " << editable << endl;
    
    editable.insert(5, ", Beautiful");
    cout << "插入后: " << editable << endl;
    
    editable.erase(5, 11);  // 删除", Beautiful"
    cout << "删除后: " << editable << endl;
    
    // 字符处理函数
    cout << "\n=== 字符处理函数 ===" << endl;
    string mixed = "Hello123World";
    cout << "原字符串: " << mixed << endl;
    
    cout << "字符分析: ";
    for (char c : mixed) {
        if (isalpha(c)) {
            cout << c << "(字母) ";
        } else if (isdigit(c)) {
            cout << c << "(数字) ";
        } else {
            cout << c << "(其他) ";
        }
    }
    cout << endl;
    
    // 大小写转换
    cout << "\n=== 大小写转换 ===" << endl;
    string caseDemo = "Hello World";
    cout << "原字符串: " << caseDemo << endl;
    
    string upper = caseDemo;
    string lower = caseDemo;
    
    for (char& c : upper) {
        c = toupper(c);
    }
    
    for (char& c : lower) {
        c = tolower(c);
    }
    
    cout << "大写: " << upper << endl;
    cout << "小写: " << lower << endl;
    
    // 字符串转数字
    cout << "\n=== 字符串转数字 ===" << endl;
    string numStr1 = "123";
    string numStr2 = "3.14";
    
    int intVal = stoi(numStr1);
    double doubleVal = stod(numStr2);
    
    cout << "字符串'" << numStr1 << "'转整数: " << intVal << endl;
    cout << "字符串'" << numStr2 << "'转浮点数: " << doubleVal << endl;
    
    // 数字转字符串
    cout << "\n=== 数字转字符串 ===" << endl;
    int number = 42;
    double pi = 3.14159;
    
    string intToStr = to_string(number);
    string doubleToStr = to_string(pi);
    
    cout << "整数" << number << "转字符串: '" << intToStr << "'" << endl;
    cout << "浮点数" << pi << "转字符串: '" << doubleToStr << "'" << endl;
    
    print_separator("字符串操作示例完成");
    
    return 0;
} 