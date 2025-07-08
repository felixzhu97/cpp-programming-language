/**
 * @file container_adapters.cpp
 * @brief 容器适配器演示 - stack、queue、priority_queue及自定义适配器
 */

#include <iostream>
#include <stack>
#include <queue>
#include <queue>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <functional>

// 自定义Stack适配器实现
template<typename T, typename Container = std::deque<T>>
class MyStack {
private:
    Container container;
    
public:
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    
    bool empty() const { return container.empty(); }
    size_type size() const { return container.size(); }
    
    void push(const value_type& value) {
        container.push_back(value);
    }
    
    void pop() {
        container.pop_back();
    }
    
    value_type& top() {
        return container.back();
    }
    
    const value_type& top() const {
        return container.back();
    }
};

// 自定义PriorityQueue适配器实现  
template<typename T, typename Container = std::vector<T>, 
         typename Compare = std::less<typename Container::value_type>>
class MyPriorityQueue {
private:
    Container container;
    Compare comp;
    
public:
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    
    MyPriorityQueue() = default;
    explicit MyPriorityQueue(const Compare& compare) : comp(compare) {}
    
    bool empty() const { return container.empty(); }
    size_type size() const { return container.size(); }
    
    const value_type& top() const {
        return container.front();
    }
    
    void push(const value_type& value) {
        container.push_back(value);
        std::push_heap(container.begin(), container.end(), comp);
    }
    
    void pop() {
        std::pop_heap(container.begin(), container.end(), comp);
        container.pop_back();
    }
};

// 限容队列实现
template<typename T>
class BoundedQueue {
private:
    std::queue<T> queue;
    size_t max_size;
    
public:
    BoundedQueue(size_t max_sz) : max_size(max_sz) {}
    
    bool push(const T& value) {
        if (queue.size() >= max_size) {
            return false;  // 队列已满
        }
        queue.push(value);
        return true;
    }
    
    bool pop(T& value) {
        if (queue.empty()) {
            return false;  // 队列为空
        }
        value = queue.front();
        queue.pop();
        return true;
    }
    
    size_t size() const { return queue.size(); }
    bool empty() const { return queue.empty(); }
    bool full() const { return queue.size() >= max_size; }
};

void demonstrate_stack() {
    std::cout << "\n=== Stack 适配器 ===\n";
    
    // 默认使用 deque 作为底层容器
    std::stack<int> st;
    
    // 入栈
    for (int i = 1; i <= 5; ++i) {
        st.push(i);
        std::cout << "push(" << i << "), size: " << st.size() << "\n";
    }
    
    // 栈操作
    std::cout << "\n栈操作:\n";
    std::cout << "top(): " << st.top() << "\n";
    std::cout << "empty(): " << std::boolalpha << st.empty() << "\n";
    
    // 出栈
    std::cout << "\n出栈序列: ";
    while (!st.empty()) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << "\n";
    
    // 不同底层容器的 stack
    std::cout << "\n不同底层容器:\n";
    std::stack<int, std::vector<int>> vector_stack;
    std::stack<int, std::list<int>> list_stack;
    
    for (int i = 1; i <= 3; ++i) {
        vector_stack.push(i);
        list_stack.push(i * 10);
    }
    
    std::cout << "vector_stack top: " << vector_stack.top() << "\n";
    std::cout << "list_stack top: " << list_stack.top() << "\n";
}

void demonstrate_queue() {
    std::cout << "\n=== Queue 适配器 ===\n";
    
    std::queue<std::string> q;
    
    // 入队
    std::vector<std::string> items = {"First", "Second", "Third", "Fourth"};
    for (const auto& item : items) {
        q.push(item);
        std::cout << "push(" << item << "), size: " << q.size() << "\n";
    }
    
    // 队列操作
    std::cout << "\n队列操作:\n";
    std::cout << "front(): " << q.front() << "\n";
    std::cout << "back(): " << q.back() << "\n";
    std::cout << "size(): " << q.size() << "\n";
    
    // 出队
    std::cout << "\n出队序列: ";
    while (!q.empty()) {
        std::cout << q.front() << " ";
        q.pop();
    }
    std::cout << "\n";
    
    // 使用 list 作为底层容器
    std::cout << "\n使用 list 底层容器:\n";
    std::queue<int, std::list<int>> list_queue;
    
    for (int i = 10; i <= 30; i += 10) {
        list_queue.push(i);
    }
    
    std::cout << "list_queue 出队: ";
    while (!list_queue.empty()) {
        std::cout << list_queue.front() << " ";
        list_queue.pop();
    }
    std::cout << "\n";
}

