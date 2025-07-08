#include "common.h"

// 1. 最简单的类定义
class SimpleClass {
    // 默认为private访问权限
    int value;
    
public:
    // 构造函数
    SimpleClass(int v) : value(v) {
        cout << "  SimpleClass构造函数调用，值: " << value << endl;
    }
    
    // 成员函数
    void setValue(int v) {
        value = v;
    }
    
    int getValue() const {
        return value;
    }
    
    void print() const {
        cout << "  SimpleClass值: " << value << endl;
    }
    
    // 析构函数
    ~SimpleClass() {
        cout << "  SimpleClass析构函数调用，值: " << value << endl;
    }
};

// 2. 学生类 - 展示基本概念
class Student {
private:
    string name;
    int age;
    double gpa;
    vector<string> courses;
    
public:
    // 默认构造函数
    Student() : name("未知"), age(0), gpa(0.0) {
        cout << "  Student默认构造函数调用" << endl;
    }
    
    // 参数化构造函数
    Student(const string& n, int a, double g) : name(n), age(a), gpa(g) {
        cout << "  Student参数化构造函数调用: " << name << endl;
    }
    
    // 拷贝构造函数
    Student(const Student& other) : name(other.name), age(other.age), gpa(other.gpa), courses(other.courses) {
        cout << "  Student拷贝构造函数调用: " << name << endl;
    }
    
    // 赋值运算符
    Student& operator=(const Student& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
            gpa = other.gpa;
            courses = other.courses;
            cout << "  Student赋值运算符调用: " << name << endl;
        }
        return *this;
    }
    
    // 析构函数
    ~Student() {
        cout << "  Student析构函数调用: " << name << endl;
    }
    
    // 访问器方法 (getter)
    const string& getName() const { return name; }
    int getAge() const { return age; }
    double getGpa() const { return gpa; }
    const vector<string>& getCourses() const { return courses; }
    
    // 修改器方法 (setter)
    void setName(const string& n) { name = n; }
    void setAge(int a) { 
        if (a >= 0 && a <= 120) {
            age = a; 
        }
    }
    void setGpa(double g) { 
        if (g >= 0.0 && g <= 4.0) {
            gpa = g; 
        }
    }
    
    // 业务逻辑方法
    void addCourse(const string& course) {
        courses.push_back(course);
        cout << "  " << name << " 添加课程: " << course << endl;
    }
    
    void removeCourse(const string& course) {
        auto it = find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
            cout << "  " << name << " 移除课程: " << course << endl;
        }
    }
    
    bool hasCourse(const string& course) const {
        return find(courses.begin(), courses.end(), course) != courses.end();
    }
    
    double calculateCredits() const {
        return courses.size() * 3.0;  // 假设每门课3学分
    }
    
    void print() const {
        cout << "  学生信息:" << endl;
        cout << "    姓名: " << name << endl;
        cout << "    年龄: " << age << endl;
        cout << "    GPA: " << gpa << endl;
        cout << "    学分: " << calculateCredits() << endl;
        cout << "    课程: ";
        for (const auto& course : courses) {
            cout << course << " ";
        }
        cout << endl;
    }
};

// 3. 银行账户类 - 展示封装
class BankAccount {
private:
    string accountNumber;
    string holderName;
    double balance;
    static int nextAccountId;  // 静态成员，用于生成账号
    
    // 私有辅助方法
    string generateAccountNumber() {
        return "ACC" + to_string(++nextAccountId);
    }
    
    bool isValidAmount(double amount) const {
        return amount > 0;
    }
    
public:
    // 构造函数
    BankAccount(const string& holder, double initialBalance = 0.0) 
        : holderName(holder), balance(initialBalance) {
        accountNumber = generateAccountNumber();
        cout << "  银行账户创建: " << accountNumber << " 持有人: " << holderName << endl;
    }
    
    // 析构函数
    ~BankAccount() {
        cout << "  银行账户销毁: " << accountNumber << endl;
    }
    
    // 只读访问器
    const string& getAccountNumber() const { return accountNumber; }
    const string& getHolderName() const { return holderName; }
    double getBalance() const { return balance; }
    
