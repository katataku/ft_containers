#ifndef INCLUDE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_
#define INCLUDE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_
namespace ft {

template <typename T, T v>
struct integral_constant {
    static const T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    const value_type operator()() const { return value; }
};

typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

template <bool _Val>
struct bool_constant {
    typedef integral_constant<bool, _Val> type;
};

}  // namespace ft

#endif  // INCLUDE_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP_
