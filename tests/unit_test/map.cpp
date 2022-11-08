#include "map.hpp"

#include <iostream>
#include <map>
#include <string>

#define START_TEST_FUNC print(__func__);
#ifndef LIB
#define LIB ft
#endif

typedef int T;
typedef std::allocator<T> Allocator;
typedef LIB::map<int, std::string> int_map;
typedef T value_type;
typedef value_type& reference;
typedef const value_type& const_reference;
typedef Allocator::pointer pointer;
typedef Allocator::const_pointer const_pointer;

void print_bool(bool x) {
    if (x)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}

void print(int x) { std::cout << x << std::endl; }
void print(std::string x) { std::cout << x << std::endl; }

void print_map(int_map& vec) {
    std::cout << "[" << vec.size() << "]";
    for (int_map::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << (*it).first << ":" << (*it).second << " ";
    std::cout << std::endl;
}

void constructor_test() {
    START_TEST_FUNC
    std::allocator<int> alloc;

    // map();
    int_map numbers0;
    print_map(numbers0);
}

int main() {
    // member function
    constructor_test();

    return 0;
}
