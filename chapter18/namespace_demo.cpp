/**
 * @file namespace_demo.cpp
 * @brief 命名空间和大型程序工具演示
 */

#include <iostream>
#include <string>

// 自定义命名空间
namespace MyLibrary {
    namespace Math {
        double pi = 3.14159;
        
        double area_circle(double radius) {
            return pi * radius * radius;
        }
        
        namespace Advanced {
            double factorial(int n) {
                return n <= 1 ? 1 : n * factorial(n - 1);
            }
        }
    }
    
    namespace String {
        std::string upper(const std::string& str) {
            std::string result = str;
            for (char& c : result) {
                c = std::toupper(c);
            }
            return result;
        }
    }
}

// 使用别名
namespace ML = MyLibrary;
namespace MLA = MyLibrary::Math::Advanced;

void demonstrate_namespaces() {
    std::cout << "\n=== 命名空间演示 ===\n";
    
    // 使用完整限定名
    std::cout << "圆面积: " << MyLibrary::Math::area_circle(5.0) << "\n";
    
    // 使用别名
    std::cout << "阶乘: " << MLA::factorial(5) << "\n";
    
    // 使用 using 声明
    using MyLibrary::String::upper;
    std::cout << "转大写: " << upper("hello world") << "\n";
    
    {
        // 局部 using namespace
        using namespace MyLibrary::Math;
        std::cout << "PI 值: " << pi << "\n";
    }
}

void demonstrate_argument_dependent_lookup() {
    std::cout << "\n=== 参数依赖查找 (ADL) 演示 ===\n";
    
    std::cout << "ADL 允许在参数的命名空间中查找函数\n";
    std::cout << "例如: std::cout << value (在 std 命名空间中查找 operator<<)\n";
}

int main() {
    std::cout << "C++ Primer Chapter 18: 大型程序工具演示\n";
    std::cout << "===================================\n";
    
    demonstrate_namespaces();
    demonstrate_argument_dependent_lookup();
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 