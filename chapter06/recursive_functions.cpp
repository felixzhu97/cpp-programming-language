#include "common.h"

// 1. 基础递归示例

// 阶乘计算
long long factorial(int n) {
    cout << "  计算 " << n << "! ";
    
    // 基础情况
    if (n <= 1) {
        cout << "(基础情况: 返回1)" << endl;
        return 1;
    }
    
    // 递归情况
    cout << "= " << n << " * " << (n-1) << "!" << endl;
    return n * factorial(n - 1);
}

// 斐波那契数列（简单递归）
long long fibonacci_simple(int n) {
    cout << "  计算 fib(" << n << ")";
    
    if (n <= 1) {
        cout << " = " << n << " (基础情况)" << endl;
        return n;
    }
    
    cout << " = fib(" << (n-1) << ") + fib(" << (n-2) << ")" << endl;
    return fibonacci_simple(n - 1) + fibonacci_simple(n - 2);
}

// 2. 优化的递归 - 记忆化斐波那契
map<int, long long> fib_memo;

long long fibonacci_memo(int n) {
    if (n <= 1) {
        return n;
    }
    
    // 检查是否已计算过
    if (fib_memo.find(n) != fib_memo.end()) {
        cout << "  从缓存获取 fib(" << n << ") = " << fib_memo[n] << endl;
        return fib_memo[n];
    }
    
    cout << "  计算 fib(" << n << ")" << endl;
    fib_memo[n] = fibonacci_memo(n - 1) + fibonacci_memo(n - 2);
    return fib_memo[n];
}

// 3. 尾递归优化示例
long long factorial_tail_recursive(int n, long long accumulator = 1) {
    cout << "  尾递归: n=" << n << ", acc=" << accumulator << endl;
    
    if (n <= 1) {
        return accumulator;
    }
    
    return factorial_tail_recursive(n - 1, n * accumulator);
}

long long fibonacci_tail_recursive(int n, long long a = 0, long long b = 1) {
    if (n == 0) return a;
    if (n == 1) return b;
    
    cout << "  尾递归: n=" << n << ", a=" << a << ", b=" << b << endl;
    return fibonacci_tail_recursive(n - 1, b, a + b);
}

// 4. 树形递归 - 汉诺塔问题
void hanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        cout << "  移动盘子 " << n << " 从 " << from << " 到 " << to << endl;
        return;
    }
    
    // 将n-1个盘子从from移动到aux
    hanoi(n - 1, from, aux, to);
    
    // 移动最大的盘子从from到to
    cout << "  移动盘子 " << n << " 从 " << from << " 到 " << to << endl;
    
    // 将n-1个盘子从aux移动到to
    hanoi(n - 1, aux, to, from);
}

// 5. 数组递归操作
int array_sum(int arr[], int size) {
    cout << "  计算数组和，剩余元素: " << size << endl;
    
    if (size == 0) {
        return 0;
    }
    
    return arr[size - 1] + array_sum(arr, size - 1);
}

int find_max(int arr[], int size) {
    if (size == 1) {
        cout << "  基础情况: 最大值 = " << arr[0] << endl;
        return arr[0];
    }
    
    int max_rest = find_max(arr, size - 1);
    int current = arr[size - 1];
    
    cout << "  比较 " << current << " 与子数组最大值 " << max_rest << endl;
    
    return (current > max_rest) ? current : max_rest;
}

void reverse_array(int arr[], int start, int end) {
    cout << "  反转: start=" << start << ", end=" << end << endl;
    
    if (start >= end) {
        return;
    }
    
    swap(arr[start], arr[end]);
    reverse_array(arr, start + 1, end - 1);
}

// 6. 字符串递归操作
bool is_palindrome(const string& str, int start, int end) {
    cout << "  检查回文: [" << start << "," << end << "] = '" 
         << str.substr(start, end - start + 1) << "'" << endl;
    
    if (start >= end) {
        return true;
    }
    
    if (str[start] != str[end]) {
        return false;
    }
    
    return is_palindrome(str, start + 1, end - 1);
}

void print_string_reverse(const string& str, int index) {
    if (index < 0) {
        return;
    }
    
    cout << str[index];
    print_string_reverse(str, index - 1);
}

int count_character(const string& str, char ch, int index) {
    if (index >= str.length()) {
        return 0;
    }
    
    int current_count = (str[index] == ch) ? 1 : 0;
    return current_count + count_character(str, ch, index + 1);
}

