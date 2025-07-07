#include "common.h"

int main() {
    print_separator("迭代器示例");
    
    // 基本迭代器概念
    cout << "=== 基本迭代器概念 ===" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    
    cout << "vector内容: ";
    print_container(vec);
    
    // begin()和end()
    cout << "\n=== begin()和end() ===" << endl;
    auto it_begin = vec.begin();
    auto it_end = vec.end();
    
    cout << "第一个元素: " << *it_begin << endl;
    cout << "迭代器遍历: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // 迭代器类型
    cout << "\n=== 迭代器类型 ===" << endl;
    vector<int>::iterator iter = vec.begin();
    vector<int>::const_iterator citer = vec.cbegin();
    
    cout << "可变迭代器: " << *iter << endl;
    cout << "常量迭代器: " << *citer << endl;
    
    // 修改元素
    *iter = 100;
    cout << "修改后第一个元素: " << vec[0] << endl;
    // *citer = 200;  // 编译错误！const_iterator不能修改元素
    
    // 反向迭代器
    cout << "\n=== 反向迭代器 ===" << endl;
    cout << "正向遍历: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    cout << "反向遍历: ";
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // 迭代器运算
    cout << "\n=== 迭代器运算 ===" << endl;
    auto it = vec.begin();
    cout << "第一个元素: " << *it << endl;
    
    ++it;  // 前进
    cout << "++it后: " << *it << endl;
    
    --it;  // 后退
    cout << "--it后: " << *it << endl;
    
    it += 2;  // 前进2个位置
    cout << "it += 2后: " << *it << endl;
    
    // 迭代器距离
    cout << "\n=== 迭代器距离 ===" << endl;
    auto first = vec.begin();
    auto last = vec.end();
    auto middle = vec.begin() + 2;
    
    cout << "容器大小: " << distance(first, last) << endl;
    cout << "begin到middle距离: " << distance(first, middle) << endl;
    cout << "middle到end距离: " << distance(middle, last) << endl;
    
    // 字符串迭代器
    cout << "\n=== 字符串迭代器 ===" << endl;
    string str = "Hello";
    cout << "字符串: " << str << endl;
    
    cout << "字符遍历: ";
    for (auto it = str.begin(); it != str.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // 修改字符串
    for (auto it = str.begin(); it != str.end(); ++it) {
        *it = toupper(*it);
    }
    cout << "转大写后: " << str << endl;
    
    // 数组迭代器
    cout << "\n=== 数组迭代器 ===" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    int* arr_begin = arr;
    int* arr_end = arr + 5;
    
    cout << "数组遍历: ";
    for (int* it = arr_begin; it != arr_end; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // C++11 begin/end函数
    cout << "\n=== C++11 begin/end函数 ===" << endl;
    cout << "使用std::begin/end: ";
    for (auto it = std::begin(arr); it != std::end(arr); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // 迭代器与算法
    cout << "\n=== 迭代器与算法 ===" << endl;
    vector<int> algVec = {5, 2, 8, 1, 9};
    cout << "原vector: ";
    print_container(algVec);
    
    // 查找
    auto found = find(algVec.begin(), algVec.end(), 8);
    if (found != algVec.end()) {
        cout << "找到8，位置: " << distance(algVec.begin(), found) << endl;
    }
    
    // 排序
    sort(algVec.begin(), algVec.end());
    cout << "排序后: ";
    print_container(algVec);
    
    // 部分排序
    vector<int> partialVec = {9, 1, 8, 2, 7, 3, 6};
    cout << "部分排序前: ";
    print_container(partialVec);
    
    sort(partialVec.begin(), partialVec.begin() + 3);
    cout << "前3个元素排序: ";
    print_container(partialVec);
    
    // 迭代器失效
    cout << "\n=== 迭代器失效 ===" << endl;
    vector<int> invalidVec = {1, 2, 3, 4, 5};
    auto invalid_it = invalidVec.begin();
    
    cout << "原vector: ";
    print_container(invalidVec);
    cout << "迭代器指向: " << *invalid_it << endl;
    
    invalidVec.push_back(6);  // 可能导致迭代器失效
    cout << "添加元素后: ";
    print_container(invalidVec);
    
    // 重新获取迭代器
    invalid_it = invalidVec.begin();
    cout << "重新获取迭代器: " << *invalid_it << endl;
    
    // 插入操作
    cout << "\n=== 插入操作 ===" << endl;
    vector<int> insertVec = {1, 2, 4, 5};
    cout << "插入前: ";
    print_container(insertVec);
    
    auto insert_it = insertVec.begin() + 2;
    insertVec.insert(insert_it, 3);
    cout << "插入3后: ";
    print_container(insertVec);
    
    // 删除操作
    cout << "\n=== 删除操作 ===" << endl;
    vector<int> eraseVec = {1, 2, 3, 4, 5};
    cout << "删除前: ";
    print_container(eraseVec);
    
    auto erase_it = eraseVec.begin() + 2;
    eraseVec.erase(erase_it);
    cout << "删除位置2后: ";
    print_container(eraseVec);
    
    // 范围删除
    vector<int> rangeEraseVec = {1, 2, 3, 4, 5, 6, 7};
    cout << "范围删除前: ";
    print_container(rangeEraseVec);
    
    rangeEraseVec.erase(rangeEraseVec.begin() + 2, rangeEraseVec.begin() + 5);
    cout << "删除位置2-4后: ";
    print_container(rangeEraseVec);
    
    // 迭代器类别
    cout << "\n=== 迭代器类别 ===" << endl;
    cout << "输入迭代器：只读，只能前进" << endl;
    cout << "输出迭代器：只写，只能前进" << endl;
    cout << "前向迭代器：可读写，只能前进" << endl;
    cout << "双向迭代器：可读写，可前进后退" << endl;
    cout << "随机访问迭代器：可读写，支持随机访问" << endl;
    
    // 实用技巧
    cout << "\n=== 实用技巧 ===" << endl;
    vector<int> tips = {1, 2, 3, 4, 5};
    
    // 安全删除
    cout << "安全删除偶数: ";
    for (auto it = tips.begin(); it != tips.end(); ) {
        if (*it % 2 == 0) {
            it = tips.erase(it);  // erase返回下一个有效迭代器
        } else {
            ++it;
        }
    }
    print_container(tips);
    
    // 迭代器适配器
    cout << "\n=== 迭代器适配器 ===" << endl;
    vector<int> source = {1, 2, 3, 4, 5};
    vector<int> dest;
    
    // 使用back_inserter
    copy(source.begin(), source.end(), back_inserter(dest));
    cout << "拷贝结果: ";
    print_container(dest);
    
    print_separator("迭代器示例完成");
    
    return 0;
} 