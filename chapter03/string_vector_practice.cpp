#include "common.h"

// 练习1：字符串处理函数
vector<string> splitString(const string& str, char delimiter) {
    vector<string> result;
    string current;
    
    for (char c : str) {
        if (c == delimiter) {
            if (!current.empty()) {
                result.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }
    
    if (!current.empty()) {
        result.push_back(current);
    }
    
    return result;
}

// 练习2：统计单词频率
void wordFrequency(const string& text) {
    cout << "=== 单词频率统计 ===" << endl;
    cout << "文本: " << text << endl;
    
    // 转换为小写并替换标点符号
    string processed;
    for (char c : text) {
        if (isalpha(c)) {
            processed += tolower(c);
        } else if (isspace(c)) {
            processed += ' ';
        }
    }
    
    // 分割单词
    vector<string> words = splitString(processed, ' ');
    
    // 统计频率（简单版本）
    vector<string> uniqueWords;
    vector<int> counts;
    
    for (const string& word : words) {
        if (word.empty()) continue;
        
        bool found = false;
        for (size_t i = 0; i < uniqueWords.size(); ++i) {
            if (uniqueWords[i] == word) {
                counts[i]++;
                found = true;
                break;
            }
        }
        
        if (!found) {
            uniqueWords.push_back(word);
            counts.push_back(1);
        }
    }
    
    cout << "单词频率:" << endl;
    for (size_t i = 0; i < uniqueWords.size(); ++i) {
        cout << uniqueWords[i] << ": " << counts[i] << endl;
    }
}

// 练习3：矩阵操作
void matrixOperations() {
    cout << "=== 矩阵操作 ===" << endl;
    
    // 创建矩阵
    vector<vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    vector<vector<int>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    
    cout << "矩阵1:" << endl;
    for (const auto& row : matrix1) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    
    cout << "矩阵2:" << endl;
    for (const auto& row : matrix2) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    
    // 矩阵加法
    vector<vector<int>> sum(3, vector<int>(3));
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            sum[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    
    cout << "矩阵1 + 矩阵2:" << endl;
    for (const auto& row : sum) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// 练习4：文本处理工具
void textProcessingTool() {
    cout << "=== 文本处理工具 ===" << endl;
    
    string text = "Hello, World! This is a sample text. Hello again!";
    cout << "原始文本: " << text << endl;
    
    // 统计字符
    int letters = 0, digits = 0, spaces = 0, punctuation = 0;
    for (char c : text) {
        if (isalpha(c)) letters++;
        else if (isdigit(c)) digits++;
        else if (isspace(c)) spaces++;
        else punctuation++;
    }
    
    cout << "字符统计:" << endl;
    cout << "字母: " << letters << endl;
    cout << "数字: " << digits << endl;
    cout << "空格: " << spaces << endl;
    cout << "标点: " << punctuation << endl;
    
    // 反转单词
    vector<string> words = splitString(text, ' ');
    cout << "反转单词顺序: ";
    for (auto it = words.rbegin(); it != words.rend(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // 查找最长单词
    string longestWord;
    for (const string& word : words) {
        string cleanWord;
        for (char c : word) {
            if (isalpha(c)) {
                cleanWord += c;
            }
        }
        if (cleanWord.length() > longestWord.length()) {
            longestWord = cleanWord;
        }
    }
    cout << "最长单词: " << longestWord << " (长度: " << longestWord.length() << ")" << endl;
}

// 练习5：动态数组练习
void dynamicArrayPractice() {
    cout << "=== 动态数组练习 ===" << endl;
    
    vector<int> numbers;
    
    // 添加斐波那契数列的前10项
    numbers.push_back(0);
    numbers.push_back(1);
    
    for (int i = 2; i < 10; ++i) {
        numbers.push_back(numbers[i-1] + numbers[i-2]);
    }
    
    cout << "斐波那契数列前10项: ";
    print_container(numbers);
    
    // 删除偶数
    cout << "删除偶数: ";
    for (auto it = numbers.begin(); it != numbers.end(); ) {
        if (*it % 2 == 0) {
            it = numbers.erase(it);
        } else {
            ++it;
        }
    }
    print_container(numbers);
    
    // 排序并查找
    sort(numbers.begin(), numbers.end());
    cout << "排序后: ";
    print_container(numbers);
    
    int target = 5;
    auto found = find(numbers.begin(), numbers.end(), target);
    if (found != numbers.end()) {
        cout << "找到" << target << "，位置: " << distance(numbers.begin(), found) << endl;
    } else {
        cout << "未找到" << target << endl;
    }
}

// 练习6：字符串模式匹配
void patternMatching() {
    cout << "=== 字符串模式匹配 ===" << endl;
    
    string text = "The quick brown fox jumps over the lazy dog";
    string pattern = "fox";
    
    cout << "文本: " << text << endl;
    cout << "模式: " << pattern << endl;
    
    // 查找所有匹配位置
    vector<size_t> positions;
    size_t pos = text.find(pattern);
    
    while (pos != string::npos) {
        positions.push_back(pos);
        pos = text.find(pattern, pos + 1);
    }
    
    cout << "找到" << positions.size() << "个匹配" << endl;
    for (size_t position : positions) {
        cout << "位置: " << position << endl;
    }
    
    // 替换所有匹配
    string replaced = text;
    string replacement = "cat";
    pos = 0;
    while ((pos = replaced.find(pattern, pos)) != string::npos) {
        replaced.replace(pos, pattern.length(), replacement);
        pos += replacement.length();
    }
    
    cout << "替换后: " << replaced << endl;
}

// 练习7：成绩管理系统
void gradeManagement() {
    cout << "=== 成绩管理系统 ===" << endl;
    
    vector<string> students = {"张三", "李四", "王五", "赵六", "孙七"};
    vector<vector<int>> grades = {
        {85, 92, 78, 88},  // 张三：语文，数学，英语，物理
        {79, 85, 82, 90},  // 李四
        {92, 88, 85, 87},  // 王五
        {88, 79, 90, 85},  // 赵六
        {91, 93, 89, 92}   // 孙七
    };
    
    vector<string> subjects = {"语文", "数学", "英语", "物理"};
    
    // 显示成绩表
    cout << "学生成绩表:" << endl;
    cout << "姓名\t";
    for (const string& subject : subjects) {
        cout << subject << "\t";
    }
    cout << "平均分" << endl;
    
    for (size_t i = 0; i < students.size(); ++i) {
        cout << students[i] << "\t";
        int total = 0;
        for (size_t j = 0; j < grades[i].size(); ++j) {
            cout << grades[i][j] << "\t";
            total += grades[i][j];
        }
        double average = static_cast<double>(total) / grades[i].size();
        cout << std::fixed << std::setprecision(1) << average << endl;
    }
    
    // 计算各科平均分
    cout << "\n各科平均分:" << endl;
    for (size_t j = 0; j < subjects.size(); ++j) {
        int total = 0;
        for (size_t i = 0; i < students.size(); ++i) {
            total += grades[i][j];
        }
        double average = static_cast<double>(total) / students.size();
        cout << subjects[j] << ": " << std::fixed << std::setprecision(1) << average << endl;
    }
    
    // 找出最高分学生
    cout << "\n各科最高分:" << endl;
    for (size_t j = 0; j < subjects.size(); ++j) {
        int maxGrade = grades[0][j];
        size_t maxIndex = 0;
        
        for (size_t i = 1; i < students.size(); ++i) {
            if (grades[i][j] > maxGrade) {
                maxGrade = grades[i][j];
                maxIndex = i;
            }
        }
        
        cout << subjects[j] << ": " << students[maxIndex] 
             << " (" << maxGrade << "分)" << endl;
    }
}

int main() {
    print_separator("字符串和向量综合练习");
    
    // 练习1：字符串分割
    cout << "=== 练习1：字符串分割 ===" << endl;
    string sentence = "apple,banana,cherry,date";
    vector<string> fruits = splitString(sentence, ',');
    cout << "分割字符串: " << sentence << endl;
    cout << "结果: ";
    for (const string& fruit : fruits) {
        cout << fruit << " ";
    }
    cout << endl << endl;
    
    // 练习2：单词频率统计
    string text = "The quick brown fox jumps over the lazy dog. The dog was lazy.";
    wordFrequency(text);
    cout << endl;
    
    // 练习3：矩阵操作
    matrixOperations();
    cout << endl;
    
    // 练习4：文本处理工具
    textProcessingTool();
    cout << endl;
    
    // 练习5：动态数组练习
    dynamicArrayPractice();
    cout << endl;
    
    // 练习6：字符串模式匹配
    patternMatching();
    cout << endl;
    
    // 练习7：成绩管理系统
    gradeManagement();
    
    print_separator("综合练习完成");
    
    return 0;
} 