// 7. 数学递归问题
int gcd(int a, int b) {
    cout << "  计算 gcd(" << a << ", " << b << ")";
    
    if (b == 0) {
        cout << " = " << a << " (基础情况)" << endl;
        return a;
    }
    
    cout << " = gcd(" << b << ", " << (a % b) << ")" << endl;
    return gcd(b, a % b);
}

double power(double base, int exponent) {
    cout << "  计算 " << base << "^" << exponent;
    
    if (exponent == 0) {
        cout << " = 1 (基础情况)" << endl;
        return 1;
    }
    
    if (exponent < 0) {
        cout << " = 1/" << base << "^" << (-exponent) << endl;
        return 1.0 / power(base, -exponent);
    }
    
    cout << " = " << base << " * " << base << "^" << (exponent-1) << endl;
    return base * power(base, exponent - 1);
}

// 快速幂算法（分治递归）
double fast_power(double base, int exponent) {
    cout << "  快速幂: " << base << "^" << exponent;
    
    if (exponent == 0) {
        cout << " = 1" << endl;
        return 1;
    }
    
    if (exponent < 0) {
        cout << " = 1/(" << base << "^" << (-exponent) << ")" << endl;
        return 1.0 / fast_power(base, -exponent);
    }
    
    if (exponent % 2 == 0) {
        cout << " = (" << base << "^" << (exponent/2) << ")^2" << endl;
        double half = fast_power(base, exponent / 2);
        return half * half;
    } else {
        cout << " = " << base << " * " << base << "^" << (exponent-1) << endl;
        return base * fast_power(base, exponent - 1);
    }
}

// 8. 组合数学
long long combination(int n, int k) {
    cout << "  计算 C(" << n << "," << k << ")";
    
    if (k == 0 || k == n) {
        cout << " = 1 (基础情况)" << endl;
        return 1;
    }
    
    if (k > n) {
        cout << " = 0 (k > n)" << endl;
        return 0;
    }
    
    cout << " = C(" << (n-1) << "," << (k-1) << ") + C(" << (n-1) << "," << k << ")" << endl;
    return combination(n - 1, k - 1) + combination(n - 1, k);
}

// 9. 二叉树递归操作
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// 计算树的高度
int tree_height(TreeNode* root) {
    if (root == nullptr) {
        cout << "  空节点，高度 = 0" << endl;
        return 0;
    }
    
    cout << "  节点 " << root->data << ":" << endl;
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    int height = 1 + max(left_height, right_height);
    cout << "  节点 " << root->data << " 的高度 = " << height << endl;
    
    return height;
}

// 中序遍历
void inorder_traversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    
    inorder_traversal(root->left);
    cout << root->data << " ";
    inorder_traversal(root->right);
}

// 计算节点总数
int count_nodes(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    
    cout << "  访问节点 " << root->data << endl;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// 查找值
bool search_tree(TreeNode* root, int target) {
    if (root == nullptr) {
        cout << "  到达空节点，未找到 " << target << endl;
        return false;
    }
    
    cout << "  检查节点 " << root->data;
    
    if (root->data == target) {
        cout << " - 找到!" << endl;
        return true;
    }
    
    cout << " - 继续搜索" << endl;
    return search_tree(root->left, target) || search_tree(root->right, target);
}

// 10. 排序算法递归实现

// 归并排序
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (int i = 0; i < k; i++) {
        arr[left + i] = temp[i];
    }
}

void merge_sort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    
    int mid = left + (right - left) / 2;
    
    cout << "  分割: [" << left << "," << mid << "] 和 [" << (mid+1) << "," << right << "]" << endl;
    
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    
    cout << "  合并: [" << left << "," << right << "]" << endl;
    merge(arr, left, mid, right);
}

// 快速排序
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        cout << "  分区: 枢轴=" << arr[pi] << ", 位置=" << pi << endl;
        
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// 11. 图形递归 - 分形图案
void draw_sierpinski_triangle(int n) {
    cout << "绘制谢尔宾斯基三角形，深度: " << n << endl;
    
    function<void(int, string)> draw;
    draw = [&](int depth, string prefix) {
        if (depth == 0) {
            cout << prefix << "▲" << endl;
            return;
        }
        
        draw(depth - 1, prefix + "  ");
        draw(depth - 1, prefix + " ");
        draw(depth - 1, prefix + "  ");
    };
    
    draw(n, "");
}

// 12. 递归优化技术

// 记忆化装饰器模板
template<typename Result, typename... Args>
class Memoizer {
private:
    map<tuple<Args...>, Result> cache;
    function<Result(Args...)> func;
    
public:
    Memoizer(function<Result(Args...)> f) : func(f) {}
    
