/**
 * @file list_container.cpp
 * @brief list 容器详细演示 - 双向链表操作、特有功能、与vector对比
 * 
 * list 是基于双向链表实现的容器，提供高效的插入和删除操作。
 * 本文件展示 list 的各种特性和适用场景。
 */

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>
#include <string>

// 演示 list 基本操作
void demonstrate_basic_operations() {
    std::cout << "\n=== List 基本操作 ===\n";
    
    // 1. 构造方式
    std::cout << "\n1. 各种构造方式：\n";
    std::list<int> l1;                           // 默认构造
    std::list<int> l2(5);                        // 指定大小
    std::list<int> l3(5, 10);                    // 大小和初值
    std::list<int> l4{1, 2, 3, 4, 5};            // 初始化列表
    std::list<int> l5(l4.begin(), l4.end());     // 迭代器范围
    std::list<int> l6(l4);                       // 拷贝构造
    std::list<int> l7(std::move(l5));            // 移动构造
    
    std::cout << "   l1 size: " << l1.size() << "\n";
    std::cout << "   l2 size: " << l2.size() << "\n";
    std::cout << "   l3 size: " << l3.size() << ", first: " << (l3.empty() ? 0 : l3.front()) << "\n";
    std::cout << "   l4 elements: ";
    for (auto x : l4) std::cout << x << " ";
    std::cout << "\n   l7 size: " << l7.size() << " (moved from l5)\n";
    std::cout << "   l5 size after move: " << l5.size() << "\n";
    
    // 2. 元素访问（list 不支持随机访问）
    std::cout << "\n2. 元素访问：\n";
    std::list<int> lst{10, 20, 30, 40, 50};
    
    std::cout << "   front(): " << lst.front() << "\n";
    std::cout << "   back(): " << lst.back() << "\n";
    // 注意：list 没有 operator[] 和 at()
    std::cout << "   注意：list 不支持 [] 和 at() 随机访问\n";
    
    // 通过迭代器访问
    auto it = lst.begin();
    std::advance(it, 2);  // 移动到第3个元素
    std::cout << "   通过迭代器访问第3个元素: " << *it << "\n";
    
    // 3. 修改操作
    std::cout << "\n3. 修改操作：\n";
    std::list<int> l_mod;
    
    // 尾部操作
    l_mod.push_back(1);
    l_mod.push_back(2);
    l_mod.push_back(3);
    std::cout << "   push_back 后: ";
    for (auto x : l_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // 头部操作（vector 不支持）
    l_mod.push_front(0);
    l_mod.push_front(-1);
    std::cout << "   push_front 后: ";
    for (auto x : l_mod) std::cout << x << " ";
    std::cout << "\n";
    
    l_mod.pop_back();
    l_mod.pop_front();
    std::cout << "   pop_back 和 pop_front 后: ";
    for (auto x : l_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // 插入操作
    auto iter = l_mod.begin();
    std::advance(iter, 1);
    l_mod.insert(iter, 99);
    std::cout << "   insert 99 到第2个位置后: ";
    for (auto x : l_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // 删除操作
    iter = l_mod.begin();
    std::advance(iter, 1);
    l_mod.erase(iter);
    std::cout << "   erase 第2个元素后: ";
    for (auto x : l_mod) std::cout << x << " ";
    std::cout << "\n";
    
    // emplace 操作
    std::list<std::string> l_str;
    l_str.emplace_back("hello");
    l_str.emplace_front("world");
    l_str.emplace(++l_str.begin(), 5, 'x');  // 在第2个位置插入 "xxxxx"
    
    std::cout << "   emplace 操作后: ";
    for (const auto& s : l_str) std::cout << "[" << s << "] ";
    std::cout << "\n";
}

// 演示 list 特有操作
void demonstrate_list_specific_operations() {
    std::cout << "\n=== List 特有操作 ===\n";
    
    // 1. splice 操作（拼接）
    std::cout << "\n1. splice 操作（链表拼接）：\n";
    std::list<int> l1{1, 2, 3};
    std::list<int> l2{10, 20, 30};
    std::list<int> l3{100, 200};
    
    std::cout << "   l1: ";
    for (auto x : l1) std::cout << x << " ";
    std::cout << "\n   l2: ";
    for (auto x : l2) std::cout << x << " ";
    std::cout << "\n   l3: ";
    for (auto x : l3) std::cout << x << " ";
    std::cout << "\n";
    
    // 将 l2 的所有元素移动到 l1 的末尾
    l1.splice(l1.end(), l2);
    std::cout << "   l1.splice(l1.end(), l2) 后:\n";
    std::cout << "   l1: ";
    for (auto x : l1) std::cout << x << " ";
    std::cout << "\n   l2: ";
    for (auto x : l2) std::cout << x << " ";
    std::cout << " (已被清空)\n";
    
    // 将 l3 的第一个元素移动到 l1 的开头
    l1.splice(l1.begin(), l3, l3.begin());
    std::cout << "   移动 l3 第一个元素到 l1 开头后:\n";
    std::cout << "   l1: ";
    for (auto x : l1) std::cout << x << " ";
    std::cout << "\n   l3: ";
    for (auto x : l3) std::cout << x << " ";
    std::cout << "\n";
    
    // 2. remove 和 remove_if 操作
    std::cout << "\n2. remove 和 remove_if 操作：\n";
    std::list<int> nums{1, 2, 3, 2, 4, 2, 5};
    
    std::cout << "   原始: ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n";
    
    nums.remove(2);  // 删除所有值为 2 的元素
    std::cout << "   remove(2) 后: ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n";
    
    nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    nums.remove_if([](int x) { return x % 2 == 0; });  // 删除所有偶数
    std::cout << "   remove_if(偶数) 后: ";
    for (auto x : nums) std::cout << x << " ";
    std::cout << "\n";
    
    // 3. unique 操作（去重）
    std::cout << "\n3. unique 操作（去重）：\n";
    std::list<int> dup{1, 1, 2, 2, 2, 3, 4, 4, 5};
    
    std::cout << "   原始: ";
    for (auto x : dup) std::cout << x << " ";
    std::cout << "\n";
    
    dup.unique();  // 删除连续的重复元素
    std::cout << "   unique() 后: ";
    for (auto x : dup) std::cout << x << " ";
    std::cout << "\n";
    
    // 自定义比较的 unique
    std::list<int> nums2{1, 3, 2, 4, 5, 7, 6, 8};
    nums2.unique([](int a, int b) { return abs(a - b) <= 1; });  // 删除差值 <= 1 的相邻元素
    std::cout << "   unique(差值<=1) 后: ";
    for (auto x : nums2) std::cout << x << " ";
    std::cout << "\n";
    
    // 4. sort 操作
    std::cout << "\n4. sort 操作：\n";
    std::list<int> unsorted{5, 2, 8, 1, 9, 3};
    
    std::cout << "   排序前: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";
    
    unsorted.sort();  // 默认升序
    std::cout << "   sort() 后: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";
    
    unsorted.sort(std::greater<int>());  // 降序
    std::cout << "   sort(降序) 后: ";
    for (auto x : unsorted) std::cout << x << " ";
    std::cout << "\n";
    
    // 自定义比较器
    std::list<std::string> words{"apple", "banana", "cat", "dog"};
    words.sort([](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    });
    std::cout << "   按长度排序: ";
    for (const auto& word : words) std::cout << word << " ";
    std::cout << "\n";
    
    // 5. merge 操作（合并有序链表）
    std::cout << "\n5. merge 操作（合并有序链表）：\n";
    std::list<int> sorted1{1, 3, 5, 7};
    std::list<int> sorted2{2, 4, 6, 8, 9};
    
    std::cout << "   sorted1: ";
    for (auto x : sorted1) std::cout << x << " ";
    std::cout << "\n   sorted2: ";
    for (auto x : sorted2) std::cout << x << " ";
    std::cout << "\n";
    
    sorted1.merge(sorted2);  // 合并到 sorted1
    std::cout << "   merge 后:\n";
    std::cout << "   sorted1: ";
    for (auto x : sorted1) std::cout << x << " ";
    std::cout << "\n   sorted2: ";
    for (auto x : sorted2) std::cout << x << " ";
    std::cout << " (已被清空)\n";
    
    // 6. reverse 操作
    std::cout << "\n6. reverse 操作：\n";
    std::list<int> rev{1, 2, 3, 4, 5};
    
    std::cout << "   原始: ";
    for (auto x : rev) std::cout << x << " ";
    std::cout << "\n";
    
    rev.reverse();
    std::cout << "   reverse() 后: ";
    for (auto x : rev) std::cout << x << " ";
    std::cout << "\n";
}

// list vs vector 性能对比
void demonstrate_performance_comparison() {
    std::cout << "\n=== List vs Vector 性能对比 ===\n";
    
    const int N = 50000;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000);
    
    auto measure_time = [](auto func, const std::string& desc) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "   " << desc << ": " << duration.count() << " μs\n";
        return duration.count();
    };
    
    // 1. 尾部插入性能
    std::cout << "\n1. 尾部插入性能 (插入 " << N << " 个元素)：\n";
    
    auto list_time1 = measure_time([&]() {
        std::list<int> lst;
        for (int i = 0; i < N; ++i) {
            lst.push_back(dis(gen));
        }
    }, "list::push_back");
    
    auto vector_time1 = measure_time([&]() {
        std::vector<int> vec;
        vec.reserve(N);  // 公平比较
        for (int i = 0; i < N; ++i) {
            vec.push_back(dis(gen));
        }
    }, "vector::push_back (预分配)");
    
    std::cout << "   Vector 比 List 快: " << static_cast<double>(list_time1) / vector_time1 << "x\n";
    
    // 2. 头部插入性能
    std::cout << "\n2. 头部插入性能 (插入 10000 个元素)：\n";
    const int head_insert_count = 10000;
    
    auto list_time2 = measure_time([&]() {
        std::list<int> lst;
        for (int i = 0; i < head_insert_count; ++i) {
            lst.push_front(dis(gen));
        }
    }, "list::push_front");
    
    auto vector_time2 = measure_time([&]() {
        std::vector<int> vec;
        for (int i = 0; i < head_insert_count; ++i) {
            vec.insert(vec.begin(), dis(gen));
        }
    }, "vector::insert(begin)");
    
    std::cout << "   List 比 Vector 快: " << static_cast<double>(vector_time2) / list_time2 << "x\n";
    
    // 3. 中间插入性能
    std::cout << "\n3. 中间插入性能 (插入 5000 个元素)：\n";
    const int mid_insert_count = 5000;
    
    // 准备数据
    std::list<int> lst_mid;
    std::vector<int> vec_mid;
    for (int i = 0; i < mid_insert_count; ++i) {
        lst_mid.push_back(i);
        vec_mid.push_back(i);
    }
    
    auto list_time3 = measure_time([&]() {
        auto it = lst_mid.begin();
        std::advance(it, lst_mid.size() / 2);
        for (int i = 0; i < 1000; ++i) {
            it = lst_mid.insert(it, dis(gen));
        }
    }, "list::insert (middle)");
    
    auto vector_time3 = measure_time([&]() {
        for (int i = 0; i < 1000; ++i) {
            vec_mid.insert(vec_mid.begin() + vec_mid.size() / 2, dis(gen));
        }
    }, "vector::insert (middle)");
    
    std::cout << "   List 比 Vector 快: " << static_cast<double>(vector_time3) / list_time3 << "x\n";
    
    // 4. 随机访问性能
    std::cout << "\n4. 随机访问性能 (访问 10000 次)：\n";
    const int access_count = 10000;
    
    // 重新准备数据
    lst_mid.clear();
    vec_mid.clear();
    for (int i = 0; i < N; ++i) {
        int val = dis(gen);
        lst_mid.push_back(val);
        vec_mid.push_back(val);
    }
    
    long long sum1 = 0, sum2 = 0;
    
    auto list_time4 = measure_time([&]() {
        for (int i = 0; i < access_count; ++i) {
            auto it = lst_mid.begin();
            std::advance(it, dis(gen) % lst_mid.size());
            sum1 += *it;
        }
    }, "list iterator advance");
    
    auto vector_time4 = measure_time([&]() {
        for (int i = 0; i < access_count; ++i) {
            sum2 += vec_mid[dis(gen) % vec_mid.size()];
        }
    }, "vector[] access");
    
    std::cout << "   Vector 比 List 快: " << static_cast<double>(list_time4) / vector_time4 << "x\n";
    std::cout << "   校验和: list=" << sum1 << ", vector=" << sum2 << "\n";
    
    // 5. 内存使用对比
    std::cout << "\n5. 内存使用对比：\n";
    std::cout << "   int 大小: " << sizeof(int) << " bytes\n";
    std::cout << "   vector<int> 每元素开销: " << sizeof(int) << " bytes\n";
    std::cout << "   list<int> 每元素开销: ~" << sizeof(int) + 2*sizeof(void*) << " bytes (节点开销)\n";
    std::cout << "   list 内存开销是 vector 的 " 
              << static_cast<double>(sizeof(int) + 2*sizeof(void*)) / sizeof(int) << " 倍\n";
}

// 迭代器稳定性演示
void demonstrate_iterator_stability() {
    std::cout << "\n=== 迭代器稳定性 ===\n";
    
    // 1. list 迭代器稳定性
    std::cout << "\n1. List 迭代器稳定性：\n";
    std::list<int> lst{1, 2, 3, 4, 5};
    
    auto it1 = lst.begin();
    auto it2 = ++lst.begin();
    auto it3 = ++++lst.begin();
    
    std::cout << "   插入前: it1=" << *it1 << ", it2=" << *it2 << ", it3=" << *it3 << "\n";
    
    // 在中间插入元素
    lst.insert(it2, 99);
    std::cout << "   插入 99 后: it1=" << *it1 << ", it2=" << *it2 << ", it3=" << *it3 << "\n";
    std::cout << "   所有迭代器仍然有效\n";
    
    // 删除元素
    auto to_erase = it2;
    lst.erase(to_erase);  // 删除 it2 指向的元素
    std::cout << "   删除 it2 指向的元素后: it1=" << *it1 << ", it3=" << *it3 << "\n";
    std::cout << "   只有被删除的迭代器失效，其他仍有效\n";
    
    // 2. vector 迭代器失效对比
    std::cout << "\n2. Vector 迭代器失效对比：\n";
    std::vector<int> vec{1, 2, 3, 4, 5};
    
    auto v_it1 = vec.begin();
    auto v_it2 = vec.begin() + 1;
    auto v_it3 = vec.begin() + 2;
    
    std::cout << "   插入前: v_it1=" << *v_it1 << ", v_it2=" << *v_it2 << ", v_it3=" << *v_it3 << "\n";
    
    // 在中间插入可能导致重新分配
    vec.insert(v_it2, 99);
    std::cout << "   插入后原迭代器可能失效，需要重新获取\n";
    
    // 重新获取迭代器
    v_it1 = vec.begin();
    v_it2 = vec.begin() + 2;  // 现在指向原来的 2
    v_it3 = vec.begin() + 3;  // 现在指向原来的 3
    
    std::cout << "   重新获取: v_it1=" << *v_it1 << ", v_it2=" << *v_it2 << ", v_it3=" << *v_it3 << "\n";
}

// 实际应用场景
void demonstrate_practical_use_cases() {
    std::cout << "\n=== 实际应用场景 ===\n";
    
    // 1. LRU 缓存实现
    std::cout << "\n1. LRU 缓存实现：\n";
    
    class LRUCache {
    private:
        struct CacheNode {
            int key, value;
            CacheNode(int k, int v) : key(k), value(v) {}
        };
        
        std::list<CacheNode> cache_list;
        std::unordered_map<int, std::list<CacheNode>::iterator> cache_map;
        size_t capacity;
        
    public:
        LRUCache(size_t cap) : capacity(cap) {}
        
        int get(int key) {
            auto it = cache_map.find(key);
            if (it == cache_map.end()) {
                return -1;  // 未找到
            }
            
            // 移动到前端（最近使用）
            cache_list.splice(cache_list.begin(), cache_list, it->second);
            return it->second->value;
        }
        
        void put(int key, int value) {
            auto it = cache_map.find(key);
            
            if (it != cache_map.end()) {
                // 更新现有键值
                it->second->value = value;
                cache_list.splice(cache_list.begin(), cache_list, it->second);
            } else {
                // 新键值
                if (cache_list.size() >= capacity) {
                    // 删除最旧的元素
                    int old_key = cache_list.back().key;
                    cache_map.erase(old_key);
                    cache_list.pop_back();
                }
                
                // 添加新元素到前端
                cache_list.emplace_front(key, value);
                cache_map[key] = cache_list.begin();
            }
        }
        
        void print() const {
            std::cout << "     缓存状态: ";
            for (const auto& node : cache_list) {
                std::cout << "{" << node.key << ":" << node.value << "} ";
            }
            std::cout << "\n";
        }
    };
    
    LRUCache lru(3);
    
    lru.put(1, 10);
    lru.put(2, 20);
    lru.put(3, 30);
    lru.print();
    
    std::cout << "   get(2): " << lru.get(2) << "\n";
    lru.print();
    
    lru.put(4, 40);  // 应该淘汰 key=1
    lru.print();
    
    // 2. 音乐播放列表
    std::cout << "\n2. 音乐播放列表：\n";
    
    class Playlist {
    private:
        std::list<std::string> songs;
        std::list<std::string>::iterator current;
        bool has_current = false;
        
    public:
        void add_song(const std::string& song) {
            songs.push_back(song);
            if (!has_current) {
                current = songs.begin();
                has_current = true;
            }
            std::cout << "     添加歌曲: " << song << "\n";
        }
        
        void remove_song(const std::string& song) {
            auto it = std::find(songs.begin(), songs.end(), song);
            if (it != songs.end()) {
                if (it == current) {
                    next_song();  // 如果删除当前歌曲，切换到下一首
                }
                songs.erase(it);
                std::cout << "     删除歌曲: " << song << "\n";
            }
        }
        
        std::string current_song() const {
            if (has_current && !songs.empty()) {
                return *current;
            }
            return "无";
        }
        
        void next_song() {
            if (!songs.empty()) {
                if (!has_current) {
                    current = songs.begin();
                    has_current = true;
                } else {
                    ++current;
                    if (current == songs.end()) {
                        current = songs.begin();  // 循环播放
                    }
                }
            }
        }
        
        void prev_song() {
            if (!songs.empty()) {
                if (!has_current) {
                    current = songs.end();
                    --current;
                    has_current = true;
                } else if (current == songs.begin()) {
                    current = songs.end();
                    --current;
                } else {
                    --current;
                }
            }
        }
        
        void shuffle() {
            if (songs.size() > 1) {
                std::vector<std::string> temp(songs.begin(), songs.end());
                std::random_device rd;
                std::mt19937 gen(rd());
                std::shuffle(temp.begin(), temp.end(), gen);
                
                std::string curr_song = has_current ? *current : "";
                songs.assign(temp.begin(), temp.end());
                
                if (!curr_song.empty()) {
                    current = std::find(songs.begin(), songs.end(), curr_song);
                    has_current = (current != songs.end());
                }
                
                std::cout << "     播放列表已打乱\n";
            }
        }
        
        void print_playlist() const {
            std::cout << "     播放列表: ";
            for (auto it = songs.begin(); it != songs.end(); ++it) {
                if (has_current && it == current) {
                    std::cout << "*" << *it << "* ";
                } else {
                    std::cout << *it << " ";
                }
            }
            std::cout << "\n";
        }
    };
    
    Playlist playlist;
    playlist.add_song("Song1");
    playlist.add_song("Song2");
    playlist.add_song("Song3");
    playlist.add_song("Song4");
    
    playlist.print_playlist();
    std::cout << "   当前播放: " << playlist.current_song() << "\n";
    
    playlist.next_song();
    std::cout << "   下一首: " << playlist.current_song() << "\n";
    
    playlist.prev_song();
    std::cout << "   上一首: " << playlist.current_song() << "\n";
    
    playlist.shuffle();
    playlist.print_playlist();
    
    // 3. 撤销/重做系统
    std::cout << "\n3. 撤销/重做系统：\n";
    
    class UndoRedoSystem {
    private:
        std::list<std::string> commands;
        std::list<std::string>::iterator current_pos;
        bool has_commands = false;
        
    public:
        void execute_command(const std::string& command) {
            if (has_commands) {
                // 删除当前位置之后的所有命令
                commands.erase(std::next(current_pos), commands.end());
            }
            
            commands.push_back(command);
            current_pos = std::prev(commands.end());
            has_commands = true;
            
            std::cout << "     执行命令: " << command << "\n";
        }
        
        bool undo() {
            if (!has_commands || current_pos == commands.begin()) {
                std::cout << "     无法撤销\n";
                return false;
            }
            
            --current_pos;
            std::cout << "     撤销: " << *std::next(current_pos) << "\n";
            return true;
        }
        
        bool redo() {
            if (!has_commands || std::next(current_pos) == commands.end()) {
                std::cout << "     无法重做\n";
                return false;
            }
            
            ++current_pos;
            std::cout << "     重做: " << *current_pos << "\n";
            return true;
        }
        
        void print_status() const {
            std::cout << "     命令历史: ";
            for (auto it = commands.begin(); it != commands.end(); ++it) {
                if (has_commands && it == current_pos) {
                    std::cout << "*" << *it << "* ";
                } else {
                    std::cout << *it << " ";
                }
            }
            std::cout << "\n";
        }
    };
    
    UndoRedoSystem undo_redo;
    
    undo_redo.execute_command("Create");
    undo_redo.execute_command("Edit");
    undo_redo.execute_command("Save");
    undo_redo.print_status();
    
    undo_redo.undo();
    undo_redo.print_status();
    
    undo_redo.undo();
    undo_redo.print_status();
    
    undo_redo.redo();
    undo_redo.print_status();
    
    undo_redo.execute_command("Delete");  // 这会清除 "Save" 命令
    undo_redo.print_status();
}

int main() {
    std::cout << "C++ Primer Chapter 9: List 容器详解\n";
    std::cout << "===================================\n";
    
    try {
        // 1. 基本操作演示
        demonstrate_basic_operations();
        
        // 2. list 特有操作
        demonstrate_list_specific_operations();
        
        // 3. 性能对比
        demonstrate_performance_comparison();
        
        // 4. 迭代器稳定性
        demonstrate_iterator_stability();
        
        // 5. 实际应用场景
        demonstrate_practical_use_cases();
        
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "\n程序执行完成！\n";
    return 0;
} 