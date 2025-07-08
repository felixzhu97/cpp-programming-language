/*
 * 第8章：IO库 - IO操纵符
 * 展示内置操纵符、自定义操纵符、参数化操纵符、操纵符的实现原理
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

namespace io_manipulators_demo {

// 1. 内置操纵符演示
void demonstrateBuiltinManipulators() {
    std::cout << "\n=== 内置操纵符演示 ===" << std::endl;
    
    // 1. 无参数操纵符
    std::cout << "\n1. 无参数操纵符：" << std::endl;
    std::cout << "默认: " << 123 << " " << 456.789 << std::endl;
    std::cout << std::hex << "十六进制: " << 123 << std::endl;
    std::cout << std::oct << "八进制: " << 123 << std::endl;
    std::cout << std::dec << "十进制: " << 123 << std::endl;
    
    std::cout << std::showbase << "显示进制前缀: ";
    std::cout << std::hex << 123 << " " << std::oct << 123 << " " << std::dec << 123 << std::endl;
    std::cout << std::noshowbase;
    
    std::cout << std::uppercase << "大写十六进制: " << std::hex << 255 << std::endl;
    std::cout << std::nouppercase << std::dec;
    
    std::cout << std::showpos << "显示正号: " << 42 << " " << -42 << std::endl;
    std::cout << std::noshowpos;
    
    double pi = 3.14159265;
    std::cout << std::showpoint << "显示小数点: " << 5.0 << std::endl;
    std::cout << std::noshowpoint;
    
    std::cout << std::fixed << "固定小数点: " << pi << std::endl;
    std::cout << std::scientific << "科学计数法: " << pi << std::endl;
    std::cout << std::defaultfloat;
    
    // 2. 参数化操纵符
    std::cout << "\n2. 参数化操纵符：" << std::endl;
    std::cout << std::setw(10) << "width10" << "|" << std::endl;
    std::cout << std::setfill('*') << std::setw(10) << "填充*" << "|" << std::endl;
    std::cout << std::setfill(' ');
    
    std::cout << std::setprecision(3) << "精度3: " << pi << std::endl;
    std::cout << std::setprecision(6) << "精度6: " << pi << std::endl;
    
    std::cout << std::setbase(16) << "setbase 16: " << 255 << std::endl;
    std::cout << std::setbase(8) << "setbase 8: " << 255 << std::endl;
    std::cout << std::setbase(10) << "setbase 10: " << 255 << std::endl;
    
    // 3. 对齐操纵符
    std::cout << "\n3. 对齐操纵符：" << std::endl;
    std::cout << std::left << std::setw(10) << "左对齐" << "|" << std::endl;
    std::cout << std::right << std::setw(10) << "右对齐" << "|" << std::endl;
    std::cout << std::internal << std::setw(10) << std::showpos << 123 << "|" << std::endl;
    std::cout << std::noshowpos;
    
    // 4. 布尔值操纵符
    std::cout << "\n4. 布尔值操纵符：" << std::endl;
    bool flag = true;
    std::cout << "默认: " << flag << " " << !flag << std::endl;
    std::cout << std::boolalpha << "文本: " << flag << " " << !flag << std::endl;
    std::cout << std::noboolalpha;
}

// 2. 自定义简单操纵符
std::ostream& tab(std::ostream& os) {
    return os << '\t';
}

std::ostream& newline(std::ostream& os) {
    return os << '\n';
}

std::ostream& separator(std::ostream& os) {
    return os << " | ";
}

std::ostream& stars(std::ostream& os) {
    return os << "***";
}

void demonstrateCustomSimpleManipulators() {
    std::cout << "\n=== 自定义简单操纵符演示 ===" << std::endl;
    
    std::cout << "使用自定义操纵符：" << newline;
    std::cout << "第一列" << tab << "第二列" << tab << "第三列" << newline;
    std::cout << "数据1" << separator << "数据2" << separator << "数据3" << newline;
    std::cout << stars << " 重要信息 " << stars << newline;
}

// 3. 自定义参数化操纵符
class repeat_manip {
private:
    char ch;
    int count;
    
public:
    repeat_manip(char c, int n) : ch(c), count(n) {}
    
    friend std::ostream& operator<<(std::ostream& os, const repeat_manip& manip) {
        for (int i = 0; i < manip.count; ++i) {
            os << manip.ch;
        }
        return os;
    }
};

repeat_manip repeat(char ch, int count) {
    return repeat_manip(ch, count);
}

class indent_manip {
private:
    int spaces;
    
public:
    indent_manip(int n) : spaces(n) {}
    
    friend std::ostream& operator<<(std::ostream& os, const indent_manip& manip) {
        for (int i = 0; i < manip.spaces; ++i) {
            os << ' ';
        }
        return os;
    }
};

indent_manip indent(int spaces) {
    return indent_manip(spaces);
}

class border_manip {
private:
    char ch;
    int width;
    
public:
    border_manip(char c, int w) : ch(c), width(w) {}
    
    friend std::ostream& operator<<(std::ostream& os, const border_manip& manip) {
        for (int i = 0; i < manip.width; ++i) {
            os << manip.ch;
        }
        return os;
    }
};

border_manip border(char ch, int width) {
    return border_manip(ch, width);
}

void demonstrateParameterizedManipulators() {
    std::cout << "\n=== 参数化操纵符演示 ===" << std::endl;
    
    std::cout << "\n使用repeat操纵符：" << std::endl;
    std::cout << repeat('=', 50) << std::endl;
    std::cout << "标题" << std::endl;
    std::cout << repeat('-', 50) << std::endl;
    
    std::cout << "\n使用indent操纵符：" << std::endl;
    std::cout << indent(0) << "级别 0" << std::endl;
    std::cout << indent(2) << "级别 1" << std::endl;
    std::cout << indent(4) << "级别 2" << std::endl;
    std::cout << indent(6) << "级别 3" << std::endl;
    
    std::cout << "\n使用border操纵符：" << std::endl;
    std::cout << border('*', 40) << std::endl;
    std::cout << "* " << std::setw(36) << std::left << "重要公告" << " *" << std::endl;
    std::cout << border('*', 40) << std::endl;
}

// 4. 状态操纵符
class save_format_manip {
private:
    std::ios::fmtflags flags;
    std::streamsize precision;
    char fill;
    
public:
    save_format_manip(std::ios& stream) 
        : flags(stream.flags()), precision(stream.precision()), fill(stream.fill()) {}
    
    friend std::ostream& operator<<(std::ostream& os, const save_format_manip& manip) {
        // 这个操纵符实际上不输出任何内容，只是保存状态
        return os;
    }
    
    void restore(std::ios& stream) {
        stream.flags(flags);
        stream.precision(precision);
        stream.fill(fill);
    }
};

class temp_format_manip {
private:
    std::ios::fmtflags flags;
    std::streamsize precision;
    
public:
    temp_format_manip(std::ios::fmtflags f, std::streamsize p) : flags(f), precision(p) {}
    
    friend std::ostream& operator<<(std::ostream& os, const temp_format_manip& manip) {
        os.flags(manip.flags);
        os.precision(manip.precision);
        return os;
    }
};

temp_format_manip temp_fixed(int precision) {
    return temp_format_manip(std::ios::fixed, precision);
}

temp_format_manip temp_scientific(int precision) {
    return temp_format_manip(std::ios::scientific, precision);
}

void demonstrateStateManipulators() {
    std::cout << "\n=== 状态操纵符演示 ===" << std::endl;
    
    double number = 3.14159265359;
    
    std::cout << "\n临时格式操纵符：" << std::endl;
    std::cout << "默认格式: " << number << std::endl;
    std::cout << temp_fixed(2) << "临时固定2位: " << number << std::endl;
    std::cout << "恢复默认: " << number << std::endl;
    std::cout << temp_scientific(4) << "临时科学计数法: " << number << std::endl;
    std::cout << std::defaultfloat << "明确恢复: " << number << std::endl;
}

// 5. 条件操纵符
class conditional_manip {
private:
    bool condition;
    std::string text;
    
public:
    conditional_manip(bool cond, const std::string& t) : condition(cond), text(t) {}
    
    friend std::ostream& operator<<(std::ostream& os, const conditional_manip& manip) {
        if (manip.condition) {
            os << manip.text;
        }
        return os;
    }
};

conditional_manip if_true(bool condition, const std::string& text) {
    return conditional_manip(condition, text);
}

conditional_manip if_false(bool condition, const std::string& text) {
    return conditional_manip(!condition, text);
}

void demonstrateConditionalManipulators() {
    std::cout << "\n=== 条件操纵符演示 ===" << std::endl;
    
    bool isLoggedIn = true;
    bool hasPermission = false;
    int userLevel = 3;
    
    std::cout << "\n条件显示信息：" << std::endl;
    std::cout << "用户状态: " 
              << if_true(isLoggedIn, "已登录") 
              << if_false(isLoggedIn, "未登录") << std::endl;
    
    std::cout << "权限状态: " 
              << if_true(hasPermission, "有权限") 
              << if_false(hasPermission, "无权限") << std::endl;
    
    std::cout << "用户级别: " 
              << if_true(userLevel >= 5, "[管理员]")
              << if_true(userLevel >= 3 && userLevel < 5, "[高级用户]")
              << if_true(userLevel < 3, "[普通用户]") << std::endl;
}

// 6. 复合操纵符
class table_cell_manip {
private:
    std::string content;
    int width;
    char border;
    
public:
    table_cell_manip(const std::string& c, int w, char b = '|') 
        : content(c), width(w), border(b) {}
    
    friend std::ostream& operator<<(std::ostream& os, const table_cell_manip& manip) {
        os << manip.border << " " 
           << std::left << std::setw(manip.width - 3) << manip.content 
           << " ";
        return os;
    }
};

table_cell_manip cell(const std::string& content, int width) {
    return table_cell_manip(content, width);
}

class table_row_end_manip {
public:
    friend std::ostream& operator<<(std::ostream& os, const table_row_end_manip&) {
        return os << "|" << std::endl;
    }
};

table_row_end_manip row_end() {
    return table_row_end_manip();
}

void demonstrateComplexManipulators() {
    std::cout << "\n=== 复合操纵符演示 ===" << std::endl;
    
    std::cout << "\n表格操纵符：" << std::endl;
    std::cout << repeat('-', 50) << std::endl;
    std::cout << cell("姓名", 12) << cell("年龄", 8) << cell("城市", 12) << cell("职业", 15) << row_end();
    std::cout << repeat('-', 50) << std::endl;
    std::cout << cell("张三", 12) << cell("25", 8) << cell("北京", 12) << cell("工程师", 15) << row_end();
    std::cout << cell("李四", 12) << cell("30", 8) << cell("上海", 12) << cell("设计师", 15) << row_end();
    std::cout << cell("王五", 12) << cell("28", 8) << cell("广州", 12) << cell("教师", 15) << row_end();
    std::cout << repeat('-', 50) << std::endl;
}

// 7. 操纵符的实现原理演示
namespace implementation_details {

// 简单操纵符类型
using simple_manipulator = std::ostream& (*)(std::ostream&);

// 参数化操纵符的实现
template<typename T>
class param_manipulator {
private:
    T value;
    std::ostream& (*func)(std::ostream&, T);
    
public:
    param_manipulator(std::ostream& (*f)(std::ostream&, T), T v) : func(f), value(v) {}
    
    friend std::ostream& operator<<(std::ostream& os, const param_manipulator& manip) {
        return manip.func(os, manip.value);
    }
};

// 具体的操纵符函数
std::ostream& print_n_chars_impl(std::ostream& os, std::pair<char, int> data) {
    for (int i = 0; i < data.second; ++i) {
        os << data.first;
    }
    return os;
}

// 便利函数
param_manipulator<std::pair<char, int>> print_n_chars(char ch, int count) {
    return param_manipulator<std::pair<char, int>>(print_n_chars_impl, std::make_pair(ch, count));
}

} // namespace implementation_details

void demonstrateImplementationPrinciples() {
    std::cout << "\n=== 操纵符实现原理演示 ===" << std::endl;
    
    using namespace implementation_details;
    
    std::cout << "\n自定义参数化操纵符实现：" << std::endl;
    std::cout << "开始" << print_n_chars('-', 20) << "结束" << std::endl;
    std::cout << "标题" << print_n_chars('=', 30) << std::endl;
    
    std::cout << "\n操纵符的本质：" << std::endl;
    std::cout << "- 简单操纵符是函数指针" << std::endl;
    std::cout << "- 参数化操纵符是包装对象" << std::endl;
    std::cout << "- 都通过operator<<重载工作" << std::endl;
}

void demonstrateIOManipulators() {
    std::cout << "\n=== IO操纵符演示 ===" << std::endl;
    
    // 1. 内置操纵符
    demonstrateBuiltinManipulators();
    
    // 2. 自定义简单操纵符
    demonstrateCustomSimpleManipulators();
    
    // 3. 参数化操纵符
    demonstrateParameterizedManipulators();
    
    // 4. 状态操纵符
    demonstrateStateManipulators();
    
    // 5. 条件操纵符
    demonstrateConditionalManipulators();
    
    // 6. 复合操纵符
    demonstrateComplexManipulators();
    
    // 7. 实现原理
    demonstrateImplementationPrinciples();
    
    std::cout << "\n=== IO操纵符演示完成 ===" << std::endl;
}

} // namespace io_manipulators_demo

int main() {
    io_manipulators_demo::demonstrateIOManipulators();
    return 0;
} 