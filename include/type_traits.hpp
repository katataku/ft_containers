

#ifndef INCLUDE_TYPE_TRAITS_HPP_
#define INCLUDE_TYPE_TRAITS_HPP_

namespace ft {
// https://en.cppreference.com/w/cpp/types/enable_if
// 実装はプログラミング言語C++第４版 p.798
template <bool B, class T = void>
struct enable_if {
    typedef T type;
};

template <class T>
struct enable_if<false, T> {};

}  // namespace ft

#endif  // INCLUDE_TYPE_TRAITS_HPP_
