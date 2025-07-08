/*
 * 第8章：IO库 - 字符串流
 * 展示stringstream的使用、字符串格式化和解析、数据类型转换
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

namespace string_streams_demo {

// 1. 基本字符串流操作
void demonstrateBasicStringStreams() {
    std::cout << "\n=== 基本字符串流操作演示 ===" << std::endl;
    
    // 1. ostringstream - 输出字符串流
    std::cout << "\n1. ostringstream（输出字符串流）：" << std::endl;
    std::ostringstream oss;
    oss << "Hello, ";
    oss << "StringStream! ";
    oss << "数字: " << 42 << ", ";
    oss << "浮点数: " << 3.14159;
    
    std::string result = oss.str();
    std::cout << "构建的字符串: " << result << std::endl;
    std::cout << "字符串长度: " << result.length() << std::endl;
    
    // 2. istringstream - 输入字符串流
    std::cout << "\n2. istringstream（输入字符串流）：" << std::endl;
    std::string data = "123 456.78 hello world";
    std::istringstream iss(data);
    
    int intVal;
    double doubleVal;
    std::string str1, str2;
    
    iss >> intVal >> doubleVal >> str1 >> str2;
    
    std::cout << "解析字符串 '" << data << "':" << std::endl;
    std::cout << "  整数: " << intVal << std::endl;
    std::cout << "  浮点数: " << doubleVal << std::endl;
    std::cout << "  字符串1: " << str1 << std::endl;
    std::cout << "  字符串2: " << str2 << std::endl;
    
    // 3. stringstream - 双向字符串流
    std::cout << "\n3. stringstream（双向字符串流）：" << std::endl;
    std::stringstream ss;
    
    // 写入数据
    ss << "临时存储: " << 999;
    std::cout << "写入后内容: " << ss.str() << std::endl;
    
    // 读取数据
    std::string temp;
    int number;
    ss >> temp >> number;
    std::cout << "读取到: " << temp << " " << number << std::endl;
    
    // 清空并重新使用
    ss.str("");  // 清空内容
    ss.clear();  // 清空状态标志
    ss << "新内容: " << 777;
    std::cout << "重新使用后: " << ss.str() << std::endl;
}

// 2. 字符串格式化
void demonstrateStringFormatting() {
    std::cout << "\n=== 字符串格式化演示 ===" << std::endl;
    
    // 1. 数值格式化
    std::cout << "\n1. 数值格式化：" << std::endl;
    std::ostringstream oss;
    
    double pi = 3.14159265359;
    int number = 42;
    
    // 设置精度
    oss << std::fixed << std::setprecision(2) << "PI (2位小数): " << pi << std::endl;
    oss << std::fixed << std::setprecision(6) << "PI (6位小数): " << pi << std::endl;
    
    // 设置宽度和填充
    oss << "数字 (宽度10, 右对齐): " << std::setw(10) << number << "|" << std::endl;
    oss << "数字 (宽度10, 左对齐): " << std::left << std::setw(10) << number << "|" << std::endl;
    oss << "数字 (宽度10, 填充0): " << std::right << std::setfill('0') << std::setw(10) << number << "|" << std::endl;
    
    // 进制转换
    oss << std::setfill(' ');  // 恢复默认填充
    oss << "十进制: " << std::dec << number << ", ";
    oss << "十六进制: " << std::hex << number << ", ";
    oss << "八进制: " << std::oct << number << std::endl;
    
    std::cout << oss.str();
    
    // 2. 表格格式化
    std::cout << "\n2. 表格格式化：" << std::endl;
    std::ostringstream table;
    
    // 表头
    table << std::left << std::setw(15) << "姓名" 
          << std::right << std::setw(8) << "年龄" 
          << std::right << std::setw(12) << "薪水" << std::endl;
    table << std::string(35, '-') << std::endl;
    
    // 数据行
    std::vector<std::tuple<std::string, int, double>> employees = {
        {"张三", 25, 5000.50},
        {"李四", 30, 6500.75},
        {"王五", 28, 5800.00}
    };
    
    for (const auto& emp : employees) {
        table << std::left << std::setw(15) << std::get<0>(emp)
              << std::right << std::setw(8) << std::get<1>(emp)
              << std::right << std::setw(12) << std::fixed << std::setprecision(2) 
              << std::get<2>(emp) << std::endl;
    }
    
    std::cout << table.str();
}

// 3. 字符串解析
void demonstrateStringParsing() {
    std::cout << "\n=== 字符串解析演示 ===" << std::endl;
    
    // 1. 逐词解析
    std::cout << "\n1. 逐词解析：" << std::endl;
    std::string sentence = "C++ is a powerful programming language";
    std::istringstream iss(sentence);
    std::vector<std::string> words;
    std::string word;
    
    while (iss >> word) {
        words.push_back(word);
    }
    
    std::cout << "句子: " << sentence << std::endl;
    std::cout << "解析出 " << words.size() << " 个单词：" << std::endl;
    for (size_t i = 0; i < words.size(); ++i) {
        std::cout << "  [" << i << "] " << words[i] << std::endl;
    }
    
    // 2. CSV解析
    std::cout << "\n2. CSV格式解析：" << std::endl;
    std::string csvLine = "张三,25,软件工程师,50000.5,北京";
    std::istringstream csvStream(csvLine);
    std::vector<std::string> fields;
    std::string field;
    
    while (std::getline(csvStream, field, ',')) {
        fields.push_back(field);
    }
    
    std::cout << "CSV行: " << csvLine << std::endl;
    std::cout << "解析出的字段：" << std::endl;
    std::vector<std::string> fieldNames = {"姓名", "年龄", "职位", "薪水", "城市"};
    for (size_t i = 0; i < fields.size() && i < fieldNames.size(); ++i) {
        std::cout << "  " << fieldNames[i] << ": " << fields[i] << std::endl;
    }
    
    // 3. 复杂数据解析
    std::cout << "\n3. 复杂数据解析：" << std::endl;
    std::string complexData = "Point(3.5, 4.2) Color[255,128,64] Size:large";
    
    // 解析坐标
    size_t pointStart = complexData.find("Point(");
    if (pointStart != std::string::npos) {
        size_t pointEnd = complexData.find(")", pointStart);
        std::string pointData = complexData.substr(pointStart + 6, pointEnd - pointStart - 6);
        std::istringstream pointStream(pointData);
        
        double x, y;
        char comma;
        pointStream >> x >> comma >> y;
        std::cout << "坐标: (" << x << ", " << y << ")" << std::endl;
    }
    
    // 解析颜色
    size_t colorStart = complexData.find("Color[");
    if (colorStart != std::string::npos) {
        size_t colorEnd = complexData.find("]", colorStart);
        std::string colorData = complexData.substr(colorStart + 6, colorEnd - colorStart - 6);
        std::istringstream colorStream(colorData);
        
        int r, g, b;
        char comma1, comma2;
        colorStream >> r >> comma1 >> g >> comma2 >> b;
        std::cout << "颜色: RGB(" << r << ", " << g << ", " << b << ")" << std::endl;
    }
    
    // 解析大小
    size_t sizeStart = complexData.find("Size:");
    if (sizeStart != std::string::npos) {
        std::string size = complexData.substr(sizeStart + 5);
        std::cout << "大小: " << size << std::endl;
    }
}

// 4. 数据类型转换
void demonstrateDataTypeConversion() {
    std::cout << "\n=== 数据类型转换演示 ===" << std::endl;
    
    // 1. 数字到字符串转换
    std::cout << "\n1. 数字到字符串转换：" << std::endl;
    
    auto numberToString = [](auto number) {
        std::ostringstream oss;
        oss << number;
        return oss.str();
    };
    
    int intNum = 42;
    double doubleNum = 3.14159;
    float floatNum = 2.718f;
    
    std::cout << "整数 " << intNum << " -> 字符串 '" << numberToString(intNum) << "'" << std::endl;
    std::cout << "双精度 " << doubleNum << " -> 字符串 '" << numberToString(doubleNum) << "'" << std::endl;
    std::cout << "浮点数 " << floatNum << " -> 字符串 '" << numberToString(floatNum) << "'" << std::endl;
    
    // 2. 字符串到数字转换
    std::cout << "\n2. 字符串到数字转换：" << std::endl;
    
    auto stringToNumber = [](const std::string& str) {
        std::istringstream iss(str);
        double number;
        if (iss >> number) {
            return number;
        }
        return 0.0;
    };
    
    std::vector<std::string> numberStrings = {"123", "45.67", "0.001", "invalid", "789.123"};
    
    for (const auto& str : numberStrings) {
        double result = stringToNumber(str);
        std::cout << "字符串 '" << str << "' -> 数字 " << result << std::endl;
    }
    
    // 3. 带错误检查的转换
    std::cout << "\n3. 带错误检查的转换：" << std::endl;
    
    auto safeStringToInt = [](const std::string& str) -> std::pair<bool, int> {
        std::istringstream iss(str);
        int number;
        if (iss >> number && iss.eof()) {
            return {true, number};
        }
        return {false, 0};
    };
    
    std::vector<std::string> testStrings = {"123", "45.67", "abc", "123abc", "  456  "};
    
    for (const auto& str : testStrings) {
        auto [success, value] = safeStringToInt(str);
        std::cout << "字符串 '" << str << "' -> ";
        if (success) {
            std::cout << "成功转换为 " << value << std::endl;
        } else {
            std::cout << "转换失败" << std::endl;
        }
    }
    
    // 4. 自定义类型转换
    std::cout << "\n4. 自定义类型转换：" << std::endl;
    
    struct Point {
        double x, y;
        
        Point(double x = 0, double y = 0) : x(x), y(y) {}
        
        std::string toString() const {
            std::ostringstream oss;
            oss << "(" << x << ", " << y << ")";
            return oss.str();
        }
        
        static Point fromString(const std::string& str) {
            // 期望格式: "(x, y)"
            std::istringstream iss(str);
            char lparen, comma, rparen;
            double x, y;
            
            if (iss >> lparen >> x >> comma >> y >> rparen && 
                lparen == '(' && comma == ',' && rparen == ')') {
                return Point(x, y);
            }
            return Point(); // 默认值
        }
    };
    
    Point p1(3.5, 4.2);
    std::string pointStr = p1.toString();
    Point p2 = Point::fromString(pointStr);
    
    std::cout << "原始点: " << p1.toString() << std::endl;
    std::cout << "字符串: " << pointStr << std::endl;
    std::cout << "解析点: " << p2.toString() << std::endl;
}

// 5. 高级字符串流技巧
void demonstrateAdvancedTechniques() {
    std::cout << "\n=== 高级字符串流技巧演示 ===" << std::endl;
    
    // 1. 流状态重置和重用
    std::cout << "\n1. 流状态重置和重用：" << std::endl;
    std::stringstream ss;
    
    for (int i = 1; i <= 3; ++i) {
        ss.str("");  // 清空内容
        ss.clear();  // 清空状态标志
        
        ss << "循环 " << i << ": 值 = " << i * i;
        std::cout << "第" << i << "次使用: " << ss.str() << std::endl;
    }
    
    // 2. 模拟sprintf功能
    std::cout << "\n2. 模拟sprintf功能：" << std::endl;
    
    auto format = [](const std::string& name, int age, double salary) {
        std::ostringstream oss;
        oss << "员工信息 - 姓名: " << name 
            << ", 年龄: " << age 
            << ", 薪水: " << std::fixed << std::setprecision(2) << salary;
        return oss.str();
    };
    
    std::string info = format("李明", 28, 6500.75);
    std::cout << info << std::endl;
    
    // 3. 字符串分割
    std::cout << "\n3. 字符串分割：" << std::endl;
    
    auto split = [](const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::istringstream iss(str);
        std::string token;
        
        while (std::getline(iss, token, delimiter)) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    };
    
    std::string text = "apple;banana;cherry;date;elderberry";
    auto fruits = split(text, ';');
    
    std::cout << "原字符串: " << text << std::endl;
    std::cout << "分割结果：" << std::endl;
    for (size_t i = 0; i < fruits.size(); ++i) {
        std::cout << "  [" << i << "] " << fruits[i] << std::endl;
    }
    
    // 4. 字符串模板替换
    std::cout << "\n4. 字符串模板替换：" << std::endl;
    
    auto replaceTemplate = [](std::string templ, 
                             const std::vector<std::pair<std::string, std::string>>& replacements) {
        for (const auto& [placeholder, value] : replacements) {
            size_t pos = 0;
            while ((pos = templ.find(placeholder, pos)) != std::string::npos) {
                templ.replace(pos, placeholder.length(), value);
                pos += value.length();
            }
        }
        return templ;
    };
    
    std::string templateStr = "Hello {name}, you are {age} years old and work in {city}.";
    std::vector<std::pair<std::string, std::string>> replacements = {
        {"{name}", "张三"},
        {"{age}", "25"},
        {"{city}", "北京"}
    };
    
    std::string result = replaceTemplate(templateStr, replacements);
    std::cout << "模板: " << templateStr << std::endl;
    std::cout << "结果: " << result << std::endl;
}

void demonstrateStringStreams() {
    std::cout << "\n=== 字符串流演示 ===" << std::endl;
    
    // 1. 基本字符串流操作
    demonstrateBasicStringStreams();
    
    // 2. 字符串格式化
    demonstrateStringFormatting();
    
    // 3. 字符串解析
    demonstrateStringParsing();
    
    // 4. 数据类型转换
    demonstrateDataTypeConversion();
    
    // 5. 高级技巧
    demonstrateAdvancedTechniques();
    
    std::cout << "\n=== 字符串流演示完成 ===" << std::endl;
}

} // namespace string_streams_demo

int main() {
    string_streams_demo::demonstrateStringStreams();
    return 0;
} 