    // 业务方法
    bool deposit(double amount) {
        if (isValidAmount(amount)) {
            balance += amount;
            cout << "  存款成功: " << amount << "，余额: " << balance << endl;
            return true;
        }
        cout << "  存款失败: 金额无效" << endl;
        return false;
    }
    
    bool withdraw(double amount) {
        if (isValidAmount(amount) && amount <= balance) {
            balance -= amount;
            cout << "  取款成功: " << amount << "，余额: " << balance << endl;
            return true;
        }
        cout << "  取款失败: 金额无效或余额不足" << endl;
        return false;
    }
    
    bool transfer(BankAccount& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            cout << "  转账成功: " << amount << " 从 " << accountNumber 
                 << " 到 " << toAccount.accountNumber << endl;
            return true;
        }
        cout << "  转账失败" << endl;
        return false;
    }
    
    void printStatement() const {
        cout << "  账户信息:" << endl;
        cout << "    账号: " << accountNumber << endl;
        cout << "    持有人: " << holderName << endl;
        cout << "    余额: $" << balance << endl;
    }
};

// 静态成员定义
int BankAccount::nextAccountId = 1000;

// 4. 几何形状类 - 展示抽象概念
class Point {
private:
    double x, y;
    
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    double getX() const { return x; }
    double getY() const { return y; }
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    
    double distanceTo(const Point& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
    
    void print() const {
        cout << "(" << x << ", " << y << ")";
    }
};

class Circle {
private:
    Point center;
    double radius;
    
public:
    Circle(const Point& c, double r) : center(c), radius(r) {
        if (radius < 0) {
            radius = 0;
        }
    }
    
    Circle(double x, double y, double r) : center(x, y), radius(r) {
        if (radius < 0) {
            radius = 0;
        }
    }
    
    const Point& getCenter() const { return center; }
    double getRadius() const { return radius; }
    
    void setCenter(const Point& c) { center = c; }
    void setRadius(double r) { 
        if (r >= 0) {
            radius = r; 
        }
    }
    
    double area() const {
        return M_PI * radius * radius;
    }
    
    double circumference() const {
        return 2 * M_PI * radius;
    }
    
    bool contains(const Point& p) const {
        return center.distanceTo(p) <= radius;
    }
    
    void print() const {
        cout << "  圆形 - 中心: ";
        center.print();
        cout << ", 半径: " << radius;
        cout << ", 面积: " << area();
        cout << ", 周长: " << circumference() << endl;
    }
};

class Rectangle {
private:
    Point topLeft;
    double width, height;
    
public:
    Rectangle(const Point& tl, double w, double h) 
        : topLeft(tl), width(w), height(h) {
        if (width < 0) width = 0;
        if (height < 0) height = 0;
    }
    
    Rectangle(double x, double y, double w, double h) 
        : topLeft(x, y), width(w), height(h) {
        if (width < 0) width = 0;
        if (height < 0) height = 0;
    }
    
    const Point& getTopLeft() const { return topLeft; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    
    Point getBottomRight() const {
        return Point(topLeft.getX() + width, topLeft.getY() + height);
    }
    
    double area() const {
        return width * height;
    }
    
    double perimeter() const {
        return 2 * (width + height);
    }
    
    bool contains(const Point& p) const {
        return p.getX() >= topLeft.getX() && 
               p.getX() <= topLeft.getX() + width &&
               p.getY() >= topLeft.getY() && 
               p.getY() <= topLeft.getY() + height;
    }
    
    void print() const {
        cout << "  矩形 - 左上角: ";
        topLeft.print();
        cout << ", 宽: " << width << ", 高: " << height;
        cout << ", 面积: " << area();
        cout << ", 周长: " << perimeter() << endl;
    }
};

// 5. 图书管理系统 - 综合示例
class Book {
private:
    string isbn;
    string title;
    string author;
    int pages;
    bool available;
    
public:
    Book(const string& isbn, const string& title, const string& author, int pages)
        : isbn(isbn), title(title), author(author), pages(pages), available(true) {}
    
    // 访问器
    const string& getIsbn() const { return isbn; }
    const string& getTitle() const { return title; }
    const string& getAuthor() const { return author; }
    int getPages() const { return pages; }
    bool isAvailable() const { return available; }
    
