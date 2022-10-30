

#ifndef INCLUDE_TYPE_TRAITS_HPP_
#define INCLUDE_TYPE_TRAITS_HPP_

namespace ft {
// https://en.cppreference.com/w/cpp/types/enable_if
template <bool Condition, class T = void>
struct enable_if {};

template <class T>
struct enable_if<true, T> {
    typedef T type;
};

}  // namespace ft

#endif  // INCLUDE_TYPE_TRAITS_HPP_
