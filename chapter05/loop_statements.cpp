#include "common.h"

int main() {
    print_separator("循环语句示例");
    
    // for循环基础
    cout << "=== for循环基础 ===" << endl;
    cout << "1到10的数字:" << endl;
    for (int i = 1; i <= 10; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // 倒序for循环
    cout << "\n倒序输出:" << endl;
    for (int i = 10; i >= 1; i--) {
        cout << i << " ";
    }
    cout << endl;
    
    // 步长不为1的循环
    cout << "\n偶数输出 (步长为2):" << endl;
    for (int i = 2; i <= 20; i += 2) {
        cout << i << " ";
    }
    cout << endl;
    
    // while循环
    cout << "\n=== while循环 ===" << endl;
    int count = 1;
    cout << "使用while循环输出1到5:" << endl;
    while (count <= 5) {
        cout << count << " ";
        count++;
    }
    cout << endl;
    
    // 查找第一个大于100的2的幂
    cout << "\n查找第一个大于100的2的幂:" << endl;
    int power = 1;
    int exponent = 0;
    while (power <= 100) {
        power *= 2;
        exponent++;
    }
    cout << "2^" << exponent << " = " << power << endl;
    
    // do-while循环
    cout << "\n=== do-while循环 ===" << endl;
    int user_input = 0;
    cout << "模拟用户输入验证 (do-while至少执行一次):" << endl;
    
    do {
        user_input++;
        cout << "第" << user_input << "次尝试输入" << endl;
        // 模拟第3次输入正确
    } while (user_input < 3);
    cout << "输入验证成功！" << endl;
    
    // 嵌套循环
    cout << "\n=== 嵌套循环 ===" << endl;
    cout << "九九乘法表:" << endl;
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= i; j++) {
            cout << j << "×" << i << "=" << i * j << "\t";
        }
        cout << endl;
    }
    
    // 打印矩阵
    cout << "\n3×4矩阵:" << endl;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 4; col++) {
            cout << "[" << row << "," << col << "] ";
        }
        cout << endl;
    }
    
    // 范围for循环 (C++11)
    cout << "\n=== 范围for循环 (C++11) ===" << endl;
    vector<string> fruits = {"苹果", "香蕉", "橙子", "葡萄", "草莓"};
    
    cout << "水果列表:" << endl;
    for (const string& fruit : fruits) {
        cout << "- " << fruit << endl;
    }
    
    // 使用auto的范围for循环
    cout << "\n使用auto的范围for循环:" << endl;
    vector<int> numbers = {10, 20, 30, 40, 50};
    for (auto num : numbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // 修改元素的范围for循环
    cout << "\n修改数组元素 (使用引用):" << endl;
    vector<int> values = {1, 2, 3, 4, 5};
    cout << "原始值: ";
    for (auto val : values) {
        cout << val << " ";
    }
    cout << endl;
    
    // 将每个元素乘以2
    for (auto& val : values) {
        val *= 2;
    }
    
    cout << "修改后: ";
    for (auto val : values) {
        cout << val << " ";
    }
    cout << endl;
    
    // 循环控制语句
    cout << "\n=== 循环控制语句 ===" << endl;
    
    // break语句
    cout << "break语句示例 - 找到第一个偶数:" << endl;
    vector<int> test_numbers = {1, 3, 7, 8, 9, 12, 15};
    for (int num : test_numbers) {
        cout << "检查数字: " << num << endl;
        if (num % 2 == 0) {
            cout << "找到第一个偶数: " << num << endl;
            break;
        }
    }
    
    // continue语句
    cout << "\ncontinue语句示例 - 只输出奇数:" << endl;
    for (int i = 1; i <= 10; i++) {
        if (i % 2 == 0) {
            continue;  // 跳过偶数
        }
        cout << i << " ";
    }
    cout << endl;
    
    // 无限循环与break
    cout << "\n无限循环与break:" << endl;
    int counter = 0;
    while (true) {
        counter++;
        cout << "循环第" << counter << "次" << endl;
        if (counter >= 5) {
            cout << "达到条件，退出循环" << endl;
            break;
        }
    }
    
    // 实际应用示例
    cout << "\n=== 实际应用示例 ===" << endl;
    
    // 1. 数组求和
    cout << "1. 数组求和:" << endl;
    vector<double> prices = {19.99, 25.50, 12.75, 8.30, 45.20};
    double total = 0.0;
    
    for (double price : prices) {
        total += price;
    }
    cout << "商品价格: ";
    for (auto price : prices) {
        cout << "$" << price << " ";
    }
    cout << "\n总价: $" << total << endl;
    
    // 2. 查找最大值和最小值
    cout << "\n2. 查找最大值和最小值:" << endl;
    vector<int> scores = {85, 92, 78, 96, 88, 73, 91};
    int max_score = scores[0];
    int min_score = scores[0];
    
    for (int score : scores) {
        if (score > max_score) {
            max_score = score;
        }
        if (score < min_score) {
            min_score = score;
        }
    }
    
    cout << "分数: ";
    for (auto score : scores) {
        cout << score << " ";
    }
    cout << "\n最高分: " << max_score << ", 最低分: " << min_score << endl;
    
    // 3. 字符串处理
    cout << "\n3. 字符串处理 - 计算字符频率:" << endl;
    string text = "hello world";
    cout << "文本: \"" << text << "\"" << endl;
    
    // 使用map计算字符频率
    map<char, int> char_count;
    for (char c : text) {
        if (c != ' ') {  // 忽略空格
            char_count[c]++;
        }
    }
    
    cout << "字符频率:" << endl;
    for (auto pair : char_count) {
        cout << "'" << pair.first << "': " << pair.second << " 次" << endl;
    }
    
    // 4. 斐波那契数列
    cout << "\n4. 斐波那契数列 (前15项):" << endl;
    int fib1 = 0, fib2 = 1;
    cout << fib1 << " " << fib2 << " ";
    
    for (int i = 2; i < 15; i++) {
        int next_fib = fib1 + fib2;
        cout << next_fib << " ";
        fib1 = fib2;
        fib2 = next_fib;
    }
    cout << endl;
    
    // 5. 素数判断
    cout << "\n5. 素数判断 (1-30):" << endl;
    cout << "素数: ";
    for (int n = 2; n <= 30; n++) {
        bool is_prime = true;
        
        // 检查是否为素数
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                is_prime = false;
                break;
            }
        }
        
        if (is_prime) {
            cout << n << " ";
        }
    }
    cout << endl;
    
    // 6. 冒泡排序
    cout << "\n6. 冒泡排序:" << endl;
    vector<int> unsorted = {64, 34, 25, 12, 22, 11, 90};
    cout << "排序前: ";
    for (auto num : unsorted) {
        cout << num << " ";
    }
    cout << endl;
    
    // 冒泡排序算法
    int n = unsorted.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (unsorted[j] > unsorted[j + 1]) {
                // 交换元素
                int temp = unsorted[j];
                unsorted[j] = unsorted[j + 1];
                unsorted[j + 1] = temp;
            }
        }
    }
    
    cout << "排序后: ";
    for (auto num : unsorted) {
        cout << num << " ";
    }
    cout << endl;
    
    // 7. 矩阵运算
    cout << "\n7. 矩阵运算 - 转置:" << endl;
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    cout << "原矩阵 (3×4):" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
    
    cout << "转置矩阵 (4×3):" << endl;
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
    
    // 8. 数字游戏 - 猜数字
    cout << "\n8. 数字游戏 - 猜数字模拟:" << endl;
    int secret_number = 42;
    vector<int> guesses = {25, 50, 40, 45, 42};
    
    cout << "神秘数字: " << secret_number << endl;
    cout << "猜测过程:" << endl;
    
    for (int i = 0; i < guesses.size(); i++) {
        int guess = guesses[i];
        cout << "第" << (i + 1) << "次猜测: " << guess;
        
        if (guess == secret_number) {
            cout << " - 恭喜！猜对了！" << endl;
            break;
        } else if (guess < secret_number) {
            cout << " - 太小了，再试试" << endl;
        } else {
            cout << " - 太大了，再试试" << endl;
        }
    }
    
    // 循环性能考虑
    cout << "\n=== 循环性能考虑 ===" << endl;
    
    // 避免在循环中重复计算
    cout << "避免在循环中重复计算:" << endl;
    vector<int> large_vector(1000);
    
    // 不好的做法 (在循环条件中调用size())
    cout << "填充向量..." << endl;
    for (int i = 0; i < large_vector.size(); i++) {  // size()会被重复调用
        large_vector[i] = i;
    }
    
    // 更好的做法
    size_t vec_size = large_vector.size();
    for (size_t i = 0; i < vec_size; i++) {
        large_vector[i] = i * 2;
    }
    
    cout << "向量前10个元素: ";
    for (int i = 0; i < 10; i++) {
        cout << large_vector[i] << " ";
    }
    cout << endl;
    
    // 循环最佳实践
    cout << "\n=== 循环最佳实践 ===" << endl;
    cout << "1. 优先使用范围for循环处理容器" << endl;
    cout << "2. 避免在循环条件中进行昂贵的计算" << endl;
    cout << "3. 使用合适的循环类型（for, while, do-while）" << endl;
    cout << "4. 考虑循环不变量，提取到循环外部" << endl;
    cout << "5. 合理使用break和continue控制循环流程" << endl;
    cout << "6. 注意循环的边界条件，避免越界访问" << endl;
    cout << "7. 对于大量数据，考虑算法复杂度和性能" << endl;
    
    print_separator("循环语句示例完成");
    
    return 0;
} 