void demonstrate_priority_queue() {
    std::cout << "\n=== Priority_queue 适配器 ===\n";
    
    // 默认大顶堆
    std::priority_queue<int> max_heap;
    
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    std::cout << "插入序列: ";
    for (auto num : nums) {
        std::cout << num << " ";
        max_heap.push(num);
    }
    std::cout << "\n";
    
    std::cout << "大顶堆出队: ";
    while (!max_heap.empty()) {
        std::cout << max_heap.top() << " ";
        max_heap.pop();
    }
    std::cout << "\n";
    
    // 小顶堆
    std::cout << "\n小顶堆:\n";
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    
    for (auto num : nums) {
        min_heap.push(num);
    }
    
    std::cout << "小顶堆出队: ";
    while (!min_heap.empty()) {
        std::cout << min_heap.top() << " ";
        min_heap.pop();
    }
    std::cout << "\n";
    
    // 自定义比较器
    std::cout << "\n自定义比较器:\n";
    
    struct Person {
        std::string name;
        int age;
        
        Person(const std::string& n, int a) : name(n), age(a) {}
    };
    
    auto person_compare = [](const Person& a, const Person& b) {
        return a.age < b.age;  // 按年龄降序
    };
    
    std::priority_queue<Person, std::vector<Person>, decltype(person_compare)> person_heap(person_compare);
    
    person_heap.emplace("Alice", 25);
    person_heap.emplace("Bob", 30);
    person_heap.emplace("Charlie", 20);
    person_heap.emplace("David", 35);
    
    std::cout << "按年龄优先级出队: ";
    while (!person_heap.empty()) {
        const auto& p = person_heap.top();
        std::cout << p.name << "(" << p.age << ") ";
        person_heap.pop();
    }
    std::cout << "\n";
}

void demonstrate_adapter_principles() {
    std::cout << "\n=== 适配器实现原理 ===\n";
    
    std::cout << "自定义 Stack 测试:\n";
    MyStack<int> my_stack;
    
    for (int i = 1; i <= 3; ++i) {
        my_stack.push(i);
        std::cout << "push(" << i << "), top: " << my_stack.top() << "\n";
    }
    
    while (!my_stack.empty()) {
        std::cout << "pop: " << my_stack.top() << "\n";
        my_stack.pop();
    }
    
    std::cout << "\n自定义 PriorityQueue 测试:\n";
    MyPriorityQueue<int> my_pq;
    
    std::vector<int> test_nums = {5, 2, 8, 1, 9};
    for (auto num : test_nums) {
        my_pq.push(num);
        std::cout << "push(" << num << "), top: " << my_pq.top() << "\n";
    }
    
    std::cout << "出队: ";
    while (!my_pq.empty()) {
        std::cout << my_pq.top() << " ";
        my_pq.pop();
    }
    std::cout << "\n";
}

