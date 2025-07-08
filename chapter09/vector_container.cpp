/**
 * @file vector_container.cpp
 * @brief vector 容器详细演示 - 基本操作、动态扩容、内存管理、迭代器失效和性能优化
 * 
 * vector 是最常用的 STL 容器，提供动态数组功能。
 * 本文件展示 vector 的各种特性和最佳实践。
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <random>
#include <string>
#include <iomanip>#include <cassert>

// 演示 vector 基本操作
void demonstrate_basic_operations() {
    std::cout << "\n=== Vector 基本操作 ===\n";
    
    // 1. 构造方式
    std::cout << "\n1. 各种构造方式：\n";
    std::vector<int> v1;                           // 默认构造
    std::vector<int> v2(5);                        // 指定大小
    std::vector<int> v3(5, 10);                    // 大小和初值
    std::vector<int> v4{1, 2, 3, 4, 5};            // 初始化列表
    std::vector<int> v5(v4.begin(), v4.end());     // 迭代器范围
    std::vector<int> v6(v4);                       // 拷贝构造
    std::vector<int> v7(std::move(v5));            // 移动构造
    
    std::cout << "   v1 size: " << v1.size() << ", capacity: " << v1.capacity() << "\n";
    std::cout << "   v2 size: " << v2.size() << ", capacity: " << v2.capacity() << "\n";
    std::cout << "   v3 size: " << v3.size() << ", first: " << (v3.empty() ? 0 : v3[0]) << "\n";
    std::cout << "   v4 size: " << v4.size() << ", elements: ";
    for (auto x : v4) std::cout << x << " ";
    std::cout << "\n   v7 size: " << v7.size() << " (moved from v5)\n";
    std::cout << "   v5 size after move: " << v5.size() << "\n";
    
    // 2. 容量管理
    std::cout << "\n2. 容量管理：\n";
    std::vector<int> v;
    std::cout << "   初始 - size: " << v.size() << ", capacity: " << v.capacity() << "\n";
    
    v.reserve(100);
    std::cout << "   reserve(100) - size: " << v.size() << ", capacity: " << v.capacity() << "\n";
    
    v.resize(50, 999);
    std::cout << "   resize(50, 999) - size: " << v.size() << ", capacity: " << v.capacity() << "\n";
    
    v.shrink_to_fit();
    std::cout << "   shrink_to_fit() - size: " << v.size() << ", capacity: " << v.capacity() << "\n";
    
    // 3. 元素访问
    std::cout << "\n3. 元素访问：\n";
    std::vector<int> vec{10, 20, 30, 40, 50};
    
    std::cout << "   operator[]: vec[2] = " << vec[2] << "\n";
    std::cout << "   at(): vec.at(2) = " << vec.at(2) << "\n";
    std::cout << "   front(): " << vec.front() << "\n";
    std::cout << "   back(): " << vec.back() << "\n";
    std::cout << "   data(): " << *vec.data() << " (原始指针访问)\n";
    
    // 边界检查示例
    try {
        std::cout << "   尝试访问 vec.at(10): ";
        std::cout << vec.at(10) << "\n";
    } catch (const std::out_of_range& e) {
        std::cout << "捕获异常: " << e.what() << "\n";
    }
    
    // 4. 修改操作
    std::cout << "\n4. 修改操作：\n";
    std::vector<int> v_mod;
    
    // 尾部操作
    v_mod.push_back(1);
    v_mod.push_back(2);
    v_mod.push_back(3);
    std::cout << "   push_back 后: ";
    for (auto x : v_mod) std::cout << x << " ";
    std::cout << "\n";
    
    v_mod.pop_back();
    std::cout << "   pop_back 后: ";
    for (auto x : v_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // 插入操作
    v_mod.insert(v_mod.begin() + 1, 99);
    std::cout << "   insert(begin()+1, 99) 后: ";
    for (auto x : v_mod) std::cout << x << " ";
    std::cout << "\n";
    
    v_mod.insert(v_mod.end(), {10, 11, 12});
    std::cout << "   insert 多个元素后: ";
    for (auto x : v_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // 删除操作
    v_mod.erase(v_mod.begin() + 1);
    std::cout << "   erase(begin()+1) 后: ";
    for (auto x : v_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // emplace 操作（原地构造）
    std::vector<std::string> v_str;
    v_str.emplace_back("hello");        // 直接构造，避免临时对象
    v_str.emplace_back(5, 'a');         // 构造 "aaaaa"
    v_str.emplace(v_str.begin(), "world");
    
    std::cout << "   emplace 操作后: ";
    for (const auto& s : v_str) std::cout << "[" << s << "] ";
    std::cout << "\n";
}

// 演示动态扩容机制
void demonstrate_dynamic_expansion() {
    std::cout << "\n=== 动态扩容机制 ===\n";
    
    std::vector<int> vec;
    std::cout << "\n观察 vector 扩容过程：\n";
    
    size_t prev_capacity = vec.capacity();
    std::cout << "   初始容量: " << prev_capacity << "\n";
    
    for (int i = 1; i <= 20; ++i) {
        vec.push_back(i);
        
        if (vec.capacity() != prev_capacity) {
            std::cout << "   添加元素 " << i << " 后扩容: " 
                      << prev_capacity << " -> " << vec.capacity() 
                      << " (增长因子: " << static_cast<double>(vec.capacity()) / prev_capacity << ")\n";
            prev_capacity = vec.capacity();
        }
    }
    
    std::cout << "\n最终状态: size=" << vec.size() << ", capacity=" << vec.capacity() << "\n";
    
    // 演示扩容的性能影响
    std::cout << "\n扩容性能对比：\n";
    
    // 不预分配的情况
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> v1;
    for (int i = 0; i < 100000; ++i) {
        v1.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    // 预分配的情况
    start = std::chrono::high_resolution_clock::now();
    std::vector<int> v2;
    v2.reserve(100000);
    for (int i = 0; i < 100000; ++i) {
        v2.push_back(i);
    }
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "   不预分配: " << duration1.count() << " μs\n";
    std::cout << "   预分配: " << duration2.count() << " μs\n";
    std::cout << "   性能提升: " << static_cast<double>(duration1.count()) / duration2.count() << "x\n";
}

// 演示内存管理
void demonstrate_memory_management() {
    std::cout << "\n=== 内存管理 ===\n";
    
    // 1. 内存布局
    std::cout << "\n1. 内存布局分析：\n";
    std::vector<int> vec{1, 2, 3, 4, 5};
    
    std::cout << "   vector 对象大小: " << sizeof(vec) << " bytes\n";
    std::cout << "   元素总大小: " << vec.size() * sizeof(int) << " bytes\n";
    std::cout << "   容量总大小: " << vec.capacity() * sizeof(int) << " bytes\n";
    std::cout << "   数据指针: " << static_cast<void*>(vec.data()) << "\n";
    
    // 检查内存连续性
    std::cout << "   内存连续性检查:\n";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << "     vec[" << i << "] address: " << &vec[i] 
                  << ", value: " << vec[i] << "\n";
    }
    
    // 2. 内存重新分配
    std::cout << "\n2. 内存重新分配观察：\n";
    std::vector<int> v;
    int* old_ptr = nullptr;
    
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
        int* new_ptr = v.data();
        
        if (new_ptr != old_ptr) {
            std::cout << "   重新分配: 容量=" << v.capacity() 
                      << ", 新地址=" << static_cast<void*>(new_ptr);
            if (old_ptr) {
                std::cout << ", 旧地址=" << static_cast<void*>(old_ptr);
            }
            std::cout << "\n";
            old_ptr = new_ptr;
        }
    }
    
    // 3. 自定义分配器示例
    std::cout << "\n3. 自定义分配器使用：\n";
    
    // 简单的统计分配器
    template<typename T>
    class StatAllocator {
    public:
        using value_type = T;
        static size_t allocation_count;
        static size_t deallocation_count;
        static size_t bytes_allocated;
        
        StatAllocator() = default;
        template<typename U> StatAllocator(const StatAllocator<U>&) {}
        
        T* allocate(size_t n) {
            allocation_count++;
            bytes_allocated += n * sizeof(T);
            std::cout << "     分配 " << n << " 个 " << typeid(T).name() 
                      << " (" << n * sizeof(T) << " bytes)\n";
            return static_cast<T*>(std::malloc(n * sizeof(T)));
        }
        
        void deallocate(T* p, size_t n) {
            deallocation_count++;
            std::cout << "     释放 " << n << " 个 " << typeid(T).name() 
                      << " (" << n * sizeof(T) << " bytes)\n";
            std::free(p);
        }
        
        template<typename U>
        bool operator==(const StatAllocator<U>&) const { return true; }
        
        template<typename U>
        bool operator!=(const StatAllocator<U>&) const { return false; }
    };
    
    template<typename T>
    size_t StatAllocator<T>::allocation_count = 0;
    template<typename T>
    size_t StatAllocator<T>::deallocation_count = 0;
    template<typename T>
    size_t StatAllocator<T>::bytes_allocated = 0;
    
    {
        std::vector<int, StatAllocator<int>> stat_vec;
        std::cout << "   使用统计分配器的 vector:\n";
        
        for (int i = 0; i < 10; ++i) {
            stat_vec.push_back(i);
        }
        
        std::cout << "   分配次数: " << StatAllocator<int>::allocation_count << "\n";
        std::cout << "   总分配字节: " << StatAllocator<int>::bytes_allocated << "\n";
    }
    
    std::cout << "   释放次数: " << StatAllocator<int>::deallocation_count << "\n";
}

// 演示迭代器失效
void demonstrate_iterator_invalidation() {
    std::cout << "\n=== 迭代器失效 ===\n";
    
    std::cout << "\n1. 扩容导致的迭代器失效：\n";
    std::vector<int> vec{1, 2, 3};
    
    auto it = vec.begin();
    auto ptr = vec.data();
    
    std::cout << "   扩容前: 迭代器指向 " << *it << ", 地址: " << &(*it) << "\n";
    std::cout << "   扩容前: 数据指针: " << static_cast<void*>(ptr) << "\n";
    
    // 强制扩容
    vec.reserve(vec.capacity() + 1);
    vec.push_back(4);
    
    std::cout << "   扩容后: 数据指针: " << static_cast<void*>(vec.data()) << "\n";
    std::cout << "   扩容后: 原迭代器已失效（不要解引用）\n";
    
    // 正确做法：重新获取迭代器
    it = vec.begin();
    std::cout << "   新迭代器指向: " << *it << ", 地址: " << &(*it) << "\n";
    
    std::cout << "\n2. 插入操作的迭代器失效：\n";
    vec = {1, 2, 3, 4, 5};
    
    auto it1 = vec.begin() + 2;  // 指向元素 3
    auto it2 = vec.end() - 1;    // 指向元素 5
    
    std::cout << "   插入前: it1 指向 " << *it1 << ", it2 指向 " << *it2 << "\n";
    
    // 在中间插入，可能触发重新分配
    vec.insert(vec.begin() + 1, 99);
    
    std::cout << "   插入后: 原迭代器可能已失效\n";
    std::cout << "   新的 vec[2] = " << vec[2] << ", vec[" << vec.size()-1 << "] = " << vec[vec.size()-1] << "\n";
    
    std::cout << "\n3. 删除操作的迭代器失效：\n";
    vec = {1, 2, 3, 4, 5};
    
    it = vec.begin() + 2;  // 指向元素 3
    std::cout << "   删除前: 迭代器指向 " << *it << "\n";
    
    // 删除当前元素，返回下一个有效迭代器
    it = vec.erase(it);
    std::cout << "   删除后: 新迭代器指向 " << *it << "\n";
    
    // 安全的删除多个元素
    std::cout << "\n4. 安全的批量删除：\n";
    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "   删除前: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 删除所有偶数 - 方法1：从后往前删
    for (auto it = vec.end() - 1; it >= vec.begin(); --it) {
        if (*it % 2 == 0) {
            vec.erase(it);
        }
    }
    
    std::cout << "   删除偶数后: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";
    
    // 删除所有大于5的数 - 方法2：使用算法
    vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec.erase(std::remove_if(vec.begin(), vec.end(), 
                            [](int x) { return x > 5; }), vec.end());
    
    std::cout << "   删除>5的数后: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n";
}

// 演示性能优化技巧
void demonstrate_performance_optimization() {
    std::cout << "\n=== 性能优化技巧 ===\n";
    
    const int N = 100000;
    
    // 1. 预分配 vs 动态增长
    std::cout << "\n1. 预分配的重要性：\n";
    
    auto measure_time = [](auto func, const std::string& desc) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "   " << desc << ": " << duration.count() << " μs\n";
        return duration.count();
    };
    
    auto time1 = measure_time([&]() {
        std::vector<int> v;
        for (int i = 0; i < N; ++i) {
            v.push_back(i);
        }
    }, "动态增长");
    
    auto time2 = measure_time([&]() {
        std::vector<int> v;
        v.reserve(N);
        for (int i = 0; i < N; ++i) {
            v.push_back(i);
        }
    }, "预分配");
    
    std::cout << "   提升倍数: " << static_cast<double>(time1) / time2 << "x\n";
    
    // 2. emplace vs push_back
    std::cout << "\n2. emplace vs push_back 性能对比：\n";
    
    class TestObject {
    public:
        int value;
        std::string name;
        
        TestObject(int v, const std::string& n) : value(v), name(n) {
            // std::cout << "构造 TestObject(" << v << ", " << n << ")\n";
        }
        
        TestObject(const TestObject& other) : value(other.value), name(other.name) {
            // std::cout << "拷贝构造 TestObject\n";
        }
        
        TestObject(TestObject&& other) noexcept : value(other.value), name(std::move(other.name)) {
            // std::cout << "移动构造 TestObject\n";
        }
    };
    
    const int obj_count = 10000;
    
    auto time3 = measure_time([&]() {
        std::vector<TestObject> v;
        v.reserve(obj_count);
        for (int i = 0; i < obj_count; ++i) {
            v.push_back(TestObject(i, "test" + std::to_string(i)));
        }
    }, "push_back + 临时对象");
    
    auto time4 = measure_time([&]() {
        std::vector<TestObject> v;
        v.reserve(obj_count);
        for (int i = 0; i < obj_count; ++i) {
            v.emplace_back(i, "test" + std::to_string(i));
        }
    }, "emplace_back");
    
    std::cout << "   emplace 提升: " << static_cast<double>(time3) / time4 << "x\n";
    
    // 3. 内存局部性优化
    std::cout << "\n3. 内存局部性对比：\n";
    
    std::vector<int> vec_data(N);
    std::iota(vec_data.begin(), vec_data.end(), 1);
    
    // 顺序访问
    auto time5 = measure_time([&]() {
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += vec_data[i];
        }
        volatile auto dummy = sum;  // 防止优化
    }, "顺序访问");
    
    // 随机访问
    std::vector<int> indices(N);
    std::iota(indices.begin(), indices.end(), 0);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(indices.begin(), indices.end(), gen);
    
    auto time6 = measure_time([&]() {
        long long sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += vec_data[indices[i]];
        }
        volatile auto dummy = sum;  // 防止优化
    }, "随机访问");
    
    std::cout << "   顺序访问优势: " << static_cast<double>(time6) / time5 << "x\n";
    
    // 4. 容量管理优化
    std::cout << "\n4. 容量管理策略：\n";
    
    std::vector<int> v1, v2, v3;
    
    // 策略1：一次性分配
    v1.reserve(N);
    auto time7 = measure_time([&]() {
        for (int i = 0; i < N; ++i) {
            v1.push_back(i);
        }
    }, "一次性预分配");
    
    // 策略2：分批分配
    auto time8 = measure_time([&]() {
        const int batch_size = 1000;
        for (int i = 0; i < N; i += batch_size) {
            v2.reserve(v2.size() + batch_size);
            for (int j = 0; j < batch_size && i + j < N; ++j) {
                v2.push_back(i + j);
            }
        }
    }, "分批预分配");
    
    // 策略3：动态增长
    auto time9 = measure_time([&]() {
        for (int i = 0; i < N; ++i) {
            v3.push_back(i);
        }
    }, "完全动态增长");
    
    std::cout << "   一次性分配最优, 比分批快: " 
              << static_cast<double>(time8) / time7 << "x\n";
    std::cout << "   比动态增长快: " 
              << static_cast<double>(time9) / time7 << "x\n";
}

// vector 的高级用法
void demonstrate_advanced_usage() {
    std::cout << "\n=== Vector 高级用法 ===\n";
    
    // 1. 二维 vector
    std::cout << "\n1. 二维 vector（矩阵）：\n";
    const int rows = 3, cols = 4;
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols, 0));
    
    // 初始化矩阵
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = i * cols + j + 1;
        }
    }
    
    std::cout << "   矩阵内容:\n";
    for (const auto& row : matrix) {
        std::cout << "   ";
        for (auto val : row) {
            std::cout << std::setw(3) << val << " ";
        }
        std::cout << "\n";
    }
    
    // 更高效的一维表示
    std::vector<int> flat_matrix(rows * cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            flat_matrix[i * cols + j] = matrix[i][j];
        }
    }
    
    std::cout << "   一维表示: ";
    for (auto val : flat_matrix) std::cout << val << " ";
    std::cout << "\n";
    
    // 2. vector<bool> 特化
    std::cout << "\n2. vector<bool> 特化：\n";
    std::vector<bool> bit_vec(16, false);
    
    // 设置一些位
    bit_vec[1] = true;
    bit_vec[3] = true;
    bit_vec[7] = true;
    bit_vec[15] = true;
    
    std::cout << "   位向量: ";
    for (size_t i = 0; i < bit_vec.size(); ++i) {
        std::cout << (bit_vec[i] ? '1' : '0');
    }
    std::cout << "\n";
    
    // 位操作
    bit_vec.flip();  // 翻转所有位
    std::cout << "   翻转后: ";
    for (size_t i = 0; i < bit_vec.size(); ++i) {
        std::cout << (bit_vec[i] ? '1' : '0');
    }
    std::cout << "\n";
    
    std::cout << "   注意: vector<bool> 的 [] 返回代理对象，不是真正的引用\n";
    
    // 3. 算法配合使用
    std::cout << "\n3. 与算法配合使用：\n";
    std::vector<int> nums{5, 2, 8, 1, 9, 3, 7, 6, 4};
    
    std::cout << "   原始: ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n";
    
    // 排序
    std::sort(nums.begin(), nums.end());
    std::cout << "   排序: ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n";
    
    // 查找
    auto it = std::find(nums.begin(), nums.end(), 5);
    if (it != nums.end()) {
        std::cout << "   找到 5 在位置: " << std::distance(nums.begin(), it) << "\n";
    }
    
    // 二分查找（要求有序）
    bool found = std::binary_search(nums.begin(), nums.end(), 7);
    std::cout << "   二分查找 7: " << (found ? "找到" : "未找到") << "\n";
    
    // 分区
    std::vector<int> part_nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto partition_point = std::partition(part_nums.begin(), part_nums.end(),
                                         [](int x) { return x % 2 == 0; });
    
    std::cout << "   偶数分区: ";
    for (auto it = part_nums.begin(); it != partition_point; ++it) {
        std::cout << *it << " ";
    }
    std::cout << "| 奇数分区: ";
    for (auto it = partition_point; it != part_nums.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // 4. 自定义比较器
    std::cout << "\n4. 自定义比较器：\n";
    std::vector<std::string> words{"apple", "banana", "cat", "dog", "elephant"};
    
    // 按长度排序
    std::sort(words.begin(), words.end(), 
             [](const std::string& a, const std::string& b) {
                 return a.length() < b.length();
             });
    
    std::cout << "   按长度排序: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << "\n";
    
    // 5. 内存池概念演示
    std::cout << "\n5. 对象池模式：\n";
    
    class ObjectPool {
    private:
        std::vector<std::unique_ptr<std::string>> pool;
        std::vector<std::string*> available;
        
    public:
        std::string* acquire() {
            if (available.empty()) {
                pool.push_back(std::make_unique<std::string>());
                std::cout << "     创建新对象，池大小: " << pool.size() << "\n";
                return pool.back().get();
            } else {
                auto obj = available.back();
                available.pop_back();
                std::cout << "     复用对象，可用: " << available.size() << "\n";
                return obj;
            }
        }
        
        void release(std::string* obj) {
            obj->clear();
            available.push_back(obj);
            std::cout << "     归还对象，可用: " << available.size() << "\n";
        }
    };
    
    ObjectPool pool;
    std::vector<std::string*> objects;
    
    // 获取对象
    for (int i = 0; i < 5; ++i) {
        auto obj = pool.acquire();
        *obj = "Object " + std::to_string(i);
        objects.push_back(obj);
    }
    
    // 释放一些对象
    pool.release(objects[1]);
    pool.release(objects[3]);
    
    // 再次获取（应该复用）
    auto reused1 = pool.acquire();
    auto reused2 = pool.acquire();
    
    *reused1 = "Reused 1";
    *reused2 = "Reused 2";
}

int main() {
    std::cout << "C++ Primer Chapter 9: Vector 容器详解\n";
    std::cout << "====================================\n";
    
    try {
        // 1. 基本操作演示
        demonstrate_basic_operations();
        
        // 2. 动态扩容机制
        demonstrate_dynamic_expansion();
        
        // 3. 内存管理
        demonstrate_memory_management();
        
        // 4. 迭代器失效
        demonstrate_iterator_invalidation();
        
        // 5. 性能优化
        demonstrate_performance_optimization();
        
        // 6. 高级用法
        demonstrate_advanced_usage();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 