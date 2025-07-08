#include "common.h"

int main() {
    print_separator("类型转换示例");
    
    // 隐式类型转换
    cout << "=== 隐式类型转换 ===" << endl;
    
    // 整数提升
    cout << "1. 整数提升:" << endl;
    char c = 'A';
    short s = 100;
    int i = c + s;  // char和short自动提升为int
    cout << "char 'A' + short 100 = " << i << endl;
    cout << "结果类型: int" << endl;
    
    // 算术转换
    cout << "\n2. 算术转换:" << endl;
    int int_val = 10;
    double double_val = 3.14;
    auto result = int_val + double_val;  // int转换为double
    cout << "int 10 + double 3.14 = " << result << endl;
    cout << "结果类型: " << typeid(result).name() << endl;
    
    // 浮点数转换
    float f = 3.14f;
    double d = f;  // float隐式转换为double
    cout << "float转double: " << f << " -> " << d << endl;
    
    // 指针转换
    cout << "\n3. 指针转换:" << endl;
    int* int_ptr = &int_val;
    void* void_ptr = int_ptr;  // 任何指针都可以转换为void*
    cout << "int*转void*: " << int_ptr << " -> " << void_ptr << endl;
    
    // 数组名转指针
    int arr[5] = {1, 2, 3, 4, 5};
    int* ptr = arr;  // 数组名隐式转换为指针
    cout << "数组名转指针: arr[0] = " << arr[0] << ", *ptr = " << *ptr << endl;
    
    // 显式类型转换 - C风格
    cout << "\n=== 显式类型转换 - C风格 ===" << endl;
    
    // 基本类型转换
    double pi = 3.14159;
    int truncated = (int)pi;  // C风格转换
    cout << "double转int: " << pi << " -> " << truncated << endl;
    
    // 指针转换
    void* generic_ptr = &int_val;
    int* specific_ptr = (int*)generic_ptr;  // void*转回int*
    cout << "void*转int*: " << generic_ptr << " -> " << specific_ptr << endl;
    cout << "解引用结果: " << *specific_ptr << endl;
    
    // 显式类型转换 - C++风格
    cout << "\n=== 显式类型转换 - C++风格 ===" << endl;
    
    // 1. static_cast
    cout << "1. static_cast:" << endl;
    double price = 19.99;
    int dollars = static_cast<int>(price);  // 安全的类型转换
    cout << "价格: $" << price << " -> " << dollars << " 美元" << endl;
    
    // 基类指针和派生类指针
    class Base { public: virtual ~Base() {} };
    class Derived : public Base { public: int value = 42; };
    
    Base* base_ptr = new Derived();
    Derived* derived_ptr = static_cast<Derived*>(base_ptr);
    cout << "基类指针转派生类指针: " << derived_ptr->value << endl;
    
    // 2. dynamic_cast
    cout << "\n2. dynamic_cast:" << endl;
    Base* base_ptr2 = new Derived();
    Derived* derived_ptr2 = dynamic_cast<Derived*>(base_ptr2);
    
    if (derived_ptr2) {
        cout << "dynamic_cast成功: " << derived_ptr2->value << endl;
    } else {
        cout << "dynamic_cast失败" << endl;
    }
    
    // 测试失败的dynamic_cast
    Base* base_only = new Base();
    Derived* failed_cast = dynamic_cast<Derived*>(base_only);
    cout << "失败的dynamic_cast: " << (failed_cast ? "成功" : "失败") << endl;
    
    // 3. const_cast
    cout << "\n3. const_cast:" << endl;
    const int const_val = 100;
    int* modifiable = const_cast<int*>(&const_val);  // 移除const
    cout << "const_cast移除const: " << *modifiable << endl;
    
    // 注意：修改原本为const的变量是未定义行为
    // *modifiable = 200;  // 危险！不要这样做
    
    // 4. reinterpret_cast
    cout << "\n4. reinterpret_cast:" << endl;
    int num = 0x12345678;
    char* byte_ptr = reinterpret_cast<char*>(&num);
    cout << "int的字节表示: ";
    for (size_t i = 0; i < sizeof(int); i++) {
        cout << hex << (static_cast<unsigned char>(byte_ptr[i]) & 0xFF) << " ";
    }
    cout << dec << endl;
    
    // 函数指针转换
    cout << "\n=== 函数指针转换 ===" << endl;
    auto add_func = [](int a, int b) { return a + b; };
    auto multiply_func = [](int a, int b) { return a * b; };
    
    // 函数指针数组
    int (*operations[])(int, int) = {add_func, multiply_func};
    
    cout << "5 + 3 = " << operations[0](5, 3) << endl;
    cout << "5 * 3 = " << operations[1](5, 3) << endl;
    
    // 字符串转换
    cout << "\n=== 字符串转换 ===" << endl;
    
    // 字符串转数字
    string str_num = "123";
    int converted_int = stoi(str_num);
    cout << "字符串转int: \"" << str_num << "\" -> " << converted_int << endl;
    
    string str_double = "3.14159";
    double converted_double = stod(str_double);
    cout << "字符串转double: \"" << str_double << "\" -> " << converted_double << endl;
    
    // 数字转字符串
    int num_to_str = 456;
    string str_result = to_string(num_to_str);
    cout << "int转字符串: " << num_to_str << " -> \"" << str_result << "\"" << endl;
    
    // 布尔转换
    cout << "\n=== 布尔转换 ===" << endl;
    
    // 数值转布尔
    int zero = 0, non_zero = 42;
    bool bool_zero = static_cast<bool>(zero);
    bool bool_non_zero = static_cast<bool>(non_zero);
    cout << "0转bool: " << (bool_zero ? "true" : "false") << endl;
    cout << "42转bool: " << (bool_non_zero ? "true" : "false") << endl;
    
    // 指针转布尔
    int* null_ptr = nullptr;
    int* valid_ptr = &int_val;
    cout << "nullptr转bool: " << (static_cast<bool>(null_ptr) ? "true" : "false") << endl;
    cout << "有效指针转bool: " << (static_cast<bool>(valid_ptr) ? "true" : "false") << endl;
    
    // 数组和指针转换
    cout << "\n=== 数组和指针转换 ===" << endl;
    
    // 多维数组
    int matrix[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    int* flat_ptr = &matrix[0][0];  // 转换为一维指针
    
    cout << "二维数组作为一维访问:" << endl;
    for (int i = 0; i < 12; i++) {
        cout << flat_ptr[i] << " ";
        if ((i + 1) % 4 == 0) cout << endl;
    }
    
    // 用户定义的转换
    cout << "\n=== 用户定义的转换 ===" << endl;
    
    // 转换构造函数
    class Temperature {
        double celsius;
    public:
        Temperature(double c) : celsius(c) {}  // 转换构造函数
        Temperature(int fahrenheit) : celsius((fahrenheit - 32) * 5.0 / 9.0) {}  // 从华氏度转换
        
        operator double() const { return celsius; }  // 转换运算符
        
        void display() const {
            cout << celsius << "°C";
        }
    };
    
    Temperature temp1 = 25.0;  // 隐式转换
    Temperature temp2 = 77;    // 从华氏度转换
    
    cout << "温度1: ";
    temp1.display();
    cout << endl;
    
    cout << "温度2: ";
    temp2.display();
    cout << endl;
    
    // 转换运算符
    double temp_value = temp1;  // 隐式转换为double
    cout << "转换为double: " << temp_value << endl;
    
    // 危险的转换
    cout << "\n=== 危险的转换 ===" << endl;
    
    // 精度丢失
    double precise = 3.14159265359;
    float less_precise = static_cast<float>(precise);
    cout << "double转float精度丢失: " << precise << " -> " << less_precise << endl;
    
    // 数据截断
    int large_int = 1000;
    char truncated_char = static_cast<char>(large_int);
    cout << "int转char截断: " << large_int << " -> " << static_cast<int>(truncated_char) << endl;
    
    // 符号问题
    int negative = -1;
    unsigned int unsigned_val = static_cast<unsigned int>(negative);
    cout << "int转unsigned: " << negative << " -> " << unsigned_val << endl;
    
    // 转换的最佳实践
    cout << "\n=== 转换的最佳实践 ===" << endl;
    cout << "1. 优先使用隐式转换（当安全时）" << endl;
    cout << "2. 使用C++风格转换而非C风格转换" << endl;
    cout << "3. 使用static_cast进行安全的类型转换" << endl;
    cout << "4. 使用dynamic_cast进行安全的多态转换" << endl;
    cout << "5. 避免使用reinterpret_cast，除非绝对必要" << endl;
    cout << "6. 小心const_cast，不要修改原本为const的数据" << endl;
    cout << "7. 检查转换是否会导致数据丢失" << endl;
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 安全的除法
    cout << "1. 安全的除法:" << endl;
    auto safe_divide = [](double a, double b) -> double {
        if (b == 0) return 0.0;
        return a / b;
    };
    
    cout << "10 / 3 = " << safe_divide(10, 3) << endl;
    cout << "10 / 0 = " << safe_divide(10, 0) << endl;
    
    // 2. 文件大小格式化
    cout << "2. 文件大小格式化:" << endl;
    auto format_file_size = [](size_t bytes) -> string {
        const size_t KB = 1024;
        const size_t MB = KB * 1024;
        const size_t GB = MB * 1024;
        
        if (bytes >= GB) {
            return to_string(static_cast<double>(bytes) / GB) + " GB";
        } else if (bytes >= MB) {
            return to_string(static_cast<double>(bytes) / MB) + " MB";
        } else if (bytes >= KB) {
            return to_string(static_cast<double>(bytes) / KB) + " KB";
        } else {
            return to_string(bytes) + " bytes";
        }
    };
    
    cout << "文件大小: " << format_file_size(1024) << endl;
    cout << "文件大小: " << format_file_size(1024 * 1024) << endl;
    cout << "文件大小: " << format_file_size(1024 * 1024 * 1024) << endl;
    
    // 3. 颜色值转换
    cout << "3. 颜色值转换:" << endl;
    auto rgb_to_hex = [](int r, int g, int b) -> string {
        // 确保值在0-255范围内
        r = max(0, min(255, r));
        g = max(0, min(255, g));
        b = max(0, min(255, b));
        
        // 转换为16进制
        stringstream ss;
        ss << "#" << hex << setfill('0') << setw(2) << r 
           << setw(2) << g << setw(2) << b;
        return ss.str();
    };
    
    cout << "RGB(255, 0, 0) = " << rgb_to_hex(255, 0, 0) << endl;
    cout << "RGB(0, 255, 0) = " << rgb_to_hex(0, 255, 0) << endl;
    cout << "RGB(0, 0, 255) = " << rgb_to_hex(0, 0, 255) << endl;
    
    // 清理动态分配的内存
    delete base_ptr;
    delete base_ptr2;
    delete base_only;
    
    print_separator("类型转换示例完成");
    
    return 0;
} 