#ifndef INCLUDE_TREE_HPP_
#define INCLUDE_TREE_HPP_

#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "iterator.hpp"
#include "utility.hpp"

namespace ft {

#define ARROW_RIGHT_SIDE "==o"
#define ARROW_LEFT_SIDE "-->"

// https://tjkendev.github.io/procon-library/cpp/binary_search_tree/avl-tree.html
template <class value_type>
class node {
 public:
    typedef typename value_type::first_type const Key;
    typedef typename value_type::second_type T;

    value_type value_;
    Key key_;
    node* left_child_;
    node* right_child_;
    node* parent_;
    int hight_;
    int factor_;

    node()
        : value_(value_type()),
          key_(Key()),
          left_child_(NULL),
          right_child_(NULL),
          parent_(NULL),
          hight_(1),
          factor_(0) {}

    node(Key k, T v)
        : value_(value_type(k, v)),
          key_(k),
          left_child_(NULL),
          right_child_(NULL),
          parent_(NULL),
          hight_(1),
          factor_(0) {}

    explicit node(const value_type& v)
        : value_(v),
          key_(v.first),
          left_child_(NULL),
          right_child_(NULL),
          parent_(NULL),
          hight_(1),
          factor_(0) {}

    ~node() {}

    node& operator=(const node& other) {
        this->value_ = other.value_;
        this->key_ = other.key_;
        this->left_child_ = other.left_child_;
        this->right_child_ = other.right_child_;
        this->parent_ = other.parent_;
        this->hight_ = other.hight_;
        return *this;
    }

    Key get_key() const { return this->key_; }
    value_type get_value() const { return this->value_; }

    size_t get_size() const {
        size_t size = 1;
        if (this->left_child_) size += left_child_->get_size();
        if (this->right_child_) size += right_child_->get_size();
        return size;
    }

    void update_hight() {
        size_t left_height = this->left_child_ ? left_child_->hight_ : 0;
        size_t right_height = this->right_child_ ? right_child_->hight_ : 0;
        hight_ = 1 + std::max(left_height, right_height);
    }

    int get_factor() {
        size_t left_height = left_child_ ? left_child_->hight_ : 0;
        size_t right_height = right_child_ ? right_child_->hight_ : 0;
        factor_ = (right_height - left_height);
        return factor_;
    }

    node* get_left() const { return left_child_; }
    node* get_right() const { return right_child_; }
    node* get_parent() const { return parent_; }

    void set_left(node* x) {
        this->left_child_ = x;
        if (x) x->parent_ = this;
    }
    void set_right(node* x) {
        right_child_ = x;
        if (x) x->parent_ = this;
    }

    void set_child(node* x, const bool& is_left) {
        if (is_left)
            this->set_left(x);
        else
            this->set_right(x);
    }

    void set_parent(node* x) { parent_ = x; }

    bool has_parent() const { return parent_ != NULL; }
    bool is_left() const {
        return (has_parent() && this == parent_->left_child_);
    }
    bool is_right() const {
        return (has_parent() && this == parent_->right_child_);
    }

    node* rotate_left() {
        node* r = this->right_child_;
        node* m = r->left_child_;
        node* p = this->parent_;

        r->parent_ = NULL;
        if (p) parent_->set_child(r, this->is_left());

        this->set_right(m);
        if (r) r->set_left(this);

        this->update_hight();
        if (r) r->update_hight();
        if (p) p->update_hight();
        return r;
    }

    node* rotate_right() {
        node* l = this->left_child_;
        node* m = l->right_child_;
        node* p = this->parent_;

        l->parent_ = NULL;
        if (p) parent_->set_child(l, this->is_left());

        this->set_left(m);
        if (l) l->set_right(this);

        this->update_hight();
        if (l) l->update_hight();
        if (p) p->update_hight();
        return l;
    }

    node* get_min_node() {
        node* cur = this;
        while (cur->left_child_) {
            cur = cur->left_child_;
        }
        return cur;
    }

    node* get_max_node() {
        node* cur = this;
        while (cur->right_child_) {
            cur = cur->right_child_;
        }
        return cur;
    }

