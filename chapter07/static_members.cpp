/*
 * 第7章：类 - 静态成员
 * 展示静态成员变量、静态成员函数、单例模式等
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <mutex>

namespace static_members_demo {

// 1. 基本静态成员演示
class Counter {
private:
    static int objectCount;  // 静态成员变量声明
    int id;
    
public:
    Counter() {
        id = ++objectCount;  // 每创建一个对象，计数器加1
        std::cout << "创建Counter对象，ID: " << id << std::endl;
    }
    
    ~Counter() {
        --objectCount;
        std::cout << "销毁Counter对象，ID: " << id << std::endl;
    }
    
    // 静态成员函数
    static int getObjectCount() {
        // 静态成员函数只能访问静态成员
        return objectCount;
    }
    
    // 普通成员函数
    int getId() const { return id; }
    
    // 静态成员函数，用于显示统计信息
    static void showStatistics() {
        std::cout << "当前存在的Counter对象数量: " << objectCount << std::endl;
    }
};

// 静态成员变量定义（必须在类外定义）
int Counter::objectCount = 0;

// 2. 静态成员的更复杂应用
class BankAccount {
private:
    static double interestRate;    // 静态利率
    static int totalAccounts;      // 总账户数
    static double totalBalance;    // 总余额
    
    std::string accountNumber;
    double balance;
    
public:
    BankAccount(const std::string& accNum, double initialBalance = 0.0)
        : accountNumber(accNum), balance(initialBalance) {
        ++totalAccounts;
        totalBalance += balance;
        std::cout << "开户成功：" << accountNumber 
                  << "，初始余额：" << balance << std::endl;
    }
    
    ~BankAccount() {
        --totalAccounts;
        totalBalance -= balance;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            totalBalance -= balance;  // 先减去旧余额
            balance += amount;
            totalBalance += balance;  // 再加上新余额
            std::cout << "存款 " << amount << "，余额：" << balance << std::endl;
        }
    }
    
    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            totalBalance -= balance;  // 先减去旧余额
            balance -= amount;
            totalBalance += balance;  // 再加上新余额
            std::cout << "取款 " << amount << "，余额：" << balance << std::endl;
            return true;
        }
        return false;
    }
    
    void applyInterest() {
        double interest = balance * interestRate;
        deposit(interest);
        std::cout << "利息：" << interest << std::endl;
    }
    
    // 静态成员函数
    static void setInterestRate(double rate) {
        interestRate = rate;
        std::cout << "银行利率调整为：" << rate * 100 << "%" << std::endl;
    }
    
    static double getInterestRate() {
        return interestRate;
    }
    
    static int getTotalAccounts() {
        return totalAccounts;
    }
    
    static double getTotalBalance() {
        return totalBalance;
    }
    
    static void showBankStatistics() {
        std::cout << "\n=== 银行统计信息 ===" << std::endl;
        std::cout << "总账户数：" << totalAccounts << std::endl;
        std::cout << "总余额：" << totalBalance << std::endl;
        std::cout << "平均余额：" << (totalAccounts > 0 ? totalBalance / totalAccounts : 0) << std::endl;
        std::cout << "当前利率：" << interestRate * 100 << "%" << std::endl;
    }
    
    // 普通成员函数
    double getBalance() const { return balance; }
    std::string getAccountNumber() const { return accountNumber; }
};

// 静态成员变量定义
double BankAccount::interestRate = 0.02;  // 2%利率
int BankAccount::totalAccounts = 0;
double BankAccount::totalBalance = 0.0;

// 3. 单例模式 - 懒汉式
class Logger {
private:
    static Logger* instance;
    static std::mutex mutex_;
    
    std::vector<std::string> logs;
    
    // 私有构造函数，防止外部创建实例
    Logger() {
        std::cout << "Logger初始化" << std::endl;
    }
    
    // 禁用拷贝构造和赋值操作
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
public:
    // 获取单例实例
    static Logger* getInstance() {
        // 双重检查锁定
        if (instance == nullptr) {
            std::lock_guard<std::mutex> lock(mutex_);
            if (instance == nullptr) {
                instance = new Logger();
            }
        }
        return instance;
    }
    
    void log(const std::string& message) {
        logs.push_back(message);
        std::cout << "[LOG] " << message << std::endl;
    }
    
    void showLogs() const {
        std::cout << "\n=== 日志记录 ===" << std::endl;
        for (size_t i = 0; i < logs.size(); ++i) {
            std::cout << i + 1 << ". " << logs[i] << std::endl;
        }
    }
    
    static void cleanup() {
        delete instance;
        instance = nullptr;
    }
};

// 静态成员定义
Logger* Logger::instance = nullptr;
std::mutex Logger::mutex_;

// 4. 单例模式 - 饿汉式
class ConfigManager {
private:
    static ConfigManager instance;  // 静态实例
    std::string configFile;
    
    ConfigManager() : configFile("default.config") {
        std::cout << "ConfigManager初始化，加载：" << configFile << std::endl;
    }
    
public:
    // 获取单例实例的引用
    static ConfigManager& getInstance() {
        return instance;
    }
    
    void setConfigFile(const std::string& filename) {
        configFile = filename;
        std::cout << "配置文件更改为：" << filename << std::endl;
    }
    
    std::string getConfigFile() const {
        return configFile;
    }
    
    void loadConfig() {
        std::cout << "加载配置文件：" << configFile << std::endl;
    }
};

// 静态实例定义
ConfigManager ConfigManager::instance;

// 5. 现代C++单例模式 - 使用智能指针
class DatabaseManager {
private:
    static std::unique_ptr<DatabaseManager> instance;
    static std::once_flag initFlag;
    
    std::string connectionString;
    
    DatabaseManager() : connectionString("localhost:3306") {
        std::cout << "DatabaseManager初始化" << std::endl;
    }
    
public:
    static DatabaseManager& getInstance() {
        std::call_once(initFlag, []() {
            instance = std::unique_ptr<DatabaseManager>(new DatabaseManager());
        });
        return *instance;
    }
    
    void connect() {
        std::cout << "连接数据库：" << connectionString << std::endl;
    }
    
    void setConnectionString(const std::string& connStr) {
        connectionString = connStr;
    }
    
    std::string getConnectionString() const {
        return connectionString;
    }
};

// 静态成员定义
std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;
std::once_flag DatabaseManager::initFlag;

// 6. 静态成员的高级应用 - 工厂模式
class Shape {
public:
    virtual ~Shape() = default;
    virtual void draw() const = 0;
    virtual std::string getType() const = 0;
};

class Circle : public Shape {
public:
    void draw() const override {
        std::cout << "绘制圆形" << std::endl;
    }
    
    std::string getType() const override {
        return "Circle";
    }
};

class Rectangle : public Shape {
public:
    void draw() const override {
        std::cout << "绘制矩形" << std::endl;
    }
    
    std::string getType() const override {
        return "Rectangle";
    }
};

class ShapeFactory {
private:
    static int shapesCreated;
    
public:
    enum ShapeType { CIRCLE, RECTANGLE };
    
    static std::unique_ptr<Shape> createShape(ShapeType type) {
        ++shapesCreated;
        
        switch (type) {
            case CIRCLE:
                std::cout << "创建圆形对象" << std::endl;
                return std::make_unique<Circle>();
            case RECTANGLE:
                std::cout << "创建矩形对象" << std::endl;
                return std::make_unique<Rectangle>();
            default:
                return nullptr;
        }
    }
    
    static int getShapesCreated() {
        return shapesCreated;
    }
    
    static void showStatistics() {
        std::cout << "工厂已创建形状数量：" << shapesCreated << std::endl;
    }
};

int ShapeFactory::shapesCreated = 0;

// 7. 静态成员常量
class MathConstants {
public:
    static const double PI;
    static const double E;
    static constexpr int MAX_PRECISION = 15;  // 编译时常量
    
    // 静态成员函数使用静态常量
    static double circleArea(double radius) {
        return PI * radius * radius;
    }
    
    static double sphereVolume(double radius) {
        return (4.0 / 3.0) * PI * radius * radius * radius;
    }
};

// 静态const成员必须在类外定义
const double MathConstants::PI = 3.14159265358979323846;
const double MathConstants::E = 2.71828182845904523536;

void demonstrateStaticMembers() {
    std::cout << "\n=== 静态成员演示 ===" << std::endl;
    
    // 1. 基本静态成员
    std::cout << "\n1. 基本静态成员计数器：" << std::endl;
    Counter::showStatistics();
    
    {
        Counter c1, c2, c3;
        Counter::showStatistics();
        std::cout << "通过对象访问静态函数：" << c1.getObjectCount() << std::endl;
    }  // 对象销毁
    
    Counter::showStatistics();
    
    // 2. 银行账户静态成员应用
    std::cout << "\n2. 银行账户系统：" << std::endl;
    BankAccount::showBankStatistics();
    
    BankAccount acc1("001", 1000);
    BankAccount acc2("002", 2000);
    BankAccount acc3("003", 1500);
    
    BankAccount::showBankStatistics();
    
    acc1.deposit(500);
    acc2.withdraw(300);
    
    BankAccount::setInterestRate(0.03);  // 调整利率
    acc1.applyInterest();
    acc2.applyInterest();
    acc3.applyInterest();
    
    BankAccount::showBankStatistics();
    
    // 3. 单例模式 - Logger
    std::cout << "\n3. 单例模式 - Logger：" << std::endl;
    Logger* logger1 = Logger::getInstance();
    Logger* logger2 = Logger::getInstance();
    
    std::cout << "两个Logger指针是否相同：" << (logger1 == logger2 ? "是" : "否") << std::endl;
    
    logger1->log("系统启动");
    logger2->log("用户登录");
    logger1->log("执行操作");
    
    logger1->showLogs();
    Logger::cleanup();
    
    // 4. 单例模式 - ConfigManager
    std::cout << "\n4. 单例模式 - ConfigManager：" << std::endl;
    ConfigManager& config1 = ConfigManager::getInstance();
    ConfigManager& config2 = ConfigManager::getInstance();
    
    std::cout << "两个ConfigManager引用是否相同：" << (&config1 == &config2 ? "是" : "否") << std::endl;
    
    config1.loadConfig();
    config2.setConfigFile("production.config");
    config1.loadConfig();
    
    // 5. 现代单例模式 - DatabaseManager
    std::cout << "\n5. 现代单例模式 - DatabaseManager：" << std::endl;
    DatabaseManager& db1 = DatabaseManager::getInstance();
    DatabaseManager& db2 = DatabaseManager::getInstance();
    
    db1.connect();
    db2.setConnectionString("remote:5432");
    db1.connect();
    
    // 6. 工厂模式
    std::cout << "\n6. 工厂模式：" << std::endl;
    auto circle = ShapeFactory::createShape(ShapeFactory::CIRCLE);
    auto rect = ShapeFactory::createShape(ShapeFactory::RECTANGLE);
    
    circle->draw();
    rect->draw();
    
    ShapeFactory::showStatistics();
    
    // 7. 静态常量
    std::cout << "\n7. 静态常量：" << std::endl;
    std::cout << "PI = " << MathConstants::PI << std::endl;
    std::cout << "E = " << MathConstants::E << std::endl;
    std::cout << "MAX_PRECISION = " << MathConstants::MAX_PRECISION << std::endl;
    
    double radius = 5.0;
    std::cout << "半径为 " << radius << " 的圆的面积：" 
              << MathConstants::circleArea(radius) << std::endl;
    std::cout << "半径为 " << radius << " 的球的体积：" 
              << MathConstants::sphereVolume(radius) << std::endl;
}

} // namespace static_members_demo

int main() {
    static_members_demo::demonstrateStaticMembers();
    return 0;
} 