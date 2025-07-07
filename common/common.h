#ifndef COMMON_H
#define COMMON_H

// 标准库头文件
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <numeric>
#include <iterator>
#include <tuple>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <regex>
#include <random>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <cassert>

// 常用命名空间
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::make_shared;
using std::make_unique;
using std::to_string;

// 工具函数和宏
#define PRINT_FUNC_NAME() cout << "=== " << __FUNCTION__ << " ===" << endl

// 用于输出分隔线
inline void print_separator(const string& title = "") {
    cout << "\n" << std::string(50, '-') << endl;
    if (!title.empty()) {
        cout << title << endl;
        cout << std::string(50, '-') << endl;
    }
}

// 用于暂停程序等待用户输入
inline void pause() {
    cout << "按回车键继续...";
    cin.ignore();
    cin.get();
}

// 用于输出容器内容
template<typename Container>
void print_container(const Container& container, const string& delimiter = " ") {
    for (const auto& item : container) {
        cout << item << delimiter;
    }
    cout << endl;
}

// 用于生成随机数
inline int random_int(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

// 用于计时
class Timer {
public:
    Timer() : start_time(std::chrono::high_resolution_clock::now()) {}
    
    double elapsed() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        return duration.count() / 1000.0; // 返回毫秒
    }
    
    void reset() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    
private:
    std::chrono::high_resolution_clock::time_point start_time;
};

#endif // COMMON_H 