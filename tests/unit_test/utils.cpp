#ifndef TESTS_UNIT_TEST_UTILS_CPP_
#define TESTS_UNIT_TEST_UTILS_CPP_

#define LOAD_FACTOR_NUM 20
// #define LOAD_FACTOR_NUM 4294967296

#define START_TEST_FUNC print_start_test_func(__func__);
void print_start_test_func(std::string func_name) {
    std::cout << "====" << func_name << "=====" << std::endl;
}

#include <assert.h>

#include <cassert>
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
