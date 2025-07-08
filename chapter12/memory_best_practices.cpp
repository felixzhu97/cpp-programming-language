/**
 * @file memory_best_practices.cpp
 * @brief 内存管理最佳实践 - RAII、异常安全、自定义分配器
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>

int main() {
    std::cout << "C++ Primer Chapter 12: 内存管理最佳实践\n";
    std::cout << "=====================================\n";
    
    std::cout << "\n=== RAII 原则 ===\n";
    std::cout << "资源获取即初始化（RAII）:\n";
    std::cout << "- 构造函数中获取资源\n";
    std::cout << "- 析构函数中释放资源\n";
    std::cout << "- 利用对象生命周期管理资源\n";
    
    class RAIIExample {
    private:
        std::string resource_name;
        
    public:
        RAIIExample(const std::string& name) : resource_name(name) {
            std::cout << "获取资源: " << resource_name << "\n";
        }
        
        ~RAIIExample() {
            std::cout << "释放资源: " << resource_name << "\n";
        }
        
        void use() {
            std::cout << "使用资源: " << resource_name << "\n";
        }
    };
    
    {
        RAIIExample resource("文件句柄");
        resource.use();
        // 离开作用域时自动释放
    }
    
    std::cout << "\n=== 智能指针最佳实践 ===\n";
    
    // 1. 优先使用 make_unique/make_shared
    auto ptr1 = std::make_unique<int>(42);
    auto ptr2 = std::make_shared<std::string>("Hello");
    
    std::cout << "make_unique: " << *ptr1 << "\n";
    std::cout << "make_shared: " << *ptr2 << "\n";
    
    // 2. 使用 unique_ptr 作为默认选择
    std::vector<std::unique_ptr<RAIIExample>> resources;
    resources.push_back(std::make_unique<RAIIExample>("资源1"));
    resources.push_back(std::make_unique<RAIIExample>("资源2"));
    
    std::cout << "\n容器中的智能指针:\n";
    for (auto& res : resources) {
        res->use();
    }
    
    std::cout << "\n=== 异常安全保证 ===\n";
    std::cout << "1. 基本保证：异常时程序处于有效状态\n";
    std::cout << "2. 强保证：异常时状态回滚\n";
    std::cout << "3. 无抛出保证：保证不抛异常\n";
    
    try {
        std::vector<std::unique_ptr<RAIIExample>> safe_resources;
        safe_resources.push_back(std::make_unique<RAIIExample>("安全资源1"));
        safe_resources.push_back(std::make_unique<RAIIExample>("安全资源2"));
        
        // 即使这里抛异常，智能指针也会自动清理
        // throw std::runtime_error("模拟异常");
        
        std::cout << "异常安全演示完成\n";
    } catch (const std::exception& e) {
        std::cout << "异常处理: " << e.what() << "\n";
    }
    
    std::cout << "\n=== 内存管理指导原则 ===\n";
    std::cout << "1. 优先使用自动内存管理（栈对象、智能指针）\n";
    std::cout << "2. 避免裸指针拥有资源\n";
    std::cout << "3. 遵循 RAII 原则\n";
    std::cout << "4. 使用现代 C++ 特性（智能指针、容器）\n";
    std::cout << "5. 注意异常安全\n";
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 