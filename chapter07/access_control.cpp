/*
 * 第7章：类 - 访问控制
 * 展示 public、private、protected 访问权限和友元的使用
 */

#include <iostream>
#include <string>
#include <vector>

namespace access_control_demo {

// 1. 基本访问控制
class Person {
private:
    std::string name;      // 私有成员：只能在类内部访问
    int age;
    std::string ssn;       // 社会保险号，高度私密

protected:
    double salary;         // 受保护成员：派生类可以访问
    std::string department;

public:
    // 构造函数
    Person(const std::string& n, int a, const std::string& s) 
        : name(n), age(a), ssn(s), salary(0.0) {}
    
    // 公有接口
    std::string getName() const { return name; }
    int getAge() const { return age; }
    
    // 设置器
    void setAge(int a) {
        if (a >= 0 && a <= 150) {
            age = a;
        }
    }
    
    // 显示公开信息
    void displayPublicInfo() const {
        std::cout << "姓名：" << name << "，年龄：" << age << std::endl;
    }
    
    // 友元函数声明
    friend void showPrivateInfo(const Person& p);
    friend class PersonManager;
    
protected:
    void setSalary(double s) { salary = s; }
    void setDepartment(const std::string& dept) { department = dept; }
};

// 2. 友元函数
void showPrivateInfo(const Person& p) {
    std::cout << "私有信息访问（通过友元函数）：" << std::endl;
    std::cout << "  姓名：" << p.name << std::endl;
    std::cout << "  年龄：" << p.age << std::endl;
    std::cout << "  社会保险号：" << p.ssn << std::endl;
    std::cout << "  薪水：" << p.salary << std::endl;
}

// 3. 友元类
class PersonManager {
private:
    std::vector<Person> employees;
    
public:
    void addEmployee(const Person& p) {
        employees.push_back(p);
    }
    
    void promoteEmployee(int index, double newSalary, const std::string& newDept) {
        if (index < employees.size()) {
            // 友元类可以访问Person的私有和受保护成员
            employees[index].salary = newSalary;
            employees[index].department = newDept;
            
            std::cout << "提升员工 " << employees[index].name 
                      << " 到部门 " << newDept 
                      << "，新薪水：" << newSalary << std::endl;
        }
    }
    
    void showAllEmployees() const {
        std::cout << "\n员工列表：" << std::endl;
        for (const auto& emp : employees) {
            std::cout << "姓名：" << emp.name 
                      << "，部门：" << emp.department 
                      << "，薪水：" << emp.salary << std::endl;
        }
    }
};

// 4. 继承中的访问控制
class Employee : public Person {
private:
    std::string employeeId;
    
public:
    Employee(const std::string& name, int age, const std::string& ssn, 
             const std::string& id)
        : Person(name, age, ssn), employeeId(id) {}
    
    void promote(double newSalary, const std::string& newDept) {
        // 可以访问protected成员
        setSalary(newSalary);
        setDepartment(newDept);
        
        std::cout << "员工 " << getName() << " 被提升！" << std::endl;
    }
    
    void showEmployeeInfo() const {
        displayPublicInfo();
        // 不能直接访问private成员，但可以访问protected成员
        std::cout << "员工ID：" << employeeId << std::endl;
        std::cout << "部门：" << department << std::endl;
        std::cout << "薪水：" << salary << std::endl;
    }
};

// 5. 不同继承方式的访问控制
class PublicDerived : public Person {
public:
    PublicDerived(const std::string& name, int age, const std::string& ssn) 
        : Person(name, age, ssn) {}
    
    void showInfo() {
        // public继承：public成员仍为public，protected成员仍为protected
        displayPublicInfo();  // OK
        // setSalary(50000);   // OK，protected成员可以访问
    }
};

class ProtectedDerived : protected Person {
public:
    ProtectedDerived(const std::string& name, int age, const std::string& ssn) 
        : Person(name, age, ssn) {}
    
    void showInfo() {
        // protected继承：public和protected成员都变为protected
        displayPublicInfo();  // OK，但外部无法访问此对象的displayPublicInfo
    }
};

class PrivateDerived : private Person {
public:
    PrivateDerived(const std::string& name, int age, const std::string& ssn) 
        : Person(name, age, ssn) {}
    
    void showInfo() {
        // private继承：public和protected成员都变为private
        displayPublicInfo();  // OK，但外部无法访问此对象的任何Person成员
    }
    
    // 可以通过using声明重新暴露某些成员
    using Person::getName;
    using Person::displayPublicInfo;
};

// 6. 封装示例：银行账户类
class BankAccount {
private:
    std::string accountNumber;
    double balance;
    std::string pin;
    
