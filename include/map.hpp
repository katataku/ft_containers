#ifndef INCLUDE_VECTOR_20COPY_HPP_
#define INCLUDE_VECTOR_20COPY_HPP_
#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_

#include <memory>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "tree.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
    /********************
     * Member type      *
     ********************/
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const Key, T> value_type;

 private:
    typedef AVL_tree<value_type> *tree_type;

 public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef AVL_tree_iterator<value_type> iterator;
    typedef const tree_type const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    /********************
     * Member Class     *
     ********************/
    class value_compare : std::binary_function<value_type, value_type, bool> {
     public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;

     protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}

     public:
        bool operator()(const value_type &lhs, const value_type &rhs) const {
            return comp(lhs.first, rhs.first);
        }
    };
    /********************
     * Member functions *
     ********************/
    // Constructor
    map() : tree(NULL), comp(Compare()), alloc(allocator_type()){};

    explicit map(const Compare &comp, const Allocator &alloc = Allocator())
        : tree(NULL), comp(comp), alloc(alloc){};

    template <class InputIt>
    map(InputIt first, InputIt last, const Compare &comp = Compare(),
        const Allocator &alloc = Allocator())
        : tree(NULL), comp(comp), alloc(alloc) {
        for (InputIt i = first; i != last; ++i) {
            insert(*i);
        }
    }

    map(const map &other) : tree(NULL), comp(Compare()), alloc(other.alloc) {
        for (iterator it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }
    };

    // Destructor
    ~map(){

    };

    map &operator=(const map &other) {
        for (iterator it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }
        return *this;
    };

    allocator_type get_allocator() const { return alloc; };
    iterator find(const Key &key);
    const_iterator find(const Key &key) const;

    size_t size() const { return tree->size(); };

    // Iterators
    // Iterators
    iterator begin() { return tree->begin(); }
    iterator begin() const { return tree->begin(); }
    iterator end() { return tree->end(); }
    iterator end() const { return tree->end(); }
    reverse_iterator rbegin() { return reverse_iterator(tree->end()); }
    reverse_iterator rend() { return reverse_iterator(tree->begin()); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(tree->end());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(tree->begin());
    }

    key_compare key_comp() const { return comp; };
    /************************
     * Non-Member functions *
     ************************/

 private:
    tree_type tree;
    key_compare comp;
    // アロケーターの値
    allocator_type alloc;

    typedef std::allocator_traits<allocator_type> traits;

    pointer allocate(size_type n) { return traits::allocate(alloc, n); }
};

template <class Key, class T, class Allocator>
bool operator==(const map<Key, T, Allocator> &lhs,
                const map<Key, T, Allocator> &rhs) {
    return (lhs.size() == rhs.size() &&
            ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Allocator>
bool operator!=(const map<Key, T, Allocator> &lhs,
                const map<Key, T, Allocator> &rhs) {
    return (!(lhs == rhs));
}

template <class Key, class T, class Allocator>
bool operator<(const map<Key, T, Allocator> &lhs,
               const map<Key, T, Allocator> &rhs) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end()));
}

template <class Key, class T, class Allocator>
bool operator<=(const map<Key, T, Allocator> &lhs,
                const map<Key, T, Allocator> &rhs) {
    return (!(lhs > rhs));
}

template <class Key, class T, class Allocator>
bool operator>(const map<Key, T, Allocator> &lhs,
               const map<Key, T, Allocator> &rhs) {
    return (rhs < lhs);
}

template <class Key, class T, class Allocator>
bool operator>=(const map<Key, T, Allocator> &lhs,
                const map<Key, T, Allocator> &rhs) {
    return (!(lhs < rhs));
}

template <class Key, class T, class Allocator>
void swap(map<T, Allocator> &lhs, map<Key, T, Allocator> &rhs) {
    lhs.swap(rhs);
}
}  // namespace ft

#endif  // INCLUDE_VECTOR_HPP_

#endif  // INCLUDE_VECTOR_20COPY_HPP_
