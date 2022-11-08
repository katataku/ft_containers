
#include <iostream>
#include <string>

void print_bool(bool x) {
    if (x)
        std::cout << "true" << std::endl;
    else
        std::cout << "false" << std::endl;
}

void print(int x) { std::cout << x << std::endl; }
void print(std::string x) { std::cout << x << std::endl; }

#include "./map.cpp"
#include "./tree.cpp"

int main() {
    main_map();
    main_tree();
}
