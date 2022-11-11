#ifndef TESTS_UNIT_TEST_UTILS_CPP_
#define TESTS_UNIT_TEST_UTILS_CPP_

#include <assert.h>

#include <iostream>
#include <string>
void print_bool(bool x) {
    if (x)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}

void print(int x) { std::cout << x << std::endl; }
void print(size_t x) { std::cout << x << std::endl; }
void print(std::string x) { std::cout << x << std::endl; }

#endif  // TESTS_UNIT_TEST_UTILS_CPP_
