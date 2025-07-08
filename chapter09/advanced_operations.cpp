/**
 * @file advanced_operations.cpp
 * @brief 容器高级操作 - 比较、交换、分配器、异常安全、移动语义
 */

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include <chrono>

void demonstrate_container_comparison() {
    std::cout << "\n=== 容器比较操作 ===\n";
    
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};
    std::vector<int> v3{1, 2, 4};
    std::vector<int> v4{1, 2};
    
    std::cout << "v1: {1, 2, 3}\n";
    std::cout << "v2: {1, 2, 3}\n";
    std::cout << "v3: {1, 2, 4}\n";
    std::cout << "v4: {1, 2}\n\n";
    
    // 相等比较
    std::cout << "相等比较:\n";
    std::cout << "v1 == v2: " << std::boolalpha << (v1 == v2) << "\n";
    std::cout << "v1 == v3: " << (v1 == v3) << "\n";
    std::cout << "v1 != v3: " << (v1 != v3) << "\n";
    
    // 字典序比较
    std::cout << "\n字典序比较:\n";
    std::cout << "v1 < v3: " << (v1 < v3) << "\n";
    std::cout << "v1 > v4: " << (v1 > v4) << "\n";
    std::cout << "v4 < v1: " << (v4 < v1) << "\n";
    
    // 自定义比较
    std::cout << "\n自定义元素比较:\n";
    struct Person {
        std::string name;
        int age;
        
        bool operator==(const Person& other) const {
            return name == other.name && age == other.age;
        }
        
        bool operator<(const Person& other) const {
            if (name != other.name) return name < other.name;
            return age < other.age;
        }
    };
    
    std::vector<Person> people1{{"Alice", 25}, {"Bob", 30}};
    std::vector<Person> people2{{"Alice", 25}, {"Bob", 30}};
    std::vector<Person> people3{{"Alice", 25}, {"Charlie", 28}};
    
    std::cout << "people1 == people2: " << (people1 == people2) << "\n";
    std::cout << "people1 < people3: " << (people1 < people3) << "\n";
}

void demonstrate_container_swap() {
    std::cout << "\n=== 容器交换操作 ===\n";
    
    std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{10, 20, 30};
    
    std::cout << "交换前:\n";
    std::cout << "v1 size: " << v1.size() << ", capacity: " << v1.capacity() << "\n";
    std::cout << "v2 size: " << v2.size() << ", capacity: " << v2.capacity() << "\n";
    
    // 记录交换前的数据指针
    auto v1_data = v1.data();
    auto v2_data = v2.data();
    
    // 使用成员函数 swap
    v1.swap(v2);
    
    std::cout << "\n交换后:\n";
    std::cout << "v1 size: " << v1.size() << ", capacity: " << v1.capacity() << "\n";
    std::cout << "v2 size: " << v2.size() << ", capacity: " << v2.capacity() << "\n";
    
    // 验证指针交换
    std::cout << "\n指针交换验证:\n";
    std::cout << "v1 新数据指针 == v2 原数据指针: " << (v1.data() == v2_data) << "\n";
    std::cout << "v2 新数据指针 == v1 原数据指针: " << (v2.data() == v1_data) << "\n";
    
    // 使用算法 swap
    std::cout << "\n使用 std::swap:\n";
    std::swap(v1, v2);
    std::cout << "再次交换后 v1 size: " << v1.size() << "\n";
    
    // swap 的性能特性
    std::cout << "\nswap 性能测试:\n";
    
    const int N = 1000000;
    std::vector<int> large1(N, 1);
    std::vector<int> large2(N, 2);
    
    auto start = std::chrono::high_resolution_clock::now();
    large1.swap(large2);
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "交换 " << N << " 个元素的 vector: " << duration.count() << " μs\n";
    std::cout << "swap 是 O(1) 操作，只交换控制信息\n";
}

