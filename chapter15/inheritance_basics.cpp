/**
 * @file inheritance_basics.cpp
 * @brief 继承基础演示 - 基类派生类、访问控制、构造析构顺序
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// 基础动物类
class Animal {
protected:
    std::string name;
    int age;
    
public:
    Animal(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Animal 构造函数: " << name << "\n";
    }
    
    virtual ~Animal() {
        std::cout << "Animal 析构函数: " << name << "\n";
    }
    
    // 公有接口
    std::string get_name() const { return name; }
    int get_age() const { return age; }
    
    void set_age(int a) { age = a; }
    
    // 虚函数 - 可被派生类重写
    virtual void make_sound() const {
        std::cout << name << " 发出了动物的声音\n";
    }
    
    virtual void move() const {
        std::cout << name << " 正在移动\n";
    }
    
    // 非虚函数
    void sleep() const {
        std::cout << name << " 正在睡觉\n";
    }
    
    void eat() const {
        std::cout << name << " 正在吃东西\n";
    }
    
    virtual void display_info() const {
        std::cout << "动物: " << name << ", 年龄: " << age << "\n";
    }
};

// 哺乳动物类 - 公有继承
class Mammal : public Animal {
protected:
    bool has_fur;
    
public:
    Mammal(const std::string& n, int a, bool fur) 
        : Animal(n, a), has_fur(fur) {
        std::cout << "Mammal 构造函数: " << name << "\n";
    }
    
    virtual ~Mammal() {
        std::cout << "Mammal 析构函数: " << name << "\n";
    }
    
    bool get_has_fur() const { return has_fur; }
    
    // 重写基类虚函数
    void move() const override {
        std::cout << name << " 用四条腿行走\n";
    }
    
    void display_info() const override {
        Animal::display_info();  // 调用基类版本
        std::cout << "毛发: " << (has_fur ? "有" : "无") << "\n";
    }
    
    // 哺乳动物特有的行为
    virtual void give_birth() const {
        std::cout << name << " 生下了幼崽\n";
    }
};

// 鸟类 - 公有继承
class Bird : public Animal {
protected:
    bool can_fly;
    
public:
    Bird(const std::string& n, int a, bool fly) 
        : Animal(n, a), can_fly(fly) {
        std::cout << "Bird 构造函数: " << name << "\n";
    }
    
    virtual ~Bird() {
        std::cout << "Bird 析构函数: " << name << "\n";
    }
    
    bool get_can_fly() const { return can_fly; }
    
    void move() const override {
        if (can_fly) {
            std::cout << name << " 正在飞翔\n";
        } else {
            std::cout << name << " 正在行走\n";
        }
    }
    
    void make_sound() const override {
        std::cout << name << " 发出鸟叫声\n";
    }
    
    void display_info() const override {
        Animal::display_info();
        std::cout << "飞行能力: " << (can_fly ? "能飞" : "不能飞") << "\n";
    }
    
    // 鸟类特有的行为
    virtual void lay_eggs() const {
        std::cout << name << " 下了蛋\n";
    }
};

// 狗类 - 从哺乳动物继承
class Dog : public Mammal {
private:
    std::string breed;
    
public:
    Dog(const std::string& n, int a, const std::string& b) 
        : Mammal(n, a, true), breed(b) {
        std::cout << "Dog 构造函数: " << name << "\n";
    }
    
    ~Dog() {
        std::cout << "Dog 析构函数: " << name << "\n";
    }
    
    std::string get_breed() const { return breed; }
    
    void make_sound() const override {
        std::cout << name << " 汪汪叫\n";
    }
    
    void display_info() const override {
        Mammal::display_info();
        std::cout << "品种: " << breed << "\n";
    }
    
    // 狗特有的行为
    void wag_tail() const {
        std::cout << name << " 摇尾巴\n";
    }
    
    void fetch() const {
        std::cout << name << " 去捡球\n";
    }
};

// 猫类 - 从哺乳动物继承
class Cat : public Mammal {
private:
    bool is_indoor;
    
public:
    Cat(const std::string& n, int a, bool indoor) 
        : Mammal(n, a, true), is_indoor(indoor) {
        std::cout << "Cat 构造函数: " << name << "\n";
    }
    
    ~Cat() {
        std::cout << "Cat 析构函数: " << name << "\n";
    }
    
    bool get_is_indoor() const { return is_indoor; }
    
    void make_sound() const override {
        std::cout << name << " 喵喵叫\n";
    }
    
    void display_info() const override {
        Mammal::display_info();
        std::cout << "生活环境: " << (is_indoor ? "室内" : "室外") << "\n";
    }
    
    // 猫特有的行为
    void purr() const {
        std::cout << name << " 发出呼噜声\n";
    }
    
    void climb() const {
        std::cout << name << " 正在爬树\n";
    }
};

// 企鹅类 - 从鸟类继承（不能飞的鸟）
class Penguin : public Bird {
private:
    std::string species;
    
public:
    Penguin(const std::string& n, int a, const std::string& s) 
        : Bird(n, a, false), species(s) {
        std::cout << "Penguin 构造函数: " << name << "\n";
    }
    
    ~Penguin() {
        std::cout << "Penguin 析构函数: " << name << "\n";
    }
    
    std::string get_species() const { return species; }
    
    void move() const override {
        std::cout << name << " 摇摆着行走或游泳\n";
    }
    
    void make_sound() const override {
        std::cout << name << " 发出企鹅叫声\n";
    }
    
    void display_info() const override {
        Bird::display_info();
        std::cout << "种类: " << species << "\n";
    }
    
    // 企鹅特有的行为
    void swim() const {
        std::cout << name << " 在海中游泳\n";
    }
    
    void slide_on_belly() const {
        std::cout << name << " 用肚子滑行\n";
    }
};

// 演示访问控制
class AccessDemo {
public:
    int public_member = 1;
    
protected:
    int protected_member = 2;
    
private:
    int private_member = 3;
    
public:
    void show_access() const {
        std::cout << "基类中访问所有成员:\n";
        std::cout << "public: " << public_member << "\n";
        std::cout << "protected: " << protected_member << "\n";
        std::cout << "private: " << private_member << "\n";
    }
};

class PublicDerived : public AccessDemo {
public:
    void show_derived_access() const {
        std::cout << "公有继承的派生类:\n";
        std::cout << "public: " << public_member << " (可访问)\n";
        std::cout << "protected: " << protected_member << " (可访问)\n";
        // std::cout << "private: " << private_member << " (不可访问)\n";
    }
};

class ProtectedDerived : protected AccessDemo {
public:
    void show_derived_access() const {
        std::cout << "保护继承的派生类:\n";
        std::cout << "public -> protected: " << public_member << "\n";
        std::cout << "protected: " << protected_member << "\n";
    }
};

class PrivateDerived : private AccessDemo {
public:
    void show_derived_access() const {
        std::cout << "私有继承的派生类:\n";
        std::cout << "public -> private: " << public_member << "\n";
        std::cout << "protected -> private: " << protected_member << "\n";
    }
};

void demonstrate_basic_inheritance() {
    std::cout << "\n=== 基本继承演示 ===\n";
    
    std::cout << "\n--- 创建对象 ---\n";
    Dog dog("Rex", 3, "拉布拉多");
    Cat cat("Whiskers", 2, true);
    Penguin penguin("Pingu", 1, "帝企鹅");
    
    std::cout << "\n--- 调用虚函数 ---\n";
    dog.make_sound();
    cat.make_sound();
    penguin.make_sound();
    
    std::cout << "\n--- 移动方式 ---\n";
    dog.move();
    cat.move();
    penguin.move();
    
    std::cout << "\n--- 显示信息 ---\n";
    dog.display_info();
    std::cout << "\n";
    cat.display_info();
    std::cout << "\n";
    penguin.display_info();
    
    std::cout << "\n--- 特有行为 ---\n";
    dog.wag_tail();
    dog.fetch();
    cat.purr();
    cat.climb();
    penguin.swim();
    penguin.slide_on_belly();
    
    std::cout << "\n--- 对象析构 ---\n";
}

void demonstrate_polymorphism() {
    std::cout << "\n=== 多态演示 ===\n";
    
    // 使用基类指针存储不同的派生类对象
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Buddy", 4, "金毛"));
    animals.push_back(std::make_unique<Cat>("Mittens", 3, false));
    animals.push_back(std::make_unique<Penguin>("Tux", 2, "阿德利企鹅"));
    
    std::cout << "\n通过基类指针调用虚函数:\n";
    for (const auto& animal : animals) {
        animal->display_info();
        animal->make_sound();
        animal->move();
        std::cout << "---\n";
    }
    
    std::cout << "\n动态类型转换演示:\n";
    for (const auto& animal : animals) {
        // 尝试转换为 Dog
        if (auto* dog = dynamic_cast<Dog*>(animal.get())) {
            std::cout << "这是一只狗: " << dog->get_breed() << "\n";
            dog->wag_tail();
        }
        // 尝试转换为 Cat
        else if (auto* cat = dynamic_cast<Cat*>(animal.get())) {
            std::cout << "这是一只猫, 室内生活: " 
                      << (cat->get_is_indoor() ? "是" : "否") << "\n";
            cat->purr();
        }
        // 尝试转换为 Penguin
        else if (auto* penguin = dynamic_cast<Penguin*>(animal.get())) {
            std::cout << "这是一只企鹅: " << penguin->get_species() << "\n";
            penguin->swim();
        }
    }
}

void demonstrate_access_control() {
    std::cout << "\n=== 访问控制演示 ===\n";
    
    AccessDemo base;
    base.show_access();
    
    std::cout << "\n";
    PublicDerived pub_derived;
    pub_derived.show_derived_access();
    // pub_derived.public_member 可以访问
    
    std::cout << "\n";
    ProtectedDerived prot_derived;
    prot_derived.show_derived_access();
    // prot_derived.public_member 不可访问（变为protected）
    
    std::cout << "\n";
    PrivateDerived priv_derived;
    priv_derived.show_derived_access();
    // priv_derived.public_member 不可访问（变为private）
}

void demonstrate_construction_destruction_order() {
    std::cout << "\n=== 构造和析构顺序演示 ===\n";
    
    std::cout << "\n--- 创建Dog对象 ---\n";
    {
        Dog dog("Max", 5, "德国牧羊犬");
        std::cout << "Dog对象创建完成\n";
    }
    std::cout << "Dog对象析构完成\n";
    
    std::cout << "\n--- 创建Penguin对象 ---\n";
    {
        Penguin penguin("Ice", 1, "国王企鹅");
        std::cout << "Penguin对象创建完成\n";
    }
    std::cout << "Penguin对象析构完成\n";
}

void demonstrate_virtual_destructor() {
    std::cout << "\n=== 虚析构函数演示 ===\n";
    
    std::cout << "\n通过基类指针删除派生类对象:\n";
    {
        std::unique_ptr<Animal> animal = std::make_unique<Dog>("Virtual", 1, "测试犬");
        // animal 会正确调用 Dog -> Mammal -> Animal 的析构函数
    }
    
    std::cout << "\n虚析构函数确保了正确的析构顺序\n";
}

void demonstrate_scope_resolution() {
    std::cout << "\n=== 作用域解析演示 ===\n";
    
    Dog dog("Scope", 2, "边境牧羊犬");
    
    std::cout << "\n调用不同层次的display_info:\n";
    std::cout << "Animal 版本:\n";
    static_cast<Animal&>(dog).Animal::display_info();
    
    std::cout << "\nMammal 版本:\n";
    static_cast<Mammal&>(dog).Mammal::display_info();
    
    std::cout << "\nDog 版本:\n";
    dog.display_info();
}

int main() {
    std::cout << "C++ Primer Chapter 15: 继承基础演示\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_basic_inheritance();
        demonstrate_polymorphism();
        demonstrate_access_control();
        demonstrate_construction_destruction_order();
        demonstrate_virtual_destructor();
        demonstrate_scope_resolution();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 