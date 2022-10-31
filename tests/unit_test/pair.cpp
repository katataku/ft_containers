#include <iostream>
#include <string>
#include <utility>

#include "utility.hpp"

#define START_TEST_FUNC print(__func__);
#ifndef LIB
#define LIB ft
#endif

typedef LIB::pair<int, int> int_pair;

void print_bool(bool x) {
    if (x)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}

void print(int x) { std::cout << x << std::endl; }
void print(std::string x) { std::cout << x << std::endl; }

void pair_test() {
    START_TEST_FUNC
    int_pair a;
    int_pair b(2, 1);
    int_pair c(a);

    print_bool(a == b);
    print_bool(a != b);
    print_bool(a < b);
    print_bool(a <= b);
    print_bool(a > b);
    print_bool(a >= b);

    print_bool(c == b);
    print_bool(c != b);
    print_bool(c < b);
    print_bool(c <= b);
    print_bool(c > b);
    print_bool(c >= b);
}

void make_pair_test() {
    START_TEST_FUNC
    int_pair a;
    int_pair b;

    b = LIB::make_pair(1, 2);
    print_bool(a == b);
    print_bool(a != b);
    print_bool(a < b);
    print_bool(a <= b);
    print_bool(a > b);
    print_bool(a >= b);
}

int main() {
    pair_test();
    make_pair_test();
    return 0;
}
