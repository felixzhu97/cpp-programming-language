#include "common.h"

int main() {
    print_separator("语句块示例");
    
    // 基本语句块
    cout << "=== 基本语句块 ===" << endl;
    
    cout << "程序开始" << endl;
    
    {
        // 这是一个基本的语句块
        cout << "进入语句块" << endl;
        int block_var = 10;
        cout << "块内变量: " << block_var << endl;
        cout << "退出语句块" << endl;
    }
    // block_var 在这里不可访问
    
    cout << "程序继续" << endl;
    
    // 变量作用域
    cout << "\n=== 变量作用域 ===" << endl;
    
    int outer_var = 100;
    cout << "外层变量: " << outer_var << endl;
    
    {
        cout << "进入内层块" << endl;
        int inner_var = 200;
        cout << "内层变量: " << inner_var << endl;
        cout << "可以访问外层变量: " << outer_var << endl;
        
        // 修改外层变量
        outer_var = 150;
        cout << "修改外层变量为: " << outer_var << endl;
    }
    
    cout << "回到外层，outer_var = " << outer_var << endl;
    // inner_var 在这里不可访问
    
    // 变量隐藏
    cout << "\n=== 变量隐藏 ===" << endl;
    
    int value = 50;
    cout << "外层 value: " << value << endl;
    
    {
        int value = 75;  // 隐藏外层的value
        cout << "内层 value (隐藏外层): " << value << endl;
        
        {
            int value = 100;  // 再次隐藏
            cout << "更内层 value: " << value << endl;
        }
        
        cout << "回到内层 value: " << value << endl;
    }
    
    cout << "回到外层 value: " << value << endl;
    
    // 嵌套语句块
    cout << "\n=== 嵌套语句块 ===" << endl;
    
    {
        cout << "第1层块开始" << endl;
        int level1 = 1;
        
        {
            cout << "第2层块开始" << endl;
            int level2 = 2;
            cout << "level1 = " << level1 << ", level2 = " << level2 << endl;
            
            {
                cout << "第3层块开始" << endl;
                int level3 = 3;
                cout << "level1 = " << level1 << ", level2 = " << level2 << ", level3 = " << level3 << endl;
                cout << "第3层块结束" << endl;
            }
            
            cout << "第2层块结束" << endl;
        }
        
        cout << "第1层块结束" << endl;
    }
    
    // 条件语句中的块
    cout << "\n=== 条件语句中的块 ===" << endl;
    
    int score = 85;
    cout << "学生分数: " << score << endl;
    
    if (score >= 90) {
        string grade = "A";
        string comment = "优秀";
        cout << "等级: " << grade << ", 评价: " << comment << endl;
    } else if (score >= 80) {
        string grade = "B";
        string comment = "良好";
        cout << "等级: " << grade << ", 评价: " << comment << endl;
    } else {
        string grade = "C";
        string comment = "需要努力";
        cout << "等级: " << grade << ", 评价: " << comment << endl;
    }
    // grade 和 comment 在这里不可访问
    
    // 循环语句中的块
    cout << "\n=== 循环语句中的块 ===" << endl;
    
    cout << "for循环中的块:" << endl;
    for (int i = 0; i < 3; i++) {
        string loop_msg = "第" + to_string(i + 1) + "次迭代";
        int square = i * i;
        cout << loop_msg << ", i^2 = " << square << endl;
        // loop_msg 和 square 在每次迭代中都会重新创建
    }
    
    cout << "\nwhile循环中的块:" << endl;
    int counter = 0;
    while (counter < 3) {
        string status = "处理中...";
        bool continue_flag = true;
        cout << status << " 计数器 = " << counter << endl;
        counter++;
        // status 和 continue_flag 在每次迭代结束时销毁
    }
    
    // 函数内的块
    cout << "\n=== 函数内的块 ===" << endl;
    
    auto processData = [](const vector<int>& data) {
        cout << "函数开始处理数据" << endl;
        
        // 数据验证块
        {
            cout << "数据验证块" << endl;
            if (data.empty()) {
                cout << "错误：数据为空" << endl;
                return;
            }
            cout << "数据验证通过，大小: " << data.size() << endl;
        }
        
        // 数据处理块
        {
            cout << "数据处理块" << endl;
            int sum = 0;
            for (int val : data) {
                sum += val;
            }
            double average = static_cast<double>(sum) / data.size();
            cout << "数据总和: " << sum << ", 平均值: " << average << endl;
        }
        
        // 结果输出块
        {
            cout << "结果输出块" << endl;
            cout << "数据处理完成" << endl;
        }
        
        cout << "函数处理结束" << endl;
    };
    
    vector<int> test_data = {1, 2, 3, 4, 5};
    processData(test_data);
    
    // 资源管理块
    cout << "\n=== 资源管理块 ===" << endl;
    
    class Resource {
    private:
        string name;
        int id;
    public:
        Resource(const string& n, int i) : name(n), id(i) {
            cout << "创建资源: " << name << " (ID: " << id << ")" << endl;
        }
        
        ~Resource() {
            cout << "销毁资源: " << name << " (ID: " << id << ")" << endl;
        }
        
        void use() {
            cout << "使用资源: " << name << endl;
        }
    };
    
    cout << "资源管理示例:" << endl;
    {
        Resource res1("数据库连接", 1);
        Resource res2("文件句柄", 2);
        
        res1.use();
        res2.use();
        
        cout << "资源使用完毕，即将离开作用域" << endl;
    }  // res1 和 res2 在这里自动销毁
    cout << "已离开资源作用域" << endl;
    
    // 异常安全的块
    cout << "\n=== 异常安全的块 ===" << endl;
    
    cout << "异常安全示例:" << endl;
    try {
        Resource safe_res("安全资源", 3);
        safe_res.use();
        
        // 模拟异常
        throw runtime_error("模拟异常");
        
        cout << "这行不会执行" << endl;
    }
    catch (const runtime_error& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
    // safe_res 即使在异常情况下也会被正确销毁
    
    // 初始化列表和块
    cout << "\n=== 初始化列表和块 ===" << endl;
    
    // C++11 初始化列表
    {
        cout << "使用初始化列表:" << endl;
        vector<string> fruits{"苹果", "香蕉", "橙子"};
        map<string, int> ages{{"张三", 25}, {"李四", 30}, {"王五", 28}};
        
        cout << "水果: ";
        for (const auto& fruit : fruits) {
            cout << fruit << " ";
        }
        cout << endl;
        
        cout << "年龄: ";
        for (const auto& pair : ages) {
            cout << pair.first << "(" << pair.second << ") ";
        }
        cout << endl;
    }
    
    // 临时对象的块
    cout << "\n=== 临时对象的块 ===" << endl;
    
    class TempObject {
    private:
        int value;
    public:
        TempObject(int v) : value(v) {
            cout << "创建临时对象: " << value << endl;
        }
        
        ~TempObject() {
            cout << "销毁临时对象: " << value << endl;
        }
        
        int getValue() const { return value; }
    };
    
    {
        cout << "临时对象示例:" << endl;
        TempObject temp1(10);
        TempObject temp2(20);
        
        cout << "temp1 = " << temp1.getValue() << ", temp2 = " << temp2.getValue() << endl;
        
        // 创建临时对象
        cout << "临时对象的值: " << TempObject(30).getValue() << endl;
    }
    cout << "临时对象块结束" << endl;
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 算法实现中的块
    cout << "1. 排序算法中的块使用:" << endl;
    
    auto bubbleSort = [](vector<int>& arr) {
        cout << "开始冒泡排序" << endl;
        
        // 排序主逻辑块
        {
            int n = arr.size();
            bool swapped;
            
            for (int i = 0; i < n - 1; i++) {
                swapped = false;
                
                // 内层循环块
                {
                    for (int j = 0; j < n - i - 1; j++) {
                        if (arr[j] > arr[j + 1]) {
                            // 交换块
                            {
                                int temp = arr[j];
                                arr[j] = arr[j + 1];
                                arr[j + 1] = temp;
                                swapped = true;
                            }
                        }
                    }
                }
                
                if (!swapped) break;  // 如果没有交换，数组已排序
            }
        }
        
        cout << "冒泡排序完成" << endl;
    };
    
    vector<int> numbers = {64, 34, 25, 12, 22, 11, 90};
    cout << "排序前: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    bubbleSort(numbers);
    
    cout << "排序后: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 2. 配置管理
    cout << "\n2. 配置管理中的块:" << endl;
    
    auto loadConfiguration = []() {
        cout << "加载配置" << endl;
        
        map<string, string> config;
        
        // 默认配置块
        {
            cout << "设置默认配置" << endl;
            config["host"] = "localhost";
            config["port"] = "8080";
            config["timeout"] = "30";
            config["debug"] = "false";
        }
        
        // 环境特定配置块
        {
            cout << "应用环境特定配置" << endl;
            string env = "production";  // 模拟环境变量
            
            if (env == "development") {
                config["debug"] = "true";
                config["timeout"] = "60";
            } else if (env == "production") {
                config["host"] = "prod.example.com";
                config["timeout"] = "10";
            }
        }
        
        // 配置验证块
        {
            cout << "验证配置" << endl;
            bool valid = true;
            
            if (config["host"].empty()) {
                cout << "错误：主机名不能为空" << endl;
                valid = false;
            }
            
            try {
                int port = stoi(config["port"]);
                if (port < 1 || port > 65535) {
                    cout << "错误：端口号无效" << endl;
                    valid = false;
                }
            }
            catch (const exception& e) {
                cout << "错误：端口号格式错误" << endl;
                valid = false;
            }
            
            if (!valid) {
                throw runtime_error("配置验证失败");
            }
        }
        
        return config;
    };
    
    try {
        auto config = loadConfiguration();
        cout << "配置加载成功:" << endl;
        for (const auto& pair : config) {
            cout << "  " << pair.first << " = " << pair.second << endl;
        }
    }
    catch (const runtime_error& e) {
        cout << "配置加载失败: " << e.what() << endl;
    }
    
    // 3. 数据处理管道
    cout << "\n3. 数据处理管道:" << endl;
    
    auto processNumbers = [](const vector<double>& input) {
        vector<double> result = input;
        
        // 数据清理块
        {
            cout << "数据清理阶段" << endl;
            for (auto& val : result) {
                if (isnan(val) || isinf(val)) {
                    val = 0.0;  // 清理无效数据
                }
            }
        }
        
        // 数据转换块
        {
            cout << "数据转换阶段" << endl;
            for (auto& val : result) {
                val = sqrt(abs(val));  // 平方根转换
            }
        }
        
        // 数据标准化块
        {
            cout << "数据标准化阶段" << endl;
            double sum = 0.0;
            for (double val : result) {
                sum += val;
            }
            double mean = sum / result.size();
            
            for (auto& val : result) {
                val = val - mean;  // 中心化
            }
        }
        
        return result;
    };
    
    vector<double> raw_data = {1.0, 4.0, 9.0, 16.0, 25.0};
    cout << "原始数据: ";
    for (double val : raw_data) {
        cout << val << " ";
    }
    cout << endl;
    
    auto processed = processNumbers(raw_data);
    cout << "处理后数据: ";
    for (double val : processed) {
        cout << fixed << setprecision(2) << val << " ";
    }
    cout << endl;
    
    // 语句块最佳实践
    cout << "\n=== 语句块最佳实践 ===" << endl;
    cout << "1. 使用块来控制变量的生命周期" << endl;
    cout << "2. 利用块进行资源管理（RAII）" << endl;
    cout << "3. 用块来组织相关的代码逻辑" << endl;
    cout << "4. 避免过深的嵌套，影响代码可读性" << endl;
    cout << "5. 合理使用变量隐藏，但要谨慎" << endl;
    cout << "6. 在函数中使用块来分离不同的处理阶段" << endl;
    cout << "7. 利用块的作用域特性确保异常安全" << endl;
    cout << "8. 使用块来限制临时变量的作用域" << endl;
    
    print_separator("语句块示例完成");
    
    return 0;
} 