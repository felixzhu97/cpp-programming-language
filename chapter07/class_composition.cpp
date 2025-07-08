/*
 * 第7章：类 - 类的组合
 * 展示组合关系、聚合关系、依赖关系、嵌套类等
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace class_composition_demo {

// 1. 组合关系 (Composition) - "has-a" 强关系
// 引擎类
class Engine {
private:
    std::string type;
    double power;
    bool running;
    
public:
    Engine(const std::string& t, double p) 
        : type(t), power(p), running(false) {}
    
    void start() {
        running = true;
        std::cout << type << "引擎启动，功率：" << power << "马力" << std::endl;
    }
    
    void stop() {
        running = false;
        std::cout << type << "引擎停止" << std::endl;
    }
    
    bool isRunning() const { return running; }
    std::string getType() const { return type; }
};

// 轮子类
class Wheel {
private:
    double diameter;
    std::string brand;
    
public:
    Wheel(double d, const std::string& b) : diameter(d), brand(b) {}
    
    void rotate() {
        std::cout << brand << "轮子旋转，直径：" << diameter << "英寸" << std::endl;
    }
    
    std::string getBrand() const { return brand; }
};

// 汽车类 - 组合关系示例
class Car {
private:
    std::string model;
    Engine engine;              // 组合：引擎是汽车的组成部分
    std::vector<Wheel> wheels;  // 组合：轮子是汽车的组成部分
    
public:
    Car(const std::string& m, const std::string& engineType, double power)
        : model(m), engine(engineType, power) {
        // 初始化四个轮子
        wheels.emplace_back(18, "米其林");
        wheels.emplace_back(18, "米其林");
        wheels.emplace_back(18, "米其林");
        wheels.emplace_back(18, "米其林");
    }
    
    void start() {
        std::cout << "启动 " << model << std::endl;
        engine.start();
        for (auto& wheel : wheels) {
            wheel.rotate();
        }
    }
    
    void stop() {
        std::cout << "停止 " << model << std::endl;
        engine.stop();
    }
    
    std::string getModel() const { return model; }
};

// 2. 聚合关系 (Aggregation) - "has-a" 弱关系
// 学生类
class Student {
private:
    std::string name;
    int studentId;
    
public:
    Student(const std::string& n, int id) : name(n), studentId(id) {}
    
    std::string getName() const { return name; }
    int getId() const { return studentId; }
    
    void study() {
        std::cout << name << " 正在学习" << std::endl;
    }
};

// 班级类 - 聚合关系示例
class Classroom {
private:
    std::string className;
    std::vector<Student*> students;  // 聚合：学生可以独立于班级存在
    
public:
    Classroom(const std::string& name) : className(name) {}
    
    void addStudent(Student* student) {
        students.push_back(student);
        std::cout << student->getName() << " 加入 " << className << std::endl;
    }
    
    void removeStudent(Student* student) {
        auto it = std::find(students.begin(), students.end(), student);
        if (it != students.end()) {
            students.erase(it);
            std::cout << student->getName() << " 离开 " << className << std::endl;
        }
    }
    
    void listStudents() const {
        std::cout << className << " 学生名单：" << std::endl;
        for (const auto& student : students) {
            std::cout << "  " << student->getName() 
                      << " (ID: " << student->getId() << ")" << std::endl;
        }
    }
    
    void conductClass() {
        std::cout << className << " 上课中..." << std::endl;
        for (auto& student : students) {
            student->study();
        }
    }
};

// 3. 依赖关系 (Dependency) - "uses-a"
class Printer {
public:
    void print(const std::string& content) {
        std::cout << "打印内容：" << content << std::endl;
    }
};

class Document {
private:
    std::string content;
    
public:
    Document(const std::string& c) : content(c) {}
    
    // 依赖关系：Document使用Printer，但不拥有它
    void printDocument(Printer& printer) {
        printer.print(content);
    }
    
    std::string getContent() const { return content; }
};

// 4. 嵌套类 (Nested Classes)
class Computer {
public:
    // 公有嵌套类
    class CPU {
    private:
        std::string brand;
        double frequency;
        
    public:
        CPU(const std::string& b, double f) : brand(b), frequency(f) {}
        
        void process() {
            std::cout << brand << " CPU处理中，频率：" << frequency << "GHz" << std::endl;
        }
        
        std::string getBrand() const { return brand; }
    };
    
private:
    // 私有嵌套类
    class PowerSupply {
    private:
        int wattage;
        
    public:
        PowerSupply(int w) : wattage(w) {}
        
        void supply() {
            std::cout << "电源供电：" << wattage << "W" << std::endl;
        }
    };
    
    CPU cpu;
    PowerSupply psu;
    std::string model;
    
public:
    Computer(const std::string& m, const std::string& cpuBrand, double freq, int power)
        : model(m), cpu(cpuBrand, freq), psu(power) {}
    
    void boot() {
        std::cout << "启动计算机：" << model << std::endl;
        psu.supply();
        cpu.process();
    }
    
    // 返回嵌套类对象的引用
    const CPU& getCPU() const { return cpu; }
};

// 5. 局部类 (Local Classes)
void demonstrateLocalClass() {
    std::cout << "\n局部类演示：" << std::endl;
    
    // 在函数内部定义的类
    class LocalTimer {
    private:
        std::string name;
        
    public:
        LocalTimer(const std::string& n) : name(n) {
            std::cout << "计时器 " << name << " 启动" << std::endl;
        }
        
        ~LocalTimer() {
            std::cout << "计时器 " << name << " 停止" << std::endl;
        }
        
        void tick() {
            std::cout << name << " tick..." << std::endl;
        }
    };
    
    LocalTimer timer("本地计时器");
    timer.tick();
}

// 6. 前向声明和相互依赖
class Teacher;  // 前向声明

class Course {
private:
    std::string courseName;
    Teacher* instructor;  // 使用指针，因为Teacher还未完全定义
    
public:
    Course(const std::string& name) : courseName(name), instructor(nullptr) {}
    
    void setInstructor(Teacher* teacher) { instructor = teacher; }
    std::string getName() const { return courseName; }
    
    void displayInfo() const;  // 定义延后到Teacher定义之后
};

class Teacher {
private:
    std::string name;
    std::vector<Course*> courses;
    
public:
    Teacher(const std::string& n) : name(n) {}
    
    void addCourse(Course* course) {
        courses.push_back(course);
        course->setInstructor(this);
    }
    
    std::string getName() const { return name; }
    
    void listCourses() const {
        std::cout << "教师 " << name << " 的课程：" << std::endl;
        for (const auto& course : courses) {
            std::cout << "  " << course->getName() << std::endl;
        }
    }
};

// Course类的延迟定义
void Course::displayInfo() const {
    std::cout << "课程：" << courseName;
    if (instructor) {
        std::cout << "，授课教师：" << instructor->getName();
    }
    std::cout << std::endl;
}

// 7. 智能指针和组合
class SmartCar {
private:
    std::string model;
    std::unique_ptr<Engine> engine;  // 独占所有权
    std::shared_ptr<Wheel> spareWheel;  // 可能被多个对象共享
    
public:
    SmartCar(const std::string& m, const std::string& engineType, double power)
        : model(m) {
        engine = std::make_unique<Engine>(engineType, power);
        spareWheel = std::make_shared<Wheel>(18, "倍耐力");
    }
    
    void start() {
        std::cout << "智能汽车 " << model << " 启动" << std::endl;
        if (engine) {
            engine->start();
        }
    }
    
    void showSpareWheel() {
        if (spareWheel) {
            std::cout << "备胎品牌：" << spareWheel->getBrand() << std::endl;
        }
    }
    
    // 移动构造函数
    SmartCar(SmartCar&& other) noexcept
        : model(std::move(other.model)),
          engine(std::move(other.engine)),
          spareWheel(std::move(other.spareWheel)) {}
};

void demonstrateClassComposition() {
    std::cout << "\n=== 类组合关系演示 ===" << std::endl;
    
    // 1. 组合关系演示
    std::cout << "\n1. 组合关系（汽车和引擎）：" << std::endl;
    Car car("奔驰C200", "涡轮增压", 184);
    car.start();
    car.stop();
    
    // 2. 聚合关系演示
    std::cout << "\n2. 聚合关系（班级和学生）：" << std::endl;
    Student student1("张三", 1001);
    Student student2("李四", 1002);
    Student student3("王五", 1003);
    
    Classroom classroom("计算机科学101班");
    classroom.addStudent(&student1);
    classroom.addStudent(&student2);
    classroom.addStudent(&student3);
    
    classroom.listStudents();
    classroom.conductClass();
    
    classroom.removeStudent(&student2);
    classroom.listStudents();
    
    // 3. 依赖关系演示
    std::cout << "\n3. 依赖关系（文档和打印机）：" << std::endl;
    Document doc("这是一个重要文档");
    Printer printer;
    doc.printDocument(printer);
    
    // 4. 嵌套类演示
    std::cout << "\n4. 嵌套类（计算机和CPU）：" << std::endl;
    Computer computer("Dell XPS", "Intel i7", 3.2, 650);
    computer.boot();
    
    // 直接创建嵌套类对象
    Computer::CPU externalCPU("AMD Ryzen", 3.8);
    externalCPU.process();
    
    // 5. 局部类演示
    demonstrateLocalClass();
    
    // 6. 前向声明和相互依赖
    std::cout << "\n6. 前向声明和相互依赖：" << std::endl;
    Teacher teacher("王教授");
    Course course1("数据结构");
    Course course2("算法设计");
    
    teacher.addCourse(&course1);
    teacher.addCourse(&course2);
    
    teacher.listCourses();
    course1.displayInfo();
    course2.displayInfo();
    
    // 7. 智能指针和组合
    std::cout << "\n7. 智能指针组合：" << std::endl;
    SmartCar smartCar("特斯拉Model 3", "电动马达", 283);
    smartCar.start();
    smartCar.showSpareWheel();
    
    // 移动语义
    SmartCar movedCar = std::move(smartCar);
    movedCar.start();
}

} // namespace class_composition_demo

int main() {
    class_composition_demo::demonstrateClassComposition();
    return 0;
} 