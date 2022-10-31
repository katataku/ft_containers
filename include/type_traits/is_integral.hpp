#ifndef INCLUDE_TYPE_TRAITS_IS_INTEGRAL_HPP_
#define INCLUDE_TYPE_TRAITS_IS_INTEGRAL_HPP_

#include "integral_constant.hpp"
#include "remove_cv.hpp"

namespace ft {

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

#endif  // INCLUDE_TYPE_TRAITS_IS_INTEGRAL_HPP_
