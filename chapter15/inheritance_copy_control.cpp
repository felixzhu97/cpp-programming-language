/**
 * @file inheritance_copy_control.cpp
 * @brief 继承中的拷贝控制演示 - 派生类的拷贝构造、赋值、析构
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>

// 基类 - 资源管理示例
class Resource {
protected:
    std::string name;
    int* data;
    size_t size;
    
public:
    Resource(const std::string& n, size_t s) 
        : name(n), size(s), data(new int[s]) {
        std::cout << "Resource 构造: " << name << " (size=" << size << ")\n";
        for (size_t i = 0; i < size; ++i) {
            data[i] = static_cast<int>(i);
        }
    }
    
    // 拷贝构造函数
    Resource(const Resource& other) 
        : name(other.name + "_copy"), size(other.size), data(new int[size]) {
        std::cout << "Resource 拷贝构造: " << name << "\n";
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    
    // 拷贝赋值运算符
    Resource& operator=(const Resource& other) {
        std::cout << "Resource 拷贝赋值: " << name << " = " << other.name << "\n";
        if (this != &other) {
            // 释放当前资源
            delete[] data;
            
            // 拷贝新资源
            name = other.name + "_assigned";
            size = other.size;
            data = new int[size];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    // 移动构造函数
    Resource(Resource&& other) noexcept 
        : name(std::move(other.name)), size(other.size), data(other.data) {
        std::cout << "Resource 移动构造: " << name << "\n";
        other.data = nullptr;
        other.size = 0;
        other.name = "moved_from";
    }
    
    // 移动赋值运算符
    Resource& operator=(Resource&& other) noexcept {
        std::cout << "Resource 移动赋值: " << name << " = " << other.name << "\n";
        if (this != &other) {
            // 释放当前资源
            delete[] data;
            
            // 移动新资源
            name = std::move(other.name);
            size = other.size;
            data = other.data;
            
            // 清空源对象
            other.data = nullptr;
            other.size = 0;
            other.name = "moved_from";
        }
        return *this;
    }
    
    // 虚析构函数
    virtual ~Resource() {
        std::cout << "Resource 析构: " << name << "\n";
        delete[] data;
    }
    
    // 访问器
    const std::string& get_name() const { return name; }
    size_t get_size() const { return size; }
    
    virtual void display() const {
        std::cout << "Resource: " << name << ", size: " << size;
        if (data) {
            std::cout << ", data: [";
            for (size_t i = 0; i < std::min(size, size_t(3)); ++i) {
                std::cout << data[i];
                if (i < std::min(size, size_t(3)) - 1) std::cout << ", ";
            }
            if (size > 3) std::cout << "...";
            std::cout << "]";
        } else {
            std::cout << ", data: null";
        }
        std::cout << "\n";
    }
    
    virtual Resource* clone() const {
        return new Resource(*this);
    }
};

// 派生类 - 额外的资源管理
class ExtendedResource : public Resource {
private:
    std::string* metadata;
    size_t metadata_count;
    
public:
    ExtendedResource(const std::string& n, size_t s, size_t meta_count) 
        : Resource(n, s), metadata_count(meta_count), 
          metadata(new std::string[meta_count]) {
        std::cout << "ExtendedResource 构造: " << name << "\n";
        for (size_t i = 0; i < metadata_count; ++i) {
            metadata[i] = "meta_" + std::to_string(i);
        }
    }
    
    // 拷贝构造函数
    ExtendedResource(const ExtendedResource& other) 
        : Resource(other), metadata_count(other.metadata_count),
          metadata(new std::string[metadata_count]) {
        std::cout << "ExtendedResource 拷贝构造: " << name << "\n";
        for (size_t i = 0; i < metadata_count; ++i) {
            metadata[i] = other.metadata[i];
        }
    }
    
    // 拷贝赋值运算符
    ExtendedResource& operator=(const ExtendedResource& other) {
        std::cout << "ExtendedResource 拷贝赋值: " << name << " = " << other.name << "\n";
        if (this != &other) {
            // 先调用基类的赋值运算符
            Resource::operator=(other);
            
            // 处理派生类的资源
            delete[] metadata;
            metadata_count = other.metadata_count;
            metadata = new std::string[metadata_count];
            for (size_t i = 0; i < metadata_count; ++i) {
                metadata[i] = other.metadata[i];
            }
        }
        return *this;
    }
    
    // 移动构造函数
    ExtendedResource(ExtendedResource&& other) noexcept 
        : Resource(std::move(other)), 
          metadata_count(other.metadata_count), 
          metadata(other.metadata) {
        std::cout << "ExtendedResource 移动构造: " << name << "\n";
        other.metadata = nullptr;
        other.metadata_count = 0;
    }
    
    // 移动赋值运算符
    ExtendedResource& operator=(ExtendedResource&& other) noexcept {
        std::cout << "ExtendedResource 移动赋值: " << name << " = " << other.name << "\n";
        if (this != &other) {
            // 先调用基类的移动赋值
            Resource::operator=(std::move(other));
            
            // 处理派生类的资源
            delete[] metadata;
            metadata_count = other.metadata_count;
            metadata = other.metadata;
            
            other.metadata = nullptr;
            other.metadata_count = 0;
        }
        return *this;
    }
    
    // 虚析构函数
    ~ExtendedResource() override {
        std::cout << "ExtendedResource 析构: " << name << "\n";
        delete[] metadata;
    }
    
    void display() const override {
        Resource::display();
        std::cout << "  Metadata count: " << metadata_count;
        if (metadata && metadata_count > 0) {
            std::cout << ", metadata: [";
            for (size_t i = 0; i < std::min(metadata_count, size_t(2)); ++i) {
                std::cout << metadata[i];
                if (i < std::min(metadata_count, size_t(2)) - 1) std::cout << ", ";
            }
            if (metadata_count > 2) std::cout << "...";
            std::cout << "]";
        }
        std::cout << "\n";
    }
    
    Resource* clone() const override {
        return new ExtendedResource(*this);
    }
    
    size_t get_metadata_count() const { return metadata_count; }
};

// 有问题的派生类 - 演示常见错误
class ProblematicDerived : public Resource {
private:
    FILE* file_handle;  // 需要特殊处理的资源
    
public:
    ProblematicDerived(const std::string& n, size_t s, const std::string& filename)
        : Resource(n, s) {
        file_handle = fopen(filename.c_str(), "w");
        std::cout << "ProblematicDerived 构造: " << name << "\n";
    }
    
    // 错误：没有正确实现拷贝控制
    // 默认拷贝构造和赋值会导致双重释放
    
    ~ProblematicDerived() override {
        std::cout << "ProblematicDerived 析构: " << name << "\n";
        if (file_handle) {
            fclose(file_handle);
        }
    }
    
    void display() const override {
        Resource::display();
        std::cout << "  File handle: " << (file_handle ? "open" : "closed") << "\n";
    }
};

// 正确的派生类 - 处理特殊资源
class CorrectDerived : public Resource {
private:
    std::unique_ptr<FILE, decltype(&fclose)> file_handle;
    
public:
    CorrectDerived(const std::string& n, size_t s, const std::string& filename)
        : Resource(n, s), file_handle(nullptr, &fclose) {
        FILE* f = fopen(filename.c_str(), "w");
        file_handle.reset(f);
        std::cout << "CorrectDerived 构造: " << name << "\n";
    }
    
    // 正确实现拷贝控制
    CorrectDerived(const CorrectDerived& other) 
        : Resource(other), file_handle(nullptr, &fclose) {
        std::cout << "CorrectDerived 拷贝构造: " << name << "\n";
        // 文件句柄不能简单拷贝，这里创建新文件
        std::string new_filename = other.name + "_copy.txt";
        FILE* f = fopen(new_filename.c_str(), "w");
        file_handle.reset(f);
    }
    
    CorrectDerived& operator=(const CorrectDerived& other) {
        std::cout << "CorrectDerived 拷贝赋值: " << name << " = " << other.name << "\n";
        if (this != &other) {
            Resource::operator=(other);
            
            // 重新打开文件
            file_handle.reset();
            std::string new_filename = other.name + "_assigned.txt";
            FILE* f = fopen(new_filename.c_str(), "w");
            file_handle.reset(f);
        }
        return *this;
    }
    
    // 移动语义
    CorrectDerived(CorrectDerived&& other) noexcept 
        : Resource(std::move(other)), file_handle(std::move(other.file_handle)) {
        std::cout << "CorrectDerived 移动构造: " << name << "\n";
    }
    
    CorrectDerived& operator=(CorrectDerived&& other) noexcept {
        std::cout << "CorrectDerived 移动赋值: " << name << " = " << other.name << "\n";
        if (this != &other) {
            Resource::operator=(std::move(other));
            file_handle = std::move(other.file_handle);
        }
        return *this;
    }
    
    ~CorrectDerived() override {
        std::cout << "CorrectDerived 析构: " << name << "\n";
        // unique_ptr 自动处理文件关闭
    }
    
    void display() const override {
        Resource::display();
        std::cout << "  File handle: " << (file_handle ? "open" : "closed") << "\n";
    }
    
    Resource* clone() const override {
        return new CorrectDerived(*this);
    }
};

void demonstrate_basic_copy_control() {
    std::cout << "\n=== 基础拷贝控制演示 ===\n";
    
    std::cout << "\n--- 创建原始对象 ---\n";
    Resource original("original", 5);
    
    std::cout << "\n--- 拷贝构造 ---\n";
    Resource copy_constructed(original);
    
    std::cout << "\n--- 拷贝赋值 ---\n";
    Resource copy_assigned("target", 3);
    copy_assigned = original;
    
    std::cout << "\n--- 移动构造 ---\n";
    Resource move_constructed(std::move(Resource("temp", 4)));
    
    std::cout << "\n--- 移动赋值 ---\n";
    Resource move_assigned("target2", 2);
    move_assigned = Resource("temp2", 6);
    
    std::cout << "\n--- 显示对象状态 ---\n";
    original.display();
    copy_constructed.display();
    copy_assigned.display();
    move_constructed.display();
    move_assigned.display();
}

void demonstrate_derived_copy_control() {
    std::cout << "\n=== 派生类拷贝控制演示 ===\n";
    
    std::cout << "\n--- 创建派生类对象 ---\n";
    ExtendedResource ext_original("ext_original", 3, 4);
    
    std::cout << "\n--- 派生类拷贝构造 ---\n";
    ExtendedResource ext_copy(ext_original);
    
    std::cout << "\n--- 派生类拷贝赋值 ---\n";
    ExtendedResource ext_target("ext_target", 2, 2);
    ext_target = ext_original;
    
    std::cout << "\n--- 派生类移动构造 ---\n";
    ExtendedResource ext_moved(std::move(ExtendedResource("temp_ext", 5, 3)));
    
    std::cout << "\n--- 显示对象状态 ---\n";
    ext_original.display();
    ext_copy.display();
    ext_target.display();
    ext_moved.display();
}

void demonstrate_polymorphic_copy() {
    std::cout << "\n=== 多态拷贝演示 ===\n";
    
    std::vector<std::unique_ptr<Resource>> resources;
    
    // 创建不同类型的对象
    resources.push_back(std::make_unique<Resource>("poly_base", 3));
    resources.push_back(std::make_unique<ExtendedResource>("poly_ext", 4, 2));
    resources.push_back(std::make_unique<CorrectDerived>("poly_correct", 2, "test.txt"));
    
    std::cout << "\n--- 原始对象 ---\n";
    for (const auto& res : resources) {
        res->display();
    }
    
    std::cout << "\n--- 多态克隆 ---\n";
    std::vector<std::unique_ptr<Resource>> cloned_resources;
    for (const auto& res : resources) {
        cloned_resources.emplace_back(res->clone());
    }
    
    std::cout << "\n--- 克隆对象 ---\n";
    for (const auto& res : cloned_resources) {
        res->display();
    }
}

void demonstrate_slicing_problem() {
    std::cout << "\n=== 切片问题演示 ===\n";
    
    ExtendedResource extended("slicing_test", 3, 2);
    extended.display();
    
    std::cout << "\n--- 切片赋值 ---\n";
    Resource base("base", 1);
    base = extended;  // 切片：只拷贝基类部分
    base.display();
    
    std::cout << "\n--- 正确的多态拷贝 ---\n";
    std::unique_ptr<Resource> poly_ptr = std::make_unique<ExtendedResource>("poly_test", 2, 3);
    std::unique_ptr<Resource> poly_copy(poly_ptr->clone());
    poly_copy->display();
}

void demonstrate_virtual_destructor_importance() {
    std::cout << "\n=== 虚析构函数重要性演示 ===\n";
    
    std::cout << "\n--- 正确的虚析构 ---\n";
    {
        std::unique_ptr<Resource> ptr = std::make_unique<ExtendedResource>("virtual_test", 2, 2);
        // 正确调用派生类和基类的析构函数
    }
    
    std::cout << "\n虚析构函数确保了正确的析构顺序\n";
}

void demonstrate_move_semantics_inheritance() {
    std::cout << "\n=== 继承中的移动语义演示 ===\n";
    
    std::cout << "\n--- 创建临时对象 ---\n";
    auto create_extended = [](const std::string& name) {
        return ExtendedResource(name, 4, 3);
    };
    
    std::cout << "\n--- 移动构造 ---\n";
    ExtendedResource moved_obj = create_extended("moved");
    moved_obj.display();
    
    std::cout << "\n--- 移动赋值 ---\n";
    ExtendedResource target("target", 1, 1);
    target = create_extended("assigned");
    target.display();
    
    std::cout << "\n--- 容器中的移动 ---\n";
    std::vector<ExtendedResource> container;
    container.emplace_back("emplace1", 2, 2);
    container.push_back(create_extended("push"));
    
    std::cout << "容器大小: " << container.size() << "\n";
    for (const auto& item : container) {
        item.display();
    }
}

void demonstrate_copy_control_guidelines() {
    std::cout << "\n=== 拷贝控制指导原则 ===\n";
    
    std::cout << "1. 三/五法则:\n";
    std::cout << "   - 如果需要自定义析构函数，通常也需要拷贝构造和拷贝赋值\n";
    std::cout << "   - C++11: 如果需要任何一个，考虑是否需要移动语义\n";
    
    std::cout << "\n2. 继承中的拷贝控制:\n";
    std::cout << "   - 派生类的拷贝控制必须调用基类的对应函数\n";
    std::cout << "   - 基类析构函数应该是虚函数\n";
    std::cout << "   - 考虑使用 =default 和 =delete\n";
    
    std::cout << "\n3. 多态拷贝:\n";
    std::cout << "   - 提供虚拷贝函数（clone）\n";
    std::cout << "   - 避免切片问题\n";
    std::cout << "   - 使用智能指针管理多态对象\n";
    
    std::cout << "\n4. 移动语义:\n";
    std::cout << "   - 移动构造和移动赋值应该是 noexcept\n";
    std::cout << "   - 移动后对象应处于有效但未指定状态\n";
    std::cout << "   - 在派生类中正确转发移动操作\n";
}

int main() {
    std::cout << "C++ Primer Chapter 15: 继承中的拷贝控制演示\n";
    std::cout << "=========================================\n";
    
    try {
        demonstrate_basic_copy_control();
        demonstrate_derived_copy_control();
        demonstrate_polymorphic_copy();
        demonstrate_slicing_problem();
        demonstrate_virtual_destructor_importance();
        demonstrate_move_semantics_inheritance();
        demonstrate_copy_control_guidelines();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 