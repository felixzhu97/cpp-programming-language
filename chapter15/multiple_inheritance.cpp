/**
 * @file multiple_inheritance.cpp
 * @brief 多重继承演示 - 多重继承基础、虚继承、菱形继承问题
 */

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <typeinfo>

// 基础接口类
class Drawable {
public:
    virtual ~Drawable() = default;
    virtual void draw() const = 0;
    virtual std::string get_drawable_info() const = 0;
};

class Movable {
public:
    virtual ~Movable() = default;
    virtual void move(double dx, double dy) = 0;
    virtual std::string get_position() const = 0;
};

class Resizable {
public:
    virtual ~Resizable() = default;
    virtual void resize(double factor) = 0;
    virtual double get_size() const = 0;
};

// 简单多重继承示例
class GraphicObject : public Drawable, public Movable, public Resizable {
protected:
    std::string name;
    double x, y;
    double size;
    
public:
    GraphicObject(const std::string& n, double px = 0, double py = 0, double s = 1.0)
        : name(n), x(px), y(py), size(s) {
        std::cout << "GraphicObject 构造: " << name << "\n";
    }
    
    virtual ~GraphicObject() {
        std::cout << "GraphicObject 析构: " << name << "\n";
    }
    
    // 实现 Drawable 接口
    void draw() const override {
        std::cout << "绘制图形对象: " << name << " at (" << x << ", " << y 
                  << ") size=" << size << "\n";
    }
    
    std::string get_drawable_info() const override {
        return "GraphicObject: " + name;
    }
    
    // 实现 Movable 接口
    void move(double dx, double dy) override {
        x += dx;
        y += dy;
        std::cout << name << " 移动了 (" << dx << ", " << dy << ")\n";
    }
    
    std::string get_position() const override {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
    
    // 实现 Resizable 接口
    void resize(double factor) override {
        size *= factor;
        std::cout << name << " 调整大小到: " << size << "\n";
    }
    
    double get_size() const override {
        return size;
    }
    
    const std::string& get_name() const { return name; }
};

// 菱形继承问题示例
class Device {
protected:
    std::string device_id;
    bool powered_on;
    
public:
    Device(const std::string& id) : device_id(id), powered_on(false) {
        std::cout << "Device 构造: " << device_id << "\n";
    }
    
    virtual ~Device() {
        std::cout << "Device 析构: " << device_id << "\n";
    }
    
    virtual void power_on() {
        powered_on = true;
        std::cout << device_id << " 开机\n";
    }
    
    virtual void power_off() {
        powered_on = false;
        std::cout << device_id << " 关机\n";
    }
    
    bool is_powered_on() const { return powered_on; }
    const std::string& get_id() const { return device_id; }
    
    virtual void display_status() const {
        std::cout << "设备: " << device_id << ", 状态: " 
                  << (powered_on ? "开机" : "关机") << "\n";
    }
};

// 有问题的多重继承（菱形继承）
class InputDevice : public Device {
protected:
    std::string input_type;
    
public:
    InputDevice(const std::string& id, const std::string& type) 
        : Device(id), input_type(type) {
        std::cout << "InputDevice 构造: " << device_id << " (" << input_type << ")\n";
    }
    
    virtual ~InputDevice() {
        std::cout << "InputDevice 析构: " << device_id << "\n";
    }
    
    virtual void process_input() {
        std::cout << device_id << " 处理 " << input_type << " 输入\n";
    }
    
    void display_status() const override {
        Device::display_status();
        std::cout << "  输入类型: " << input_type << "\n";
    }
};

class OutputDevice : public Device {
protected:
    std::string output_type;
    
public:
    OutputDevice(const std::string& id, const std::string& type) 
        : Device(id), output_type(type) {
        std::cout << "OutputDevice 构造: " << device_id << " (" << output_type << ")\n";
    }
    
    virtual ~OutputDevice() {
        std::cout << "OutputDevice 析构: " << device_id << "\n";
    }
    
    virtual void generate_output() {
        std::cout << device_id << " 生成 " << output_type << " 输出\n";
    }
    
