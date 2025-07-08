/**
 * @file dynamic_memory_basics.cpp
 * @brief 动态内存基础 - new/delete、内存泄露、野指针等问题
 */

#include <iostream>
#include <vector>
#include <memory>

void demonstrate_new_delete() {
    std::cout << "\n=== new/delete 基础 ===\n";
    
    // 1. 基本的 new/delete
    int* ptr = new int(42);
    std::cout << "动态分配的整数: " << *ptr << "\n";
    delete ptr;
    
    // 2. 数组的 new[]/delete[]
    int* arr = new int[5]{1, 2, 3, 4, 5};
    std::cout << "动态数组: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
    delete[] arr;
    
    // 3. 对象的动态分配
    class SimpleClass {
    public:
        int value;
        SimpleClass(int v) : value(v) {
            std::cout << "构造 SimpleClass(" << v << ")\n";
        }
        ~SimpleClass() {
            std::cout << "析构 SimpleClass(" << value << ")\n";
        }
    };
    
    SimpleClass* obj = new SimpleClass(100);
    std::cout << "对象值: " << obj->value << "\n";
    delete obj;
}

void demonstrate_memory_problems() {
    std::cout << "\n=== 内存问题演示 ===\n";
    
    // 1. 内存泄露示例（仅演示，不实际泄露）
    std::cout << "1. 内存泄露问题:\n";
    {
        int* leak_ptr = new int(999);
        std::cout << "分配内存，值: " << *leak_ptr << "\n";
        // 忘记 delete leak_ptr; - 这会造成内存泄露
        // 为了演示，我们这里删除它
        delete leak_ptr;
        std::cout << "   应该 delete，否则内存泄露\n";
    }
    
    // 2. 野指针问题
    std::cout << "\n2. 野指针问题:\n";
    int* dangling_ptr = new int(123);
    std::cout << "删除前值: " << *dangling_ptr << "\n";
    delete dangling_ptr;
    // dangling_ptr 现在是野指针，不应该使用
    dangling_ptr = nullptr; // 良好习惯：设为 nullptr
    std::cout << "   删除后应设置为 nullptr\n";
    
    // 3. 重复删除问题
    std::cout << "\n3. 重复删除问题:\n";
    int* ptr = new int(456);
    delete ptr;
    ptr = nullptr; // 避免重复删除
    // delete ptr; // 如果不设为 nullptr，这会导致未定义行为
    std::cout << "   设置为 nullptr 可避免重复删除\n";
    
    // 4. 数组删除问题
    std::cout << "\n4. 数组删除问题:\n";
    int* arr = new int[10];
    delete[] arr; // 正确：使用 delete[]
    // delete arr; // 错误：应该使用 delete[]
    std::cout << "   数组必须使用 delete[]\n";
}

void demonstrate_exception_safety() {
    std::cout << "\n=== 异常安全问题 ===\n";
    
    class ExceptionClass {
    public:
        ExceptionClass() {
            std::cout << "构造 ExceptionClass\n";
            // 模拟构造函数可能抛异常
            // throw std::runtime_error("构造失败");
        }
        ~ExceptionClass() {
            std::cout << "析构 ExceptionClass\n";
        }
    };
    
    // 不安全的代码示例
    std::cout << "不安全的异常处理:\n";
    try {
        ExceptionClass* obj1 = new ExceptionClass();
        ExceptionClass* obj2 = new ExceptionClass();
        
        // 如果这里抛异常，obj1 和 obj2 可能泄露
        // throw std::runtime_error("操作失败");
        
        delete obj1;
        delete obj2;
        std::cout << "   正常情况下能正确清理\n";
    } catch (const std::exception& e) {
        std::cout << "   异常情况下可能内存泄露\n";
    }
    
    // 安全的代码示例（使用智能指针）
    std::cout << "\n安全的异常处理（智能指针）:\n";
    try {
        std::unique_ptr<ExceptionClass> obj1 = std::make_unique<ExceptionClass>();
        std::unique_ptr<ExceptionClass> obj2 = std::make_unique<ExceptionClass>();
        
        // 即使这里抛异常，智能指针也会自动清理
        // throw std::runtime_error("操作失败");
        
        std::cout << "   智能指针确保异常安全\n";
    } catch (const std::exception& e) {
        std::cout << "   异常情况下智能指针自动清理\n";
    }
}

void demonstrate_best_practices() {
    std::cout << "\n=== 最佳实践 ===\n";
    
    // 1. 优先使用智能指针
    std::cout << "1. 使用智能指针替代裸指针:\n";
    {
        auto ptr = std::make_unique<int>(42);
        std::cout << "   智能指针值: " << *ptr << "\n";
        // 自动清理，无需手动 delete
    }
    
    // 2. 使用容器替代动态数组
    std::cout << "\n2. 使用容器替代动态数组:\n";
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        std::cout << "   vector 大小: " << vec.size() << "\n";
        // 自动管理内存
    }
    
    // 3. RAII 原则
    std::cout << "\n3. RAII 原则示例:\n";
    class RAIIResource {
    private:
        int* data;
        
    public:
        RAIIResource(size_t size) : data(new int[size]) {
            std::cout << "   RAII: 构造时分配资源\n";
        }
        
        ~RAIIResource() {
            delete[] data;
            std::cout << "   RAII: 析构时自动释放资源\n";
        }
        
        // 禁用拷贝，使用移动语义
        RAIIResource(const RAIIResource&) = delete;
        RAIIResource& operator=(const RAIIResource&) = delete;
        
        RAIIResource(RAIIResource&& other) noexcept : data(other.data) {
            other.data = nullptr;
        }
        
        RAIIResource& operator=(RAIIResource&& other) noexcept {
            if (this != &other) {
                delete[] data;
                data = other.data;
                other.data = nullptr;
            }
            return *this;
        }
    };
    
    {
        RAIIResource resource(10);
        // 离开作用域时自动清理
    }
}

int main() {
    std::cout << "C++ Primer Chapter 12: 动态内存基础\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_new_delete();
        demonstrate_memory_problems();
        demonstrate_exception_safety();
        demonstrate_best_practices();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 