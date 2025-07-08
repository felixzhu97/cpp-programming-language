/**
 * @file smart_pointers.cpp
 * @brief 智能指针演示 - unique_ptr、shared_ptr、weak_ptr 的使用
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// 简单的资源类
class Resource {
private:
    std::string name;
    static int count;
    
public:
    Resource(const std::string& n) : name(n) {
        ++count;
        std::cout << "创建资源: " << name << " (总数: " << count << ")\n";
    }
    
    ~Resource() {
        --count;
        std::cout << "销毁资源: " << name << " (剩余: " << count << ")\n";
    }
    
    void use() const {
        std::cout << "使用资源: " << name << "\n";
    }
    
    const std::string& get_name() const { return name; }
};

int Resource::count = 0;

void demonstrate_unique_ptr() {
    std::cout << "\n=== unique_ptr 演示 ===\n";
    
    // 1. 创建 unique_ptr
    std::unique_ptr<Resource> ptr1 = std::make_unique<Resource>("资源1");
    ptr1->use();
    
    // 2. 移动语义
    std::unique_ptr<Resource> ptr2 = std::move(ptr1);
    std::cout << "移动后 ptr1 是否为空: " << (ptr1 == nullptr ? "是" : "否") << "\n";
    ptr2->use();
    
    // 3. 重置指针
    ptr2.reset(new Resource("资源2"));
    ptr2->use();
    
    // 4. 释放所有权
    Resource* raw_ptr = ptr2.release();
    std::cout << "释放后 ptr2 是否为空: " << (ptr2 == nullptr ? "是" : "否") << "\n";
    raw_ptr->use();
    delete raw_ptr; // 手动删除
    
    std::cout << "unique_ptr 演示结束\n";
}

void demonstrate_shared_ptr() {
    std::cout << "\n=== shared_ptr 演示 ===\n";
    
    // 1. 创建 shared_ptr
    std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>("共享资源");
    std::cout << "引用计数: " << ptr1.use_count() << "\n";
    
    // 2. 拷贝增加引用计数
    {
        std::shared_ptr<Resource> ptr2 = ptr1;
        std::cout << "拷贝后引用计数: " << ptr1.use_count() << "\n";
        ptr2->use();
        
        std::vector<std::shared_ptr<Resource>> vec;
        vec.push_back(ptr1);
        vec.push_back(ptr2);
        std::cout << "存入容器后引用计数: " << ptr1.use_count() << "\n";
    } // ptr2 和 vec 销毁
    
    std::cout << "作用域结束后引用计数: " << ptr1.use_count() << "\n";
    ptr1->use();
    
    // 3. 重置引用
    ptr1.reset();
    std::cout << "重置后引用计数: " << ptr1.use_count() << "\n";
    
    std::cout << "shared_ptr 演示结束\n";
}

void demonstrate_weak_ptr() {
    std::cout << "\n=== weak_ptr 演示 ===\n";
    
    std::weak_ptr<Resource> weak_ptr;
    
    {
        std::shared_ptr<Resource> shared_ptr = std::make_shared<Resource>("弱引用资源");
        weak_ptr = shared_ptr;
        
        std::cout << "shared_ptr 引用计数: " << shared_ptr.use_count() << "\n";
        std::cout << "weak_ptr 是否过期: " << (weak_ptr.expired() ? "是" : "否") << "\n";
        
        // 从 weak_ptr 获取 shared_ptr
        if (auto locked_ptr = weak_ptr.lock()) {
            locked_ptr->use();
            std::cout << "通过 weak_ptr 访问，引用计数: " << locked_ptr.use_count() << "\n";
        }
    } // shared_ptr 销毁
    
    std::cout << "shared_ptr 销毁后 weak_ptr 是否过期: " << (weak_ptr.expired() ? "是" : "否") << "\n";
    
    if (auto locked_ptr = weak_ptr.lock()) {
        locked_ptr->use();
    } else {
        std::cout << "weak_ptr 已过期，无法访问资源\n";
    }
    
    std::cout << "weak_ptr 演示结束\n";
}

// 循环引用问题演示
struct Node {
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> parent; // 使用 weak_ptr 避免循环引用
    
    Node(const std::string& n) : name(n) {
        std::cout << "创建节点: " << name << "\n";
    }
    
    ~Node() {
        std::cout << "销毁节点: " << name << "\n";
    }
};

void demonstrate_circular_reference() {
    std::cout << "\n=== 循环引用问题演示 ===\n";
    
    {
        std::shared_ptr<Node> parent = std::make_shared<Node>("父节点");
        std::shared_ptr<Node> child = std::make_shared<Node>("子节点");
        
        parent->next = child;
        child->parent = parent; // 使用 weak_ptr，避免循环引用
        
        std::cout << "父节点引用计数: " << parent.use_count() << "\n";
        std::cout << "子节点引用计数: " << child.use_count() << "\n";
        
        // 访问父节点
        if (auto p = child->parent.lock()) {
            std::cout << "子节点的父节点: " << p->name << "\n";
        }
    } // 所有 shared_ptr 离开作用域
    
    std::cout << "作用域结束，观察析构函数调用\n";
}

void demonstrate_smart_pointer_best_practices() {
    std::cout << "\n=== 智能指针最佳实践 ===\n";
    
    // 1. 优先使用 make_unique 和 make_shared
    auto resource1 = std::make_unique<Resource>("最佳实践1");
    auto resource2 = std::make_shared<Resource>("最佳实践2");
    
    // 2. 工厂函数
    auto create_resource = [](const std::string& name) -> std::unique_ptr<Resource> {
        return std::make_unique<Resource>(name);
    };
    
    auto factory_resource = create_resource("工厂创建");
    factory_resource->use();
    
    // 3. 容器中使用智能指针
    std::vector<std::unique_ptr<Resource>> resources;
    resources.push_back(std::make_unique<Resource>("容器资源1"));
    resources.push_back(std::make_unique<Resource>("容器资源2"));
    resources.push_back(std::make_unique<Resource>("容器资源3"));
    
    std::cout << "容器中有 " << resources.size() << " 个资源\n";
    for (const auto& res : resources) {
        res->use();
    }
    
    // 4. 自定义删除器
    auto custom_deleter = [](Resource* ptr) {
        std::cout << "自定义删除器删除: " << ptr->get_name() << "\n";
        delete ptr;
    };
    
    std::unique_ptr<Resource, decltype(custom_deleter)> custom_ptr(
        new Resource("自定义删除"), custom_deleter);
    
    std::cout << "智能指针最佳实践演示结束\n";
}

int main() {
    std::cout << "C++ Primer Chapter 12: 智能指针演示\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_unique_ptr();
        demonstrate_shared_ptr();
        demonstrate_weak_ptr();
        demonstrate_circular_reference();
        demonstrate_smart_pointer_best_practices();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 