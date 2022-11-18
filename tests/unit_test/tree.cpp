#include "tree.hpp"

#include <iostream>
#include <string>
#include <utility>

#include "utility.hpp"

#ifndef LIB
#define LIB ft
#endif

typedef ft::pair<const int, int> int_int_pair;
typedef ft::AVL_tree<int, int, std::less<int>, std::allocator<int> > AVLtree;

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

    a.remove(103);
    a.print_tree();
}

int main_tree() {
    tree_remove_test();
    // tree_insert_test();
    // tree_insert_stress_test();
    return 0;
}