    void display_status() const override {
        Device::display_status();
        std::cout << "  输出类型: " << output_type << "\n";
    }
};

// 有问题的菱形继承
class ProblematicIODevice : public InputDevice, public OutputDevice {
public:
    ProblematicIODevice(const std::string& id) 
        : InputDevice(id, "keyboard"), OutputDevice(id, "screen") {
        std::cout << "ProblematicIODevice 构造: " << id << "\n";
    }
    
    ~ProblematicIODevice() {
        std::cout << "ProblematicIODevice 析构\n";
    }
    
    // 二义性问题
    // void power_on() { ... }  // 调用哪个基类的 power_on？
    // std::string get_id() { ... }  // 调用哪个基类的 get_id？
    
    void demo_ambiguity() {
        // 需要明确指定作用域
        InputDevice::power_on();
        OutputDevice::power_off();
        
        std::cout << "Input device ID: " << InputDevice::get_id() << "\n";
        std::cout << "Output device ID: " << OutputDevice::get_id() << "\n";
    }
};

// 使用虚继承解决菱形继承问题
class VirtualInputDevice : virtual public Device {
protected:
    std::string input_type;
    
public:
    VirtualInputDevice(const std::string& id, const std::string& type) 
        : Device(id), input_type(type) {
        std::cout << "VirtualInputDevice 构造: " << device_id << " (" << input_type << ")\n";
    }
    
    virtual ~VirtualInputDevice() {
        std::cout << "VirtualInputDevice 析构: " << device_id << "\n";
    }
    
    virtual void process_input() {
        std::cout << device_id << " 处理 " << input_type << " 输入\n";
    }
    
    void display_status() const override {
        Device::display_status();
        std::cout << "  输入类型: " << input_type << "\n";
    }
    
    const std::string& get_input_type() const { return input_type; }
};

class VirtualOutputDevice : virtual public Device {
protected:
    std::string output_type;
    
public:
    VirtualOutputDevice(const std::string& id, const std::string& type) 
        : Device(id), output_type(type) {
        std::cout << "VirtualOutputDevice 构造: " << device_id << " (" << output_type << ")\n";
    }
    
    virtual ~VirtualOutputDevice() {
        std::cout << "VirtualOutputDevice 析构: " << device_id << "\n";
    }
    
    virtual void generate_output() {
        std::cout << device_id << " 生成 " << output_type << " 输出\n";
    }
    
    void display_status() const override {
        Device::display_status();
        std::cout << "  输出类型: " << output_type << "\n";
    }
    
    const std::string& get_output_type() const { return output_type; }
};

// 解决菱形继承的正确方式
class IODevice : public VirtualInputDevice, public VirtualOutputDevice {
public:
    IODevice(const std::string& id) 
        : Device(id),  // 直接初始化虚基类
          VirtualInputDevice(id, "触摸"), 
          VirtualOutputDevice(id, "显示") {
        std::cout << "IODevice 构造: " << id << "\n";
    }
    
    ~IODevice() {
        std::cout << "IODevice 析构: " << device_id << "\n";
    }
    
    // 现在可以直接调用基类方法，没有二义性
    void operate() {
        power_on();  // 只有一个 Device 实例
        process_input();
        generate_output();
    }
    
    void display_status() const override {
        std::cout << "IO设备状态:\n";
        Device::display_status();
        std::cout << "  输入类型: " << get_input_type() << "\n";
        std::cout << "  输出类型: " << get_output_type() << "\n";
    }
};

// 混入模式示例
template<typename Base>
class Loggable : public Base {
private:
    mutable std::vector<std::string> log_entries;
    
public:
    template<typename... Args>
    Loggable(Args&&... args) : Base(std::forward<Args>(args)...) {}
    
    void log(const std::string& message) const {
        log_entries.push_back(message);
        std::cout << "日志: " << message << "\n";
    }
    
    void show_log() const {
        std::cout << "日志记录:\n";
        for (const auto& entry : log_entries) {
            std::cout << "  - " << entry << "\n";
        }
    }
    
    size_t get_log_count() const { return log_entries.size(); }
};

template<typename Base>
class Serializable : public Base {
public:
    template<typename... Args>
    Serializable(Args&&... args) : Base(std::forward<Args>(args)...) {}
    
