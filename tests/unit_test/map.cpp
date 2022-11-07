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

void print_vec(int_map& vec) {
    std::cout << "[" << vec.size() << "/" << vec.capacity() << "]";
    for (int_map::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void constructor_test() {
    START_TEST_FUNC
    std::allocator<int> alloc;

    // map();
    int_map numbers0(0);
    print_vec(numbers0);

    // explicit map( const Allocator& alloc );
    int_map numbers1(alloc);
    print_vec(numbers1);

    // template <class InputIt>
    // map(InputIt first, InputIt last, const Allocator& alloc =
    // Allocator());
    int_map numbers2_a(15);
    int_map numbers2_b(numbers2_a.begin(), numbers2_a.end());
    print(numbers2_a.size());
    print(numbers2_b.size());
    print_vec(numbers2_a);
    print_vec(numbers2_b);

    // map( const map& other );
    int_map numbers3_a(5);
    int_map numbers3_b(numbers3_a);
    print(numbers3_a.size());
    print(numbers3_b.size());
    print_vec(numbers3_a);
    print_vec(numbers3_b);
}

int main() {
    // member function
    constructor_test();

    return 0;
}
