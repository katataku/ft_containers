#include "tree.hpp"

#include <iostream>
#include <string>
#include <utility>

#include "utility.hpp"

#define START_TEST_FUNC print(__func__);
#ifndef LIB
#define LIB ft
#endif

typedef ft::AVL_tree<int, int> AVLtree;
void print_bool(bool x) {
    if (x)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}

void print(int x) { std::cout << x << std::endl; }
void print(std::string x) { std::cout << x << std::endl; }

void tree_remove_test() {
    START_TEST_FUNC
    AVLtree a(510, 510);
    a.insert(520, 520);
    a.insert(100, 100);
    a.insert(102, 102);
    a.insert(98, 98);
    a.insert(96, 96);
    a.insert(97, 97);
    a.insert(99, 99);
    a.insert(101, 101);
    a.insert(103, 103);
    a.remove(97);
    a.remove(98);

    a.print_tree();
    a.remove(96);
    a.print_tree();

    // a.remove(103);
    // a.print_tree();
}

int main() {
    tree_remove_test();
    // tree_insert_test();
    // tree_insert_stress_test();
    return 0;
}