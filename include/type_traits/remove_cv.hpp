#ifndef INCLUDE_TYPE_TRAITS_REMOVE_CV_HPP_
#define INCLUDE_TYPE_TRAITS_REMOVE_CV_HPP_

namespace ft {

template <class T>
struct remove_const {
    typedef T type;
};

template <class T>
struct remove_const<const T> {
    typedef T type;
};

template <class T>
struct remove_volatile {
    typedef T type;
};

template <class T>
struct remove_volatile<volatile T> {
    typedef T type;
};

template <class T>
struct remove_cv {
    typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};
}  // namespace ft

#endif  // INCLUDE_TYPE_TRAITS_REMOVE_CV_HPP_
