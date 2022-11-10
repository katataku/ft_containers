#include "map.hpp"

#include <iostream>
#include <map>
#include <string>

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

void constructor_test() {
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

int main_map() {
    // member function
    constructor_test();

    return 0;
}
