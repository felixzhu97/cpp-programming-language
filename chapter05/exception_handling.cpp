#include "common.h"

// 自定义异常类
class DivisionByZeroException : public exception {
public:
    const char* what() const noexcept override {
        return "错误：除数不能为零";
    }
};

class InvalidInputException : public exception {
private:
    string message;
public:
    InvalidInputException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

// 可能抛出异常的函数
double safeDivide(double a, double b) {
    if (b == 0.0) {
        throw DivisionByZeroException();
    }
    return a / b;
}

// 数组访问函数
int getArrayElement(const vector<int>& arr, size_t index) {
    if (index >= arr.size()) {
        throw out_of_range("数组索引越界");
    }
    return arr[index];
}

// 文件操作模拟
void simulateFileOperation(const string& filename) {
    if (filename.empty()) {
        throw InvalidInputException("文件名不能为空");
    }
    if (filename.find(".txt") == string::npos) {
        throw InvalidInputException("仅支持.txt文件");
    }
    // 模拟文件操作成功
    cout << "成功处理文件: " << filename << endl;
}

int main() {
    print_separator("异常处理示例");
    
    // 基本异常处理 - try-catch
    cout << "=== 基本异常处理 - try-catch ===" << endl;
    
    try {
        double result = safeDivide(10.0, 2.0);
        cout << "10.0 / 2.0 = " << result << endl;
        
        // 这里会抛出异常
        result = safeDivide(10.0, 0.0);
        cout << "这行代码不会执行" << endl;
    }
    catch (const DivisionByZeroException& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    
    cout << "异常处理后继续执行" << endl;
    
    // 多种异常类型
    cout << "\n=== 多种异常类型 ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    try {
        cout << "数组元素[2]: " << getArrayElement(numbers, 2) << endl;
        cout << "数组元素[10]: " << getArrayElement(numbers, 10) << endl;
    }
    catch (const out_of_range& e) {
        cout << "越界异常: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "其他异常: " << e.what() << endl;
    }
    
    // 自定义异常
    cout << "\n=== 自定义异常 ===" << endl;
    
    vector<string> filenames = {"document.txt", "image.jpg", "", "data.txt"};
    
    for (const string& filename : filenames) {
        try {
            cout << "处理文件: \"" << filename << "\"" << endl;
            simulateFileOperation(filename);
        }
        catch (const InvalidInputException& e) {
            cout << "输入异常: " << e.what() << endl;
        }
    }
    
    // 异常重新抛出
    cout << "\n=== 异常重新抛出 ===" << endl;
    
    auto processWithLogging = [](double a, double b) {
        try {
            cout << "开始计算 " << a << " / " << b << endl;
            double result = safeDivide(a, b);
            cout << "计算完成，结果: " << result << endl;
            return result;
        }
        catch (const DivisionByZeroException& e) {
            cout << "记录错误日志: " << e.what() << endl;
            throw;  // 重新抛出异常
        }
    };
    
    try {
        processWithLogging(20.0, 4.0);
        processWithLogging(15.0, 0.0);
    }
    catch (const DivisionByZeroException& e) {
        cout << "最终处理异常: " << e.what() << endl;
    }
    
    // 嵌套异常处理
    cout << "\n=== 嵌套异常处理 ===" << endl;
    
    try {
        cout << "外层try块开始" << endl;
        
        try {
            cout << "内层try块开始" << endl;
            throw runtime_error("内层异常");
        }
        catch (const runtime_error& e) {
            cout << "内层catch: " << e.what() << endl;
            throw logic_error("外层异常");  // 抛出新异常
        }
        
        cout << "这行不会执行" << endl;
    }
    catch (const logic_error& e) {
        cout << "外层catch: " << e.what() << endl;
    }
    
    // 标准异常类型
    cout << "\n=== 标准异常类型 ===" << endl;
    
    // 1. bad_alloc - 内存分配失败
    cout << "1. 内存分配异常模拟:" << endl;
    try {
        // 模拟内存分配失败（实际中很难触发）
        cout << "正常内存分配..." << endl;
        vector<int> vec(1000);
        cout << "内存分配成功" << endl;
    }
    catch (const bad_alloc& e) {
        cout << "内存分配失败: " << e.what() << endl;
    }
    
    // 2. invalid_argument - 无效参数
    cout << "\n2. 无效参数异常:" << endl;
    try {
        string str = "abc123";
        int num = stoi(str);  // 这会抛出异常
    }
    catch (const invalid_argument& e) {
        cout << "无效参数: " << e.what() << endl;
    }
    
    // 3. range_error - 范围错误
    cout << "\n3. 范围错误异常:" << endl;
    try {
        string str = "999999999999999999999999999999";
        int num = stoi(str);  // 数值超出范围
    }
    catch (const out_of_range& e) {
        cout << "数值超出范围: " << e.what() << endl;
    }
    
    // 异常安全性
    cout << "\n=== 异常安全性 ===" << endl;
    
    // RAII (Resource Acquisition Is Initialization)
    cout << "RAII 资源管理:" << endl;
    
    class Resource {
    private:
        string name;
    public:
        Resource(const string& n) : name(n) {
            cout << "获取资源: " << name << endl;
        }
        
        ~Resource() {
            cout << "释放资源: " << name << endl;
        }
        
        void use() {
            cout << "使用资源: " << name << endl;
        }
    };
    
    try {
        Resource res("数据库连接");
        res.use();
        
        // 即使这里抛出异常，资源也会被正确释放
        throw runtime_error("模拟异常");
    }
    catch (const runtime_error& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    // Resource的析构函数会自动调用，释放资源
    
    // 智能指针的异常安全性
    cout << "\n智能指针的异常安全性:" << endl;
    
    try {
        unique_ptr<vector<int>> ptr = make_unique<vector<int>>(10, 42);
        cout << "智能指针创建成功，大小: " << ptr->size() << endl;
        
        // 即使抛出异常，智能指针也会自动释放内存
        throw runtime_error("模拟异常");
    }
    catch (const runtime_error& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    // unique_ptr会自动释放内存
    
    // 异常处理的最佳实践
    cout << "\n=== 异常处理最佳实践 ===" << endl;
    
    // 1. 函数级别的异常处理
    cout << "1. 函数级别的异常处理:" << endl;
    
    auto safeOperation = [](const vector<int>& data, int divisor) -> double {
        try {
            if (data.empty()) {
                throw invalid_argument("数组为空");
            }
            if (divisor == 0) {
                throw invalid_argument("除数不能为零");
            }
            
            double sum = 0;
            for (int val : data) {
                sum += val;
            }
            return sum / divisor;
        }
        catch (const invalid_argument& e) {
            cout << "参数错误: " << e.what() << endl;
            return 0.0;  // 返回默认值
        }
    };
    
    vector<int> test_data = {1, 2, 3, 4, 5};
    cout << "正常操作结果: " << safeOperation(test_data, 2) << endl;
    cout << "异常操作结果: " << safeOperation(test_data, 0) << endl;
    
    // 2. 异常规范和noexcept
    cout << "\n2. 异常规范和noexcept:" << endl;
    
    // 不抛出异常的函数
    auto noThrowFunction = []() noexcept -> int {
        return 42;
    };
    
    // 可能抛出异常的函数
    auto mayThrowFunction = []() -> int {
        throw runtime_error("可能的异常");
        return 0;
    };
    
    cout << "不抛出异常的函数: " << noThrowFunction() << endl;
    
    try {
        mayThrowFunction();
    }
    catch (const runtime_error& e) {
        cout << "捕获可能的异常: " << e.what() << endl;
    }
    
    // 3. 异常链和nested_exception
    cout << "\n3. 异常链:" << endl;
    
    auto chainedExceptionDemo = []() {
        try {
            throw runtime_error("原始异常");
        }
        catch (const runtime_error& e) {
            cout << "捕获原始异常: " << e.what() << endl;
            throw logic_error("链式异常");
        }
    };
    
    try {
        chainedExceptionDemo();
    }
    catch (const logic_error& e) {
        cout << "捕获链式异常: " << e.what() << endl;
    }
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 配置文件读取
    cout << "1. 配置文件读取模拟:" << endl;
    
    class ConfigReader {
    public:
        static map<string, string> loadConfig(const string& filename) {
            if (filename.empty()) {
                throw invalid_argument("配置文件名不能为空");
            }
            
            map<string, string> config;
            
            // 模拟读取配置文件
            if (filename == "config.txt") {
                config["host"] = "localhost";
                config["port"] = "8080";
                config["timeout"] = "30";
            } else if (filename == "invalid.conf") {
                throw runtime_error("配置文件格式错误");
            } else {
                throw runtime_error("配置文件不存在");
            }
            
            return config;
        }
    };
    
    vector<string> config_files = {"config.txt", "invalid.conf", "missing.txt"};
    
    for (const string& file : config_files) {
        try {
            auto config = ConfigReader::loadConfig(file);
            cout << "成功加载配置文件: " << file << endl;
            for (const auto& pair : config) {
                cout << "  " << pair.first << " = " << pair.second << endl;
            }
        }
        catch (const invalid_argument& e) {
            cout << "参数错误 [" << file << "]: " << e.what() << endl;
        }
        catch (const runtime_error& e) {
            cout << "运行时错误 [" << file << "]: " << e.what() << endl;
        }
    }
    
    // 2. 数据验证
    cout << "\n2. 数据验证:" << endl;
    
    class DataValidator {
    public:
        static void validateAge(int age) {
            if (age < 0) {
                throw invalid_argument("年龄不能为负数");
            }
            if (age > 150) {
                throw out_of_range("年龄超出合理范围");
            }
        }
        
        static void validateEmail(const string& email) {
            if (email.empty()) {
                throw invalid_argument("邮箱不能为空");
            }
            if (email.find('@') == string::npos) {
                throw invalid_argument("邮箱格式不正确");
            }
        }
    };
    
    vector<pair<int, string>> userData = {
        {25, "user@example.com"},
        {-5, "invalid@email.com"},
        {200, "user@domain.org"},
        {30, "invalidemail"}
    };
    
    for (const auto& data : userData) {
        try {
            cout << "验证数据: 年龄=" << data.first << ", 邮箱=" << data.second << endl;
            DataValidator::validateAge(data.first);
            DataValidator::validateEmail(data.second);
            cout << "数据验证通过" << endl;
        }
        catch (const invalid_argument& e) {
            cout << "数据验证失败: " << e.what() << endl;
        }
        catch (const out_of_range& e) {
            cout << "数据超出范围: " << e.what() << endl;
        }
    }
    
    // 异常处理总结
    cout << "\n=== 异常处理总结 ===" << endl;
    cout << "1. 使用异常处理错误情况，而非正常控制流" << endl;
    cout << "2. 抛出异常时提供有意义的错误信息" << endl;
    cout << "3. 使用RAII确保资源正确释放" << endl;
    cout << "4. 在适当的层次捕获和处理异常" << endl;
    cout << "5. 考虑使用noexcept标记不抛出异常的函数" << endl;
    cout << "6. 避免在析构函数中抛出异常" << endl;
    cout << "7. 使用标准异常类型，或从它们派生自定义异常" << endl;
    cout << "8. 异常处理不应该成为性能瓶颈" << endl;
    
    print_separator("异常处理示例完成");
    
    return 0;
} 