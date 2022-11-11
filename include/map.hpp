#ifndef INCLUDE_VECTOR_20COPY_HPP_
#define INCLUDE_VECTOR_20COPY_HPP_
#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_

#include <memory>
#include <stdexcept>

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
    typedef const iterator const_iterator;
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
    /********************
     * Element Access   *
     ********************/
    // Tat
    T &at(const Key &key) {
        if (find(key) == end()) throw std::out_of_range("out of range");
        return find(key)->second;
    }
    const T &at(const Key &key) const {
        if (find(key) == end()) throw std::out_of_range("out of range");
        return find(key)->second;
    }

    // operator[]
    T &operator[](const Key &key) {
        return insert(ft::make_pair(key, T())).first->second;
    }

    /********************
     * Iterators        *
     ********************/
    iterator begin() {
        if (!tree) return NULL;
        return tree->begin();
    }
    const_iterator begin() const {
        if (!tree) return NULL;
        return tree->begin();
    }
    iterator end() {
        if (!tree) return NULL;
        return tree->end();
    }
    const_iterator end() const {
        if (!tree) return NULL;
        return tree->end();
    }
    reverse_iterator rbegin() {
        if (!tree) return NULL;
        return reverse_iterator(tree->end());
    }
    reverse_iterator rend() {
        if (!tree) return NULL;
        return reverse_iterator(tree->begin());
    }
    const_reverse_iterator rbegin() const {
        if (!tree) return NULL;
        return const_reverse_iterator(tree->end());
    }
    const_reverse_iterator rend() const {
        if (!tree) return NULL;
        return const_reverse_iterator(tree->begin());
    }

    /********************
     * Capacity         *
     ********************/
    bool empty() const { return size() == 0; };

    size_type size() const {
        if (tree) return tree->size();
        return 0;
    };

    // TODO: テスト用なので、最後に修正。
    size_type max_size() const {
        return std::numeric_limits<difference_type>::max() / 32;
    };

    /********************
     * Modifiers        *
     ********************/
    // TODO:impl testcode;
    void clear() {
        if (tree) {
            tree->clear();
            tree = NULL;
        }
    }

    // insert
    // TODO: impl testcode;
    ft::pair<iterator, bool> insert(const value_type &value) {
        if (!tree) tree = new AVL_tree<value_type>();
        return tree->insert(value);
    };

    // TODO: impl testcode;
    iterator insert(iterator pos, const value_type &value) {
        (void)pos;
        return insert(value).first;
    };

    // TODO: impl testcode;
    template <class InputIt>
    void insert(InputIt first, InputIt last) {
        for (InputIt it = first; it != last; ++it) {
            insert(*it);
        }
    };

    // erase
    iterator erase(iterator pos) {
        Key key = pos->base->get_key();
        erase(key);
        return NULL;
    }
    iterator erase(iterator first, iterator last) {
        for (iterator it = first; it != last; ++it) {
            Key key = it->base->get_key();
            erase(key);
        }
        return NULL;
    }
    size_type erase(const Key &key) { return tree->remove(key) ? 1 : 0; }

    // swap
    void swap(map &other) {
        if (*this != other) {
            tree_type tmp = other.tree;
            other.tree = this->tree;
            this->tree = tmp;
        }
    }
    /********************
     * Lookup           *
     ********************/
    // count
    // TODO: impl testcode;
    size_type count(const Key &key) const {
        if (find(key) == end()) {
            return 0;
        }
        return 1;
    }

    // find
    // TODO: impl;
    iterator find(const Key &key) {
        for (iterator it = begin(); it != end(); ++it) {
            if (it->first == key) return it;
        }
        return end();
    }
    const_iterator find(const Key &key) const {
        for (const_iterator it = begin(); it != end(); ++it) {
            if (it->first == key) return it;
        }
        return end();
    }

    // equal_range
    ft::pair<iterator, iterator> equal_range(const Key &key) {
        return ft::make_pair<iterator, iterator>(lower_bound(key),
                                                 upper_bound(key));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
        return ft::make_pair<const_iterator, const_iterator>(lower_bound(key),
                                                             upper_bound(key));
    }

    // lower_bound
    iterator lower_bound(const Key &key) {
        for (iterator it = begin(); it != end(); ++it) {
            if (!(*it.first < key)) return it;
        }
        return end();
    }
    const_iterator lower_bound(const Key &key) const {
        for (iterator it = begin(); it != end(); ++it) {
            if (!(*it.first < key)) return it;
        }
        return end();
    }

    // upper_bound
    iterator upper_bound(const Key &key) {
        for (iterator it = begin(); it != end(); ++it) {
            if ((*it.first > key)) return it;
        }
        return end();
    }
    const_iterator upper_bound(const Key &key) const {
        for (iterator it = begin(); it != end(); ++it) {
            if ((*it.first > key)) return it;
        }
        return end();
    }

    /************
     * Observer *
     ************/
    // key_compare
    key_compare key_comp() const { return comp; };
    // value_comp
    value_compare value_comp() const { return value_compare(key_comp()); };

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

template <class Key, class T, class Compare, class Allocator>
void swap(map<Key, T, Compare, Allocator> &lhs,
          map<Key, T, Compare, Allocator> &rhs) {
    lhs.swap(rhs);
}
}  // namespace ft

#endif  // INCLUDE_VECTOR_HPP_

#endif  // INCLUDE_VECTOR_20COPY_HPP_