    node* get_next_node() {
        if (this->right_child_) {
            return (this->right_child_->get_min_node());
        }
        node* cur = this;
        while (cur->is_right()) {
            cur = cur->parent_;
        }
        return cur->parent_;
    }

    node* get_prev_node() {
        if (this->left_child_) {
            return (this->left_child_->get_max_node());
        }
        node* cur = this;
        while (cur->is_left()) {
            cur = cur->parent_;
        }
        return cur->parent_;
    }
    void print(value_type x) {
        std::cout << x.first << ":" << x.second << std::endl;
    }
    void print(std::string x) { std::cout << x << std::endl; }

    void print_arrow(value_type start, value_type end, std::string arrow) {
        std::cout << start.first << ":" << start.second << arrow << end.first
                  << ":" << end.second << std::endl;
    }

    void print_node() {
        print(this->get_value());
        if (this->left_child_) {
            print_arrow(this->get_value(), this->left_child_->get_value(),
                        ARROW_LEFT_SIDE);
            this->left_child_->print_node();
        }
        if (this->right_child_) {
            print_arrow(this->get_value(), this->right_child_->get_value(),
                        ARROW_RIGHT_SIDE);
            this->right_child_->print_node();
        }
    }
};

// Non-member functions
template <class value_type1, class value_type2>
bool operator==(const ft::node<value_type1>& lhs,
                const ft::node<value_type2>& rhs) {
    return lhs.get_value() == rhs.get_value();
}

template <class value_type1, class value_type2>
bool operator!=(const ft::node<value_type1>& lhs,
                const ft::node<value_type2>& rhs) {
    return lhs.get_value() != rhs.get_value();
}

template <class value_type, class Node>
struct AVL_tree_iterator
    : public ft::iterator<std::bidirectional_iterator_tag, value_type> {
 private:
    typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>
        base_iterator;

 public:  // member typedefs
    typedef typename base_iterator::iterator_category iterator_category;
    // typedef typename base_iterator::value_type value_type;
    typedef typename base_iterator::difference_type difference_type;
    typedef typename base_iterator::pointer pointer;
    typedef typename base_iterator::reference reference;

 private:
    typedef typename value_type::first_type Key;
    typedef typename value_type::second_type T;
    typedef Node node_type;
    // typedef node<value_type>* node_ptr;
    typedef node_type* node_ptr;

 private:
    node_ptr current_;

 public:
    node_ptr base() const { return current_; }

    explicit AVL_tree_iterator(node_ptr node) : current_(node) {}

    /********************
     * LegacyIterator   *
     ********************/

    // CopyConstructible
    template <class Iter, class N>
    AVL_tree_iterator(const AVL_tree_iterator<Iter, N>& other)
        : current_(NULL) {
        *this = other;
    }

    // CopyAssignable
    template <class Iter, class N>
    AVL_tree_iterator& operator=(const AVL_tree_iterator<Iter, N>& other) {
        current_ = reinterpret_cast<node_ptr>(other.base());
        return *this;
    }
    // Destructible
    ~AVL_tree_iterator() {}

    // Swappable

    // dereferenceable
    reference operator*() const { return (current_->value_); }

    // incrementable
    AVL_tree_iterator& operator++() {
        current_ = current_->get_next_node();
        return *this;
    }
    AVL_tree_iterator operator++(int) {
        AVL_tree_iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    /**********************
     * LegacyInputIterator*
     **********************/

    // EqualityComparable

    pointer operator->() const { return &(current_->value_); }

    /************************
     * LegacyForwardIterator*
     ************************/

    // DefaultConstructible
    AVL_tree_iterator() : current_(NULL) {}

    // Multipass guarantee
    // trivial: nothing todo.

    // Equality and inequality comparison
    // describe in Non-member functions.

    /******************************
     * LegacyBidirectionalIterator*
     ******************************/
    // decrementable
    AVL_tree_iterator& operator--() {
        current_ = current_->get_prev_node();
        return *this;
    }
    AVL_tree_iterator operator--(int) {
        AVL_tree_iterator tmp(*this);
        --(*this);
        return tmp;
    }
};

// Non-member functions
template <class Iter11, class Iter21, class Node1, class Node2>
bool operator==(const ft::AVL_tree_iterator<Iter11, Node1>& lhs,
                const ft::AVL_tree_iterator<Iter21, Node2>& rhs) {
    return (lhs.base()) == (rhs.base());
}
template <class Iter11, class Iter21, class Node1, class Node2>
bool operator!=(const ft::AVL_tree_iterator<Iter11, Node1>& lhs,
                const ft::AVL_tree_iterator<Iter21, Node2>& rhs) {
    return !(lhs == rhs);
}

template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class AVL_tree {
 public:
    typedef ft::pair<Key, T> value_type;
    typedef const value_type const_value_type;
    typedef node<value_type> node_type;
    typedef node<value_type>* node_ptr;

    typedef std::size_t size_type;

    typedef Allocator allocator_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename Allocator::pointer pointer;
    typedef typename Allocator::const_pointer const_pointer;
    typedef AVL_tree_iterator<value_type, node_type> iterator;
    typedef AVL_tree_iterator<const_value_type, node_type> const_iterator;
    typedef ft::reverse_iterator<iterator> reverse_iterator;
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    AVL_tree() : end_(create_node()) { set_root(NULL); }

    explicit AVL_tree(value_type v) : end_(create_node()) {
        set_root(create_node(v));
    }
    AVL_tree(Key k, T t) : end_(create_node()) { set_root(create_node(k, t)); }
    ~AVL_tree() {
        clear();
        delete_node(end_);
    }

    node_ptr create_node() { return create_node(value_type(Key(), T())); }

    node_ptr create_node(const Key k, T t) {
        return create_node(value_type(k, t));
    }

    node_ptr create_node(const value_type& val) {
        // 異なる型に対してのAllocatorの型を取得する方法
        // node用Allocatorの実態はallocを使用。
        // https://in-neuro.hatenablog.com/entry/2018/08/01/114441
        typedef typename Allocator::template rebind<node_type>::other
            node_allocator_type;
        node_allocator_type node_alloc = alloc;

        node_ptr new_node = node_alloc.allocate(1);
        node_alloc.construct(new_node, node_type(val));
        return new_node;
    }

    void delete_node(node_ptr node) {
        typedef typename Allocator::template rebind<node_type>::other
            node_allocator_type;
        node_allocator_type node_alloc = alloc;

        node_alloc.destroy(node);
        node_alloc.deallocate(node, 1);
    }

    size_type size() const {
        if (get_root() == NULL) return 0;
        return get_root()->get_size();
    }

    void balance(node_ptr node) {
        while (node != NULL) {
            if (node == end_) {
                set_root(end_->left_child_);
                return;
            }
            node->update_hight();
            int f = node->get_factor();
            if (f >= 2) {
                if (node->right_child_->get_factor() < 0) {
                    node->right_child_->rotate_right();
                }
                node->rotate_left();
                set_root(end_->left_child_);
                return;
            }
            if (f <= -2) {
                if (node->left_child_->get_factor() > 0) {
                    node->left_child_->rotate_left();
                }
                node->rotate_right();
                set_root(end_->left_child_);
                return;
            }
            if (node->parent_ == NULL) {
                break;
            }
            node = node->parent_;
        }
        set_root(node);
    }

    node_ptr find(Key x) {
        node_ptr cur = get_root();
        while (true) {
            if (cur == NULL) return NULL;
            Key k = cur->get_key();
            if (k == x) return cur;
            if (x < k) {
                cur = cur->left_child_;
            } else {
                cur = cur->right_child_;
            }
        }
    }

    bool remove(Key x) {
        node_ptr tar = find(x);
        if (tar == NULL) return false;
        node_ptr l = tar->left_child_;
        node_ptr r = tar->right_child_;
        node_ptr p = tar->parent_;
        if (l == NULL) {
            if (p) p->set_child(r, tar->is_left());
            if (r) {
                r->parent_ = p;
                balance(r);
            } else {
                balance(p);
            }
        } else {
            node_ptr replace_node = l->get_max_node();
            if (replace_node->has_parent()) {
                replace_node->parent_->set_child(NULL, replace_node->is_left());
            }
            if (p) p->set_child(replace_node, tar->is_left());
            replace_node->set_left(tar->left_child_);
            replace_node->set_right(r);
            replace_node->set_parent(p);
            balance(replace_node);
        }
        delete_node(tar);
        return true;
    }

    typedef ft::pair<iterator, bool> insert_ret_type;
    insert_ret_type insert(Key key, T value) {
        node_ptr f = find(key);
        if (f != NULL) return insert_ret_type(iterator(f), false);
        return __insert(search_parent(key), create_node(key, value));
    }

    insert_ret_type insert(const value_type& v) {
        node_ptr f = find(v.first);
        if (f != NULL) return insert_ret_type(iterator(f), false);
        return __insert(search_parent(v.first), create_node(v));
    }

 private:
    insert_ret_type __insert(node_ptr new_parent, node_ptr new_node) {
        if (new_parent == NULL) {
            set_root(new_node);
        } else {
            new_parent->set_child(new_node,
                                  new_node->get_key() < new_parent->get_key());
            balance(new_node);
        }
        return insert_ret_type(iterator(new_node), true);
    }

 public:
    void print_tree() {
        print("-----------------");
        print("https://mermaid.live/edit");
        print("-----------------");
        print("```mermaid");
        print("graph TB;");
        get_root()->print_node();
        print("```");
        print("-----------------");
    }

    iterator begin() {
        if (get_root() == NULL) return end();
        return iterator(get_root()->get_min_node());
    }
    iterator end() { return iterator(end_); }

    const_iterator begin() const {
        if (get_root() == NULL) return end();
        return const_iterator(get_root()->get_min_node());
    }
    const_iterator end() const { return const_iterator(end_); }

    reverse_iterator rbegin() {
        if (get_root() == NULL) return rend();
        return reverse_iterator(iterator(get_root()->get_max_node()));
    }
    reverse_iterator rend() { return reverse_iterator(end()); }

    reverse_iterator rbegin() const { return reverse_iterator(end()); }
    reverse_iterator rend() const { return reverse_iterator(begin()); }

    void clear() {
        iterator it = begin();
        while (it != end()) {
            Key key = it.base()->get_key();
            ++it;
            remove(key);
        }
    }

    node_ptr get_root() const { return root_; }

 private:
    node_ptr root_;
    // rootの親としてend用の擬似ノードを配置する。
    node_ptr end_;

    node_ptr set_root(node_ptr root) {
        root_ = root;
        end_->set_left(root);
        return root;
    }

    // アロケーターの値
    allocator_type alloc;

    pointer allocate(size_type n) { return allocator_type::allocate(alloc, n); }
    void deallocate(pointer p, size_type n) {
        allocator_type::deallocate(alloc, p, n);
    }
    void construct(pointer ptr) { allocator_type::construct(alloc, ptr); }
    void construct(pointer ptr, const_reference value) {
        allocator_type::construct(alloc, ptr, value);
    }
    void destroy(pointer ptr) { allocator_type::destroy(alloc, ptr); }
    void destroy_until(reverse_iterator rend) {
        for (reverse_iterator riter = rbegin(); riter != rend; ++riter) {
            destroy(&*riter);
        }
    }

    node_ptr search_parent(const Key& x) {
        node_ptr cur = get_root();
        if (cur == NULL) return NULL;
        while (true) {
            if (x < cur->get_key()) {
                if (cur->left_child_ == NULL) return cur;
                cur = cur->left_child_;
            } else {
                if (cur->right_child_ == NULL) return cur;
                cur = cur->right_child_;
            }
        }
    }

    void print(std::string x) { std::cout << x << std::endl; }
    void print_nodeinfo(node_ptr tar) {
        std::cout << "tar:" << tar->value << std::endl;
        std::cout << "tar->parent:" << tar->parent_->value << std::endl;
        std::cout << "tar->left_child_:" << tar->left_child_->value
                  << std::endl;
        std::cout << "tar->right_child_:" << tar->right_child_->value
                  << std::endl;
    }
};

}  // namespace ft

#endif  // INCLUDE_TREE_HPP_