    virtual std::string serialize() const {
        return "Serialized: " + this->get_name();
    }
    
    virtual void deserialize(const std::string& data) {
        std::cout << "反序列化数据: " << data << "\n";
    }
};

// 多重继承的设计模式
class Printable {
public:
    virtual ~Printable() = default;
    virtual void print() const = 0;
};

class Saveable {
public:
    virtual ~Saveable() = default;
    virtual bool save(const std::string& filename) const = 0;
    virtual bool load(const std::string& filename) = 0;
};

class Document : public Printable, public Saveable {
private:
    std::string content;
    std::string title;
    
public:
    Document(const std::string& t, const std::string& c) 
        : title(t), content(c) {
        std::cout << "Document 构造: " << title << "\n";
    }
    
    virtual ~Document() {
        std::cout << "Document 析构: " << title << "\n";
    }
    
    // 实现 Printable
    void print() const override {
        std::cout << "打印文档: " << title << "\n";
        std::cout << "内容: " << content << "\n";
    }
    
    // 实现 Saveable
    bool save(const std::string& filename) const override {
        std::cout << "保存文档 '" << title << "' 到 " << filename << "\n";
        return true;
    }
    
    bool load(const std::string& filename) override {
        std::cout << "从 " << filename << " 加载文档\n";
        return true;
    }
    
