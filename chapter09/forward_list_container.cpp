/**
 * @file forward_list_container.cpp
 * @brief forward_list 容器演示 - 单向链表操作、内存效率、特殊迭代器
 */

#include <iostream>
#include <forward_list>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>

void demonstrate_forward_list_basics() {
    std::cout << "\n=== Forward_list 基本操作 ===\n";
    
    // 构造
    std::forward_list<int> fl1;
    std::forward_list<int> fl2(5, 10);
    std::forward_list<int> fl3{1, 2, 3, 4, 5};
    
    std::cout << "fl3 内容: ";
    for (auto x : fl3) std::cout << x << " ";
    std::cout << "\n";
    
    // 只支持前向迭代
    std::cout << "\n迭代器特性:\n";
    auto it = fl3.begin();
    std::cout << "第一个元素: " << *it << "\n";
    ++it;
    std::cout << "第二个元素: " << *it << "\n";
    // --it;  // 错误：不支持后退
    
    // 元素访问（只有 front）
    std::cout << "front(): " << fl3.front() << "\n";
    // std::cout << fl3.back();  // 错误：没有 back()
    
    // 修改操作
    fl3.push_front(0);
    std::cout << "push_front(0) 后: ";
    for (auto x : fl3) std::cout << x << " ";
    std::cout << "\n";
    
    fl3.pop_front();
    std::cout << "pop_front() 后: ";
    for (auto x : fl3) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_special_operations() {
    std::cout << "\n=== Forward_list 特殊操作 ===\n";
    
    std::forward_list<int> fl{1, 2, 3, 4, 5};
    
    // insert_after 和 erase_after
    std::cout << "\ninsert_after 和 erase_after:\n";
    std::cout << "原始: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
    
    auto it = fl.begin();
    ++it;  // 指向第二个元素 (2)
    fl.insert_after(it, 99);
    std::cout << "在第二个元素后插入99: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
    
    it = fl.begin();
    ++it;  // 重新定位到第二个元素
    fl.erase_after(it);  // 删除第三个元素
    std::cout << "删除第三个元素: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
    
    // before_begin() 的使用
    std::cout << "\nbefore_begin() 的使用:\n";
    fl.insert_after(fl.before_begin(), 0);  // 在开头插入
    std::cout << "在开头插入0: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
    
    fl.erase_after(fl.before_begin());  // 删除第一个元素
    std::cout << "删除第一个元素: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
}

void demonstrate_algorithms() {
    std::cout << "\n=== 算法和操作 ===\n";
    
    // remove 和 remove_if
    std::forward_list<int> fl{1, 2, 3, 2, 4, 2, 5};
    std::cout << "原始: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
    
    fl.remove(2);
    std::cout << "remove(2) 后: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
    
    fl = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    fl.remove_if([](int x) { return x % 2 == 0; });
    std::cout << "remove_if(偶数) 后: ";
    for (auto x : fl) std::cout << x << " ";
    std::cout << "\n";
    
    // unique
    std::forward_list<int> dup{1, 1, 2, 2, 2, 3, 4, 4, 5};
    std::cout << "\n去重操作:\n";
    std::cout << "原始: ";
    for (auto x : dup) std::cout << x << " ";
    std::cout << "\n";
    
    dup.unique();
    std::cout << "unique() 后: ";
    for (auto x : dup) std::cout << x << " ";
    std::cout << "\n";
    
    // sort
    std::forward_list<int> unsorted{5, 2, 8, 1, 9, 3};
    std::cout << "\n排序操作:\n";
    std::cout << "原始: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";
    
    unsorted.sort();
    std::cout << "sort() 后: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";
    
    // merge
    std::forward_list<int> sorted1{1, 3, 5};
    std::forward_list<int> sorted2{2, 4, 6, 7};
    
    std::cout << "\n合并操作:\n";
    std::cout << "sorted1: ";
    for (auto x : sorted1) std::cout << x << " ";
    std::cout << "\nsorted2: ";
    for (auto x : sorted2) std::cout << x << " ";
    std::cout << "\n";
    
    sorted1.merge(sorted2);
    std::cout << "merge 后 sorted1: ";
    for (auto x : sorted1) std::cout << x << " ";
    std::cout << "\nsorted2: ";
    for (auto x : sorted2) std::cout << x << " ";
    std::cout << " (已清空)\n";
    
    // splice_after
    std::forward_list<int> fl1{1, 2, 3};
    std::forward_list<int> fl2{10, 20, 30};
    
    std::cout << "\nsplice_after 操作:\n";
    std::cout << "fl1: ";
    for (auto x : fl1) std::cout << x << " ";
    std::cout << "\nfl2: ";
    for (auto x : fl2) std::cout << x << " ";
    std::cout << "\n";
    
    auto it1 = fl1.begin();
    ++it1;  // 指向元素2
    fl1.splice_after(it1, fl2);  // 在元素2后拼接fl2
    
    std::cout << "splice_after 后 fl1: ";
    for (auto x : fl1) std::cout << x << " ";
    std::cout << "\nfl2: ";
    for (auto x : fl2) std::cout << x << " ";
    std::cout << " (已清空)\n";
}

void demonstrate_memory_efficiency() {
    std::cout << "\n=== 内存效率对比 ===\n";
    
    std::cout << "内存开销分析:\n";
    std::cout << "int 大小: " << sizeof(int) << " bytes\n";
    std::cout << "指针大小: " << sizeof(void*) << " bytes\n";
    
    // 估算每个节点的开销
    struct ForwardNode {
        int data;
        ForwardNode* next;
    };
    
    struct ListNode {
        int data;
        ListNode* next;
        ListNode* prev;
    };
    
    std::cout << "forward_list 节点开销: " << sizeof(ForwardNode) << " bytes\n";
    std::cout << "list 节点开销: " << sizeof(ListNode) << " bytes\n";
    std::cout << "vector 元素开销: " << sizeof(int) << " bytes\n";
    
    std::cout << "\nforward_list vs list 内存节省: " 
              << static_cast<double>(sizeof(ListNode)) / sizeof(ForwardNode) << "x\n";
    
    const int N = 10000;
    auto measure_time = [](auto func, const std::string& desc) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "   " << desc << ": " << duration.count() << " μs\n";
        return duration.count();
    };
    
    std::cout << "\n构造性能对比:\n";
    
    auto fl_time = measure_time([&]() {
        std::forward_list<int> fl;
        for (int i = 0; i < N; ++i) {
            fl.push_front(i);
        }
    }, "forward_list::push_front");
    
    auto list_time = measure_time([&]() {
        std::list<int> lst;
        for (int i = 0; i < N; ++i) {
            lst.push_front(i);
        }
    }, "list::push_front");
    
    std::cout << "forward_list vs list: " 
              << static_cast<double>(list_time) / fl_time << "x\n";
}

