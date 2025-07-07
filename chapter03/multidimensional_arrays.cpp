#include "common.h"

int main() {
    print_separator("多维数组示例");
    
    // 二维数组创建和初始化
    cout << "=== 二维数组创建和初始化 ===" << endl;
    
    // 方式1：完全初始化
    int matrix1[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // 方式2：部分初始化
    int matrix2[3][4] = {
        {1, 2},
        {5, 6, 7},
        {9}
    };
    
    // 方式3：线性初始化
    int matrix3[2][3] = {1, 2, 3, 4, 5, 6};
    
    cout << "完全初始化矩阵:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << matrix1[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\n部分初始化矩阵:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << matrix2[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\n线性初始化矩阵:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matrix3[i][j] << " ";
        }
        cout << endl;
    }
    
    // 二维数组访问
    cout << "\n=== 二维数组访问 ===" << endl;
    int access[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    cout << "矩阵内容:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << access[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "对角线元素: ";
    for (int i = 0; i < 3; ++i) {
        cout << access[i][i] << " ";
    }
    cout << endl;
    
    // 范围for循环遍历
    cout << "\n=== 范围for循环遍历 ===" << endl;
    int rangeMatrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    cout << "使用范围for循环:" << endl;
    for (const auto& row : rangeMatrix) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    
    // 二维数组作为参数
    cout << "\n=== 二维数组作为参数 ===" << endl;
    cout << "二维数组作为参数需要指定除第一维外的所有维度大小" << endl;
    cout << "例如：void func(int arr[][4], int rows)" << endl;
    
    // 动态二维数组
    cout << "\n=== 动态二维数组 ===" << endl;
    
    // 方式1：指针数组
    int rows = 3, cols = 4;
    int** dynamicMatrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        dynamicMatrix[i] = new int[cols];
    }
    
    // 初始化
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            dynamicMatrix[i][j] = i * cols + j + 1;
        }
    }
    
    cout << "动态二维数组:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << dynamicMatrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // 释放内存
    for (int i = 0; i < rows; ++i) {
        delete[] dynamicMatrix[i];
    }
    delete[] dynamicMatrix;
    
    // 方式2：一维数组模拟二维数组
    cout << "\n=== 一维数组模拟二维数组 ===" << endl;
    int* flatArray = new int[rows * cols];
    
    // 初始化
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            flatArray[i * cols + j] = i * cols + j + 1;
        }
    }
    
    cout << "一维数组模拟二维数组:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << flatArray[i * cols + j] << " ";
        }
        cout << endl;
    }
    
    delete[] flatArray;
    
    // 三维数组
    cout << "\n=== 三维数组 ===" << endl;
    int cube[2][3][4];
    
    // 初始化三维数组
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                cube[i][j][k] = i * 12 + j * 4 + k + 1;
            }
        }
    }
    
    cout << "三维数组内容:" << endl;
    for (int i = 0; i < 2; ++i) {
        cout << "层 " << i << ":" << endl;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                cout << cube[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    
    // 使用vector创建二维数组
    cout << "\n=== 使用vector创建二维数组 ===" << endl;
    vector<vector<int>> vectorMatrix(3, vector<int>(4));
    
    // 初始化
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            vectorMatrix[i][j] = i * 4 + j + 1;
        }
    }
    
    cout << "vector二维数组:" << endl;
    for (const auto& row : vectorMatrix) {
        for (const auto& element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    
    // 不规则二维数组
    cout << "\n=== 不规则二维数组 ===" << endl;
    vector<vector<int>> irregularMatrix = {
        {1, 2, 3},
        {4, 5},
        {6, 7, 8, 9, 10}
    };
    
    cout << "不规则二维数组:" << endl;
    for (size_t i = 0; i < irregularMatrix.size(); ++i) {
        cout << "行 " << i << ": ";
        for (size_t j = 0; j < irregularMatrix[i].size(); ++j) {
            cout << irregularMatrix[i][j] << " ";
        }
        cout << endl;
    }
    
    // 矩阵运算示例
    cout << "\n=== 矩阵运算示例 ===" << endl;
    int matA[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    int matB[2][3] = {
        {7, 8, 9},
        {10, 11, 12}
    };
    
    int matC[2][3];
    
    // 矩阵加法
    cout << "矩阵A:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matA[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "矩阵B:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matB[i][j] << " ";
        }
        cout << endl;
    }
    
    // 执行加法
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            matC[i][j] = matA[i][j] + matB[i][j];
        }
    }
    
    cout << "矩阵C = A + B:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << matC[i][j] << " ";
        }
        cout << endl;
    }
    
    // 矩阵转置
    cout << "\n=== 矩阵转置 ===" << endl;
    int original[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    int transposed[3][2];
    
    // 执行转置
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            transposed[j][i] = original[i][j];
        }
    }
    
    cout << "原矩阵:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << original[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "转置矩阵:" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << transposed[i][j] << " ";
        }
        cout << endl;
    }
    
    // 内存布局
    cout << "\n=== 内存布局 ===" << endl;
    int layout[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    
    cout << "二维数组内存布局（行优先）:" << endl;
    cout << "地址\t\t值" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << &layout[i][j] << "\t" << layout[i][j] << endl;
        }
    }
    
    // 性能比较
    cout << "\n=== 性能比较 ===" << endl;
    cout << "二维数组访问方式性能比较:" << endl;
    cout << "1. 原生数组：最快，内存连续" << endl;
    cout << "2. vector<vector>：较慢，内存可能不连续" << endl;
    cout << "3. 一维数组模拟：快，内存连续，但需要手动计算索引" << endl;
    cout << "4. 动态二维数组：较慢，需要额外的指针解引用" << endl;
    
    print_separator("多维数组示例完成");
    
    return 0;
} 