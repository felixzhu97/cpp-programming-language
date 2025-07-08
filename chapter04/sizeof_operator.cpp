#include "common.h"

int main() {
    print_separator("sizeof运算符示例");
    
    // 基本数据类型的sizeof
    cout << "=== 基本数据类型的sizeof ===" << endl;
    cout << "char: " << sizeof(char) << " 字节" << endl;
    cout << "short: " << sizeof(short) << " 字节" << endl;
    cout << "int: " << sizeof(int) << " 字节" << endl;
    cout << "long: " << sizeof(long) << " 字节" << endl;
    cout << "long long: " << sizeof(long long) << " 字节" << endl;
    cout << "float: " << sizeof(float) << " 字节" << endl;
    cout << "double: " << sizeof(double) << " 字节" << endl;
    cout << "long double: " << sizeof(long double) << " 字节" << endl;
    cout << "bool: " << sizeof(bool) << " 字节" << endl;
    
    // 指针类型的sizeof
    cout << "\n=== 指针类型的sizeof ===" << endl;
    int* int_ptr = nullptr;
    double* double_ptr = nullptr;
    char* char_ptr = nullptr;
    void* void_ptr = nullptr;
    
    cout << "int*: " << sizeof(int_ptr) << " 字节" << endl;
    cout << "double*: " << sizeof(double_ptr) << " 字节" << endl;
    cout << "char*: " << sizeof(char_ptr) << " 字节" << endl;
    cout << "void*: " << sizeof(void_ptr) << " 字节" << endl;
    cout << "注意：所有指针类型的大小都相同" << endl;
    
    // 数组的sizeof
    cout << "\n=== 数组的sizeof ===" << endl;
    int arr1[5] = {1, 2, 3, 4, 5};
    double arr2[10];
    char arr3[20] = "Hello";
    
    cout << "int[5]: " << sizeof(arr1) << " 字节" << endl;
    cout << "double[10]: " << sizeof(arr2) << " 字节" << endl;
    cout << "char[20]: " << sizeof(arr3) << " 字节" << endl;
    
    // 计算数组元素个数
    cout << "\n=== 计算数组元素个数 ===" << endl;
    size_t arr1_size = sizeof(arr1) / sizeof(arr1[0]);
    size_t arr2_size = sizeof(arr2) / sizeof(arr2[0]);
    
    cout << "arr1元素个数: " << arr1_size << endl;
    cout << "arr2元素个数: " << arr2_size << endl;
    
    // 字符串的sizeof
    cout << "\n=== 字符串的sizeof ===" << endl;
    string str1 = "Hello";
    string str2 = "Hello World";
    string str3 = "This is a very long string to test sizeof";
    
    cout << "string类型本身的大小: " << sizeof(string) << " 字节" << endl;
    cout << "str1 (\"" << str1 << "\") 的sizeof: " << sizeof(str1) << " 字节" << endl;
    cout << "str2 (\"" << str2 << "\") 的sizeof: " << sizeof(str2) << " 字节" << endl;
    cout << "str3 (\"" << str3 << "\") 的sizeof: " << sizeof(str3) << " 字节" << endl;
    cout << "注意：string对象的sizeof是固定的，不依赖于内容长度" << endl;
    
    // C风格字符串的sizeof
    cout << "\n=== C风格字符串的sizeof ===" << endl;
    char cstr1[] = "Hello";
    char cstr2[] = "Hello World";
    char cstr3[100] = "Test";
    
    cout << "cstr1 (\"" << cstr1 << "\") 的sizeof: " << sizeof(cstr1) << " 字节" << endl;
    cout << "cstr2 (\"" << cstr2 << "\") 的sizeof: " << sizeof(cstr2) << " 字节" << endl;
    cout << "cstr3 (\"" << cstr3 << "\") 的sizeof: " << sizeof(cstr3) << " 字节" << endl;
    cout << "注意：C风格字符串数组的sizeof包括终止符\\0" << endl;
    
    // 结构体的sizeof
    cout << "\n=== 结构体的sizeof ===" << endl;
    struct Point {
        int x;
        int y;
    };
    
    struct Student {
        int id;
        char name[20];
        double score;
    };
    
    struct Padding {
        char a;      // 1字节
        int b;       // 4字节
        char c;      // 1字节
    };
    
    cout << "Point结构体: " << sizeof(Point) << " 字节" << endl;
    cout << "Student结构体: " << sizeof(Student) << " 字节" << endl;
    cout << "Padding结构体: " << sizeof(Padding) << " 字节 (注意内存对齐)" << endl;
    
    // 内存对齐详解
    cout << "\n=== 内存对齐详解 ===" << endl;
    cout << "Padding结构体成员分析:" << endl;
    cout << "  char a: 1字节" << endl;
    cout << "  int b: 4字节 (需要4字节对齐)" << endl;
    cout << "  char c: 1字节" << endl;
    cout << "理论大小: 1 + 4 + 1 = 6字节" << endl;
    cout << "实际大小: " << sizeof(Padding) << " 字节 (由于内存对齐)" << endl;
    
    // 使用#pragma pack控制对齐
    cout << "\n=== 不同对齐方式的结构体 ===" << endl;
    
    #pragma pack(push, 1)  // 1字节对齐
    struct PackedStruct {
        char a;
        int b;
        char c;
    };
    #pragma pack(pop)
    
    cout << "1字节对齐的结构体: " << sizeof(PackedStruct) << " 字节" << endl;
    
    // 联合体的sizeof
    cout << "\n=== 联合体的sizeof ===" << endl;
    union TestUnion {
        int i;
        float f;
        char c[4];
    };
    
    cout << "TestUnion联合体: " << sizeof(TestUnion) << " 字节" << endl;
    cout << "注意：联合体的大小等于最大成员的大小" << endl;
    
    // 枚举的sizeof
    cout << "\n=== 枚举的sizeof ===" << endl;
    enum Color { RED, GREEN, BLUE };
    enum class Status { ACTIVE, INACTIVE, PENDING };
    
    cout << "enum Color: " << sizeof(Color) << " 字节" << endl;
    cout << "enum class Status: " << sizeof(Status) << " 字节" << endl;
    
    // 类的sizeof
    cout << "\n=== 类的sizeof ===" << endl;
    class EmptyClass {};
    
    class SimpleClass {
        int value;
    };
    
    class ClassWithMethods {
        int value;
    public:
        void setValue(int v) { value = v; }
        int getValue() const { return value; }
    };
    
    cout << "空类: " << sizeof(EmptyClass) << " 字节" << endl;
    cout << "有一个int成员的类: " << sizeof(SimpleClass) << " 字节" << endl;
    cout << "有成员函数的类: " << sizeof(ClassWithMethods) << " 字节" << endl;
    cout << "注意：成员函数不会增加类的大小" << endl;
    
    // 虚函数的影响
    cout << "\n=== 虚函数的影响 ===" << endl;
    class BaseClass {
        int value;
    };
    
    class VirtualClass {
        int value;
    public:
        virtual void func() {}
    };
    
    cout << "没有虚函数的类: " << sizeof(BaseClass) << " 字节" << endl;
    cout << "有虚函数的类: " << sizeof(VirtualClass) << " 字节" << endl;
    cout << "注意：虚函数会增加类的大小（虚函数表指针）" << endl;
    
    // 继承的sizeof
    cout << "\n=== 继承的sizeof ===" << endl;
    class Base {
        int base_value;
    };
    
    class Derived : public Base {
        int derived_value;
    };
    
    cout << "基类: " << sizeof(Base) << " 字节" << endl;
    cout << "派生类: " << sizeof(Derived) << " 字节" << endl;
    
    // 容器的sizeof
    cout << "\n=== 容器的sizeof ===" << endl;
    vector<int> vec1;
    vector<int> vec2(100);
    vector<int> vec3(1000);
    
    cout << "空vector: " << sizeof(vec1) << " 字节" << endl;
    cout << "100个元素的vector: " << sizeof(vec2) << " 字节" << endl;
    cout << "1000个元素的vector: " << sizeof(vec3) << " 字节" << endl;
    cout << "注意：vector对象的sizeof是固定的，不依赖于元素个数" << endl;
    
    // sizeof的编译时特性
    cout << "\n=== sizeof的编译时特性 ===" << endl;
    cout << "sizeof是编译时运算符，不会计算表达式的值" << endl;
    
    int x = 5;
    int size_result = sizeof(x++);
    cout << "sizeof(x++): " << size_result << " 字节" << endl;
    cout << "x的值: " << x << " (注意：x没有被自增)" << endl;
    
    // sizeof用于表达式
    cout << "\n=== sizeof用于表达式 ===" << endl;
    int a = 10, b = 20;
    cout << "sizeof(a + b): " << sizeof(a + b) << " 字节" << endl;
    cout << "sizeof(a * 1.5): " << sizeof(a * 1.5) << " 字节" << endl;
    cout << "sizeof(a > b): " << sizeof(a > b) << " 字节" << endl;
    
    // 实际应用场景
    cout << "\n=== 实际应用场景 ===" << endl;
    
    // 1. 动态内存分配
    cout << "1. 动态内存分配:" << endl;
    int* dynamic_array = new int[10];
    cout << "分配了 " << 10 * sizeof(int) << " 字节的内存" << endl;
    delete[] dynamic_array;
    
    // 2. 结构体序列化
    cout << "2. 结构体序列化:" << endl;
    struct Data {
        int id;
        float value;
        char status;
    };
    
    Data data = {1, 3.14f, 'A'};
    cout << "Data结构体大小: " << sizeof(Data) << " 字节" << endl;
    cout << "可以安全地进行二进制序列化" << endl;
    
    // 3. 数组边界检查
    cout << "3. 数组边界检查:" << endl;
    int test_array[5] = {1, 2, 3, 4, 5};
    size_t array_length = sizeof(test_array) / sizeof(test_array[0]);
    cout << "数组长度: " << array_length << endl;
    
    // 4. 缓冲区大小计算
    cout << "4. 缓冲区大小计算:" << endl;
    char buffer[1024];
    cout << "缓冲区大小: " << sizeof(buffer) << " 字节" << endl;
    
    // 5. 类型大小比较
    cout << "5. 类型大小比较:" << endl;
    cout << "在这个系统上:" << endl;
    cout << "  指针大小: " << sizeof(void*) << " 字节 (" << (sizeof(void*) == 8 ? "64位" : "32位") << ")" << endl;
    cout << "  long大小: " << sizeof(long) << " 字节" << endl;
    cout << "  size_t大小: " << sizeof(size_t) << " 字节" << endl;
    
    // 常见错误和注意事项
    cout << "\n=== 常见错误和注意事项 ===" << endl;
    cout << "1. 指针参数的sizeof会返回指针大小，而非数组大小" << endl;
    cout << "2. string对象的sizeof是固定的，要获取字符串长度用length()方法" << endl;
    cout << "3. 结构体的sizeof可能因内存对齐而大于成员大小之和" << endl;
    cout << "4. sizeof(表达式)不会计算表达式的值" << endl;
    cout << "5. 虚函数会增加类的大小（虚函数表指针）" << endl;
    
    print_separator("sizeof运算符示例完成");
    
    return 0;
} 