    Result operator()(Args... args) {
        auto key = make_tuple(args...);
        if (cache.find(key) != cache.end()) {
            return cache[key];
        }
        
        Result result = func(args...);
        cache[key] = result;
        return result;
    }
};

// 13. 递归与迭代的对比
long long factorial_iterative(int n) {
    long long result = 1;
    cout << "  迭代计算 " << n << "!: ";
    
    for (int i = 1; i <= n; i++) {
        result *= i;
        cout << i << " ";
    }
    
    cout << "= " << result << endl;
    return result;
}

long long fibonacci_iterative(int n) {
    if (n <= 1) return n;
    
    long long a = 0, b = 1, temp;
    cout << "  迭代计算 fib(" << n << "): ";
    cout << a << " " << b << " ";
    
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
        cout << temp << " ";
    }
    
    cout << endl;
    return b;
}

// 14. 递归深度监控
int max_recursion_depth = 0;
int current_depth = 0;

void track_recursion_depth(int n) {
    current_depth++;
    max_recursion_depth = max(max_recursion_depth, current_depth);
    
    cout << "  当前深度: " << current_depth << ", n = " << n << endl;
    
    if (n > 0) {
        track_recursion_depth(n - 1);
    }
    
    current_depth--;
}

int main() {
    print_separator("递归函数详解");
    
    // 1. 基础递归示例
    cout << "=== 基础递归示例 ===" << endl;
    
    cout << "阶乘计算:" << endl;
    long long fact5 = factorial(5);
    cout << "结果: 5! = " << fact5 << endl;
    
    cout << "\n简单斐波那契数列 (注意递归调用):" << endl;
    long long fib5 = fibonacci_simple(5);
    cout << "结果: fib(5) = " << fib5 << endl;
    
    // 2. 记忆化优化
    cout << "\n=== 记忆化优化 ===" << endl;
    
    fib_memo.clear();
    cout << "记忆化斐波那契数列:" << endl;
    long long fib10 = fibonacci_memo(10);
    cout << "结果: fib(10) = " << fib10 << endl;
    
    // 3. 尾递归优化
    cout << "\n=== 尾递归优化 ===" << endl;
    
    cout << "尾递归阶乘:" << endl;
    long long tail_fact = factorial_tail_recursive(5);
    cout << "结果: 5! = " << tail_fact << endl;
    
    cout << "\n尾递归斐波那契:" << endl;
    long long tail_fib = fibonacci_tail_recursive(8);
    cout << "结果: fib(8) = " << tail_fib << endl;
    
    // 4. 汉诺塔问题
    cout << "\n=== 汉诺塔问题 ===" << endl;
    
    cout << "汉诺塔 (3个盘子):" << endl;
    hanoi(3, 'A', 'C', 'B');
    
    // 5. 数组递归操作
    cout << "\n=== 数组递归操作 ===" << endl;
    
    int arr[] = {3, 7, 1, 9, 4};
    int size = 5;
    
    cout << "数组: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    cout << "\n数组求和:" << endl;
    int sum = array_sum(arr, size);
    cout << "结果: " << sum << endl;
    
    cout << "\n查找最大值:" << endl;
    int max_val = find_max(arr, size);
    cout << "结果: " << max_val << endl;
    
    cout << "\n反转数组:" << endl;
    reverse_array(arr, 0, size - 1);
    cout << "反转后: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 6. 字符串递归操作
    cout << "\n=== 字符串递归操作 ===" << endl;
    
    string test_str = "racecar";
    cout << "检查回文: '" << test_str << "'" << endl;
    bool is_pal = is_palindrome(test_str, 0, test_str.length() - 1);
    cout << "结果: " << (is_pal ? "是回文" : "不是回文") << endl;
    
    cout << "\n反向打印字符串 'hello': ";
    print_string_reverse("hello", 4);
    cout << endl;
    
    cout << "\n统计字符 'l' 在 'hello' 中的数量:" << endl;
    int char_count = count_character("hello", 'l', 0);
    cout << "结果: " << char_count << endl;
    
    // 7. 数学递归问题
    cout << "\n=== 数学递归问题 ===" << endl;
    
    cout << "最大公约数:" << endl;
    int gcd_result = gcd(48, 18);
    cout << "结果: gcd(48, 18) = " << gcd_result << endl;
    
    cout << "\n幂运算:" << endl;
    double power_result = power(2, 5);
    cout << "结果: 2^5 = " << power_result << endl;
    
    cout << "\n快速幂算法:" << endl;
    double fast_power_result = fast_power(2, 10);
    cout << "结果: 2^10 = " << fast_power_result << endl;
    
    cout << "\n组合数:" << endl;
    long long comb_result = combination(5, 2);
    cout << "结果: C(5,2) = " << comb_result << endl;
    
    // 8. 二叉树递归操作
    cout << "\n=== 二叉树递归操作 ===" << endl;
    
    // 构建示例树
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    cout << "树的高度:" << endl;
    int height = tree_height(root);
    cout << "结果: " << height << endl;
    
    cout << "\n中序遍历: ";
    inorder_traversal(root);
    cout << endl;
    
    cout << "\n节点计数:" << endl;
    int node_count = count_nodes(root);
    cout << "结果: " << node_count << " 个节点" << endl;
    
    cout << "\n搜索值 5:" << endl;
    bool found = search_tree(root, 5);
    cout << "结果: " << (found ? "找到" : "未找到") << endl;
    
    // 9. 排序算法
    cout << "\n=== 递归排序算法 ===" << endl;
    
    vector<int> merge_arr = {38, 27, 43, 3, 9, 82, 10};
    cout << "归并排序前: ";
    for (int val : merge_arr) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "归并排序过程:" << endl;
    merge_sort(merge_arr, 0, merge_arr.size() - 1);
    
    cout << "归并排序后: ";
    for (int val : merge_arr) {
        cout << val << " ";
    }
    cout << endl;
    
    vector<int> quick_arr = {64, 34, 25, 12, 22, 11, 90};
    cout << "\n快速排序前: ";
    for (int val : quick_arr) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "快速排序过程:" << endl;
    quick_sort(quick_arr, 0, quick_arr.size() - 1);
    
    cout << "快速排序后: ";
    for (int val : quick_arr) {
        cout << val << " ";
    }
    cout << endl;
    
    // 10. 分形图案
    cout << "\n=== 分形图案 ===" << endl;
    draw_sierpinski_triangle(3);
    
    // 11. 递归vs迭代性能对比
    cout << "\n=== 递归vs迭代性能对比 ===" << endl;
    
    const int n = 10;
    
    cout << "计算 " << n << "! :" << endl;
    
    auto start = chrono::high_resolution_clock::now();
    long long rec_result = factorial(n);
    auto mid = chrono::high_resolution_clock::now();
    long long iter_result = factorial_iterative(n);
    auto end = chrono::high_resolution_clock::now();
    
    auto rec_time = chrono::duration_cast<chrono::microseconds>(mid - start);
    auto iter_time = chrono::duration_cast<chrono::microseconds>(end - mid);
    
    cout << "递归结果: " << rec_result << ", 时间: " << rec_time.count() << " 微秒" << endl;
    cout << "迭代结果: " << iter_result << ", 时间: " << iter_time.count() << " 微秒" << endl;
    
    // 12. 递归深度监控
    cout << "\n=== 递归深度监控 ===" << endl;
    
    max_recursion_depth = 0;
    current_depth = 0;
    
    cout << "跟踪递归深度 (n=5):" << endl;
    track_recursion_depth(5);
    cout << "最大递归深度: " << max_recursion_depth << endl;
    
    // 13. 递归的最佳实践和注意事项
    cout << "\n=== 递归最佳实践 ===" << endl;
    cout << "1. 确保有明确的基础情况（递归终止条件）" << endl;
    cout << "2. 确保递归调用朝着基础情况前进" << endl;
    cout << "3. 避免重复计算，考虑使用记忆化" << endl;
    cout << "4. 注意栈溢出问题，考虑尾递归优化" << endl;
    cout << "5. 对于大数据量，考虑迭代替代方案" << endl;
    cout << "6. 递归深度过大时使用显式栈" << endl;
    cout << "7. 理解递归的时间和空间复杂度" << endl;
    cout << "8. 使用递归时要考虑调试的复杂性" << endl;
    cout << "9. 某些问题用递归表达更自然（树、图遍历）" << endl;
    cout << "10. 在生产环境中要测试极端情况" << endl;
    
    // 14. 递归陷阱和常见错误
    cout << "\n=== 递归常见错误 ===" << endl;
    cout << "错误1: 缺少基础情况 -> 无限递归" << endl;
    cout << "错误2: 递归调用不收敛 -> 栈溢出" << endl;
    cout << "错误3: 重复计算过多 -> 性能问题" << endl;
    cout << "错误4: 递归深度过大 -> 栈空间不足" << endl;
    cout << "错误5: 参数传递错误 -> 逻辑错误" << endl;
    cout << "错误6: 忽略边界条件 -> 运行时错误" << endl;
    
    // 清理内存
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
    
    print_separator("递归函数详解完成");
    
    return 0;
} 