void demonstrate_allocators() {
    std::cout << "\n=== 分配器 ===\n";
    
    // 默认分配器
    std::cout << "默认分配器信息:\n";
    std::allocator<int> alloc;
    std::cout << "max_size(): " << alloc.max_size() << "\n";
    
    // 使用分配器手动管理内存
    std::cout << "\n手动内存管理:\n";
    int* ptr = alloc.allocate(5);  // 分配5个int的空间
    
    // 构造对象
    for (int i = 0; i < 5; ++i) {
        alloc.construct(ptr + i, i + 1);
    }
    
    std::cout << "构造的对象: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << ptr[i] << " ";
    }
    std::cout << "\n";
    
    // 销毁对象
    for (int i = 0; i < 5; ++i) {
        alloc.destroy(ptr + i);
    }
    
    // 释放内存
    alloc.deallocate(ptr, 5);
    std::cout << "已清理内存\n";
    
    // 自定义分配器示例
    std::cout << "\n自定义分配器:\n";
    
    template<typename T>
    class TrackingAllocator {
    public:
        using value_type = T;
        static size_t allocations;
        static size_t deallocations;
        static size_t bytes_allocated;
        
        TrackingAllocator() = default;
        template<typename U> TrackingAllocator(const TrackingAllocator<U>&) {}
        
        T* allocate(size_t n) {
            allocations++;
            bytes_allocated += n * sizeof(T);
            std::cout << "   分配 " << n << " 个 " << typeid(T).name() 
                      << " (" << n * sizeof(T) << " bytes)\n";
            return static_cast<T*>(std::malloc(n * sizeof(T)));
        }
        
        void deallocate(T* p, size_t n) {
            deallocations++;
            std::cout << "   释放 " << n << " 个 " << typeid(T).name() 
                      << " (" << n * sizeof(T) << " bytes)\n";
            std::free(p);
        }
        
        template<typename U>
        bool operator==(const TrackingAllocator<U>&) const { return true; }
    };
    
    template<typename T>
    size_t TrackingAllocator<T>::allocations = 0;
    template<typename T>
    size_t TrackingAllocator<T>::deallocations = 0;
    template<typename T>
    size_t TrackingAllocator<T>::bytes_allocated = 0;
    
    {
        std::vector<int, TrackingAllocator<int>> tracked_vector;
        
        for (int i = 0; i < 10; ++i) {
            tracked_vector.push_back(i);
        }
        
        std::cout << "   分配次数: " << TrackingAllocator<int>::allocations << "\n";
        std::cout << "   总分配字节: " << TrackingAllocator<int>::bytes_allocated << "\n";
    }
    
    std::cout << "   释放次数: " << TrackingAllocator<int>::deallocations << "\n";
}

void demonstrate_exception_safety() {
    std::cout << "\n=== 异常安全性 ===\n";
    
    // 异常安全的资源类
    class ExceptionTest {
    private:
        int* data;
        size_t size;
        static int construction_count;
        
    public:
        ExceptionTest(size_t n) : data(new int[n]), size(n) {
            construction_count++;
            std::cout << "   构造 ExceptionTest #" << construction_count 
                      << ", size=" << size << "\n";
            
            // 模拟构造失败
            if (construction_count % 4 == 0) {
                delete[] data;
                throw std::runtime_error("构造失败");
            }
            
            for (size_t i = 0; i < size; ++i) {
                data[i] = static_cast<int>(i);
            }
        }
        
        ~ExceptionTest() {
            std::cout << "   析构 ExceptionTest, size=" << size << "\n";
            delete[] data;
        }
        
        // 拷贝构造
        ExceptionTest(const ExceptionTest& other) : data(new int[other.size]), size(other.size) {
            construction_count++;
            std::cout << "   拷贝构造 ExceptionTest #" << construction_count << "\n";
            
            if (construction_count % 4 == 0) {
                delete[] data;
                throw std::runtime_error("拷贝构造失败");
            }
            
            std::copy(other.data, other.data + size, data);
        }
        
        // 移动构造 (noexcept)
        ExceptionTest(ExceptionTest&& other) noexcept 
            : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
            std::cout << "   移动构造 ExceptionTest\n";
        }
        
        int get_value(size_t index) const {
            return (index < size) ? data[index] : 0;
        }
    };
    
    int ExceptionTest::construction_count = 0;
    
    std::cout << "强异常安全测试:\n";
    
    std::vector<ExceptionTest> safe_vector;
    safe_vector.reserve(5);  // 避免重新分配
    
    for (int i = 1; i <= 6; ++i) {
        try {
            safe_vector.emplace_back(i);
            std::cout << "   成功添加元素 " << i << ", vector size: " 
                      << safe_vector.size() << "\n";
        } catch (const std::exception& e) {
            std::cout << "   异常: " << e.what() 
                      << ", vector size: " << safe_vector.size() << "\n";
            std::cout << "   容器保持一致状态\n";
        }
    }
    
    // 测试 vector 的异常安全保证
    std::cout << "\nvector 扩容异常安全:\n";
    
    std::vector<ExceptionTest> growth_vector;
    
    try {
        // 这会触发多次扩容
        for (int i = 1; i <= 10; ++i) {
            growth_vector.emplace_back(i);
        }
    } catch (const std::exception& e) {
        std::cout << "   扩容时发生异常: " << e.what() << "\n";
        std::cout << "   当前 vector size: " << growth_vector.size() << "\n";
    }
}

