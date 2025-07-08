/**
 * @file array_container.cpp
 * @brief array 容器演示 - 固定大小数组、与C数组对比、编译时特性
 */

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

void demonstrate_array_basics() {
    std::cout << "\n=== Array 基本操作 ===\n";
    
    // 构造方式
    std::array<int, 5> arr1{};              // 零初始化
    std::array<int, 5> arr2{1, 2, 3, 4, 5}; // 列表初始化
    std::array<int, 5> arr3 = {10, 20, 30}; // 部分初始化，剩余为0
    
    std::cout << "arr1: ";
    for (auto x : arr1) std::cout << x << " ";
    std::cout << "\narr2: ";
    for (auto x : arr2) std::cout << x << " ";
    std::cout << "\narr3: ";
    for (auto x : arr3) std::cout << x << " ";
    std::cout << "\n";
    
    // 大小和容量
    std::cout << "\n大小信息:\n";
    std::cout << "size(): " << arr2.size() << "\n";
    std::cout << "max_size(): " << arr2.max_size() << "\n";
    std::cout << "empty(): " << std::boolalpha << arr2.empty() << "\n";
    
    // 元素访问
    std::cout << "\n元素访问:\n";
    std::cout << "arr2[2]: " << arr2[2] << "\n";
    std::cout << "arr2.at(2): " << arr2.at(2) << "\n";
    std::cout << "front(): " << arr2.front() << "\n";
    std::cout << "back(): " << arr2.back() << "\n";
    std::cout << "data(): " << *arr2.data() << "\n";
    
    // 修改操作
    arr2.fill(99);
    std::cout << "\nfill(99) 后: ";
    for (auto x : arr2) std::cout << x << " ";
    std::cout << "\n";
    
    std::array<int, 5> arr4{5, 4, 3, 2, 1};
    arr2.swap(arr4);
    std::cout << "swap 后 arr2: ";
    for (auto x : arr2) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_vs_c_array() {
    std::cout << "\n=== 与C数组对比 ===\n";
    
    // C数组
    int c_arr[5] = {1, 2, 3, 4, 5};
    
    // std::array
    std::array<int, 5> std_arr{1, 2, 3, 4, 5};
    
    std::cout << "C数组大小: " << sizeof(c_arr) / sizeof(c_arr[0]) << "\n";
    std::cout << "std::array大小: " << std_arr.size() << "\n";
    
    // 函数传递
    auto print_c_array = [](int arr[], size_t size) {
        std::cout << "C数组传递后大小: " << sizeof(arr) << " (退化为指针)\n";
        for (size_t i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    };
    
    auto print_std_array = [](const std::array<int, 5>& arr) {
        std::cout << "std::array大小保持: " << arr.size() << "\n";
        for (auto x : arr) {
            std::cout << x << " ";
        }
        std::cout << "\n";
    };
    
    std::cout << "\n函数传递:\n";
    print_c_array(c_arr, 5);
    print_std_array(std_arr);
    
    // 赋值操作
    std::cout << "\n赋值操作:\n";
    std::array<int, 5> arr_copy = std_arr;  // 可以直接赋值
    std::cout << "std::array 可以直接赋值\n";
    
    // int c_arr_copy[5] = c_arr;  // 编译错误：C数组不能直接赋值
    std::cout << "C数组不能直接赋值，需要使用memcpy或循环\n";
}

void demonstrate_compile_time_features() {
    std::cout << "\n=== 编译时特性 ===\n";
    
    // constexpr array
    constexpr std::array<int, 5> const_arr{1, 2, 3, 4, 5};
    constexpr auto first = const_arr[0];  // 编译时计算
    
    std::cout << "constexpr array 第一个元素: " << first << "\n";
    
    // 编译时大小
    constexpr auto size = const_arr.size();
    std::cout << "编译时大小: " << size << "\n";
    
    // 模板推导 (C++17)
    #if __cplusplus >= 201703L
    std::array deduced{1, 2, 3, 4, 5};  // 推导为 std::array<int, 5>
    std::cout << "C++17模板推导大小: " << deduced.size() << "\n";
    #endif
    
    // 结构化绑定 (C++17)
    #if __cplusplus >= 201703L
    std::array<int, 3> triple{10, 20, 30};
    auto [a, b, c] = triple;
    std::cout << "结构化绑定: a=" << a << ", b=" << b << ", c=" << c << "\n";
    #endif
}

void demonstrate_algorithms() {
    std::cout << "\n=== 算法应用 ===\n";
    
    std::array<int, 10> arr{5, 2, 8, 1, 9, 3, 7, 4, 6, 0};
    
    std::cout << "原始: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";
    
    // 排序
    std::sort(arr.begin(), arr.end());
    std::cout << "排序: ";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";
    
    // 查找
    auto it = std::find(arr.begin(), arr.end(), 5);
    if (it != arr.end()) {
        std::cout << "找到 5 在位置: " << std::distance(arr.begin(), it) << "\n";
    }
    
    // 累积
    auto sum = std::accumulate(arr.begin(), arr.end(), 0);
    std::cout << "元素和: " << sum << "\n";
    
    // 变换
    std::array<int, 10> squared;
    std::transform(arr.begin(), arr.end(), squared.begin(),
                   [](int x) { return x * x; });
    
    std::cout << "平方: ";
    for (auto x : squared) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_multidimensional() {
    std::cout << "\n=== 多维数组 ===\n";
    
    // 二维数组
    std::array<std::array<int, 3>, 3> matrix = {{
        {{1, 2, 3}},
        {{4, 5, 6}},
        {{7, 8, 9}}
    }};
    
    std::cout << "3x3矩阵:\n";
    for (const auto& row : matrix) {
        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
    
    // 使用索引访问
    std::cout << "matrix[1][2]: " << matrix[1][2] << "\n";
    
    // 矩阵转置
    std::array<std::array<int, 3>, 3> transposed;
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            transposed[j][i] = matrix[i][j];
        }
    }
    
    std::cout << "转置后:\n";
    for (const auto& row : transposed) {
        for (auto val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

void demonstrate_use_cases() {
    std::cout << "\n=== 实际应用 ===\n";
    
    // 1. 查找表
    std::cout << "\n查找表示例:\n";
    constexpr std::array<int, 13> fibonacci = {
        0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144
    };
    
    auto get_fibonacci = [&](size_t n) -> int {
        return (n < fibonacci.size()) ? fibonacci[n] : -1;
    };
    
    std::cout << "斐波那契数列前13项: ";
    for (size_t i = 0; i < fibonacci.size(); ++i) {
        std::cout << get_fibonacci(i) << " ";
    }
    std::cout << "\n";
    
    // 2. 状态机
    std::cout << "\n状态机示例:\n";
    enum class State { START, RUNNING, PAUSED, STOPPED };
    
    std::array<std::string, 4> state_names = {
        "START", "RUNNING", "PAUSED", "STOPPED"
    };
    
    auto print_state = [&](State s) {
        std::cout << "当前状态: " << state_names[static_cast<int>(s)] << "\n";
    };
    
    print_state(State::START);
    print_state(State::RUNNING);
    print_state(State::PAUSED);
    
    // 3. 固定缓冲区
    std::cout << "\n环形缓冲区:\n";
    class RingBuffer {
    private:
        std::array<int, 5> buffer{};
        size_t head = 0;
        size_t tail = 0;
        size_t count = 0;
        
    public:
        bool push(int value) {
            if (count >= buffer.size()) return false;
            buffer[tail] = value;
            tail = (tail + 1) % buffer.size();
            ++count;
            return true;
        }
        
        bool pop(int& value) {
            if (count == 0) return false;
            value = buffer[head];
            head = (head + 1) % buffer.size();
            --count;
            return true;
        }
        
        void print() const {
            std::cout << "缓冲区: ";
            for (size_t i = 0; i < buffer.size(); ++i) {
                if (i == head && count > 0) std::cout << "[";
                std::cout << buffer[i];
                if (i == (tail - 1 + buffer.size()) % buffer.size() && count > 0) std::cout << "]";
                std::cout << " ";
            }
            std::cout << "(count=" << count << ")\n";
        }
    };
    
    RingBuffer rb;
    
    for (int i = 1; i <= 7; ++i) {
        if (rb.push(i)) {
            std::cout << "推入 " << i << ": ";
        } else {
            std::cout << "缓冲区满，无法推入 " << i << ": ";
        }
        rb.print();
    }
    
    int value;
    while (rb.pop(value)) {
        std::cout << "弹出 " << value << ": ";
        rb.print();
    }
}

int main() {
    std::cout << "C++ Primer Chapter 9: Array 容器\n";
    std::cout << "================================\n";
    
    demonstrate_array_basics();
    demonstrate_vs_c_array();
    demonstrate_compile_time_features();
    demonstrate_algorithms();
    demonstrate_multidimensional();
    demonstrate_use_cases();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 