    void set_content(const std::string& c) { content = c; }
    const std::string& get_title() const { return title; }
};

void demonstrate_basic_multiple_inheritance() {
    std::cout << "\n=== 基本多重继承演示 ===\n";
    
    GraphicObject obj("多重继承对象", 10, 20, 2.0);
    
    std::cout << "\n调用不同接口的方法:\n";
    
    // 作为 Drawable 使用
    Drawable* drawable = &obj;
    drawable->draw();
    std::cout << "可绘制信息: " << drawable->get_drawable_info() << "\n";
    
    // 作为 Movable 使用
    Movable* movable = &obj;
    movable->move(5, -3);
    std::cout << "位置: " << movable->get_position() << "\n";
    
    // 作为 Resizable 使用
    Resizable* resizable = &obj;
    resizable->resize(1.5);
    std::cout << "大小: " << resizable->get_size() << "\n";
    
    // 检查类型
    std::cout << "\n类型检查:\n";
    std::cout << "是 Drawable? " << (dynamic_cast<Drawable*>(&obj) ? "是" : "否") << "\n";
    std::cout << "是 Movable? " << (dynamic_cast<Movable*>(&obj) ? "是" : "否") << "\n";
    std::cout << "是 Resizable? " << (dynamic_cast<Resizable*>(&obj) ? "是" : "否") << "\n";
}

void demonstrate_diamond_problem() {
    std::cout << "\n=== 菱形继承问题演示 ===\n";
    
    std::cout << "\n--- 有问题的菱形继承 ---\n";
    ProblematicIODevice problem_device("问题设备");
    
    // 显示大小问题
    std::cout << "ProblematicIODevice 大小: " << sizeof(ProblematicIODevice) << " 字节\n";
    std::cout << "包含两个 Device 实例!\n";
    
    problem_device.demo_ambiguity();
}

void demonstrate_virtual_inheritance() {
    std::cout << "\n=== 虚继承解决方案演示 ===\n";
    
    std::cout << "\n--- 虚继承的正确实现 ---\n";
    IODevice good_device("正确设备");
    
    std::cout << "IODevice 大小: " << sizeof(IODevice) << " 字节\n";
    std::cout << "只有一个 Device 实例!\n";
    
    good_device.operate();
    good_device.display_status();
    
    // 类型转换正常工作
    Device* device_ptr = &good_device;
    VirtualInputDevice* input_ptr = &good_device;
    VirtualOutputDevice* output_ptr = &good_device;
    
    std::cout << "\n通过不同指针访问:\n";
    std::cout << "Device ID: " << device_ptr->get_id() << "\n";
    std::cout << "Input type: " << input_ptr->get_input_type() << "\n";
    std::cout << "Output type: " << output_ptr->get_output_type() << "\n";
}

void demonstrate_mixin_pattern() {
    std::cout << "\n=== 混入模式演示 ===\n";
    
    // 创建具有日志和序列化功能的图形对象
    using LoggableGraphic = Loggable<GraphicObject>;
    using SerializableGraphic = Serializable<GraphicObject>;
    using FullFeaturedGraphic = Loggable<Serializable<GraphicObject>>;
    
    std::cout << "\n--- 可记录日志的图形对象 ---\n";
    LoggableGraphic logged_obj("日志对象", 5, 5, 1.0);
    logged_obj.draw();
    logged_obj.log("对象已绘制");
    logged_obj.move(2, 3);
    logged_obj.log("对象已移动");
    logged_obj.show_log();
    
    std::cout << "\n--- 可序列化的图形对象 ---\n";
    SerializableGraphic serializable_obj("序列化对象", 1, 1, 2.0);
    std::string data = serializable_obj.serialize();
    std::cout << "序列化结果: " << data << "\n";
    
    std::cout << "\n--- 全功能图形对象 ---\n";
    FullFeaturedGraphic full_obj("全功能对象", 0, 0, 1.5);
    full_obj.draw();
    full_obj.log("全功能对象已创建");
    std::string full_data = full_obj.serialize();
    std::cout << "完整序列化: " << full_data << "\n";
    full_obj.show_log();
}

void demonstrate_interface_segregation() {
    std::cout << "\n=== 接口分离原则演示 ===\n";
    
    Document doc("示例文档", "这是文档内容");
    
    // 不同的客户端可以通过不同接口使用对象
    std::cout << "\n--- 打印服务使用 ---\n";
    Printable* printable = &doc;
    printable->print();
    
    std::cout << "\n--- 存储服务使用 ---\n";
    Saveable* saveable = &doc;
    saveable->save("document.txt");
    saveable->load("backup.txt");
    
    // 完整对象功能
    std::cout << "\n--- 完整文档对象 ---\n";
    std::cout << "文档标题: " << doc.get_title() << "\n";
}

void demonstrate_multiple_inheritance_guidelines() {
    std::cout << "\n=== 多重继承设计指导原则 ===\n";
    
    std::cout << "1. 接口继承 vs 实现继承:\n";
    std::cout << "   - 优先使用纯接口类（抽象基类）\n";
    std::cout << "   - 避免多个有状态的基类\n";
    
    std::cout << "\n2. 虚继承:\n";
    std::cout << "   - 只在需要解决菱形继承时使用\n";
    std::cout << "   - 虚继承有额外的性能开销\n";
    std::cout << "   - 虚基类的构造函数由最终派生类调用\n";
    
    std::cout << "\n3. 设计原则:\n";
    std::cout << "   - 遵循接口分离原则\n";
    std::cout << "   - 考虑使用组合代替继承\n";
    std::cout << "   - 使用混入模式增加功能\n";
    
    std::cout << "\n4. 常见陷阱:\n";
    std::cout << "   - 名称冲突和二义性\n";
    std::cout << "   - 构造和析构顺序\n";
    std::cout << "   - 类型转换的复杂性\n";
}

void demonstrate_construction_order() {
    std::cout << "\n=== 多重继承构造顺序演示 ===\n";
    
    std::cout << "\n多重继承的构造顺序:\n";
    std::cout << "1. 虚基类（按继承声明顺序）\n";
    std::cout << "2. 非虚基类（按继承声明顺序）\n";
    std::cout << "3. 成员变量（按声明顺序）\n";
    std::cout << "4. 构造函数体\n";
    
    std::cout << "\n--- 实际构造演示 ---\n";
    {
        IODevice construction_demo("构造演示");
    }
    std::cout << "--- 析构完成 ---\n";
    
    std::cout << "\n析构顺序与构造顺序相反\n";
}

int main() {
    std::cout << "C++ Primer Chapter 15: 多重继承演示\n";
    std::cout << "=================================\n";
    
    try {
        demonstrate_basic_multiple_inheritance();
        demonstrate_diamond_problem();
        demonstrate_virtual_inheritance();
        demonstrate_mixin_pattern();
        demonstrate_interface_segregation();
        demonstrate_multiple_inheritance_guidelines();
        demonstrate_construction_order();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 