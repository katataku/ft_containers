#ifndef INCLUDE_ITERATOR_REVERSE_ITERATOR_HPP_
#define INCLUDE_ITERATOR_REVERSE_ITERATOR_HPP_

#include "iterator.hpp"
#include "iterator_traits.hpp"

namespace ft {

/********************
 * reverse_iterator *
 ********************/
template <class Iter>
class reverse_iterator
    : public iterator<typename ft::iterator_traits<Iter>::iterator_category,
                      typename ft::iterator_traits<Iter>::value_type,
                      typename ft::iterator_traits<Iter>::difference_type,
                      typename ft::iterator_traits<Iter>::pointer,
                      typename ft::iterator_traits<Iter>::reference> {
 private:
    typedef ft::iterator_traits<Iter> traits_type;

    /********************
     * Member type      *
     ********************/
 public:
    typedef Iter iterator_type;
    typedef typename traits_type::iterator_category iterator_category;
    typedef typename traits_type::value_type value_type;
    typedef typename traits_type::difference_type difference_type;
    typedef typename traits_type::pointer pointer;
    typedef typename traits_type::reference reference;

    /********************
     * Member functions *
     ********************/
    // iterator
    reverse_iterator() : current(){};
    explicit reverse_iterator(iterator_type __x) : current(__x){};
    template <class U>
    reverse_iterator(const reverse_iterator<U>& other)
        : current(other.base()){};

    template <class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other) {
        current = other.base();
        return *this;
    };
    iterator_type base() const { return current; };
    reference operator*() const {
        Iter __tmp = current;
        return *--__tmp;
    };
    pointer operator->() const { return std::addressof(operator*()); };

    reference operator[](difference_type n) const { return *(*this + n); };

    reverse_iterator& operator++() {
        --current;
        return *this;
    };
    reverse_iterator& operator--() {
        ++current;
        return *this;
    };
    reverse_iterator operator++(int) {
        reverse_iterator tmp(*this);
        --current;
        return tmp;
    };
    reverse_iterator operator--(int) {
        reverse_iterator tmp(*this);
        ++current;
        return tmp;
    };
    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(current - n);
    }
    reverse_iterator& operator+=(difference_type n) {
        current -= n;
        return *this;
    }
    reverse_iterator operator-(difference_type n) const {
        return reverse_iterator(current + n);
    }
    reverse_iterator& operator-=(difference_type n) {
        current += n;
        return *this;
    }

    /********************
     * Member object    *
     ********************/
 protected:
    Iter current;
};

/************************
 * Non-Member functions *
 ************************/
template <class Iterator1, class Iterator2>
bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
    return lhs.base() == rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
    return lhs.base() != rhs.base();
}

template <class Iterator1, class Iterator2>
bool operator<(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
    return lhs.base() < rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
               const ft::reverse_iterator<Iterator2>& rhs) {
    return lhs.base() > rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
    return lhs.base() <= rhs.base();
}
template <class Iterator1, class Iterator2>
bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,
                const ft::reverse_iterator<Iterator2>& rhs) {
    return lhs.base() >= rhs.base();
}

template <class Iter>
reverse_iterator<Iter> operator+(
    typename reverse_iterator<Iter>::difference_type n,
    const reverse_iterator<Iter>& it) {
    return reverse_iterator<Iter>(it.base() - n);
}

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
    return rhs.base() - lhs.base();
}
}  // namespace ft

#endif  // INCLUDE_ITERATOR_REVERSE_ITERATOR_HPP_