    // 业务方法
    void borrow() {
        if (available) {
            available = false;
            cout << "  《" << title << "》已借出" << endl;
        } else {
            cout << "  《" << title << "》已被借出" << endl;
        }
    }
    
    void returnBook() {
        if (!available) {
            available = true;
            cout << "  《" << title << "》已归还" << endl;
        } else {
            cout << "  《" << title << "》本来就在图书馆" << endl;
        }
    }
    
    void print() const {
        cout << "  图书信息:" << endl;
        cout << "    ISBN: " << isbn << endl;
        cout << "    标题: " << title << endl;
        cout << "    作者: " << author << endl;
        cout << "    页数: " << pages << endl;
        cout << "    状态: " << (available ? "可借" : "已借出") << endl;
    }
};

class Library {
private:
    string name;
    vector<Book> books;
    
public:
    Library(const string& name) : name(name) {
        cout << "  图书馆创建: " << name << endl;
    }
    
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "  添加图书: 《" << book.getTitle() << "》" << endl;
    }
    
    Book* findBook(const string& isbn) {
        for (auto& book : books) {
            if (book.getIsbn() == isbn) {
                return &book;
            }
        }
        return nullptr;
    }
    
    vector<Book*> findBooksByAuthor(const string& author) {
        vector<Book*> result;
        for (auto& book : books) {
            if (book.getAuthor() == author) {
                result.push_back(&book);
            }
        }
        return result;
    }
    
    void listAvailableBooks() const {
        cout << "  " << name << " 可借图书:" << endl;
        for (const auto& book : books) {
            if (book.isAvailable()) {
                cout << "    - 《" << book.getTitle() << "》 by " 
                     << book.getAuthor() << endl;
            }
        }
    }
    
