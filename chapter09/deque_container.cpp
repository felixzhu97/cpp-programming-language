/**
 * @file deque_container.cpp
 * @brief deque 容器演示 - 双端队列操作、内存模型、与vector/list对比
 */

#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <random>

void demonstrate_deque_basics() {
    std::cout << "\n=== Deque 基本操作 ===\n";
    
    // 构造
    std::deque<int> dq1;
    std::deque<int> dq2(5, 10);
    std::deque<int> dq3{1, 2, 3, 4, 5};
    
    std::cout << "构造后大小: " << dq3.size() << "\n";
    
    // 双端操作
    dq3.push_front(0);
    dq3.push_back(6);
    std::cout << "双端添加后: ";
    for (auto x : dq3) std::cout << x << " ";
    std::cout << "\n";
    
    // 随机访问
    std::cout << "随机访问 dq3[3]: " << dq3[3] << "\n";
    std::cout << "front: " << dq3.front() << ", back: " << dq3.back() << "\n";
    
    // 插入删除
    dq3.insert(dq3.begin() + 2, 99);
    dq3.erase(dq3.begin() + 4);
    std::cout << "插入删除后: ";
    for (auto x : dq3) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_performance() {
    std::cout << "\n=== 性能对比 ===\n";
    
    const int N = 50000;
    auto measure_time = [](auto func, const std::string& desc) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "   " << desc << ": " << duration.count() << " μs\n";
        return duration.count();
    };
    
    // 头部插入
    std::cout << "\n头部插入性能:\n";
    
    auto deque_time = measure_time([&]() {
        std::deque<int> dq;
        for (int i = 0; i < N; ++i) {
            dq.push_front(i);
        }
    }, "deque::push_front");
    
    auto vector_time = measure_time([&]() {
        std::vector<int> vec;
        for (int i = 0; i < N; ++i) {
            vec.insert(vec.begin(), i);
        }
    }, "vector::insert(begin)");
    
    auto list_time = measure_time([&]() {
        std::list<int> lst;
        for (int i = 0; i < N; ++i) {
            lst.push_front(i);
        }
    }, "list::push_front");
    
    std::cout << "deque vs vector: " << static_cast<double>(vector_time) / deque_time << "x faster\n";
    std::cout << "deque vs list: " << static_cast<double>(list_time) / deque_time << "x\n";
    
    // 随机访问
    std::cout << "\n随机访问性能:\n";
    std::deque<int> dq(N);
    std::vector<int> vec(N);
    std::iota(dq.begin(), dq.end(), 1);
    std::iota(vec.begin(), vec.end(), 1);
    
    long long sum1 = 0, sum2 = 0;
    
    auto deque_access = measure_time([&]() {
        for (int i = 0; i < N; ++i) {
            sum1 += dq[i % N];
        }
    }, "deque[] access");
    
    auto vector_access = measure_time([&]() {
        for (int i = 0; i < N; ++i) {
            sum2 += vec[i % N];
        }
    }, "vector[] access");
    
    std::cout << "vector vs deque: " << static_cast<double>(deque_access) / vector_access << "x faster\n";
}

void demonstrate_use_cases() {
    std::cout << "\n=== 实际应用 ===\n";
    
    // 滑动窗口
    std::cout << "\n滑动窗口最大值:\n";
    std::vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    
    std::deque<int> window;
    std::vector<int> result;
    
    for (int i = 0; i < nums.size(); ++i) {
        // 移除窗口外的元素
        while (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }
        
        // 维护递减序列
        while (!window.empty() && nums[window.back()] <= nums[i]) {
            window.pop_back();
        }
        
        window.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[window.front()]);
        }
    }
    
    std::cout << "原数组: ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n窗口大小: " << k << "\n";
    std::cout << "最大值: ";
    for (auto x : result) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::cout << "C++ Primer Chapter 9: Deque 容器\n";
    std::cout << "================================\n";
    
    demonstrate_deque_basics();
    demonstrate_performance();
    demonstrate_use_cases();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 