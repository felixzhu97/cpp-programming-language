/**
 * @file advanced_memory.cpp
 * @brief 高级内存技术 - placement new、内存对齐、自定义分配器
 */

#include <iostream>
#include <memory>
#include <new>
#include <cstdlib>

// 简单内存池类
class SimpleMemoryPool {
private:
    static const size_t POOL_SIZE = 1024;
    char pool[POOL_SIZE];
    size_t next_free;
    
public:
    SimpleMemoryPool() : next_free(0) {
        std::cout << "内存池初始化，大小: " << POOL_SIZE << " 字节\n";
    }
    
    void* allocate(size_t size) {
        if (next_free + size > POOL_SIZE) {
            std::cout << "内存池空间不足\n";
            return nullptr;
        }
        
        void* ptr = pool + next_free;
        next_free += size;
        std::cout << "从内存池分配 " << size << " 字节，剩余: " 
                  << (POOL_SIZE - next_free) << " 字节\n";
        return ptr;
    }
    
    void reset() {
        next_free = 0;
        std::cout << "内存池重置\n";
    }
};

int main() {
    std::cout << "C++ Primer Chapter 12: 高级内存技术\n";
    std::cout << "=================================\n";
    
    std::cout << "\n=== placement new 演示 ===\n";
    
    // 预先分配内存缓冲区
    alignas(int) char buffer[sizeof(int) * 3];
    std::cout << "缓冲区地址: " << static_cast<void*>(buffer) << "\n";
    
    // 使用 placement new 在指定位置构造对象
    int* p1 = new(buffer) int(42);
    int* p2 = new(buffer + sizeof(int)) int(84);
    int* p3 = new(buffer + 2 * sizeof(int)) int(126);
    
    std::cout << "p1 地址: " << p1 << ", 值: " << *p1 << "\n";
    std::cout << "p2 地址: " << p2 << ", 值: " << *p2 << "\n";
    std::cout << "p3 地址: " << p3 << ", 值: " << *p3 << "\n";
    
    // 基本类型不需要显式调用析构函数
    // 对于有自定义析构函数的类，需要显式调用
    
    std::cout << "\n=== 内存对齐演示 ===\n";
    
    struct AlignedStruct {
        char c;
        int i;
        double d;
    };
    
    std::cout << "AlignedStruct 大小: " << sizeof(AlignedStruct) << "\n";
    std::cout << "char 对齐: " << alignof(char) << "\n";
    std::cout << "int 对齐: " << alignof(int) << "\n";
    std::cout << "double 对齐: " << alignof(double) << "\n";
    std::cout << "AlignedStruct 对齐: " << alignof(AlignedStruct) << "\n";
    
    // 强制对齐
    struct alignas(64) CacheLineAligned {
        int data[16];
    };
    
    std::cout << "CacheLineAligned 大小: " << sizeof(CacheLineAligned) << "\n";
    std::cout << "CacheLineAligned 对齐: " << alignof(CacheLineAligned) << "\n";
    
    std::cout << "\n=== 自定义分配器基础 ===\n";
    
    class SimpleAllocator {
    public:
        static void* allocate(size_t size) {
            std::cout << "自定义分配器分配 " << size << " 字节\n";
            return std::malloc(size);
        }
        
        static void deallocate(void* ptr) {
            std::cout << "自定义分配器释放内存\n";
            std::free(ptr);
        }
    };
    
    // 使用自定义分配器
    void* mem = SimpleAllocator::allocate(sizeof(int));
    int* custom_ptr = new(mem) int(999);
    std::cout << "自定义分配器创建的整数: " << *custom_ptr << "\n";
    
    // 基本类型不需要析构函数调用
    SimpleAllocator::deallocate(mem);
    
    std::cout << "\n=== 内存池概念演示 ===\n";
    
    SimpleMemoryPool pool;
    void* pool_mem1 = pool.allocate(sizeof(int));
    void* pool_mem2 = pool.allocate(sizeof(double));
    void* pool_mem3 = pool.allocate(sizeof(char[100]));
    
    pool.reset();
    
    std::cout << "\n=== 现代 C++ 内存管理总结 ===\n";
    std::cout << "1. 优先使用智能指针和容器\n";
    std::cout << "2. 理解 RAII 原则\n";
    std::cout << "3. 注意内存对齐和性能\n";
    std::cout << "4. 在需要时使用自定义分配器\n";
    std::cout << "5. 避免手动内存管理\n";
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 