    void printStatistics() const {
        int total = books.size();
        int available = 0;
        for (const auto& book : books) {
            if (book.isAvailable()) {
                available++;
            }
        }
        
        cout << "  " << name << " 统计信息:" << endl;
        cout << "    总藏书: " << total << endl;
        cout << "    可借: " << available << endl;
        cout << "    已借出: " << (total - available) << endl;
    }
};

// 6. 对象生命周期演示
void demonstrateObjectLifecycle() {
    cout << "=== 对象生命周期演示 ===" << endl;
    
    cout << "1. 栈对象:" << endl;
    {
        SimpleClass obj1(10);
        obj1.print();
    }  // obj1在这里自动销毁
    
    cout << "\n2. 动态对象:" << endl;
    SimpleClass* obj2 = new SimpleClass(20);
    obj2->print();
    delete obj2;  // 手动销毁
    
    cout << "\n3. 容器中的对象:" << endl;
    {
        vector<SimpleClass> objects;
        objects.emplace_back(30);  // 直接在容器中构造
        objects.emplace_back(40);
        
        for (const auto& obj : objects) {
            obj.print();
        }
    }  // 容器销毁时，所有对象自动销毁
}

int main() {
    print_separator("类基础概念详解");
    
    // 1. 对象生命周期
    demonstrateObjectLifecycle();
    
    // 2. 学生类使用
    cout << "\n=== 学生类使用示例 ===" << endl;
    
    Student student1;  // 默认构造
    student1.setName("张三");
    student1.setAge(20);
    student1.setGpa(3.5);
    student1.addCourse("数学");
    student1.addCourse("物理");
    student1.addCourse("化学");
    student1.print();
    
    Student student2("李四", 21, 3.8);  // 参数化构造
    student2.addCourse("计算机科学");
    student2.addCourse("数据结构");
    student2.print();
    
    Student student3 = student2;  // 拷贝构造
    student3.setName("王五");
    student3.addCourse("算法");
    student3.print();
    
    student1 = student3;  // 赋值运算符
    student1.print();
    
    // 3. 银行账户系统
    cout << "\n=== 银行账户系统 ===" << endl;
    
    BankAccount account1("张三", 1000.0);
    BankAccount account2("李四", 500.0);
    
    account1.printStatement();
    account2.printStatement();
    
    account1.deposit(200.0);
    account1.withdraw(150.0);
    account1.transfer(account2, 300.0);
    
    cout << "\n操作后的账户状态:" << endl;
    account1.printStatement();
    account2.printStatement();
    
    // 4. 几何形状
    cout << "\n=== 几何形状示例 ===" << endl;
    
    Point p1(3, 4);
    Point p2(6, 8);
    
    cout << "点p1: ";
    p1.print();
    cout << ", 点p2: ";
    p2.print();
    cout << ", 距离: " << p1.distanceTo(p2) << endl;
    
    Circle circle(p1, 5.0);
    circle.print();
    
    cout << "p2在圆内: " << (circle.contains(p2) ? "是" : "否") << endl;
    
    Rectangle rect(Point(0, 0), 10, 8);
    rect.print();
    
    cout << "p1在矩形内: " << (rect.contains(p1) ? "是" : "否") << endl;
    cout << "p2在矩形内: " << (rect.contains(p2) ? "是" : "否") << endl;
    
    // 5. 图书管理系统
    cout << "\n=== 图书管理系统 ===" << endl;
    
    Library library("市立图书馆");
    
    library.addBook(Book("978-0134685991", "Effective Modern C++", "Scott Meyers", 334));
    library.addBook(Book("978-0321563842", "The C++ Programming Language", "Bjarne Stroustrup", 1376));
    library.addBook(Book("978-0134494166", "A Tour of C++", "Bjarne Stroustrup", 256));
    
    library.printStatistics();
    library.listAvailableBooks();
    
    cout << "\n借书操作:" << endl;
    Book* book = library.findBook("978-0134685991");
    if (book) {
        book->borrow();
    }
    
    library.printStatistics();
    library.listAvailableBooks();
    
    cout << "\n还书操作:" << endl;
    if (book) {
        book->returnBook();
    }
    
    library.printStatistics();
    
    cout << "\n按作者查找:" << endl;
    auto bjarne_books = library.findBooksByAuthor("Bjarne Stroustrup");
    cout << "  Bjarne Stroustrup的书籍:" << endl;
    for (const auto& b : bjarne_books) {
        cout << "    - 《" << b->getTitle() << "》" << endl;
    }
    
    // 6. 类的基本概念总结
    cout << "\n=== 类的基本概念总结 ===" << endl;
    cout << "1. 封装 (Encapsulation):" << endl;
    cout << "   - 数据和方法组合在一起" << endl;
    cout << "   - 隐藏内部实现细节" << endl;
    cout << "   - 通过访问控制保护数据" << endl;
    
    cout << "\n2. 数据成员 (Data Members):" << endl;
    cout << "   - 类的属性或状态" << endl;
    cout << "   - 通常声明为private" << endl;
    cout << "   - 通过成员函数访问" << endl;
    
    cout << "\n3. 成员函数 (Member Functions):" << endl;
    cout << "   - 构造函数和析构函数" << endl;
    cout << "   - 访问器和修改器" << endl;
    cout << "   - 业务逻辑方法" << endl;
    
    cout << "\n4. 访问控制 (Access Control):" << endl;
    cout << "   - private: 类内部访问" << endl;
    cout << "   - protected: 类和派生类访问" << endl;
    cout << "   - public: 任何地方访问" << endl;
    
    cout << "\n5. 对象生命周期:" << endl;
    cout << "   - 构造: 对象创建时自动调用构造函数" << endl;
    cout << "   - 使用: 通过成员函数操作对象" << endl;
    cout << "   - 销毁: 对象销毁时自动调用析构函数" << endl;
    
    // 7. 设计原则
    cout << "\n=== 类设计原则 ===" << endl;
    cout << "1. 单一职责原则: 一个类只负责一个功能" << endl;
    cout << "2. 封装原则: 隐藏实现细节，暴露必要接口" << endl;
    cout << "3. 一致性原则: 命名和行为保持一致" << endl;
    cout << "4. 最小接口原则: 只提供必要的公共接口" << endl;
    cout << "5. 资源管理原则: 谁创建谁负责销毁" << endl;
    cout << "6. 异常安全原则: 保证操作的异常安全性" << endl;
    cout << "7. 性能考虑: 合理设计减少不必要的开销" << endl;
    
    print_separator("类基础概念详解完成");
    
    return 0;
} 