/**
 * @file container_overview.cpp
 * @brief STL 容器概述 - 容器分类、通用接口、选择原则和性能特性
 * 
 * STL 提供了多种容器，每种容器都有不同的性能特性和适用场景。
 * 本文件展示了如何理解和选择合适的容器。
 */

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <array>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>

// 展示容器分类
void demonstrate_container_classification() {
    std::cout << "\n=== STL 容器分类 ===\n";
    
    // 1. 顺序容器 (Sequential Containers)
    std::cout << "\n1. 顺序容器：\n";
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::list<int> lst{1, 2, 3, 4, 5};
    std::deque<int> deq{1, 2, 3, 4, 5};
    std::array<int, 5> arr{1, 2, 3, 4, 5};
    std::forward_list<int> flst{1, 2, 3, 4, 5};
    
    std::cout << "   - vector: ";
    for (auto x : vec) std::cout << x << " ";
    std::cout << "\n   - list: ";
    for (auto x : lst) std::cout << x << " ";
    std::cout << "\n   - deque: ";
    for (auto x : deq) std::cout << x << " ";
    std::cout << "\n   - array: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n   - forward_list: ";
    for (auto x : flst) std::cout << x << " ";
    std::cout << "\n";
    
    // 2. 关联容器 (Associative Containers)
    std::cout << "\n2. 关联容器：\n";
    std::set<int> s{5, 2, 8, 1, 9};
    std::map<std::string, int> m{{"apple", 1}, {"banana", 2}, {"orange", 3}};
    
    std::cout << "   - set: ";
    for (auto x : s) std::cout << x << " ";
    std::cout << "\n   - map: ";
    for (auto& p : m) std::cout << "{" << p.first << ":" << p.second << "} ";
    std::cout << "\n";
    
    // 3. 无序关联容器 (Unordered Associative Containers)
    std::cout << "\n3. 无序关联容器：\n";
    std::unordered_set<int> us{5, 2, 8, 1, 9};
    std::unordered_map<std::string, int> um{{"apple", 1}, {"banana", 2}, {"orange", 3}};
    
    std::cout << "   - unordered_set: ";
    for (auto x : us) std::cout << x << " ";
    std::cout << "\n   - unordered_map: ";
    for (auto& p : um) std::cout << "{" << p.first << ":" << p.second << "} ";
    std::cout << "\n";
    
    // 4. 容器适配器 (Container Adapters)
    std::cout << "\n4. 容器适配器：\n";
    std::stack<int> st;
    std::queue<int> q;
    std::priority_queue<int> pq;
    
    for (int i = 1; i <= 3; ++i) {
        st.push(i);
        q.push(i);
        pq.push(i);
    }
    
    std::cout << "   - stack (LIFO): ";
    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    
    std::cout << "\n   - queue (FIFO): ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    
    std::cout << "\n   - priority_queue (max-heap): ";
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";
}

