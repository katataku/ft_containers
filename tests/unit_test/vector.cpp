#include "vector.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "./utils.cpp"

#define START_TEST_FUNC print(__func__);
#ifndef LIB
#define LIB ft
#endif

typedef int T;
typedef std::allocator<T> Allocator;
typedef LIB::vector<int> int_vector;
typedef T value_type;
typedef value_type& reference;
typedef const value_type& const_reference;
typedef Allocator::pointer pointer;
typedef Allocator::const_pointer const_pointer;

static void print_vec(int_vector& vec) {
    std::cout << "[" << vec.size() << "/" << vec.capacity() << "]";
    for (int_vector::iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << *it << " ";
    std::cout << std::endl;
}

static void constructor_test() {
    START_TEST_FUNC
    std::allocator<int> alloc;

    // vector();
    int_vector numbers0(0);
    print_vec(numbers0);

    // explicit vector( const Allocator& alloc );
    int_vector numbers1(alloc);
    print_vec(numbers1);

    // template <class InputIt>
    // vector(InputIt first, InputIt last, const Allocator& alloc =
    // Allocator());
    int_vector numbers2_a(15);
    int_vector numbers2_b(numbers2_a.begin(), numbers2_a.end());
    print(numbers2_a.size());
    print(numbers2_b.size());
    print_vec(numbers2_a);
    print_vec(numbers2_b);

    // vector( const vector& other );
    int_vector numbers3_a(5);
    int_vector numbers3_b(numbers3_a);
    print(numbers3_a.size());
    print(numbers3_b.size());
    print_vec(numbers3_a);
    print_vec(numbers3_b);
}

static void assign_test() {
    START_TEST_FUNC
    int_vector numbers0(3);
    print_vec(numbers0);

    numbers0.assign(2, 1);
    print_vec(numbers0);

    int_vector numbers1;
    numbers1.push_back(1);
    numbers1.push_back(2);
    numbers1.push_back(3);
    numbers1.push_back(4);
    numbers1.push_back(5);

    numbers0.assign(numbers1.begin(), numbers1.end());
    print_vec(numbers0);
}

static void at_test() {
    START_TEST_FUNC
    int_vector numbers0(3);
    print(numbers0.at(0));
    print(numbers0.at(1));
    print(numbers0.at(2));
}
static void operator_test() {
    START_TEST_FUNC
    int_vector numbers(3);
    numbers[1] = 1;
    print(numbers[0]);
    print(numbers[1]);
    print(numbers[2]);

    const int_vector numbers_const(3);
    print(numbers_const[0]);
    print(numbers_const[1]);
    print(numbers_const[2]);
}
static void front_test() {
    START_TEST_FUNC
    int_vector numbers(3);
    numbers[0] = 2;
    reference x = numbers.front();
    print(x);

    const int_vector numbers_const(3);
    const_reference y = numbers_const.front();
    print(y);
}

static void back_test() {
    START_TEST_FUNC
    int_vector numbers(3);
    numbers[2] = 2;
    reference x = numbers.back();
    print(x);

    const int_vector numbers_const(3);
    const_reference y = numbers_const.back();
    print(y);
}

static void data_test() {
    START_TEST_FUNC
    int_vector numbers(3);
    numbers[2] = 2;
    pointer x = numbers.data();
    print(*(x + 0));
    print(*(x + 1));
    print(*(x + 2));

    const int_vector numbers_const(3);
    const_pointer y = numbers_const.data();
    print(*(y + 0));
    print(*(y + 1));
    print(*(y + 2));
}

static void push_back_test() {
    START_TEST_FUNC
    int_vector numbers;
    print_vec(numbers);
    numbers.push_back(1);
    print_vec(numbers);
    numbers.push_back(2);
    print_vec(numbers);
    numbers.push_back(3);
    print_vec(numbers);
    numbers.push_back(3);
    print_vec(numbers);
    numbers.push_back(3);
    print_vec(numbers);
    numbers.push_back(3);
    print_vec(numbers);
}

static void iterator_test() {
    START_TEST_FUNC
    int_vector numbers(5);
    numbers[0] = 0;
    numbers[1] = 1;
    numbers[2] = 2;
    numbers[3] = 3;
    numbers[4] = 4;
    print_vec(numbers);
    for (int_vector::iterator it = numbers.begin(); it != numbers.end(); ++it) {
        print(*it);
    }
    for (int_vector::reverse_iterator it = numbers.rbegin();
         it != numbers.rend(); ++it) {
        print(*it);
    }
}
static void empty_test() {
    START_TEST_FUNC
    int_vector numbers;
    print_bool(numbers.empty());
    numbers.push_back(1);
    print_bool(numbers.empty());

    int_vector numbers1(1);
    print_bool(numbers1.empty());
    numbers1.push_back(1);
    print_bool(numbers1.empty());
}

static void size_test() {
    START_TEST_FUNC
    int_vector numbers;
    print(numbers.size());
    numbers.push_back(1);
    print(numbers.size());

    int_vector numbers1(1);
    print(numbers.size());
    numbers1.push_back(1);
    print(numbers.size());
}

static void max_size_test() {
    START_TEST_FUNC
    int_vector numbers;
    print(numbers.max_size());
    numbers.push_back(1);
    print(numbers.max_size());

    int_vector numbers1(1);
    print(numbers.max_size());
    numbers1.push_back(1);
    print(numbers.max_size());
}
static void reserve_test() {
    START_TEST_FUNC
    int_vector numbers(3);
    numbers.reserve(5);
    print_vec(numbers);
    numbers.push_back(1);
    numbers.reserve(3);
    print_vec(numbers);
    numbers.reserve(18);
    print_vec(numbers);
}

static void capacity_test() {
    START_TEST_FUNC
    int_vector numbers;
    print(numbers.capacity());
    print_vec(numbers);
    numbers.reserve(5);
    print(numbers.capacity());
    print_vec(numbers);
    numbers.push_back(1);
    print(numbers.capacity());
    print_vec(numbers);
    numbers.reserve(8);
    print(numbers.capacity());
    print_vec(numbers);

    int_vector numbers1(3);
    print(numbers.capacity());
    print_vec(numbers);
}

static void clear_test() {
    START_TEST_FUNC
    int_vector numbers;
    print_vec(numbers);
    numbers.push_back(1);
    print_vec(numbers);
    numbers.push_back(1);
    print_vec(numbers);
    numbers.push_back(1);
    print_vec(numbers);
    numbers.clear();
    print_vec(numbers);
    numbers.push_back(1);
    print_vec(numbers);
    numbers.clear();
    print_vec(numbers);
}

static void insert_test() {
    START_TEST_FUNC
    int_vector numbers;
    print_vec(numbers);
    numbers.push_back(1);
    print_vec(numbers);
    numbers.insert(numbers.begin() + 1, 4, 4);
    print_vec(numbers);
    numbers.insert(numbers.begin() + 1, 9, 9);
    print_vec(numbers);
    numbers.insert(numbers.begin() + 1, 2, 2);
    print_vec(numbers);

    int_vector numbers1;
    numbers1.push_back(1);
    numbers1.push_back(2);
    numbers1.push_back(3);
    numbers1.push_back(4);
    numbers1.push_back(5);

    numbers.insert(numbers.begin(), numbers1.begin(), numbers1.end());
    print_vec(numbers);
}
static void erase_test() {
    START_TEST_FUNC
    int_vector::iterator iter;
    int_vector numbers;
    print_vec(numbers);
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.push_back(6);
    print_vec(numbers);
    iter = numbers.erase(numbers.begin());
    print_vec(numbers);
    print(*iter);
    iter = numbers.erase(numbers.begin() + 1);
    print_vec(numbers);
    print(*iter);
    iter = numbers.erase(numbers.begin(), numbers.end() - 1);
    print_vec(numbers);
    print(*iter);
    iter = numbers.erase(numbers.begin(), numbers.end());
    print_vec(numbers);
    assert(iter == numbers.end());
}

static void pop_back_test() {
    START_TEST_FUNC
    int_vector numbers;
    print_vec(numbers);
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);
    numbers.push_back(4);
    numbers.push_back(5);
    numbers.push_back(6);
    print_vec(numbers);
    numbers.pop_back();
    print_vec(numbers);
    numbers.pop_back();
    print_vec(numbers);
    numbers.pop_back();
    print_vec(numbers);
    numbers.pop_back();
    print_vec(numbers);
}
static void resize_test() {
    START_TEST_FUNC
    int_vector numbers;
    numbers.resize(5);
    print_vec(numbers);
    numbers.push_back(1);
    numbers.resize(3, 3);
    print_vec(numbers);
    numbers.resize(18);
    print_vec(numbers);
}

