#include "common.h"

// 结构体定义
struct Person {
    string name;
    int age;
    double height;
};

// 枚举类型
enum Color {
    RED,
    GREEN,
    BLUE
};

// 枚举类（C++11）
enum class Status {
    ACTIVE,
    INACTIVE,
    PENDING
};

// 联合体
union Data {
    int intVal;
    double doubleVal;
    char charVal;
};

int main() {
    print_separator("复合类型示例");
    
    // 数组
    cout << "=== 数组 ===" << endl;
    int arr[5] = {1, 2, 3, 4, 5};
    cout << "数组元素: ";
    for (int i = 0; i < 5; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 多维数组
    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    cout << "二维数组:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // 字符数组
    char cStr[20] = "Hello, C++";
    cout << "字符数组: " << cStr << endl;
    
    // 结构体
    cout << "\n=== 结构体 ===" << endl;
    Person person1;
    person1.name = "张三";
    person1.age = 25;
    person1.height = 175.5;
    
    Person person2 = {"李四", 30, 168.0};  // 列表初始化
    
    cout << "Person 1: " << person1.name << ", " << person1.age << "岁, " << person1.height << "cm" << endl;
    cout << "Person 2: " << person2.name << ", " << person2.age << "岁, " << person2.height << "cm" << endl;
    
    // 结构体数组
    Person people[2] = {
        {"王五", 28, 180.0},
        {"赵六", 35, 165.0}
    };
    
    cout << "结构体数组:" << endl;
    for (int i = 0; i < 2; ++i) {
        cout << "  " << people[i].name << ", " << people[i].age << "岁" << endl;
    }
    
    // 枚举类型
    cout << "\n=== 枚举类型 ===" << endl;
    Color myColor = RED;
    cout << "颜色值: " << myColor << endl;
    
    switch (myColor) {
        case RED:
            cout << "选择了红色" << endl;
            break;
        case GREEN:
            cout << "选择了绿色" << endl;
            break;
        case BLUE:
            cout << "选择了蓝色" << endl;
            break;
    }
    
    // 枚举类（C++11）
    cout << "\n=== 枚举类（C++11） ===" << endl;
    Status currentStatus = Status::ACTIVE;
    
    switch (currentStatus) {
        case Status::ACTIVE:
            cout << "状态：活跃" << endl;
            break;
        case Status::INACTIVE:
            cout << "状态：非活跃" << endl;
            break;
        case Status::PENDING:
            cout << "状态：待定" << endl;
            break;
    }
    
    // 联合体
    cout << "\n=== 联合体 ===" << endl;
    Data data;
    data.intVal = 42;
    cout << "设置int值: " << data.intVal << endl;
    
    data.doubleVal = 3.14;
    cout << "设置double值: " << data.doubleVal << endl;
    cout << "此时int值（可能被覆盖）: " << data.intVal << endl;
    
    // 类型别名
    cout << "\n=== 类型别名 ===" << endl;
    typedef int Integer;
    using Real = double;  // C++11方式
    
    Integer num1 = 100;
    Real num2 = 3.14159;
    
    cout << "typedef Integer: " << num1 << endl;
    cout << "using Real: " << num2 << endl;
    
    // 复杂类型声明
    cout << "\n=== 复杂类型声明 ===" << endl;
    
    // 指向数组的指针
    int (*ptrToArray)[5] = &arr;
    cout << "指向数组的指针: " << (*ptrToArray)[0] << endl;
    
    // 指针数组
    int* arrayOfPtrs[3];
    int x = 10, y = 20, z = 30;
    arrayOfPtrs[0] = &x;
    arrayOfPtrs[1] = &y;
    arrayOfPtrs[2] = &z;
    
    cout << "指针数组: ";
    for (int i = 0; i < 3; ++i) {
        cout << *arrayOfPtrs[i] << " ";
    }
    cout << endl;
    
    // 指向结构体的指针
    cout << "\n=== 指向结构体的指针 ===" << endl;
    Person* personPtr = &person1;
    cout << "通过指针访问: " << personPtr->name << ", " << personPtr->age << "岁" << endl;
    cout << "等价写法: " << (*personPtr).name << ", " << (*personPtr).age << "岁" << endl;
    
    // auto关键字预览
    cout << "\n=== auto关键字预览 ===" << endl;
    auto autoInt = 42;        // 推断为int
    auto autoDouble = 3.14;   // 推断为double
    auto autoString = "Hello"; // 推断为const char*
    
    cout << "auto int: " << autoInt << endl;
    cout << "auto double: " << autoDouble << endl;
    cout << "auto string: " << autoString << endl;
    
    print_separator("复合类型示例完成");
    
    return 0;
} 