#include <iostream>
#include <vector>

#include "vector.hpp"
#define LIB std

int main() {
    LIB::vector<int> numbers0(0);
    std::cout << numbers0.size() << std::endl;
    LIB::vector<int> numbers1(1);
    std::cout << numbers1.size() << std::endl;
    LIB::vector<int> numbers5(5);
    std::cout << numbers5.size() << std::endl;
}
