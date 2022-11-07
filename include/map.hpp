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
 private:
    typedef AVL_tree_iterator<T> tree_type;

 public:
    /********************
     * Member type      *
     ********************/
    typedef Key key_type;
    typedef T mapped_type;
    typedef ft::pair<const Key, T> value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef Compare key_compare;
    typedef Allocator allocator_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef tree_type iterator;
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
    map() : tree(NULL), alloc(allocator_type()){};

    explicit map(const Compare &comp, const Allocator &alloc = Allocator())
        : tree(NULL), alloc(alloc){};

    template <class InputIt>
    map(InputIt first, InputIt last, const Compare &comp = Compare(),
        const Allocator &alloc = Allocator())
        : tree(NULL), alloc(alloc) {
        for (InputIt i = first; i != last; ++i) {
            insert(*i);
        }
    }

    map(const map &other) : tree(NULL), alloc(other.alloc) {
        for (iterator it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }
    };

    // Destructor
    ~map() {
        clear();
        deallocate();
    };

    map &operator=(const map &other) {
        clear();
        for (iterator it = other.begin(); it != other.end(); ++it) {
            insert(*it);
        }
        return *this;
    };

    allocator_type get_allocator() const { return alloc; };

    // Element Access
    reference at(size_type i) {
        if (i >= size()) throw std::out_of_range("index is out of range.");
        return first[i];
    }
    const_reference at(size_type i) const {
        if (i >= size()) throw std::out_of_range("index is out of range.");
        return first[i];
    }

    reference operator[](size_type i) { return first[i]; }
    const_reference operator[](size_type i) const { return first[i]; }

    reference front() { return *first; }
    const_reference front() const { return *first; }
    reference back() { return *(last - 1); }
    const_reference back() const { return *(last - 1); }

    pointer data() { return first; }
    const_pointer data() const { return first; }

    // Iterators
    iterator begin() { return first; }
    iterator begin() const { return first; }
    iterator end() { return last; }
    iterator end() const { return last; }
    reverse_iterator rbegin() { return reverse_iterator(last); }
    reverse_iterator rend() { return reverse_iterator(first); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(last);
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(first);
    }

    // Capacity
    bool empty() const { return size() == 0; }
    size_type size() const { return end() - begin(); }
    size_type max_size() const { return alloc.max_size(); };

    void reserve(size_type sz) {
        if (sz <= capacity()) {
            return;
        }
        pointer ptr = allocate(sz);
        pointer old_first = first;
        pointer old_last = last;
        size_type old_capacity = capacity();

        first = ptr;
        last = first;
        reserved_last = first + sz;

        for (pointer old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last) {
            construct(last, *old_iter);
        }

        for (reverse_iterator riter = reverse_iterator(old_last),
                              rend = reverse_iterator(old_first);
             riter != rend; ++riter) {
            destroy(&*riter);
        }
        alloc.deallocate(old_first, old_capacity);
    }
    size_type capacity() const { return reserved_last - first; }

    // Modifiers
    void clear() { destroy_until(rend()); };

    // https://cplusplus.com/reference/vector/vector/insert/
    iterator insert(iterator position, const value_type &val) {
        insert(position, 1, val);
        return position;
    };

    void insert(iterator position, size_type n, const value_type &val) {
        if (n == 0) return;
        difference_type pos_diff = position - begin();
        size_type new_size = size() + n;
        if (new_size > capacity()) reserve(recommend(new_size));
        iterator new_position = begin() + pos_diff;
        while (size() < new_size) {
            construct(++last);
        }
        std::copy_backward(new_position, last - n, last);
        std::fill(new_position, new_position + n, val);
        return;
    };

    // https://github.dev/llvm/llvm-project/blob/main/libcxx/include/vector
    template <class InputIterator>
    typename ft::enable_if<!std::is_integral<InputIterator>::value, void>::type
    insert(iterator position, InputIterator f, InputIterator l) {
        difference_type pos_diff = position - begin();
        size_type n = l - f;
        size_type new_size = size() + n;
        if (new_size > capacity()) reserve(recommend(new_size));
        iterator new_position = begin() + pos_diff;
        while (size() < new_size) {
            construct(++last);
        }
        std::copy_backward(new_position, last - n, last);
        std::copy(f, l, new_position);
        return;
    };
    iterator erase(iterator pos) { return erase(pos, pos + 1); };
    iterator erase(iterator f, iterator l) {
        size_type erase_size = l - f;
        pointer new_last = last - erase_size;
        std::copy(l, last, f);
        for (iterator it = new_last; it != last; ++it) {
            destroy(it);
        }
        last = new_last;
        return f;
    };

    void push_back(const_reference value) {
        if (size() + 1 > capacity()) {
            reserve(recommend(size() + 1));
        }
        construct(last++, value);
    }
    void pop_back() { erase(end() - 1); };

    void resize(size_type count, T value = T()) {
        if (count < size()) {
            size_type diff = size() - count;
            destroy_until(rbegin() + diff);
            last = first + count;
        } else if (count > size()) {
            reserve(recommend(count));
            for (; size() < count; ++last) {
                construct(last, value);
            }
        }
    };

    void swap(vector &other) {
        pointer tmp_first = other.first;
        pointer tmp_last = other.last;
        pointer tmp_reserved_last = other.reserved_last;

        other.first = first;
        other.last = last;
        other.reserved_last = reserved_last;
        first = tmp_first;
        last = tmp_last;
        reserved_last = tmp_reserved_last;
    };
    /************************
     * Non-Member functions *
     ************************/

 private:
    tree_type tree;
    // アロケーターの値
    allocator_type alloc;

    typedef std::allocator_traits<allocator_type> traits;

    pointer allocate(size_type n) { return traits::allocate(alloc, n); }
    void deallocate() { traits::deallocate(alloc, first, capacity()); }
    void construct(pointer ptr) { traits::construct(alloc, ptr); }
    void construct(pointer ptr, const_reference value) {
        traits::construct(alloc, ptr, value);
    }
    void destroy(pointer ptr) { traits::destroy(alloc, ptr); }
    void destroy_until(reverse_iterator rend) {
        for (reverse_iterator riter = rbegin(); riter != rend;
             ++riter, --last) {
            destroy(&*riter);
        }
    }

    // https://github.dev/llvm/llvm-project/blob/main/libcxx/include/vector
    size_type recommend(size_type new_size) {
        size_type maxsize = max_size();
        if (maxsize < new_size) {
            throw std::length_error("vector");
        }
        size_type cap = capacity();
        if (maxsize / 2 <= cap) {
            return (maxsize);
        }
        return (std::max<size_type>(new_size, cap * 2));
    }
};

template <class T, class Allocator>
bool operator==(const map<T, Allocator> &lhs, const map<T, Allocator> &rhs) {
    return (lhs.size() == rhs.size() &&
            ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Allocator>
bool operator!=(const map<T, Allocator> &lhs, const map<T, Allocator> &rhs) {
    return (!(lhs == rhs));
}

template <class T, class Allocator>
bool operator<(const map<T, Allocator> &lhs, const map<T, Allocator> &rhs) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end()));
}

template <class T, class Allocator>
bool operator<=(const map<T, Allocator> &lhs, const map<T, Allocator> &rhs) {
    return (!(lhs > rhs));
}

template <class T, class Allocator>
bool operator>(const map<T, Allocator> &lhs, const map<T, Allocator> &rhs) {
    return (rhs < lhs);
}

template <class T, class Allocator>
bool operator>=(const map<T, Allocator> &lhs, const map<T, Allocator> &rhs) {
    return (!(lhs < rhs));
}

template <class T, class Allocator>
void swap(map<T, Allocator> &lhs, map<T, Allocator> &rhs) {
    lhs.swap(rhs);
}
}  // namespace ft

#endif  // INCLUDE_VECTOR_HPP_

#endif  // INCLUDE_VECTOR_20COPY_HPP_