    // 私有辅助函数
    bool validatePin(const std::string& inputPin) const {
        return inputPin == pin;
    }
    
public:
    BankAccount(const std::string& accNum, const std::string& p) 
        : accountNumber(accNum), balance(0.0), pin(p) {}
    
    // 存款
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "存款 " << amount << " 成功，当前余额：" << balance << std::endl;
        }
    }
    
    // 取款（需要验证PIN）
    bool withdraw(double amount, const std::string& inputPin) {
        if (!validatePin(inputPin)) {
            std::cout << "PIN码错误！" << std::endl;
            return false;
        }
        
        if (amount > balance) {
            std::cout << "余额不足！" << std::endl;
            return false;
        }
        
        balance -= amount;
        std::cout << "取款 " << amount << " 成功，当前余额：" << balance << std::endl;
        return true;
    }
    
    // 查询余额（需要验证PIN）
    double getBalance(const std::string& inputPin) const {
        if (validatePin(inputPin)) {
            return balance;
        } else {
            std::cout << "PIN码错误！" << std::endl;
            return -1;
        }
    }
    
    // 友元操作符重载
    friend std::ostream& operator<<(std::ostream& os, const BankAccount& account);
};

std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
    os << "账户：" << account.accountNumber << "，余额：***（隐私保护）";
    return os;
}

// 7. 访问控制的实际应用
class DatabaseConnection {
private:
    std::string connectionString;
    bool connected;
    
    // 私有连接方法
    bool connect() {
        // 模拟连接过程
        connected = true;
        std::cout << "数据库连接成功" << std::endl;
        return true;
    }
    
    void disconnect() {
        connected = false;
        std::cout << "数据库连接已断开" << std::endl;
    }
    
public:
    DatabaseConnection(const std::string& connStr) 
        : connectionString(connStr), connected(false) {}
    
    ~DatabaseConnection() {
        if (connected) {
            disconnect();
        }
    }
    
    bool executeQuery(const std::string& query) {
        if (!connected) {
            connect();
        }
        
        std::cout << "执行查询：" << query << std::endl;
        return true;
    }
    
    bool isConnected() const { return connected; }
};

void demonstrateAccessControl() {
    std::cout << "\n=== 访问控制演示 ===" << std::endl;
    
    // 1. 基本访问控制
    std::cout << "\n1. 基本访问控制：" << std::endl;
    Person person("张三", 30, "123-45-6789");
    person.displayPublicInfo();
    
    // person.name = "李四";  // 错误：私有成员无法访问
    person.setAge(31);       // 正确：通过公有接口修改
    
    // 2. 友元函数
    std::cout << "\n2. 友元函数访问私有成员：" << std::endl;
    showPrivateInfo(person);
    
    // 3. 友元类
    std::cout << "\n3. 友元类管理：" << std::endl;
    PersonManager manager;
    manager.addEmployee(person);
    manager.promoteEmployee(0, 80000, "技术部");
    manager.showAllEmployees();
    
    // 4. 继承中的访问控制
    std::cout << "\n4. 继承中的访问控制：" << std::endl;
    Employee emp("王五", 28, "987-65-4321", "EMP001");
    emp.promote(75000, "开发部");
    emp.showEmployeeInfo();
    
    // 5. 不同继承方式
    std::cout << "\n5. 不同继承方式：" << std::endl;
    PublicDerived pubDerived("赵六", 35, "111-22-3333");
    pubDerived.displayPublicInfo();  // public继承，可以访问
    
    PrivateDerived privDerived("孙七", 40, "444-55-6666");
    privDerived.displayPublicInfo();  // 通过using声明重新暴露
    std::cout << "私有继承对象的getName：" << privDerived.getName() << std::endl;
    
    // 6. 封装示例：银行账户
    std::cout << "\n6. 银行账户封装：" << std::endl;
    BankAccount account("12345678", "1234");
    account.deposit(1000);
    account.withdraw(200, "1234");
    account.withdraw(200, "5678");  // 错误的PIN
    
    double balance = account.getBalance("1234");
    if (balance >= 0) {
        std::cout << "当前余额：" << balance << std::endl;
    }
    
    // 7. 数据库连接封装
    std::cout << "\n7. 数据库连接封装：" << std::endl;
    DatabaseConnection db("localhost:3306/mydb");
    db.executeQuery("SELECT * FROM users");
    std::cout << "连接状态：" << (db.isConnected() ? "已连接" : "未连接") << std::endl;
}

} // namespace access_control_demo

int main() {
    access_control_demo::demonstrateAccessControl();
    return 0;
} 