// 展示容器的通用接口
void demonstrate_common_interface() {
    std::cout << "\n=== 容器通用接口 ===\n";
    
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::list<int> lst{1, 2, 3, 4, 5};
    
    // 1. 类型别名
    std::cout << "\n1. 类型别名：\n";
    std::cout << "   vector::value_type size: " << sizeof(std::vector<int>::value_type) << " bytes\n";
    std::cout << "   vector::size_type max: " << std::vector<int>::size_type(-1) << "\n";
    std::cout << "   vector::difference_type range: " << 
                 sizeof(std::vector<int>::difference_type) * 8 << " bits\n";
    
    // 2. 构造和赋值
    std::cout << "\n2. 构造和赋值：\n";
    std::vector<int> v1;                    // 默认构造
    std::vector<int> v2(5);                 // 大小构造
    std::vector<int> v3(5, 10);             // 值构造
    std::vector<int> v4{1, 2, 3, 4, 5};     // 列表构造
    std::vector<int> v5(v4);                // 拷贝构造
    std::vector<int> v6(std::move(v4));     // 移动构造
    
    std::cout << "   v2 size: " << v2.size() << ", v3[0]: " << v3[0] << "\n";
    std::cout << "   v5 size: " << v5.size() << ", v6 size: " << v6.size() << "\n";
    std::cout << "   v4 size after move: " << v4.size() << "\n";
    
    // 3. 大小和容量
    std::cout << "\n3. 大小和容量：\n";
    std::cout << "   vec.size(): " << vec.size() << "\n";
    std::cout << "   vec.max_size(): " << vec.max_size() << "\n";
    std::cout << "   vec.empty(): " << std::boolalpha << vec.empty() << "\n";
    if constexpr (requires { vec.capacity(); }) {
        std::cout << "   vec.capacity(): " << vec.capacity() << "\n";
    }
    
    // 4. 迭代器
    std::cout << "\n4. 迭代器：\n";
    std::cout << "   Forward iteration: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n   Reverse iteration: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    // 5. 元素访问（适用于支持的容器）
    std::cout << "\n5. 元素访问：\n";
    if (!vec.empty()) {
        std::cout << "   vec.front(): " << vec.front() << "\n";
        std::cout << "   vec.back(): " << vec.back() << "\n";
        std::cout << "   vec[1]: " << vec[1] << "\n";
        std::cout << "   vec.at(1): " << vec.at(1) << "\n";
    }
    
    // 6. 修改操作
    std::cout << "\n6. 修改操作：\n";
    std::vector<int> v_mod{1, 2, 3};
    v_mod.push_back(4);
    v_mod.pop_back();
    v_mod.insert(v_mod.begin() + 1, 99);
    v_mod.erase(v_mod.begin());
    
    std::cout << "   After modifications: ";
    for (auto x : v_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // 7. 交换和清空
    std::cout << "\n7. 交换和清空：\n";
    std::vector<int> v_a{1, 2, 3};
    std::vector<int> v_b{4, 5, 6, 7};
    
    std::cout << "   Before swap - v_a size: " << v_a.size() 
              << ", v_b size: " << v_b.size() << "\n";
    v_a.swap(v_b);
    std::cout << "   After swap - v_a size: " << v_a.size() 
              << ", v_b size: " << v_b.size() << "\n";
    
    v_a.clear();
    std::cout << "   After clear - v_a size: " << v_a.size() << "\n";
}

// 性能测试辅助函数
template<typename Container, typename Generator>
auto measure_time(Container& container, Generator gen, const std::string& operation) {
    auto start = std::chrono::high_resolution_clock::now();
    gen(container);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "   " << operation << ": " << duration.count() << " μs\n";
    return duration;
}

// 展示性能特性
void demonstrate_performance_characteristics() {
    std::cout << "\n=== 性能特性对比 ===\n";
    
    const int N = 10000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    // 1. 插入性能
    std::cout << "\n1. 插入性能 (插入 " << N << " 个元素)：\n";
    
    // vector - 尾部插入
    std::vector<int> vec;
    vec.reserve(N);  // 预分配以公平比较
    measure_time(vec, [&](auto& c) {
        for (int i = 0; i < N; ++i) {
            c.push_back(dis(gen));
        }
    }, "vector::push_back");
    
    // list - 尾部插入
    std::list<int> lst;
    measure_time(lst, [&](auto& c) {
        for (int i = 0; i < N; ++i) {
            c.push_back(dis(gen));
        }
    }, "list::push_back");
    
    // deque - 尾部插入
    std::deque<int> deq;
    measure_time(deq, [&](auto& c) {
        for (int i = 0; i < N; ++i) {
            c.push_back(dis(gen));
        }
    }, "deque::push_back");
    
    // 2. 中间插入性能
    std::cout << "\n2. 中间插入性能 (插入 1000 个元素到中间)：\n";
    
    std::vector<int> vec_mid(N);
    measure_time(vec_mid, [&](auto& c) {
        for (int i = 0; i < 1000; ++i) {
            c.insert(c.begin() + c.size()/2, dis(gen));
        }
    }, "vector::insert (middle)");
    
    std::list<int> lst_mid(N);
    auto it = lst_mid.begin();
    std::advance(it, N/2);
    measure_time(lst_mid, [&](auto& c) {
        auto iter = c.begin();
        std::advance(iter, c.size()/2);
        for (int i = 0; i < 1000; ++i) {
            iter = c.insert(iter, dis(gen));
        }
    }, "list::insert (middle)");
    
    // 3. 随机访问性能
    std::cout << "\n3. 随机访问性能 (访问 " << N << " 次)：\n";
    
    // 重新填充容器
    vec.clear();
    lst.clear();
    deq.clear();
    for (int i = 0; i < N; ++i) {
        int val = dis(gen);
        vec.push_back(val);
        lst.push_back(val);
        deq.push_back(val);
    }
    
    int sum = 0;
    measure_time(vec, [&](auto& c) {
        for (int i = 0; i < N; ++i) {
            sum += c[i % c.size()];
        }
    }, "vector[] access");
    
    measure_time(deq, [&](auto& c) {
        for (int i = 0; i < N; ++i) {
            sum += c[i % c.size()];
        }
    }, "deque[] access");
    
    // list 没有随机访问
    measure_time(lst, [&](auto& c) {
        for (int i = 0; i < N; ++i) {
            auto it = c.begin();
            std::advance(it, i % c.size());
            sum += *it;
        }
    }, "list iterator advance");
    
    std::cout << "   Sum (to prevent optimization): " << sum << "\n";
    
    // 4. 内存使用
    std::cout << "\n4. 内存使用分析：\n";
    std::cout << "   vector<int> 单个元素开销: " << sizeof(int) << " bytes\n";
    std::cout << "   list<int> 单个元素开销: ~" << sizeof(int) + 2*sizeof(void*) << " bytes (节点)\n";
    std::cout << "   deque<int> 单个元素开销: " << sizeof(int) << " bytes (分块)\n";
}

// 容器选择指南
void demonstrate_container_selection_guide() {
    std::cout << "\n=== 容器选择指南 ===\n";
    
    std::cout << "\n1. vector - 动态数组\n";
    std::cout << "   优势：\n";
    std::cout << "     - 随机访问 O(1)\n";
    std::cout << "     - 尾部插入/删除 O(1) 摊还\n";
    std::cout << "     - 内存紧凑，缓存友好\n";
    std::cout << "     - 支持 data() 获取原始指针\n";
    std::cout << "   劣势：\n";
    std::cout << "     - 中间插入/删除 O(n)\n";
    std::cout << "     - 扩容时需要重新分配和拷贝\n";
    std::cout << "   适用场景：需要随机访问、主要在尾部操作的场景\n";
    
    std::cout << "\n2. list - 双向链表\n";
    std::cout << "   优势：\n";
    std::cout << "     - 任意位置插入/删除 O(1)\n";
    std::cout << "     - 插入/删除不会使迭代器失效\n";
    std::cout << "     - 提供 splice 等特有操作\n";
    std::cout << "   劣势：\n";
    std::cout << "     - 没有随机访问\n";
    std::cout << "     - 额外的指针开销\n";
    std::cout << "     - 缓存不友好\n";
    std::cout << "   适用场景：频繁在中间插入/删除、不需要随机访问\n";
    
    std::cout << "\n3. deque - 双端队列\n";
    std::cout << "   优势：\n";
    std::cout << "     - 随机访问 O(1)\n";
    std::cout << "     - 两端插入/删除 O(1)\n";
    std::cout << "     - 不需要重新分配整块内存\n";
    std::cout << "   劣势：\n";
    std::cout << "     - 中间插入/删除 O(n)\n";
    std::cout << "     - 比 vector 复杂的内存模型\n";
    std::cout << "   适用场景：需要在两端操作、需要随机访问\n";
    
    std::cout << "\n4. array - 固定大小数组\n";
    std::cout << "   优势：\n";
    std::cout << "     - 编译时确定大小\n";
    std::cout << "     - 没有动态分配开销\n";
    std::cout << "     - 与 C 数组兼容\n";
    std::cout << "   劣势：\n";
    std::cout << "     - 固定大小，不能扩容\n";
    std::cout << "   适用场景：大小固定的小型数据集\n";
    
    std::cout << "\n5. forward_list - 单向链表\n";
    std::cout << "   优势：\n";
    std::cout << "     - 最小的内存开销\n";
    std::cout << "     - 插入/删除 O(1)\n";
    std::cout << "   劣势：\n";
    std::cout << "     - 只能向前遍历\n";
    std::cout << "     - 功能相对受限\n";
    std::cout << "   适用场景：内存敏感、只需要向前访问的场景\n";
}

// 异常安全性演示
void demonstrate_exception_safety() {
    std::cout << "\n=== 异常安全性 ===\n";
    
    // 异常安全的类
    class SafeResource {
    private:
        int* data;
        size_t size;
        
    public:
        SafeResource(size_t n) : data(new int[n]), size(n) {
            std::cout << "   构造 SafeResource, size=" << size << "\n";
            for (size_t i = 0; i < size; ++i) {
                data[i] = static_cast<int>(i);
            }
        }
        
        ~SafeResource() {
            std::cout << "   析构 SafeResource, size=" << size << "\n";
            delete[] data;
        }
        
        // 拷贝构造可能抛异常
        SafeResource(const SafeResource& other) : data(new int[other.size]), size(other.size) {
            // 模拟可能的异常
            static int copy_count = 0;
            if (++copy_count % 3 == 0) {
                delete[] data;
                throw std::runtime_error("拷贝构造失败");
            }
            
            std::copy(other.data, other.data + size, data);
            std::cout << "   拷贝构造 SafeResource, size=" << size << "\n";
        }
        
        SafeResource& operator=(const SafeResource& other) {
            if (this != &other) {
                SafeResource temp(other);  // 强异常安全
                swap(temp);
            }
            return *this;
        }
        
        void swap(SafeResource& other) noexcept {
            std::swap(data, other.data);
            std::swap(size, other.size);
        }
        
        int get_value(size_t index) const {
            return (index < size) ? data[index] : 0;
        }
    };
    
    std::cout << "\n1. 容器的异常安全保证：\n";
    
    // 测试 vector 的异常安全
    std::vector<SafeResource> vec;
    vec.reserve(2);  // 避免重新分配
    
    try {
        vec.emplace_back(3);  // 第一个对象
        std::cout << "   成功添加第一个对象\n";
        
        vec.emplace_back(4);  // 第二个对象
        std::cout << "   成功添加第二个对象\n";
        
        vec.emplace_back(5);  // 第三个对象，可能失败
        std::cout << "   成功添加第三个对象\n";
        
    } catch (const std::exception& e) {
        std::cout << "   捕获异常: " << e.what() << "\n";
        std::cout << "   vector 大小: " << vec.size() << "\n";
        std::cout << "   容器保持一致状态\n";
    }
    
    std::cout << "\n2. 强异常安全操作：\n";
    try {
        std::vector<SafeResource> vec1;
        vec1.emplace_back(2);
        
        std::vector<SafeResource> vec2;
        vec2.emplace_back(3);
        
        // swap 提供 noexcept 保证
        std::cout << "   交换前: vec1.size()=" << vec1.size() 
                  << ", vec2.size()=" << vec2.size() << "\n";
        vec1.swap(vec2);
        std::cout << "   交换后: vec1.size()=" << vec1.size() 
                  << ", vec2.size()=" << vec2.size() << "\n";
        
    } catch (const std::exception& e) {
        std::cout << "   交换操作异常: " << e.what() << "\n";
    }
}

int main() {
    std::cout << "C++ Primer Chapter 9: 顺序容器概述\n";
    std::cout << "=====================================\n";
    
    try {
        // 1. 容器分类演示
        demonstrate_container_classification();
        
        // 2. 通用接口演示
        demonstrate_common_interface();
        
        // 3. 性能特性对比
        demonstrate_performance_characteristics();
        
        // 4. 容器选择指南
        demonstrate_container_selection_guide();
        
        // 5. 异常安全性
        demonstrate_exception_safety();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 