void demonstrate_practical_applications() {
    std::cout << "\n=== 实际应用示例 ===\n";
    
    // 1. 表达式求值（使用栈）
    std::cout << "\n1. 后缀表达式求值:\n";
    
    auto evaluate_postfix = [](const std::vector<std::string>& tokens) -> int {
        std::stack<int> operands;
        
        for (const auto& token : tokens) {
            if (token == "+") {
                int b = operands.top(); operands.pop();
                int a = operands.top(); operands.pop();
                operands.push(a + b);
            } else if (token == "-") {
                int b = operands.top(); operands.pop();
                int a = operands.top(); operands.pop();
                operands.push(a - b);
            } else if (token == "*") {
                int b = operands.top(); operands.pop();
                int a = operands.top(); operands.pop();
                operands.push(a * b);
            } else if (token == "/") {
                int b = operands.top(); operands.pop();
                int a = operands.top(); operands.pop();
                operands.push(a / b);
            } else {
                operands.push(std::stoi(token));
            }
        }
        
        return operands.top();
    };
    
    std::vector<std::string> postfix = {"5", "3", "+", "2", "*", "7", "-"};
    std::cout << "   表达式: ";
    for (const auto& token : postfix) std::cout << token << " ";
    std::cout << "\n   结果: " << evaluate_postfix(postfix) << " (应该是9)\n";
    
    // 2. 任务调度（使用优先队列）
    std::cout << "\n2. 任务优先级调度:\n";
    
    struct Task {
        std::string name;
        int priority;
        int id;
        
        Task(const std::string& n, int p, int i) : name(n), priority(p), id(i) {}
    };
    
    auto task_compare = [](const Task& a, const Task& b) {
        if (a.priority != b.priority) {
            return a.priority < b.priority;  // 高优先级先执行
        }
        return a.id > b.id;  // 同优先级，先来先服务
    };
    
    std::priority_queue<Task, std::vector<Task>, decltype(task_compare)> task_queue(task_compare);
    
    task_queue.emplace("低优先级任务", 1, 1);
    task_queue.emplace("紧急任务", 5, 2);
    task_queue.emplace("普通任务", 3, 3);
    task_queue.emplace("重要任务", 4, 4);
    task_queue.emplace("另一个紧急任务", 5, 5);
    
    std::cout << "   任务执行顺序:\n";
    while (!task_queue.empty()) {
        const auto& task = task_queue.top();
        std::cout << "     " << task.name << " (优先级:" << task.priority 
                  << ", ID:" << task.id << ")\n";
        task_queue.pop();
    }
    
    // 3. 广度优先搜索（使用队列）
    std::cout << "\n3. 广度优先搜索模拟:\n";
    
    struct GraphNode {
        int value;
        std::vector<int> neighbors;
        
        GraphNode(int v) : value(v) {}
    };
    
    std::vector<GraphNode> graph = {
        GraphNode(0),  // 节点 0
        GraphNode(1),  // 节点 1
        GraphNode(2),  // 节点 2
        GraphNode(3),  // 节点 3
        GraphNode(4)   // 节点 4
    };
    
    // 构建图的邻接关系
    graph[0].neighbors = {1, 2};
    graph[1].neighbors = {0, 3, 4};
    graph[2].neighbors = {0, 4};
    graph[3].neighbors = {1};
    graph[4].neighbors = {1, 2};
    
    auto bfs = [&](int start) {
        std::vector<bool> visited(graph.size(), false);
        std::queue<int> bfs_queue;
        
        bfs_queue.push(start);
        visited[start] = true;
        
        std::cout << "   BFS 遍历顺序: ";
        while (!bfs_queue.empty()) {
            int current = bfs_queue.front();
            bfs_queue.pop();
            
            std::cout << current << " ";
            
            for (int neighbor : graph[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    bfs_queue.push(neighbor);
                }
            }
        }
        std::cout << "\n";
    };
    
    bfs(0);  // 从节点 0 开始 BFS
    
    // 4. 限容队列
    std::cout << "\n4. 限容队列实现:\n";
    
    BoundedQueue<int> bounded_queue(3);
    
    std::cout << "   限容队列测试 (最大容量3):\n";
    for (int i = 1; i <= 5; ++i) {
        if (bounded_queue.push(i)) {
            std::cout << "     成功推入 " << i << ", 队列大小: " << bounded_queue.size() << "\n";
        } else {
            std::cout << "     队列已满，无法推入 " << i << "\n";
        }
    }
    
    int value;
    while (bounded_queue.pop(value)) {
        std::cout << "     弹出 " << value << ", 队列大小: " << bounded_queue.size() << "\n";
    }
}

int main() {
    std::cout << "C++ Primer Chapter 9: 容器适配器\n";
    std::cout << "===============================\n";
    
    demonstrate_stack();
    demonstrate_queue();
    demonstrate_priority_queue();
    demonstrate_adapter_principles();
    demonstrate_practical_applications();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 