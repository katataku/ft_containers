#ifndef INCLUDE_MAP_HPP_
#define INCLUDE_MAP_HPP_

#include <limits>
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
    typedef AVL_tree<Key, T> tree_type;
    typedef tree_type *tree_ptr;

 public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef typename tree_type::iterator iterator;
    typedef typename tree_type::const_iterator const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    /********************
     * Member Class     *
     ********************/
    class value_compare : std::binary_function<value_type, value_type, bool> {
        friend class map;

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
    map() : tree_(create_tree()), comp(Compare()), alloc(allocator_type()){};

    explicit map(const Compare &comp, const Allocator &alloc = Allocator())
        : tree_(create_tree()), comp(comp), alloc(alloc){};

    template <class InputIt>
    map(InputIt first, InputIt last, const Compare &comp = Compare(),
        const Allocator &alloc = Allocator())
        : tree_(create_tree()), comp(comp), alloc(alloc) {
        for (InputIt i = first; i != last; ++i) {
            insert(*i);
        }
    }

    map(const map &other)
        : tree_(create_tree()), comp(Compare()), alloc(other.alloc) {
        // iterator other_end = other.end();
        for (iterator it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }
    };

    // Destructor
    ~map() { delete_tree(tree_); };

    map &operator=(const map &other) {
        clear();
        iterator other_end = other.end();
        for (iterator it = other.begin(); it != other_end; ++it) {
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
        if (find(key) == end())
            throw std::out_of_range("map::at:  key not found");
        return find(key)->second;
    }
    const T &at(const Key &key) const {
        if (find(key) == end())
            throw std::out_of_range("map::at:  key not found");
        return find(key)->second;
    }

    // operator[]
    T &operator[](const Key &key) {
        return insert(ft::make_pair(key, T())).first->second;
    }

    /********************
     * Iterators        *
     ********************/
    iterator begin() { return tree_->begin(); }
    const_iterator begin() const { return tree_->begin(); }
    iterator end() { return tree_->end(); }
    const_iterator end() const { return tree_->end(); }
    reverse_iterator rbegin() { return reverse_iterator(tree_->end()); }
    reverse_iterator rend() { return reverse_iterator(tree_->begin()); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(tree_->end());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(tree_->begin());
    }

    /********************
     * Capacity         *
     ********************/
    bool empty() const { return size() == 0; };

    size_type size() const {
        if (tree_) return tree_->size();
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
        if (tree_) {
            tree_->clear();
        }
    }

    // insert
    ft::pair<iterator, bool> insert(const value_type &value) {
        if (tree_ == NULL) {
            tree_ = create_tree();
        }
        return tree_->insert(value);
    };

    iterator insert(iterator pos, const value_type &value) {
        (void)pos;
        return insert(value).first;
    };

    template <class InputIt>
    void insert(InputIt first, InputIt last) {
        for (InputIt it = first; it != last; ++it) {
            insert(*it);
        }
    }

    // erase
    iterator erase(iterator pos) {
        Key key = pos.base()->get_key();
        erase(key);
        return NULL;
    }
    iterator erase(iterator first, iterator last) {
        iterator it = first;
        while (it != last) {
            Key key = it.base()->get_key();
            ++it;
            erase(key);
        }
        return NULL;
    }
    size_type erase(const Key &key) { return tree_->remove(key) ? 1 : 0; }

    // swap
    void swap(map &other) {
        if (*this != other) {
            tree_ptr tmp = other.tree_;
            other.tree_ = this->tree_;
            this->tree_ = tmp;
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
        return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
        return ft::pair<const_iterator, const_iterator>(lower_bound(key),
                                                        upper_bound(key));
    }

    // lower_bound
    iterator lower_bound(const Key &key) {
        for (iterator it = begin(); it != end(); ++it) {
            if (!(it.base()->get_key() < key)) return it;
        }
        return end();
    }
    const_iterator lower_bound(const Key &key) const {
        for (iterator it = begin(); it != end(); ++it) {
            if (!(it.base()->get_key() < key)) return it;
        }
        return end();
    }

    // upper_bound
    iterator upper_bound(const Key &key) {
        for (iterator it = begin(); it != end(); ++it) {
            if ((it.base()->get_key() > key)) return it;
        }
        return end();
    }
    const_iterator upper_bound(const Key &key) const {
        for (iterator it = begin(); it != end(); ++it) {
            if ((it.base()->get_key() > key)) return it;
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

    tree_ptr get_tree() { return tree_; }

    tree_ptr tree_;

 private:
    key_compare comp;
    // アロケーターの値
    allocator_type alloc;

    tree_ptr create_tree() {
        // 異なる型に対してのAllocatorの型を取得する方法
        // node用Allocatorの実態はallocを使用。
        // https://in-neuro.hatenablog.com/entry/2018/08/01/114441
        typedef typename Allocator::template rebind<tree_type>::other
            tree_allocator_type;
        tree_allocator_type tree_alloc = alloc;

        tree_ptr new_tree = tree_alloc.allocate(1);
        tree_alloc.construct(new_tree);
        return new_tree;
    }

    void delete_tree(tree_ptr tree) {
        typedef typename Allocator::template rebind<tree_type>::other
            tree_allocator_type;
        tree_allocator_type tree_alloc = alloc;

        tree_alloc.destroy(tree);
        tree_alloc.deallocate(tree, 1);
    }

    pointer allocate(size_type n) { return allocator_type::allocate(alloc, n); }
};

template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
    return (lhs.size() == rhs.size() &&
            ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
    return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Allocator>
bool operator<(const map<Key, T, Compare, Allocator> &lhs,
               const map<Key, T, Compare, Allocator> &rhs) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end()));
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
    return (!(lhs > rhs));
}

template <class Key, class T, class Compare, class Allocator>
bool operator>(const map<Key, T, Compare, Allocator> &lhs,
               const map<Key, T, Compare, Allocator> &rhs) {
    return (rhs < lhs);
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key, T, Compare, Allocator> &lhs,
                const map<Key, T, Compare, Allocator> &rhs) {
    return (!(lhs < rhs));
}

template <class Key, class T, class Compare, class Allocator>
void swap(map<Key, T, Compare, Allocator> &lhs,
          map<Key, T, Compare, Allocator> &rhs) {
    lhs.swap(rhs);
}
}  // namespace ft

#endif  // INCLUDE_MAP_HPP_
