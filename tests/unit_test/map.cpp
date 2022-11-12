#include "map.hpp"

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "./utils.cpp"

#ifndef LIB
#define LIB ft
#endif

typedef int Key;
typedef std::string T;

typedef LIB::map<int, std::string> int_map;

typedef int_map::key_type key_type;
typedef int_map::mapped_type mapped_type;
typedef int_map::value_type value_type;
typedef std::allocator<value_type> Allocator;

void print_map(int_map& map) {
    std::cout << "empty:";
    print_bool(map.empty());
    std::cout << "[" << map.size() << "/" << map.max_size() << "]";
    for (int_map::iterator it = map.begin(); it != map.end(); ++it) {
        std::cout << (*it).first << ":" << (*it).second << " ";
    }
    std::cout << std::endl;
}

value_type my_make_pair(const key_type k, mapped_type v) {
    return LIB::make_pair<const key_type, mapped_type>(k, v);
}

static void constructor_map_test() {
    START_TEST_FUNC
    Allocator alloc;

    // map();
    int_map numbers0;
    print_map(numbers0);

    print("---insert---");
    value_type v = my_make_pair(1, "hello1");
    print_bool(numbers0.insert(v).second);
    print_map(numbers0);

    print("---insert---");
    value_type v2 = my_make_pair(2, "hello2");
    print_bool(numbers0.insert(v2).second);
    print_map(numbers0);

    print("---find---");
    int_map::const_iterator cit = numbers0.find(2);
    print(cit->second);
    print((numbers0.find(1))->second);
}

static void at_map_test() {
    START_TEST_FUNC
    int_map numbers0;
    value_type v = my_make_pair(1, "hello1");
    print_bool(numbers0.insert(v).second);
    value_type v2 = my_make_pair(2, "hello2");
    print_bool(numbers0.insert(v2).second);

    print(numbers0.at(2));
    try {
        print(numbers0.at(0));
    } catch (std::exception& e) {
        print(e.what());
    }
}

static void operator_map_test() {
    START_TEST_FUNC
    int_map numbers0;
    value_type v = my_make_pair(1, "hello1");
    numbers0.insert(v);
    value_type v2 = my_make_pair(2, "hello2");
    numbers0.insert(v2);

    print(numbers0[1]);
    print(numbers0[2]);
    print(numbers0[0]);
}

static void empty_map_test() {
    START_TEST_FUNC
    int_map numbers0;
    std::cout << "empty:";
    print_bool(numbers0.empty());

    value_type v = my_make_pair(1, "hello1");
    numbers0.insert(v);
    std::cout << "empty:";
    print_bool(numbers0.empty());
}

static void size_map_test() {
    START_TEST_FUNC
    int_map numbers0;
    std::cout << "size:";
    print(numbers0.size());

    value_type v = my_make_pair(1, "hello1");
    numbers0.insert(v);
    std::cout << "size:";
    print(numbers0.size());
}

static void max_size_map_test() {
    START_TEST_FUNC
    int_map numbers0;
    std::cout << "max_size:";
    print(numbers0.max_size());

    value_type v = my_make_pair(1, "hello1");
    numbers0.insert(v);
    std::cout << "max_size:";
    print(numbers0.max_size());
}

static void insert_map_test() {
    START_TEST_FUNC
    Allocator alloc;

    // map();
    int_map numbers0;
    print_map(numbers0);

    value_type v = my_make_pair(1, "hello1");
    print_bool(numbers0.insert(v).second);
    print_map(numbers0);

    value_type v2 = my_make_pair(2, "hello2");
    numbers0.insert(numbers0.end(), v2);
    print_map(numbers0);

    int_map numbers1;
    value_type v3 = my_make_pair(3, "hello3");
    value_type v4 = my_make_pair(4, "hello4");
    numbers1.insert(v3);
    numbers1.insert(v4);
    numbers0.insert(numbers1.begin(), numbers1.end());
    print_map(numbers0);
}

static void erase_map_test() {
    START_TEST_FUNC
    Allocator alloc;

    int_map numbers0;
    value_type v = my_make_pair(1, "hello1");
    value_type v2 = my_make_pair(2, "hello2");
    value_type v3 = my_make_pair(3, "hello3");
    value_type v4 = my_make_pair(4, "hello4");
    numbers0.insert(v);
    numbers0.insert(v2);
    numbers0.insert(v3);
    numbers0.insert(v4);
    print_map(numbers0);

    numbers0.erase(numbers0.begin());
    print_map(numbers0);
    // numbers0.tree->print_tree();

    // numbers0.erase(numbers0.begin(), ++(numbers0.begin()));
    // print_map(numbers0);
    // numbers0.tree->print_tree();

    // print(numbers0.erase(3));
    // print_map(numbers0);
    // numbers0.tree->print_tree();
}

int main_map() {
    START_TEST_FUNC
    // Member functions
    constructor_map_test();
    // Element access
    at_map_test();
    operator_map_test();
    // Capacity
    empty_map_test();
    size_map_test();
    max_size_map_test();
    // Modifier
    insert_map_test();
    erase_map_test();

    return 0;
}
