#include "common.h"

// 打印二进制表示的辅助函数
void print_binary(unsigned int num, int bits = 8) {
    cout << "二进制: ";
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((num >> i) & 1);
        if (i % 4 == 0 && i != 0) cout << " ";
    }
    cout << " (十进制: " << num << ")";
}

int main() {
    print_separator("位运算符示例");
    
    // 基本位运算符
    cout << "=== 基本位运算符 ===" << endl;
    unsigned int a = 60;    // 60 = 0011 1100
    unsigned int b = 13;    // 13 = 0000 1101
    
    cout << "a = " << a << ", b = " << b << endl;
    print_binary(a); cout << " <- a" << endl;
    print_binary(b); cout << " <- b" << endl;
    
    // 按位与 (&)
    unsigned int and_result = a & b;
    cout << "\n按位与 (a & b):" << endl;
    print_binary(and_result); cout << " <- 结果" << endl;
    
    // 按位或 (|)
    unsigned int or_result = a | b;
    cout << "\n按位或 (a | b):" << endl;
    print_binary(or_result); cout << " <- 结果" << endl;
    
    // 按位异或 (^)
    unsigned int xor_result = a ^ b;
    cout << "\n按位异或 (a ^ b):" << endl;
    print_binary(xor_result); cout << " <- 结果" << endl;
    
    // 按位取反 (~)
    unsigned int not_a = ~a;
    cout << "\n按位取反 (~a):" << endl;
    print_binary(not_a); cout << " <- 结果" << endl;
    
    // 左移运算符 (<<)
    cout << "\n=== 左移运算符 (<<) ===" << endl;
    unsigned int shift_num = 5;  // 5 = 0000 0101
    cout << "原始数: " << shift_num << endl;
    print_binary(shift_num); cout << " <- 原始" << endl;
    
    for (int i = 1; i <= 3; i++) {
        unsigned int left_shifted = shift_num << i;
        cout << "左移 " << i << " 位: " << left_shifted << endl;
        print_binary(left_shifted); cout << " <- 结果" << endl;
    }
    
    // 右移运算符 (>>)
    cout << "\n=== 右移运算符 (>>) ===" << endl;
    unsigned int large_num = 80;  // 80 = 0101 0000
    cout << "原始数: " << large_num << endl;
    print_binary(large_num); cout << " <- 原始" << endl;
    
    for (int i = 1; i <= 3; i++) {
        unsigned int right_shifted = large_num >> i;
        cout << "右移 " << i << " 位: " << right_shifted << endl;
        print_binary(right_shifted); cout << " <- 结果" << endl;
    }
    
    // 有符号数的右移
    cout << "\n=== 有符号数的右移 ===" << endl;
    int signed_num = -8;  // 负数使用二进制补码表示
    cout << "有符号数 " << signed_num << " 右移:" << endl;
    
    for (int i = 1; i <= 3; i++) {
        int signed_shifted = signed_num >> i;
        cout << "右移 " << i << " 位: " << signed_shifted << endl;
    }
    
    // 位运算的复合赋值运算符
    cout << "\n=== 位运算的复合赋值运算符 ===" << endl;
    unsigned int compound = 12;  // 12 = 0000 1100
    cout << "初始值: " << compound << endl;
    print_binary(compound); cout << " <- 初始" << endl;
    
    compound &= 10;  // 与10做按位与
    cout << "compound &= 10: " << compound << endl;
    print_binary(compound); cout << " <- &= 10" << endl;
    
    compound |= 5;   // 与5做按位或
    cout << "compound |= 5: " << compound << endl;
    print_binary(compound); cout << " <- |= 5" << endl;
    
    compound ^= 3;   // 与3做按位异或
    cout << "compound ^= 3: " << compound << endl;
    print_binary(compound); cout << " <- ^= 3" << endl;
    
    compound <<= 2;  // 左移2位
    cout << "compound <<= 2: " << compound << endl;
    print_binary(compound); cout << " <- <<= 2" << endl;
    
    compound >>= 1;  // 右移1位
    cout << "compound >>= 1: " << compound << endl;
    print_binary(compound); cout << " <- >>= 1" << endl;
    
    // 位运算的实际应用
    cout << "\n=== 位运算的实际应用 ===" << endl;
    
    // 1. 检查某一位是否为1
    cout << "1. 检查某一位是否为1:" << endl;
    unsigned int test_num = 45;  // 45 = 0010 1101
    cout << "测试数: " << test_num << endl;
    print_binary(test_num); cout << " <- 测试数" << endl;
    
    for (int bit = 0; bit < 6; bit++) {
        bool is_set = (test_num & (1 << bit)) != 0;
        cout << "第" << bit << "位: " << (is_set ? "1" : "0") << endl;
    }
    
    // 2. 设置某一位为1
    cout << "\n2. 设置某一位为1:" << endl;
    unsigned int set_bit_num = 8;  // 8 = 0000 1000
    cout << "原始数: " << set_bit_num << endl;
    print_binary(set_bit_num); cout << " <- 原始" << endl;
    
    set_bit_num |= (1 << 1);  // 设置第1位为1
    cout << "设置第1位为1: " << set_bit_num << endl;
    print_binary(set_bit_num); cout << " <- 结果" << endl;
    
    // 3. 清除某一位（设置为0）
    cout << "\n3. 清除某一位（设置为0）:" << endl;
    unsigned int clear_bit_num = 15;  // 15 = 0000 1111
    cout << "原始数: " << clear_bit_num << endl;
    print_binary(clear_bit_num); cout << " <- 原始" << endl;
    
    clear_bit_num &= ~(1 << 2);  // 清除第2位
    cout << "清除第2位: " << clear_bit_num << endl;
    print_binary(clear_bit_num); cout << " <- 结果" << endl;
    
    // 4. 切换某一位（0变1，1变0）
    cout << "\n4. 切换某一位:" << endl;
    unsigned int toggle_num = 10;  // 10 = 0000 1010
    cout << "原始数: " << toggle_num << endl;
    print_binary(toggle_num); cout << " <- 原始" << endl;
    
    toggle_num ^= (1 << 0);  // 切换第0位
    cout << "切换第0位: " << toggle_num << endl;
    print_binary(toggle_num); cout << " <- 结果" << endl;
    
    // 5. 计算2的幂
    cout << "\n5. 使用左移计算2的幂:" << endl;
    for (int i = 0; i <= 5; i++) {
        unsigned int power_of_2 = 1 << i;
        cout << "2^" << i << " = " << power_of_2 << endl;
    }
    
    // 6. 判断一个数是否是2的幂
    cout << "\n6. 判断一个数是否是2的幂:" << endl;
    vector<int> test_powers = {1, 2, 4, 6, 8, 16, 20, 32};
    for (int num : test_powers) {
        bool is_power_of_2 = (num > 0) && ((num & (num - 1)) == 0);
        cout << num << " 是2的幂: " << (is_power_of_2 ? "是" : "否") << endl;
    }
    
    // 7. 计算一个数的二进制中1的个数
    cout << "\n7. 计算二进制中1的个数:" << endl;
    unsigned int count_num = 45;  // 45 = 0010 1101
    cout << "数字: " << count_num << endl;
    print_binary(count_num); cout << " <- 二进制" << endl;
    
    int count = 0;
    unsigned int temp = count_num;
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    cout << "二进制中1的个数: " << count << endl;
    
    // 使用Brian Kernighan算法
    count = 0;
    temp = count_num;
    while (temp) {
        temp &= (temp - 1);  // 清除最低位的1
        count++;
    }
    cout << "使用Brian Kernighan算法: " << count << endl;
    
    // 8. 位掩码操作
    cout << "\n8. 位掩码操作:" << endl;
    
    // 定义权限位掩码
    const unsigned int READ_PERMISSION = 1 << 0;    // 0001
    const unsigned int WRITE_PERMISSION = 1 << 1;   // 0010
    const unsigned int EXECUTE_PERMISSION = 1 << 2; // 0100
    const unsigned int DELETE_PERMISSION = 1 << 3;  // 1000
    
    cout << "权限位掩码:" << endl;
    cout << "READ: "; print_binary(READ_PERMISSION, 4); cout << endl;
    cout << "WRITE: "; print_binary(WRITE_PERMISSION, 4); cout << endl;
    cout << "EXECUTE: "; print_binary(EXECUTE_PERMISSION, 4); cout << endl;
    cout << "DELETE: "; print_binary(DELETE_PERMISSION, 4); cout << endl;
    
    // 设置权限
    unsigned int permissions = 0;
    permissions |= READ_PERMISSION;
    permissions |= WRITE_PERMISSION;
    
    cout << "\n设置读写权限:" << endl;
    print_binary(permissions, 4); cout << endl;
    
    // 检查权限
    cout << "检查权限:" << endl;
    cout << "有读权限: " << ((permissions & READ_PERMISSION) ? "是" : "否") << endl;
    cout << "有写权限: " << ((permissions & WRITE_PERMISSION) ? "是" : "否") << endl;
    cout << "有执行权限: " << ((permissions & EXECUTE_PERMISSION) ? "是" : "否") << endl;
    cout << "有删除权限: " << ((permissions & DELETE_PERMISSION) ? "是" : "否") << endl;
    
    // 移除权限
    permissions &= ~WRITE_PERMISSION;
    cout << "\n移除写权限后:" << endl;
    print_binary(permissions, 4); cout << endl;
    cout << "有写权限: " << ((permissions & WRITE_PERMISSION) ? "是" : "否") << endl;
    
    // 9. 字节交换
    cout << "\n9. 字节交换示例:" << endl;
    unsigned int original = 0x12345678;
    cout << "原始数: 0x" << hex << original << dec << endl;
    
    // 交换字节（仅作演示，实际应用中有专门的函数）
    unsigned int swapped = ((original & 0xFF) << 24) |
                          ((original & 0xFF00) << 8) |
                          ((original & 0xFF0000) >> 8) |
                          ((original & 0xFF000000) >> 24);
    
    cout << "字节交换后: 0x" << hex << swapped << dec << endl;
    
    print_separator("位运算符示例完成");
    
    return 0;
} 