#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_

#include <memory>

namespace ft {
template <typename T, typename Allocator = std::allocator<T> >
class vector {
 public:
    // value_typeなどネストされた型名
    typedef T value_type;
    vector(std::size_t n = 0, Allocator a = Allocator()) {
        _size = n;
        (void)a;
    };
    ~vector(){};
    vector(const vector &x);
    vector &operator=(const vector &x);

    // 要素アクセス
    void push_back(const T &x);
    T &operator[](std::size_t i);
    int size() { return this->_size; };

 private:
    int _size;
};
}  // namespace ft

#endif  // INCLUDE_VECTOR_HPP_
