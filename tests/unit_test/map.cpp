#include "map.hpp"

#include <iostream>
#include <map>
#include <string>

#include "./utils.cpp"

#define START_TEST_FUNC print(__func__);
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

static void constructor_test() {
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

static void at_test() {
    START_TEST_FUNC
    int_map numbers0;
    value_type v = my_make_pair(1, "hello1");
    print_bool(numbers0.insert(v).second);
    value_type v2 = my_make_pair(2, "hello2");
    print_bool(numbers0.insert(v2).second);

    print(numbers0.at(1));
    print(numbers0.at(2));
    try {
        print(numbers0.at(0));
    } catch (std::exception& e) {
        print(e.what());
    }
}

static void operator_test() {
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

static void empty_test() {
    START_TEST_FUNC
    int_map numbers0;
    std::cout << "empty:";
    print_bool(numbers0.empty());

    value_type v = my_make_pair(1, "hello1");
    numbers0.insert(v);
    std::cout << "empty:";
    print_bool(numbers0.empty());
}

static void size_test() {
    START_TEST_FUNC
    int_map numbers0;
    std::cout << "size:";
    print(numbers0.size());

    value_type v = my_make_pair(1, "hello1");
    numbers0.insert(v);
    std::cout << "size:";
    print(numbers0.size());
}

static void max_size_test() {
    START_TEST_FUNC
    int_map numbers0;
    std::cout << "max_size:";
    print(numbers0.max_size());

    value_type v = my_make_pair(1, "hello1");
    numbers0.insert(v);
    std::cout << "max_size:";
    print(numbers0.max_size());
}

int main_map() {
    // Member functions
    constructor_test();
    // Element access
    at_test();
    operator_test();
    // Capacity
    empty_test();
    size_test();
    max_size_test();
    // Modifier

    return 0;
}
