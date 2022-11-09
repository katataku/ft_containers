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

typedef ft::map<int, std::string> int_map;

typedef int_map::key_type key_type;
typedef int_map::mapped_type mapped_type;
typedef int_map::value_type value_type;
typedef std::allocator<value_type> Allocator;

void print_map(int_map& map) {
    std::cout << "[" << map.size() << "]";
    for (int_map::iterator it = map.begin(); it != map.end(); ++it) {
        std::cout << (*it).first << ":" << (*it).second << " ";
    }
    std::cout << std::endl;
}

void constructor_test() {
    START_TEST_FUNC
    Allocator alloc;

    // map();
    int_map numbers0;
    print_map(numbers0);

    value_type v = ft::make_pair<const key_type, mapped_type>(1, "hello1");
    print_bool(numbers0.insert(v).second);
    print_map(numbers0);

    value_type v2 = ft::make_pair<const key_type, mapped_type>(2, "hello2");
    print_bool(numbers0.insert(v2).second);
    print_map(numbers0);

    int_map::const_iterator cit = numbers0.find(2);
    print(cit->second);
    print((numbers0.find(1))->second);
}

int main_map() {
    // member function
    constructor_test();

    return 0;
}
