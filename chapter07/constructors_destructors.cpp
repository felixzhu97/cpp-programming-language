#include "common.h"

// 1. 构造函数的不同类型演示
class ConstructorDemo {
private:
    int value;
    string name;
    vector<int> data;
    
public:
    // 1.1 默认构造函数
    ConstructorDemo() : value(0), name("default") {
        cout << "  默认构造函数调用: " << name << ", value=" << value << endl;
    }
    
    // 1.2 参数化构造函数
    ConstructorDemo(int v) : value(v), name("parameterized") {
        cout << "  参数化构造函数调用: " << name << ", value=" << value << endl;
    }
    
    // 1.3 多参数构造函数
    ConstructorDemo(int v, const string& n) : value(v), name(n) {
        cout << "  多参数构造函数调用: " << name << ", value=" << value << endl;
    }
    
    // 1.4 初始化列表构造函数 (C++11)
    ConstructorDemo(initializer_list<int> init_list) : value(0), name("init_list") {
        data = init_list;
        for (int val : data) {
            value += val;
        }
        cout << "  初始化列表构造函数调用: " << name << ", sum=" << value << endl;
    }
    
    // 1.5 拷贝构造函数
    ConstructorDemo(const ConstructorDemo& other) 
        : value(other.value), name(other.name + "_copy"), data(other.data) {
        cout << "  拷贝构造函数调用: " << name << ", value=" << value << endl;
    }
    
    // 1.6 移动构造函数 (C++11)
    ConstructorDemo(ConstructorDemo&& other) noexcept
        : value(other.value), name(move(other.name) + "_moved"), data(move(other.data)) {
        other.value = 0;
        cout << "  移动构造函数调用: " << name << ", value=" << value << endl;
    }
    
    // 1.7 析构函数
    ~ConstructorDemo() {
        cout << "  析构函数调用: " << name << ", value=" << value << endl;
    }
    
    // 赋值运算符
    ConstructorDemo& operator=(const ConstructorDemo& other) {
        if (this != &other) {
            value = other.value;
            name = other.name + "_assigned";
            data = other.data;
            cout << "  拷贝赋值运算符调用: " << name << ", value=" << value << endl;
        }
        return *this;
    }
    
    ConstructorDemo& operator=(ConstructorDemo&& other) noexcept {
        if (this != &other) {
            value = other.value;
            name = move(other.name) + "_move_assigned";
            data = move(other.data);
            other.value = 0;
            cout << "  移动赋值运算符调用: " << name << ", value=" << value << endl;
        }
        return *this;
    }
    
    void print() const {
        cout << "    对象: " << name << ", value=" << value << ", data_size=" << data.size() << endl;
    }
};

// 2. 构造函数委托 (C++11)
class DelegatingConstructor {
private:
    int x, y;
    string label;
    
    // 私有初始化方法
    void init() {
        cout << "    初始化完成: " << label << "(" << x << ", " << y << ")" << endl;
    }
    
public:
    // 主构造函数
    DelegatingConstructor(int x, int y, const string& label) 
        : x(x), y(y), label(label) {
        cout << "  主构造函数调用: " << label << endl;
        init();
    }
    
    // 委托给主构造函数
    DelegatingConstructor() : DelegatingConstructor(0, 0, "origin") {
        cout << "  默认构造函数委托完成" << endl;
    }
    
    // 委托给主构造函数
    DelegatingConstructor(int x, int y) : DelegatingConstructor(x, y, "point") {
        cout << "  双参数构造函数委托完成" << endl;
    }
    
    void print() const {
        cout << "  " << label << ": (" << x << ", " << y << ")" << endl;
    }
};

// 3. 继承中的构造函数
class Base {
protected:
    int base_value;
    
public:
    Base() : base_value(0) {
        cout << "  Base默认构造函数" << endl;
    }
    
    Base(int value) : base_value(value) {
        cout << "  Base参数化构造函数: " << base_value << endl;
    }
    
    virtual ~Base() {
        cout << "  Base析构函数: " << base_value << endl;
    }
    
    virtual void print() const {
        cout << "  Base: " << base_value << endl;
    }
};

class Derived : public Base {
private:
    int derived_value;
    
public:
    Derived() : Base(), derived_value(0) {
        cout << "  Derived默认构造函数" << endl;
    }
    
    Derived(int base_val, int derived_val) : Base(base_val), derived_value(derived_val) {
        cout << "  Derived参数化构造函数: " << derived_value << endl;
    }
    
    ~Derived() {
        cout << "  Derived析构函数: " << derived_value << endl;
    }
    
    void print() const override {
        cout << "  Derived: base=" << base_value << ", derived=" << derived_value << endl;
    }
};

