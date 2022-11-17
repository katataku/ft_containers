#ifndef INCLUDE_VECTOR_HPP_
#define INCLUDE_VECTOR_HPP_

#include <algorithm>
#include <iterator>
#include <memory>
#include <utility>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "type_traits.hpp"
namespace ft {
template <class T, class Allocator = std::allocator<T> >
class vector {
 public:
    /********************
     * Member type      *
     ********************/
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type &reference;
    typedef const value_type &const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef pointer iterator;
    typedef const pointer const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    /********************
     * Member functions *
     ********************/
    // Constructor
    vector()
        : first_(NULL),
          last_(NULL),
          reserved_last_(NULL),
          alloc_(allocator_type()) {}
    explicit vector(const Allocator &alloc)
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc) {}

    explicit vector(size_type count, const T &value = T(),
                    const Allocator &alloc = Allocator())
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc) {
        resize(count, value);
    }

    template <class InputIt>
    vector(InputIt first, InputIt last, const Allocator &alloc = Allocator())
        : first_(NULL), last_(NULL), reserved_last_(NULL), alloc_(alloc) {
        reserve(recommend(last - first));
        for (InputIt i = first; i != last; ++i) {
            push_back(*i);
        }
    }

    vector(const vector &other)
        : first_(NULL),
          last_(NULL),
          reserved_last_(NULL),
          alloc_(other.alloc_) {
        resize(other.size());
        for (size_type i = 0; i < other.size(); ++i) {
            first_[i] = other[i];
        }
    }

    // Destructor
    ~vector() {
        clear();
        deallocate();
    }

    vector &operator=(const vector &other) {
        clear();
        resize(other.size());
        for (size_type i = 0; i < other.size(); ++i) {
            first_[i] = other[i];
        }
        return *this;
    }

    void assign(size_type count, const T &value) {
        clear();
        reserve(count);
        insert(begin(), count, value);
    }

    template <class InputIt>
    typename ft::enable_if<!std::is_integral<InputIt>::value, void>::type
    assign(InputIt f, InputIt l) {
        clear();
        reserve(std::distance(f, l));
        insert(begin(), f, l);
    }

    allocator_type get_allocator() const { return alloc_; }

    // Element Access
    reference at(size_type i) {
        if (i >= size()) throw std::out_of_range("index is out of range.");
        return first_[i];
    }
    const_reference at(size_type i) const {
        if (i >= size()) throw std::out_of_range("index is out of range.");
        return first_[i];
    }

    reference operator[](size_type i) { return first_[i]; }
    const_reference operator[](size_type i) const { return first_[i]; }

    reference front() { return *first_; }
    const_reference front() const { return *first_; }
    reference back() { return *(last_ - 1); }
    const_reference back() const { return *(last_ - 1); }

    pointer data() { return first_; }
    const_pointer data() const { return first_; }

    // Iterators
    iterator begin() { return first_; }
    iterator begin() const { return first_; }
    iterator end() { return last_; }
    iterator end() const { return last_; }
    reverse_iterator rbegin() { return reverse_iterator(last_); }
    reverse_iterator rend() { return reverse_iterator(first_); }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(last_);
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(first_);
    }

    // Capacity
    bool empty() const { return size() == 0; }
    size_type size() const { return end() - begin(); }
    size_type max_size() const { return alloc_.max_size(); }

    void reserve(size_type sz) {
        if (sz <= capacity()) {
            return;
        }
        pointer ptr = allocate(sz);
        pointer old_first = first_;
        pointer old_last = last_;
        size_type old_capacity = capacity();

        first_ = ptr;
        last_ = first_;
        reserved_last_ = first_ + sz;

        for (pointer old_iter = old_first; old_iter != old_last;
             ++old_iter, ++last_) {
            construct(last_, *old_iter);
        }

        for (reverse_iterator riter = reverse_iterator(old_last),
                              rend = reverse_iterator(old_first);
             riter != rend; ++riter) {
            destroy(&*riter);
        }
        alloc_.deallocate(old_first, old_capacity);
    }
    size_type capacity() const { return reserved_last_ - first_; }

    // Modifiers
    void clear() { destroy_until(rend()); }

    // https://cplusplus.com/reference/vector/vector/insert/
    iterator insert(iterator position, const value_type &val) {
        insert(position, 1, val);
        return position;
    }

    void insert(iterator position, size_type n, const value_type &val) {
        if (n == 0) return;
        difference_type pos_diff = std::distance(begin(), position);
        size_type new_size = size() + n;
        if (new_size > capacity()) reserve(recommend(new_size));
        iterator new_position = begin() + pos_diff;
        while (size() < new_size) {
            construct(last_++);
        }
        std::copy_backward(new_position, last_ - n, last_);
        std::fill(new_position, new_position + n, val);
        return;
    }

    // https://github.dev/llvm/llvm-project/blob/main/libcxx/include/vector
    template <class InputIterator>
    typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
    insert(iterator position, InputIterator f, InputIterator l) {
        difference_type pos_diff = position - begin();
        size_type n = l - f;
        size_type new_size = size() + n;
        if (new_size > capacity()) reserve(recommend(new_size));
        iterator new_position = begin() + pos_diff;
        while (size() < new_size) {
            construct(last_++);
        }
        std::copy_backward(new_position, last_ - n, last_);
        std::copy(f, l, new_position);
        return;
    }
    iterator erase(iterator pos) { return erase(pos, pos + 1); }
    iterator erase(iterator f, iterator l) {
        size_type erase_size = l - f;
        pointer new_last = last_ - erase_size;
        std::copy(l, last_, f);
        for (iterator it = new_last; it != last_; ++it) {
            destroy(it);
        }
        last_ = new_last;
        return f;
    }

    void push_back(const_reference value) {
        if (size() + 1 > capacity()) {
            reserve(recommend(size() + 1));
        }
        construct(last_++, value);
    }
    void pop_back() { erase(end() - 1); }

    void resize(size_type count, T value = T()) {
        if (count < size()) {
            size_type diff = size() - count;
            destroy_until(rbegin() + diff);
            last_ = first_ + count;
        } else if (count > size()) {
            reserve(recommend(count));
            for (; size() < count; ++last_) {
                construct(last_, value);
            }
        }
    }

    void swap(vector &other) {
        pointer tmp_first = other.first_;
        pointer tmp_last = other.last_;
        pointer tmp_reserved_last = other.reserved_last_;

        other.first_ = first_;
        other.last_ = last_;
        other.reserved_last_ = reserved_last_;
        first_ = tmp_first;
        last_ = tmp_last;
        reserved_last_ = tmp_reserved_last;
    }
    /************************
     * Non-Member functions *
     ************************/

 private:
    // 先頭の要素へのポインター
    pointer first_;
    // 最後の要素の1つ前方のポインター
    pointer last_;
    // 確保したストレージの終端
    pointer reserved_last_;
    // アロケーターの値
    allocator_type alloc_;

    typedef std::allocator_traits<allocator_type> traits;

    pointer allocate(size_type n) { return traits::allocate(alloc_, n); }
    void deallocate() { traits::deallocate(alloc_, first_, capacity()); }
    void construct(pointer ptr) { traits::construct(alloc_, ptr); }
    void construct(pointer ptr, const_reference value) {
        traits::construct(alloc_, ptr, value);
    }
    void destroy(pointer ptr) { traits::destroy(alloc_, ptr); }
    void destroy_until(reverse_iterator rend) {
        for (reverse_iterator riter = rbegin(); riter != rend;
             ++riter, --last_) {
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
bool operator==(const ft::vector<T, Allocator> &lhs,
                const ft::vector<T, Allocator> &rhs) {
    return (lhs.size() == rhs.size() &&
            ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Allocator>
bool operator!=(const ft::vector<T, Allocator> &lhs,
                const ft::vector<T, Allocator> &rhs) {
    return (!(lhs == rhs));
}

template <class T, class Allocator>
bool operator<(const ft::vector<T, Allocator> &lhs,
               const ft::vector<T, Allocator> &rhs) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
                                        rhs.end()));
}

template <class T, class Allocator>
bool operator<=(const ft::vector<T, Allocator> &lhs,
                const ft::vector<T, Allocator> &rhs) {
    return (!(lhs > rhs));
}

template <class T, class Allocator>
bool operator>(const ft::vector<T, Allocator> &lhs,
               const ft::vector<T, Allocator> &rhs) {
    return (rhs < lhs);
}

template <class T, class Allocator>
bool operator>=(const ft::vector<T, Allocator> &lhs,
                const ft::vector<T, Allocator> &rhs) {
    return (!(lhs < rhs));
}

template <class T, class Allocator>
void swap(ft::vector<T, Allocator> &lhs, ft::vector<T, Allocator> &rhs) {
    lhs.swap(rhs);
}
}  // namespace ft

#endif  // INCLUDE_VECTOR_HPP_