static void swap_test() {
    START_TEST_FUNC
    int_vector numbers1;
    numbers1.resize(5);
    numbers1[0] = 0;
    numbers1[1] = 1;
    numbers1[2] = 2;
    numbers1[3] = 3;
    numbers1[4] = 4;
    int_vector numbers2;
    numbers2.resize(10, 2);
    int_vector::iterator iter = numbers1.begin();
    print_vec(numbers1);
    print_vec(numbers2);
    print(*(iter++));
    print(*iter);
    numbers1.swap(numbers2);
    print_vec(numbers1);
    print_vec(numbers2);
    print(*(iter++));
    print(*iter);
}

static void get_allocator_test() {
    START_TEST_FUNC
    std::allocator<int> alloc;
    int_vector numbers1;
    print_bool(numbers1.get_allocator() == alloc);
}

static void eq_test() {
    START_TEST_FUNC
    int_vector numbers1;
    numbers1.resize(5);
    numbers1[0] = 0;
    numbers1[1] = 1;
    numbers1[2] = 2;
    numbers1[3] = 3;
    numbers1[4] = 4;
    int_vector numbers2;
    numbers2 = numbers1;
    print_vec(numbers1);
    print_vec(numbers2);
}

static void comp_op_test() {
    START_TEST_FUNC
    int_vector numbers1;
    numbers1.resize(5);
    numbers1[0] = 0;
    numbers1[1] = 1;
    numbers1[2] = 2;
    numbers1[3] = 3;
    numbers1[4] = 4;
    int_vector numbers2;
    numbers2.resize(5);
    numbers2[0] = 0;
    numbers2[1] = 1;
    numbers2[2] = 2;
    numbers2[3] = 3;
    numbers2[4] = 4;

    print_bool(numbers1 == numbers2);
    print_bool(numbers1 != numbers2);
    print_bool(numbers1 < numbers2);
    print_bool(numbers1 > numbers2);
    print_bool(numbers1 <= numbers2);
    print_bool(numbers1 >= numbers2);
    numbers2[4] = 999;
    print_bool(numbers1 == numbers2);
    print_bool(numbers1 != numbers2);
    print_bool(numbers1 < numbers2);
    print_bool(numbers1 > numbers2);
    print_bool(numbers1 <= numbers2);
    print_bool(numbers1 >= numbers2);
}
static void nonmember_swap_test() {
    START_TEST_FUNC
    int_vector numbers1;
    numbers1.resize(5);
    numbers1[0] = 0;
    numbers1[1] = 1;
    numbers1[2] = 2;
    numbers1[3] = 3;
    numbers1[4] = 4;
    int_vector numbers2;
    numbers2.resize(10, 2);
    int_vector::iterator iter = numbers1.begin();
    print_vec(numbers1);
    print_vec(numbers2);
    print(*(iter++));
    print(*iter);
    LIB::swap(numbers1, numbers2);
    print_vec(numbers1);
    print_vec(numbers2);
    print(*(iter++));
    print(*iter);
}

template <typename T>
static void func(
    T t, typename LIB::enable_if<LIB::is_integral<T>::value>::type* = 0) {
    std::cout << t << "は整数だよ" << std::endl;
}

template <typename T>
static void func(
    T t, typename LIB::enable_if<!LIB::is_integral<T>::value>::type* = 0) {
    std::cout << t << "引数は整数じゃないよ" << std::endl;
}

static void is_integral_test() {
    int a = 10;
    func(a);
}

int main_vector() {
    // member function
    constructor_test();
    eq_test();
    assign_test();
    get_allocator_test();

    // element access
    at_test();
    operator_test();
    front_test();
    back_test();
    data_test();

    // iterators
    iterator_test();

    // capacity
    empty_test();
    size_test();
    max_size_test();
    reserve_test();
    capacity_test();

    // Modifiers
    clear_test();
    insert_test();
    erase_test();
    push_back_test();
    pop_back_test();
    resize_test();
    swap_test();

    // Non-member functions
    comp_op_test();
    nonmember_swap_test();

    is_integral_test();
    return 0;
}
