#include "common.h"

int main() {
    print_separator("vector容器示例");
    
    // vector创建和初始化
    cout << "=== vector创建和初始化 ===" << endl;
    vector<int> vec1;                           // 空vector
    vector<int> vec2(5);                        // 5个元素，值为0
    vector<int> vec3(5, 10);                    // 5个元素，值为10
    vector<int> vec4 = {1, 2, 3, 4, 5};         // 列表初始化
    vector<int> vec5(vec4);                     // 拷贝构造
    
    cout << "vec1大小: " << vec1.size() << endl;
    cout << "vec2: ";
    print_container(vec2);
    cout << "vec3: ";
    print_container(vec3);
    cout << "vec4: ";
    print_container(vec4);
    cout << "vec5: ";
    print_container(vec5);
    
    // vector大小和容量
    cout << "\n=== vector大小和容量 ===" << endl;
    vector<int> sizeDemo = {1, 2, 3, 4, 5};
    cout << "vector: ";
    print_container(sizeDemo);
    cout << "size(): " << sizeDemo.size() << endl;
    cout << "capacity(): " << sizeDemo.capacity() << endl;
    cout << "empty(): " << std::boolalpha << sizeDemo.empty() << endl;
    cout << "max_size(): " << sizeDemo.max_size() << endl;
    
    // 添加元素
    cout << "\n=== 添加元素 ===" << endl;
    vector<int> addDemo;
    cout << "初始vector: ";
    print_container(addDemo);
    
    addDemo.push_back(10);
    addDemo.push_back(20);
    addDemo.push_back(30);
    cout << "添加元素后: ";
    print_container(addDemo);
    
    // 使用emplace_back（C++11）
    addDemo.emplace_back(40);
    cout << "使用emplace_back: ";
    print_container(addDemo);
    
    // 访问元素
    cout << "\n=== 访问元素 ===" << endl;
    vector<int> accessDemo = {10, 20, 30, 40, 50};
    cout << "vector: ";
    print_container(accessDemo);
    
    cout << "第一个元素 [0]: " << accessDemo[0] << endl;
    cout << "最后一个元素: " << accessDemo[accessDemo.size() - 1] << endl;
    cout << "使用at(2): " << accessDemo.at(2) << endl;
    cout << "front(): " << accessDemo.front() << endl;
    cout << "back(): " << accessDemo.back() << endl;
    
    // 修改元素
    cout << "\n=== 修改元素 ===" << endl;
    vector<int> modifyDemo = {1, 2, 3, 4, 5};
    cout << "修改前: ";
    print_container(modifyDemo);
    
    modifyDemo[0] = 100;
    modifyDemo.at(1) = 200;
    cout << "修改后: ";
    print_container(modifyDemo);
    
    // 遍历vector
    cout << "\n=== 遍历vector ===" << endl;
    vector<string> stringVec = {"apple", "banana", "cherry", "date"};
    
    cout << "范围for循环: ";
    for (const auto& item : stringVec) {
        cout << item << " ";
    }
    cout << endl;
    
    cout << "传统for循环: ";
    for (size_t i = 0; i < stringVec.size(); ++i) {
        cout << stringVec[i] << " ";
    }
    cout << endl;
    
    // 插入和删除
    cout << "\n=== 插入和删除 ===" << endl;
    vector<int> insertDemo = {1, 2, 3, 4, 5};
    cout << "原vector: ";
    print_container(insertDemo);
    
    // 插入元素
    insertDemo.insert(insertDemo.begin() + 2, 99);
    cout << "插入99: ";
    print_container(insertDemo);
    
    // 删除最后一个元素
    insertDemo.pop_back();
    cout << "删除最后元素: ";
    print_container(insertDemo);
    
    // 删除指定位置元素
    insertDemo.erase(insertDemo.begin() + 2);
    cout << "删除位置2的元素: ";
    print_container(insertDemo);
    
    // 清空vector
    cout << "\n=== 清空vector ===" << endl;
    vector<int> clearDemo = {1, 2, 3, 4, 5};
    cout << "清空前大小: " << clearDemo.size() << endl;
    clearDemo.clear();
    cout << "清空后大小: " << clearDemo.size() << endl;
    cout << "是否为空: " << clearDemo.empty() << endl;
    
    // vector赋值
    cout << "\n=== vector赋值 ===" << endl;
    vector<int> assignDemo;
    assignDemo.assign(5, 42);  // 赋值5个42
    cout << "assign(5, 42): ";
    print_container(assignDemo);
    
    vector<int> source = {10, 20, 30};
    assignDemo.assign(source.begin(), source.end());
    cout << "assign from iterator: ";
    print_container(assignDemo);
    
    // vector重置大小
    cout << "\n=== vector重置大小 ===" << endl;
    vector<int> resizeDemo = {1, 2, 3};
    cout << "原大小: " << resizeDemo.size() << ", 内容: ";
    print_container(resizeDemo);
    
    resizeDemo.resize(5);
    cout << "resize(5): ";
    print_container(resizeDemo);
    
    resizeDemo.resize(7, 99);
    cout << "resize(7, 99): ";
    print_container(resizeDemo);
    
    resizeDemo.resize(3);
    cout << "resize(3): ";
    print_container(resizeDemo);
    
    // 二维vector
    cout << "\n=== 二维vector ===" << endl;
    vector<vector<int>> matrix2D(3, vector<int>(4, 1));
    cout << "3x4矩阵（初始值为1）:\n";
    for (size_t i = 0; i < matrix2D.size(); ++i) {
        for (size_t j = 0; j < matrix2D[i].size(); ++j) {
            cout << matrix2D[i][j] << " ";
        }
        cout << endl;
    }
    
    // 修改二维vector
    matrix2D[1][2] = 99;
    cout << "修改[1][2]后:\n";
    for (const auto& row : matrix2D) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    
    // vector算法示例
    cout << "\n=== vector算法示例 ===" << endl;
    vector<int> algDemo = {5, 2, 8, 1, 9, 3};
    cout << "原vector: ";
    print_container(algDemo);
    
    // 排序
    sort(algDemo.begin(), algDemo.end());
    cout << "排序后: ";
    print_container(algDemo);
    
    // 查找
    auto it = find(algDemo.begin(), algDemo.end(), 5);
    if (it != algDemo.end()) {
        cout << "找到5，位置: " << (it - algDemo.begin()) << endl;
    }
    
    // 计数
    int count = std::count(algDemo.begin(), algDemo.end(), 5);
    cout << "元素5的个数: " << count << endl;
    
    // vector性能提示
    cout << "\n=== vector性能提示 ===" << endl;
    vector<int> perfDemo;
    perfDemo.reserve(1000);  // 预分配空间
    cout << "预分配1000个元素的空间" << endl;
    cout << "capacity(): " << perfDemo.capacity() << endl;
    cout << "size(): " << perfDemo.size() << endl;
    
    // 动态扩容演示
    cout << "\n=== 动态扩容演示 ===" << endl;
    vector<int> growDemo;
    cout << "动态扩容过程:" << endl;
    
    for (int i = 0; i < 10; ++i) {
        growDemo.push_back(i);
        cout << "size: " << growDemo.size() 
             << ", capacity: " << growDemo.capacity() << endl;
    }
    
    print_separator("vector容器示例完成");
    
    return 0;
} 