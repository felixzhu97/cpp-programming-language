/*
 * 第8章：IO库 - 格式化输入输出
 * 展示格式化控制、精度控制、宽度控制、对齐方式、数制转换
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

namespace formatted_io_demo {

// 1. 基本格式化控制
void demonstrateBasicFormatting() {
    std::cout << "\n=== 基本格式化控制演示 ===" << std::endl;
    
    double number = 3.14159265359;
    int integer = 42;
    
    // 1. 精度控制
    std::cout << "\n1. 精度控制：" << std::endl;
    std::cout << "默认格式: " << number << std::endl;
    std::cout << std::setprecision(3) << "3位精度: " << number << std::endl;
    std::cout << std::setprecision(6) << "6位精度: " << number << std::endl;
    
    // 2. 固定小数点格式
    std::cout << "\n2. 固定小数点格式：" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "固定2位小数: " << number << std::endl;
    std::cout << std::fixed << std::setprecision(4) << "固定4位小数: " << number << std::endl;
    
    // 3. 科学计数法格式
    std::cout << "\n3. 科学计数法格式：" << std::endl;
    std::cout << std::scientific << std::setprecision(3) << "科学计数法: " << number << std::endl;
    
    // 4. 默认格式（重置）
    std::cout << "\n4. 重置格式：" << std::endl;
    std::cout << std::defaultfloat << "重置后: " << number << std::endl;
    
    // 5. 整数格式
    std::cout << "\n5. 整数格式：" << std::endl;
    std::cout << "十进制: " << std::dec << integer << std::endl;
    std::cout << "十六进制: " << std::hex << integer << std::endl;
    std::cout << "八进制: " << std::oct << integer << std::endl;
    std::cout << std::dec;  // 重置为十进制
}

// 2. 宽度和对齐控制
void demonstrateWidthAndAlignment() {
    std::cout << "\n=== 宽度和对齐控制演示 ===" << std::endl;
    
    std::string names[] = {"Alice", "Bob", "Charlie", "David"};
    int ages[] = {25, 30, 35, 28};
    double salaries[] = {5000.5, 6500.75, 7200.0, 5800.25};
    
    // 1. 基本宽度控制
    std::cout << "\n1. 基本宽度控制：" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(10) << names[i] 
                  << std::setw(5) << ages[i] 
                  << std::setw(10) << std::fixed << std::setprecision(2) << salaries[i] << std::endl;
    }
    
    // 2. 左对齐
    std::cout << "\n2. 左对齐：" << std::endl;
    std::cout << std::left;
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(10) << names[i] 
                  << std::setw(5) << ages[i] 
                  << std::setw(10) << std::fixed << std::setprecision(2) << salaries[i] << std::endl;
    }
    
    // 3. 右对齐（默认）
    std::cout << "\n3. 右对齐：" << std::endl;
    std::cout << std::right;
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(10) << names[i] 
                  << std::setw(5) << ages[i] 
                  << std::setw(10) << std::fixed << std::setprecision(2) << salaries[i] << std::endl;
    }
    
    // 4. 内部对齐（数字符号和数值分离）
    std::cout << "\n4. 内部对齐：" << std::endl;
    std::cout << std::internal;
    double negativeNumbers[] = {-123.45, -67.89, -1000.0, -5.5};
    for (double num : negativeNumbers) {
        std::cout << std::setw(10) << std::showpos << num << std::endl;
    }
    std::cout << std::noshowpos;  // 取消显示正号
    
    // 5. 填充字符
    std::cout << "\n5. 填充字符：" << std::endl;
    std::cout << std::right << std::setfill('*');
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(15) << names[i] << std::endl;
    }
    std::cout << std::setfill(' ');  // 重置为空格填充
}

// 3. 数制转换和特殊格式
void demonstrateBaseAndSpecialFormats() {
    std::cout << "\n=== 数制转换和特殊格式演示 ===" << std::endl;
    
    int number = 255;
    
    // 1. 不同进制显示
    std::cout << "\n1. 数制转换（数字 " << number << "）：" << std::endl;
    std::cout << "十进制: " << std::dec << number << std::endl;
    std::cout << "十六进制: " << std::hex << number << std::endl;
    std::cout << "八进制: " << std::oct << number << std::endl;
    
    // 2. 显示进制前缀
    std::cout << "\n2. 显示进制前缀：" << std::endl;
    std::cout << std::showbase;
    std::cout << "十进制: " << std::dec << number << std::endl;
    std::cout << "十六进制: " << std::hex << number << std::endl;
    std::cout << "八进制: " << std::oct << number << std::endl;
    std::cout << std::noshowbase;
    
    // 3. 大小写控制
    std::cout << "\n3. 十六进制大小写：" << std::endl;
    std::cout << std::hex << std::showbase;
    std::cout << "小写: " << std::nouppercase << number << std::endl;
    std::cout << "大写: " << std::uppercase << number << std::endl;
    std::cout << std::noshowbase << std::nouppercase;
    
    // 4. 浮点数特殊格式
    std::cout << "\n4. 浮点数特殊格式：" << std::endl;
    double floatNum = 123.0;
    
    std::cout << std::dec;  // 重置为十进制
    std::cout << "默认: " << floatNum << std::endl;
    std::cout << std::showpoint << "显示小数点: " << floatNum << std::endl;
    std::cout << std::noshowpoint;
    
    // 5. 正负号控制
    std::cout << "\n5. 正负号控制：" << std::endl;
    std::cout << "默认: " << 42 << " " << -42 << std::endl;
    std::cout << std::showpos << "显示正号: " << 42 << " " << -42 << std::endl;
    std::cout << std::noshowpos;
}

// 4. 复杂表格格式化
void demonstrateTableFormatting() {
    std::cout << "\n=== 复杂表格格式化演示 ===" << std::endl;
    
    struct Student {
        std::string name;
        int id;
        double gpa;
        std::string major;
        int year;
    };
    
    std::vector<Student> students = {
        {"张三", 1001, 3.85, "计算机科学", 2},
        {"李四", 1002, 3.62, "电子工程", 3},
        {"王五", 1003, 3.91, "数学", 1},
        {"赵六", 1004, 3.45, "物理", 4},
        {"孙七", 1005, 3.78, "化学", 2}
    };
    
    // 创建表格
    std::cout << "\n学生信息表：" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    
    // 表头
    std::cout << std::left 
              << std::setw(12) << "姓名"
              << std::setw(8) << "学号"
              << std::setw(8) << "GPA"
              << std::setw(15) << "专业"
              << std::setw(8) << "年级" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    // 数据行
    for (const auto& student : students) {
        std::cout << std::left 
                  << std::setw(12) << student.name
                  << std::setw(8) << student.id
                  << std::setw(8) << std::fixed << std::setprecision(2) << student.gpa
                  << std::setw(15) << student.major
                  << std::setw(8) << student.year << std::endl;
    }
    std::cout << std::string(70, '=') << std::endl;
    
    // 统计信息
    double totalGPA = 0;
    for (const auto& student : students) {
        totalGPA += student.gpa;
    }
    double averageGPA = totalGPA / students.size();
    
    std::cout << "\n统计信息：" << std::endl;
    std::cout << "学生总数: " << students.size() << std::endl;
    std::cout << "平均GPA: " << std::fixed << std::setprecision(3) << averageGPA << std::endl;
}

// 5. 格式化状态管理
void demonstrateFormatStateManagement() {
    std::cout << "\n=== 格式化状态管理演示 ===" << std::endl;
    
    double number = 3.14159;
    
    // 1. 保存和恢复格式状态
    std::cout << "\n1. 保存和恢复格式状态：" << std::endl;
    std::cout << "原始格式: " << number << std::endl;
    
    // 保存当前格式状态
    std::ios::fmtflags originalFlags = std::cout.flags();
    std::streamsize originalPrecision = std::cout.precision();
    
    // 修改格式
    std::cout << std::fixed << std::setprecision(2) << "修改后: " << number << std::endl;
    
    // 恢复原始格式
    std::cout.flags(originalFlags);
    std::cout.precision(originalPrecision);
    std::cout << "恢复后: " << number << std::endl;
    
    // 2. 使用RAII管理格式状态
    std::cout << "\n2. RAII格式状态管理：" << std::endl;
    
    class FormatGuard {
    private:
        std::ios& stream;
        std::ios::fmtflags flags;
        std::streamsize precision;
        char fill;
        
    public:
        FormatGuard(std::ios& s) : stream(s) {
            flags = stream.flags();
            precision = stream.precision();
            fill = stream.fill();
        }
        
        ~FormatGuard() {
            stream.flags(flags);
            stream.precision(precision);
            stream.fill(fill);
        }
    };
    
    std::cout << "RAII前: " << number << std::endl;
    {
        FormatGuard guard(std::cout);
        std::cout << std::scientific << std::setprecision(4) << "RAII中: " << number << std::endl;
    }  // guard析构，自动恢复格式
    std::cout << "RAII后: " << number << std::endl;
    
    // 3. 格式标志的操作
    std::cout << "\n3. 格式标志的操作：" << std::endl;
    
    // 设置特定标志
    std::cout.setf(std::ios::showpos);
    std::cout << "设置showpos: " << 42 << std::endl;
    
    // 取消特定标志
    std::cout.unsetf(std::ios::showpos);
    std::cout << "取消showpos: " << 42 << std::endl;
    
    // 同时设置和取消标志
    std::cout.setf(std::ios::hex, std::ios::basefield);  // 设置十六进制，清除其他进制标志
    std::cout << "十六进制: " << 255 << std::endl;
    std::cout.setf(std::ios::dec, std::ios::basefield);  // 重置为十进制
}

// 6. 自定义格式化函数
void demonstrateCustomFormatting() {
    std::cout << "\n=== 自定义格式化函数演示 ===" << std::endl;
    
    // 1. 货币格式化
    auto formatCurrency = [](double amount, const std::string& currency = "￥") {
        std::ostringstream oss;
        oss << currency << std::fixed << std::setprecision(2) << amount;
        return oss.str();
    };
    
    std::cout << "\n1. 货币格式化：" << std::endl;
    std::cout << formatCurrency(1234.56) << std::endl;
    std::cout << formatCurrency(999.9, "$") << std::endl;
    std::cout << formatCurrency(5000, "€") << std::endl;
    
    // 2. 百分比格式化
    auto formatPercentage = [](double value, int precision = 1) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision) << (value * 100) << "%";
        return oss.str();
    };
    
    std::cout << "\n2. 百分比格式化：" << std::endl;
    std::cout << "0.1234 -> " << formatPercentage(0.1234) << std::endl;
    std::cout << "0.9876 -> " << formatPercentage(0.9876, 2) << std::endl;
    std::cout << "0.5 -> " << formatPercentage(0.5, 0) << std::endl;
    
    // 3. 文件大小格式化
    auto formatFileSize = [](long long bytes) {
        std::ostringstream oss;
        const char* units[] = {"B", "KB", "MB", "GB", "TB"};
        int unitIndex = 0;
        double size = static_cast<double>(bytes);
        
        while (size >= 1024 && unitIndex < 4) {
            size /= 1024;
            unitIndex++;
        }
        
        oss << std::fixed << std::setprecision(unitIndex == 0 ? 0 : 2) << size << " " << units[unitIndex];
        return oss.str();
    };
    
    std::cout << "\n3. 文件大小格式化：" << std::endl;
    std::cout << "512 bytes -> " << formatFileSize(512) << std::endl;
    std::cout << "2048 bytes -> " << formatFileSize(2048) << std::endl;
    std::cout << "1572864 bytes -> " << formatFileSize(1572864) << std::endl;
    std::cout << "1073741824 bytes -> " << formatFileSize(1073741824) << std::endl;
    
    // 4. 时间格式化（简化版）
    auto formatTime = [](int hours, int minutes, int seconds, bool is24Hour = true) {
        std::ostringstream oss;
        if (is24Hour) {
            oss << std::setfill('0') << std::setw(2) << hours << ":"
                << std::setw(2) << minutes << ":"
                << std::setw(2) << seconds;
        } else {
            int displayHour = hours == 0 ? 12 : (hours > 12 ? hours - 12 : hours);
            std::string ampm = hours < 12 ? "AM" : "PM";
            oss << std::setfill('0') << std::setw(2) << displayHour << ":"
                << std::setw(2) << minutes << ":"
                << std::setw(2) << seconds << " " << ampm;
        }
        return oss.str();
    };
    
    std::cout << "\n4. 时间格式化：" << std::endl;
    std::cout << "14:30:45 (24小时) -> " << formatTime(14, 30, 45) << std::endl;
    std::cout << "14:30:45 (12小时) -> " << formatTime(14, 30, 45, false) << std::endl;
    std::cout << "09:15:30 (12小时) -> " << formatTime(9, 15, 30, false) << std::endl;
}

void demonstrateFormattedIO() {
    std::cout << "\n=== 格式化输入输出演示 ===" << std::endl;
    
    // 1. 基本格式化控制
    demonstrateBasicFormatting();
    
    // 2. 宽度和对齐控制
    demonstrateWidthAndAlignment();
    
    // 3. 数制转换和特殊格式
    demonstrateBaseAndSpecialFormats();
    
    // 4. 复杂表格格式化
    demonstrateTableFormatting();
    
    // 5. 格式化状态管理
    demonstrateFormatStateManagement();
    
    // 6. 自定义格式化函数
    demonstrateCustomFormatting();
    
    std::cout << "\n=== 格式化IO演示完成 ===" << std::endl;
}

} // namespace formatted_io_demo

int main() {
    formatted_io_demo::demonstrateFormattedIO();
    return 0;
} 