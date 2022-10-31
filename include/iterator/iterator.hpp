#ifndef INCLUDE_ITERATOR_ITERATOR_HPP_
#define INCLUDE_ITERATOR_ITERATOR_HPP_
#include <cstddef>

namespace ft {

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator {
    typedef Category iterator_category;
    typedef T value_type;
    typedef Distance difference_type;
    typedef Pointer pointer;
    typedef Reference reference;
};
}  // namespace ft

#endif  // INCLUDE_ITERATOR_ITERATOR_HPP_