void demonstrate_move_semantics() {
    std::cout << "\n=== 移动语义 ===\n";
    
    // 移动感知的类
    class MovableResource {
    private:
        std::unique_ptr<int[]> data;
        size_t size;
        
    public:
        MovableResource(size_t n) : data(std::make_unique<int[]>(n)), size(n) {
            std::cout << "   构造 MovableResource, size=" << size 
                      << ", data=" << data.get() << "\n";
            for (size_t i = 0; i < size; ++i) {
                data[i] = static_cast<int>(i);
            }
        }
        
        ~MovableResource() {
            std::cout << "   析构 MovableResource, size=" << size 
                      << ", data=" << data.get() << "\n";
        }
        
        // 拷贝构造
        MovableResource(const MovableResource& other) 
            : data(std::make_unique<int[]>(other.size)), size(other.size) {
            std::cout << "   拷贝构造 MovableResource\n";
            std::copy(other.data.get(), other.data.get() + size, data.get());
        }
        
        // 移动构造
        MovableResource(MovableResource&& other) noexcept 
            : data(std::move(other.data)), size(other.size) {
            other.size = 0;
            std::cout << "   移动构造 MovableResource\n";
        }
        
        // 拷贝赋值
        MovableResource& operator=(const MovableResource& other) {
            if (this != &other) {
                std::cout << "   拷贝赋值 MovableResource\n";
                data = std::make_unique<int[]>(other.size);
                size = other.size;
                std::copy(other.data.get(), other.data.get() + size, data.get());
            }
            return *this;
        }
        
        // 移动赋值
        MovableResource& operator=(MovableResource&& other) noexcept {
            if (this != &other) {
                std::cout << "   移动赋值 MovableResource\n";
                data = std::move(other.data);
                size = other.size;
                other.size = 0;
            }
            return *this;
        }
        
        size_t get_size() const { return size; }
        int get_value(size_t index) const {
            return (data && index < size) ? data[index] : -1;
        }
    };
    
    std::cout << "移动语义测试:\n";
    
    std::vector<MovableResource> resources;
    
    // push_back vs emplace_back
    std::cout << "\npush_back 临时对象:\n";
    resources.push_back(MovableResource(3));
    
    std::cout << "\nemplace_back 原地构造:\n";
    resources.emplace_back(4);
    
    // 移动现有对象
    std::cout << "\n移动现有对象:\n";
    MovableResource resource(5);
    resources.push_back(std::move(resource));
    std::cout << "移动后原对象 size: " << resource.get_size() << "\n";
    
    // 容器的移动
    std::cout << "\n容器移动:\n";
    auto moved_vector = std::move(resources);
    std::cout << "移动后原容器 size: " << resources.size() << "\n";
    std::cout << "移动后新容器 size: " << moved_vector.size() << "\n";
    
    // 性能对比
    std::cout << "\n性能对比:\n";
    
    const int N = 10000;
    
    auto measure_time = [](auto func, const std::string& desc) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "   " << desc << ": " << duration.count() << " μs\n";
        return duration.count();
    };
    
    // 创建大量字符串进行测试
    std::vector<std::string> source_strings;
    for (int i = 0; i < N; ++i) {
        source_strings.push_back("String number " + std::to_string(i));
    }
    
    auto copy_time = measure_time([&]() {
        std::vector<std::string> copy_vector;
        copy_vector.reserve(N);
        for (const auto& str : source_strings) {
            copy_vector.push_back(str);  // 拷贝
        }
    }, "拷贝构造");
    
    auto move_time = measure_time([&]() {
        std::vector<std::string> move_vector;
        move_vector.reserve(N);
        for (auto& str : source_strings) {
            move_vector.push_back(std::move(str));  // 移动
        }
    }, "移动构造");
    
    std::cout << "移动比拷贝快: " << static_cast<double>(copy_time) / move_time << "x\n";
}

int main() {
    std::cout << "C++ Primer Chapter 9: 容器高级操作\n";
    std::cout << "=================================\n";
    
    demonstrate_container_comparison();
    demonstrate_container_swap();
    demonstrate_allocators();
    demonstrate_exception_safety();
    demonstrate_move_semantics();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 