#ifndef INCLUDE_TYPE_TRAITS_HPP_
#define INCLUDE_TYPE_TRAITS_HPP_

#include "type_traits/integral_constant.hpp"
#include "type_traits/remove_cv.hpp"

namespace ft {
// https://en.cppreference.com/w/cpp/types/enable_if
// 実装はプログラミング言語C++第４版 p.798
template <bool B, class T = void>
struct enable_if {
    typedef T type;
};

template <class T>
struct enable_if<false, T> {};

template <class T>
struct __libcpp_is_integral : public false_type {};

template <>
struct __libcpp_is_integral<bool> : public true_type {};

template <>
struct __libcpp_is_integral<int> : public true_type {};

template <class T>
struct is_integral
    : public bool_constant<
          __libcpp_is_integral<typename remove_cv<T>::type>::value>::type {};
}  // namespace ft

#endif  // INCLUDE_TYPE_TRAITS_HPP_