// 4. 资源管理类 - RAII原则
class ResourceManager {
private:
    int* data;
    size_t size;
    string name;
    
public:
    // 构造函数 - 获取资源
    ResourceManager(size_t s, const string& n) : size(s), name(n) {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = static_cast<int>(i);
        }
        cout << "  资源获取: " << name << ", 分配 " << size << " 个整数" << endl;
    }
    
    // 拷贝构造函数 - 深拷贝
    ResourceManager(const ResourceManager& other) 
        : size(other.size), name(other.name + "_copy") {
        data = new int[size];
        for (size_t i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
        cout << "  资源拷贝: " << name << ", 复制 " << size << " 个整数" << endl;
    }
    
    // 移动构造函数 - 转移所有权
    ResourceManager(ResourceManager&& other) noexcept 
        : data(other.data), size(other.size), name(move(other.name) + "_moved") {
        other.data = nullptr;
        other.size = 0;
        cout << "  资源移动: " << name << endl;
    }
    
    // 拷贝赋值运算符
    ResourceManager& operator=(const ResourceManager& other) {
        if (this != &other) {
            // 释放当前资源
            delete[] data;
            
            // 拷贝新资源
            size = other.size;
            name = other.name + "_assigned";
            data = new int[size];
            for (size_t i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
            cout << "  资源拷贝赋值: " << name << endl;
        }
        return *this;
    }
    
    // 移动赋值运算符
    ResourceManager& operator=(ResourceManager&& other) noexcept {
        if (this != &other) {
            // 释放当前资源
            delete[] data;
            
            // 移动新资源
            data = other.data;
            size = other.size;
            name = move(other.name) + "_move_assigned";
            
            other.data = nullptr;
            other.size = 0;
            cout << "  资源移动赋值: " << name << endl;
        }
        return *this;
    }
    
    // 析构函数 - 释放资源
    ~ResourceManager() {
        if (data) {
            cout << "  资源释放: " << name << ", 释放 " << size << " 个整数" << endl;
            delete[] data;
        } else {
            cout << "  空对象析构: " << name << endl;
        }
    }
    
    // 访问方法
    int& operator[](size_t index) {
        if (index < size) {
            return data[index];
        }
        throw out_of_range("Index out of range");
    }
    
    size_t getSize() const { return size; }
    const string& getName() const { return name; }
    
    void print() const {
        if (data && size > 0) {
            cout << "  " << name << " [" << size << "]: ";
            for (size_t i = 0; i < min(size, size_t(10)); i++) {
                cout << data[i] << " ";
            }
            if (size > 10) cout << "...";
            cout << endl;
        } else {
            cout << "  " << name << ": 空对象" << endl;
        }
    }
};

// 5. 智能指针替代手动内存管理
class SmartResourceManager {
private:
    unique_ptr<int[]> data;
    size_t size;
    string name;
    
public:
    SmartResourceManager(size_t s, const string& n) 
        : data(make_unique<int[]>(s)), size(s), name(n) {
        for (size_t i = 0; i < size; i++) {
            data[i] = static_cast<int>(i * 2);
        }
        cout << "  智能指针资源获取: " << name << ", 分配 " << size << " 个整数" << endl;
    }
    
    // 禁用拷贝（因为unique_ptr不可拷贝）
    SmartResourceManager(const SmartResourceManager&) = delete;
    SmartResourceManager& operator=(const SmartResourceManager&) = delete;
    
    // 移动构造函数
    SmartResourceManager(SmartResourceManager&& other) noexcept 
        : data(move(other.data)), size(other.size), name(move(other.name) + "_moved") {
        other.size = 0;
        cout << "  智能指针资源移动: " << name << endl;
    }
    
    // 移动赋值运算符
    SmartResourceManager& operator=(SmartResourceManager&& other) noexcept {
        if (this != &other) {
            data = move(other.data);
            size = other.size;
            name = move(other.name) + "_move_assigned";
            other.size = 0;
            cout << "  智能指针资源移动赋值: " << name << endl;
        }
        return *this;
    }
    
    ~SmartResourceManager() {
        cout << "  智能指针资源自动释放: " << name << endl;
    }
    
    int& operator[](size_t index) {
        if (index < size) {
            return data[index];
        }
        throw out_of_range("Index out of range");
    }
    
    size_t getSize() const { return size; }
    const string& getName() const { return name; }
    
    void print() const {
        if (data && size > 0) {
            cout << "  " << name << " [" << size << "]: ";
            for (size_t i = 0; i < min(size, size_t(10)); i++) {
                cout << data[i] << " ";
            }
            if (size > 10) cout << "...";
            cout << endl;
        } else {
            cout << "  " << name << ": 空对象" << endl;
        }
    }
};

// 6. 构造函数异常安全
class ExceptionSafeClass {
private:
    int* array1;
    int* array2;
    size_t size1, size2;
    
public:
    ExceptionSafeClass(size_t s1, size_t s2, bool throw_exception = false) 
        : array1(nullptr), array2(nullptr), size1(s1), size2(s2) {
        
        try {
            cout << "  尝试分配第一个数组..." << endl;
            array1 = new int[size1];
            
            if (throw_exception) {
                throw runtime_error("模拟构造异常");
            }
            
            cout << "  尝试分配第二个数组..." << endl;
            array2 = new int[size2];
            
            cout << "  构造成功完成" << endl;
        } catch (...) {
            // 清理已分配的资源
            delete[] array1;
            array1 = nullptr;
            cout << "  构造异常，清理已分配资源" << endl;
            throw;  // 重新抛出异常
        }
    }
    
    ~ExceptionSafeClass() {
        cout << "  析构函数清理资源" << endl;
        delete[] array1;
        delete[] array2;
    }
    
    // 禁用拷贝和赋值（简化示例）
    ExceptionSafeClass(const ExceptionSafeClass&) = delete;
    ExceptionSafeClass& operator=(const ExceptionSafeClass&) = delete;
};

// 7. 对象计数器
class ObjectCounter {
private:
    static int object_count;
    static int total_created;
    int id;
    
public:
    ObjectCounter() : id(++total_created) {
        ++object_count;
        cout << "  对象 #" << id << " 创建，当前总数: " << object_count << endl;
    }
    
    ObjectCounter(const ObjectCounter& other) : id(++total_created) {
        ++object_count;
        cout << "  对象 #" << id << " 拷贝创建（从 #" << other.id 
             << "），当前总数: " << object_count << endl;
    }
    
    ~ObjectCounter() {
        --object_count;
        cout << "  对象 #" << id << " 销毁，当前总数: " << object_count << endl;
    }
    
    static int getObjectCount() { return object_count; }
    static int getTotalCreated() { return total_created; }
    
    int getId() const { return id; }
};

// 静态成员定义
int ObjectCounter::object_count = 0;
int ObjectCounter::total_created = 0;

void demonstrateConstructorTypes() {
    cout << "=== 构造函数类型演示 ===" << endl;
    
    cout << "1. 默认构造函数:" << endl;
    ConstructorDemo obj1;
    obj1.print();
    
    cout << "\n2. 参数化构造函数:" << endl;
    ConstructorDemo obj2(42);
    obj2.print();
    
    cout << "\n3. 多参数构造函数:" << endl;
    ConstructorDemo obj3(100, "custom");
    obj3.print();
    
    cout << "\n4. 初始化列表构造函数:" << endl;
    ConstructorDemo obj4{1, 2, 3, 4, 5};
    obj4.print();
    
    cout << "\n5. 拷贝构造函数:" << endl;
    ConstructorDemo obj5 = obj3;  // 拷贝构造
    obj5.print();
    
    cout << "\n6. 移动构造函数:" << endl;
    ConstructorDemo obj6 = move(obj2);  // 移动构造
    obj6.print();
    obj2.print();  // obj2已被移动
    
    cout << "\n7. 赋值运算符:" << endl;
    obj1 = obj3;  // 拷贝赋值
    obj1.print();
    
    cout << "\n8. 移动赋值运算符:" << endl;
    obj1 = move(obj4);  // 移动赋值
    obj1.print();
    obj4.print();  // obj4已被移动
    
    cout << "\n函数结束，对象开始销毁..." << endl;
}

void demonstrateDelegatingConstructors() {
    cout << "\n=== 构造函数委托演示 ===" << endl;
    
    DelegatingConstructor p1;
    p1.print();
    
    DelegatingConstructor p2(5, 10);
    p2.print();
    
    DelegatingConstructor p3(1, 2, "custom_point");
    p3.print();
}

void demonstrateInheritanceConstructors() {
    cout << "\n=== 继承中的构造函数演示 ===" << endl;
    
    cout << "创建Base对象:" << endl;
    Base base(10);
    base.print();
    
    cout << "\n创建Derived对象:" << endl;
    Derived derived(20, 30);
    derived.print();
    
    cout << "\n多态调用:" << endl;
    Base* ptr = new Derived(40, 50);
    ptr->print();
    delete ptr;  // 虚析构函数确保正确销毁
    
    cout << "\n函数结束，对象开始销毁..." << endl;
}

void demonstrateRAII() {
    cout << "\n=== RAII资源管理演示 ===" << endl;
    
    cout << "1. 创建资源管理对象:" << endl;
    ResourceManager rm1(5, "manager1");
    rm1.print();
    
    cout << "\n2. 拷贝构造:" << endl;
    ResourceManager rm2 = rm1;
    rm2.print();
    
    cout << "\n3. 移动构造:" << endl;
    ResourceManager rm3 = move(rm1);
    rm3.print();
    rm1.print();  // rm1已被移动
    
    cout << "\n4. 拷贝赋值:" << endl;
    ResourceManager rm4(3, "manager4");
    rm4 = rm2;
    rm4.print();
    
    cout << "\n5. 移动赋值:" << endl;
    rm4 = move(rm3);
    rm4.print();
    rm3.print();  // rm3已被移动
    
    cout << "\n6. 智能指针版本:" << endl;
    SmartResourceManager srm1(8, "smart_manager1");
    srm1.print();
    
    SmartResourceManager srm2 = move(srm1);
    srm2.print();
    srm1.print();  // srm1已被移动
    
    cout << "\n函数结束，资源自动释放..." << endl;
}

void demonstrateExceptionSafety() {
    cout << "\n=== 构造函数异常安全演示 ===" << endl;
    
    cout << "1. 正常构造:" << endl;
    try {
        ExceptionSafeClass obj1(5, 10, false);
        cout << "  对象构造成功" << endl;
    } catch (const exception& e) {
        cout << "  捕获异常: " << e.what() << endl;
    }
    
    cout << "\n2. 构造异常:" << endl;
    try {
        ExceptionSafeClass obj2(5, 10, true);
        cout << "  这行不应该执行" << endl;
    } catch (const exception& e) {
        cout << "  捕获异常: " << e.what() << endl;
        cout << "  资源已正确清理" << endl;
    }
}

void demonstrateObjectCounting() {
    cout << "\n=== 对象计数演示 ===" << endl;
    
    cout << "初始状态 - 对象数: " << ObjectCounter::getObjectCount() 
         << ", 总创建数: " << ObjectCounter::getTotalCreated() << endl;
    
    {
        cout << "\n创建对象作用域:" << endl;
        ObjectCounter obj1;
        ObjectCounter obj2;
        ObjectCounter obj3 = obj1;  // 拷贝构造
        
        cout << "作用域内 - 对象数: " << ObjectCounter::getObjectCount() 
             << ", 总创建数: " << ObjectCounter::getTotalCreated() << endl;
    }
    
    cout << "\n作用域结束后 - 对象数: " << ObjectCounter::getObjectCount() 
         << ", 总创建数: " << ObjectCounter::getTotalCreated() << endl;
}

int main() {
    print_separator("构造函数和析构函数详解");
    
    // 1. 构造函数类型
    demonstrateConstructorTypes();
    
    // 2. 构造函数委托
    demonstrateDelegatingConstructors();
    
    // 3. 继承中的构造
    demonstrateInheritanceConstructors();
    
    // 4. RAII资源管理
    demonstrateRAII();
    
    // 5. 异常安全
    demonstrateExceptionSafety();
    
    // 6. 对象计数
    demonstrateObjectCounting();
    
    // 7. 构造和析构的最佳实践
    cout << "\n=== 构造和析构最佳实践 ===" << endl;
    cout << "1. 构造函数原则:" << endl;
    cout << "   - 使用初始化列表而不是赋值" << endl;
    cout << "   - 尽早初始化所有成员" << endl;
    cout << "   - 处理构造异常" << endl;
    cout << "   - 避免在构造函数中调用虚函数" << endl;
    
    cout << "\n2. 析构函数原则:" << endl;
    cout << "   - 析构函数应该是虚函数（如果类有虚函数）" << endl;
    cout << "   - 析构函数不应该抛出异常" << endl;
    cout << "   - 遵循RAII原则" << endl;
    cout << "   - 按构造的逆序销毁" << endl;
    
    cout << "\n3. 三/五法则:" << endl;
    cout << "   - 如果需要自定义析构函数，通常也需要拷贝构造和拷贝赋值" << endl;
    cout << "   - C++11添加了移动构造和移动赋值" << endl;
    cout << "   - 考虑使用=default和=delete" << endl;
    
    cout << "\n4. RAII原则:" << endl;
    cout << "   - 资源获取即初始化" << endl;
    cout << "   - 构造函数获取资源" << endl;
    cout << "   - 析构函数释放资源" << endl;
    cout << "   - 异常安全保证" << endl;
    
    cout << "\n5. 性能考虑:" << endl;
    cout << "   - 使用移动语义避免不必要的拷贝" << endl;
    cout << "   - 合理使用初始化列表" << endl;
    cout << "   - 考虑对象池和内存池" << endl;
    cout << "   - 避免虚函数调用开销" << endl;
    
    cout << "\n最终状态 - 对象数: " << ObjectCounter::getObjectCount() 
         << ", 总创建数: " << ObjectCounter::getTotalCreated() << endl;
    
    print_separator("构造函数和析构函数详解完成");
    
    return 0;
} 