void demonstrate_limitations() {
    std::cout << "\n=== 使用限制 ===\n";
    
    std::forward_list<int> fl{1, 2, 3, 4, 5};
    
    // 1. 没有 size() 方法
    std::cout << "1. 没有 size() 方法:\n";
    // std::cout << fl.size();  // 错误：没有 size()
    
    auto size = std::distance(fl.begin(), fl.end());
    std::cout << "   需要使用 distance(): " << size << "\n";
    
    // 2. 没有反向迭代器
    std::cout << "\n2. 没有反向迭代器:\n";
    // for (auto it = fl.rbegin(); it != fl.rend(); ++it)  // 错误
    std::cout << "   不支持 rbegin()/rend()\n";
    
    // 3. 只能前向遍历
    std::cout << "\n3. 只能前向遍历:\n";
    auto it = fl.begin();
    std::cout << "   可以: ++it -> " << *(++it) << "\n";
    // --it;  // 错误：不能后退
    std::cout << "   不可以: --it\n";
    
    // 4. 插入删除的限制
    std::cout << "\n4. 插入删除的特殊性:\n";
    std::cout << "   - 只有 insert_after/erase_after\n";
    std::cout << "   - 需要 before_begin() 来操作第一个元素\n";
    std::cout << "   - 没有 push_back/pop_back\n";
}

void demonstrate_use_cases() {
    std::cout << "\n=== 适用场景 ===\n";
    
    // 1. 简单的栈
    std::cout << "\n1. 简单栈实现:\n";
    class SimpleStack {
    private:
        std::forward_list<int> data;
        
    public:
        void push(int value) {
            data.push_front(value);
        }
        
        bool pop(int& value) {
            if (data.empty()) return false;
            value = data.front();
            data.pop_front();
            return true;
        }
        
        bool top(int& value) const {
            if (data.empty()) return false;
            value = data.front();
            return true;
        }
        
        bool empty() const {
            return data.empty();
        }
        
        void print() const {
            std::cout << "     栈内容: ";
            for (auto x : data) std::cout << x << " ";
            std::cout << "(栈顶在左)\n";
        }
    };
    
    SimpleStack stack;
    
    for (int i = 1; i <= 5; ++i) {
        stack.push(i);
        std::cout << "   push(" << i << "): ";
        stack.print();
    }
    
    int value;
    while (stack.pop(value)) {
        std::cout << "   pop() -> " << value << ": ";
        stack.print();
    }
    
    // 2. 内存敏感的场景
    std::cout << "\n2. 内存敏感场景:\n";
    std::cout << "   - 嵌入式系统\n";
    std::cout << "   - 只需要单向遍历的链表\n";
    std::cout << "   - 频繁插入删除，但不需要双向访问\n";
    std::cout << "   - 实现其他数据结构的基础组件\n";
    
    // 3. 链表归并排序
    std::cout << "\n3. 链表归并排序示例:\n";
    std::forward_list<int> unsorted{64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "   排序前: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";
    
    // 使用内置排序
    unsorted.sort();
    
    std::cout << "   排序后: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n   forward_list::sort() 是原地排序，内存效率高\n";
}

int main() {
    std::cout << "C++ Primer Chapter 9: Forward_list 容器\n";
    std::cout << "=======================================\n";
    
    demonstrate_forward_list_basics();
    demonstrate_special_operations();
    demonstrate_algorithms();
    demonstrate_memory_efficiency();
    demonstrate_limitations();
    demonstrate_use_cases();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 