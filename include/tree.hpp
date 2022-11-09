#ifndef INCLUDE_TREE_HPP_
#define INCLUDE_TREE_HPP_

#include <iostream>

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

    // typedef Key key_type;
    // typedef T mapped_type;
    // typedef ft::pair<const Key, T> value_type;

    value_type value;
    node* left_child;
    node* right_child;
    node* parent;
    int hight;

    node()
        : value(value_type()),
          left_child(NULL),
          right_child(NULL),
          parent(NULL),
          hight(-1){};

    node(Key k, T v)
        : value(value_type(k, v)),
          left_child(NULL),
          right_child(NULL),
          parent(NULL),
          hight(-1){};

    node& operator=(const node& other) {
        this->value = other.value;
        this->left_child = other.left_child;
        this->right_child = other.right_child;
        this->parent = other.parent;
        this->hight = other.hight;
        return *this;
    }

    Key get_key() const { return this->value.first; }
    value_type get_value() const { return this->value; }

    size_t get_size() {
        size_t size = 1;
        if (this->left_child) size += left_child->get_size();
        if (this->right_child) size += right_child->get_size();
        return size;
    }
    int get_hight() {
        this->update_hight();
        return hight;
    }

    void update_hight() {
        size_t left_height = this->left_child ? left_child->get_hight() : 0;
        size_t right_height = this->right_child ? right_child->get_hight() : 0;
        hight = 1 + std::max(left_height, right_height);
    }

    int factor() const {
        size_t left_height = left_child ? left_child->get_hight() : 0;
        size_t right_height = right_child ? right_child->get_hight() : 0;
        return (right_height - left_height);
    }

    bool is_balanced() { return -1 <= factor() && factor() <= 1; }

    node* get_root_node() {
        node* cur = this;
        while (cur->parent != NULL) cur = cur->parent;
        return cur;
    }

    node* get_left() { return left_child; }
    node* get_right() { return right_child; }
    node* get_parent() { return parent; }

    void set_left(node* x) {
        left_child = x;
        if (x) x->parent = this;
    }
    void set_right(node* x) {
        right_child = x;
        if (x) x->parent = this;
    }

    void set_child(node* x, bool is_left) {
        if (is_left)
            this->set_left(x);
        else
            this->set_right(x);
    }

    void set_parent(node* x) { parent = x; }

    bool has_parent() const { return parent != NULL; }
    bool is_left() const {
        return (has_parent() && this == parent->left_child);
    }
    bool is_right() const {
        return (has_parent() && this == parent->right_child);
    }

    node* rotate_left() {
        assert(this->right_child);

        node* r = this->right_child;
        node* m = r->left_child;
        node* p = this->parent;

        r->parent = NULL;
        if (p) parent->set_child(r, this->is_left());

        this->set_right(m);
        if (r) r->set_left(this);

        this->update_hight();
        if (r) r->update_hight();
        if (p) p->update_hight();
        return r;
    }

    node* rotate_right() {
        node* l = this->left_child;
        node* m = l->right_child;
        node* p = this->parent;

        l->parent = NULL;
        if (p) parent->set_child(l, this->is_left());

        this->set_left(m);
        if (l) l->set_right(this);

        this->update_hight();
        if (l) l->update_hight();
        if (p) p->update_hight();
        return l;
    }

    node* get_min_node() {
        node* cur = this;
        while (cur->left_child) {
            cur = cur->left_child;
        }
        return cur;
    }

    node* get_max_node() {
        node* cur = this;
        while (cur->right_child) {
            cur = cur->right_child;
        }
        return cur;
    }

    node* get_next_node() {
        if (this->right_child) {
            return (this->right_child->get_min_node());
        } else {
            node* cur = this;
            while (cur->is_right()) {
                cur = cur->parent;
            }
            return cur->parent;
        }
    }

    node* get_prev_node() {
        if (this->left) {
            return (this->left->get_max_node());
        } else {
            node* cur = this;
            while (cur->is_left()) {
                cur = cur->parent;
            }
            return cur->parent;
        }
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
        print(this->value);
        if (this->left_child) {
            print_arrow(this->value, this->left_child->value, ARROW_LEFT_SIDE);
            this->left_child->print_node();
        }
        if (this->right_child) {
            print_arrow(this->value, this->right_child->value,
                        ARROW_RIGHT_SIDE);
            this->right_child->print_node();
        }
    }
};

template <class value_type>
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
    typedef node<value_type>* node_ptr;

 private:
    node_ptr current;

 public:
    node_ptr base() const { return current; }

    AVL_tree_iterator(node_ptr node) : current(node) {}

    /********************
     * LegacyIterator   *
     ********************/

    // CopyConstructible
    template <class Iter>
    AVL_tree_iterator(const AVL_tree_iterator<Iter>& other) : current(NULL) {
        *this = other;
    }

    // CopyAssignable
    template <class Iter>
    AVL_tree_iterator& operator=(const AVL_tree_iterator<Iter>& other) {
        current = other.base();
        return *this;
    }
    // Destructible
    ~AVL_tree_iterator() {}

    // Swappable

    // dereferenceable
    reference operator*() const { return (current->value); }

    // incrementable
    AVL_tree_iterator& operator++() {
        current = current->get_next_node();
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

    pointer operator->() const { return &(current->value); }

    /************************
     * LegacyForwardIterator*
     ************************/

    // DefaultConstructible
    AVL_tree_iterator() : current(NULL) {}

    // Multipass guarantee
    // trivial: nothing todo.

    // Equality and inequality comparison\
    // describe in Non-member functions.

    /******************************
     * LegacyBidirectionalIterator*
     ******************************/
    // decrementable
    AVL_tree_iterator& operator--() {
        current = current->get_prev_node();
        return *this;
    }
    AVL_tree_iterator operator--(int) {
        AVL_tree_iterator tmp(*this);
        --(*this);
        return tmp;
    }
};

// Non-member functions
template <class Iter11, class Iter21>
bool operator==(const ft::AVL_tree_iterator<Iter11>& lhs,
                const ft::AVL_tree_iterator<Iter21>& rhs) {
    return lhs.base() == rhs.base();
}
template <class Iter11, class Iter21>
bool operator!=(const ft::AVL_tree_iterator<Iter11>& lhs,
                const ft::AVL_tree_iterator<Iter21>& rhs) {
    return lhs.base() != rhs.base();
}

template <class value_type>
class AVL_tree {
 public:
    typedef typename value_type::first_type Key;
    typedef typename value_type::second_type T;

    typedef node<value_type>* node_ptr;
    typedef AVL_tree_iterator<value_type> iterator;
    typedef std::size_t size_type;

    node_ptr root;

    AVL_tree() : root(NULL){};
    AVL_tree(value_type x) : root(new node<value_type>(x)){};
    AVL_tree(Key k, T v) : root(new node<value_type>(k, v)){};

    node_ptr search_parent(Key x) {
        if (root == NULL) return NULL;
        node_ptr cur = root;
        while (1) {
            if (x < cur->get_key()) {
                if (cur->left_child == NULL) return cur;
                cur = cur->left_child;
            } else {
                if (cur->right_child == NULL) return cur;
                cur = cur->right_child;
            }
        }
    }
    size_type size() const { return root->get_size(); };

    void balance(node_ptr node) {
        if (node == NULL) return;
        if (!node->is_balanced()) {
            if (node->factor() > 0) {
                if (node->right_child->factor() < 0) {
                    node->right_child->rotate_right();
                }
                node->rotate_left();
            } else {
                if (node->left_child->factor() > 0) {
                    node->left_child->rotate_left();
                }
                node->rotate_right();
            }
        }

        balance(node->parent);
    }

    node_ptr find(Key x) {
        node_ptr cur = root;
        while (1) {
            if (cur == NULL) return NULL;
            if (cur->get_key() == x) return cur;
            if (x < cur->get_key()) {
                cur = cur->left_child;
            } else {
                cur = cur->right_child;
            }
        }
    }

    void print_nodeinfo(node_ptr tar) {
        std::cout << "tar:" << tar->value << std::endl;
        std::cout << "tar->parent:" << tar->parent->value << std::endl;
        std::cout << "tar->left_child:" << tar->left_child->value << std::endl;
        std::cout << "tar->right_child:" << tar->right_child->value
                  << std::endl;
    }

    bool remove(Key x) {
        node_ptr tar = find(x);
        if (tar == NULL) return false;
        if (tar->left_child == NULL) {
            if (tar->has_parent()) {
                if (tar->is_left()) {
                    tar->parent->set_left(tar->right_child);
                } else {
                    tar->parent->set_right(tar->right_child);
                }
            }
            if (tar->right_child) {
                tar->right_child->parent = tar->parent;
                balance(tar->right_child);
                root = tar->right_child->get_root_node();
            }
            if (tar->has_parent()) {
                balance(tar->parent);
                root = tar->parent->get_root_node();
            }
            delete tar;

        } else {
            node_ptr replace_node = tar->left_child->get_max_node();
            if (replace_node->has_parent()) {
                if (replace_node->is_left()) {
                    replace_node->parent->set_left(NULL);
                } else {
                    replace_node->parent->set_right(NULL);
                }
            }
            replace_node->parent = NULL;
            if (tar->has_parent()) {
                if (tar->is_left()) {
                    tar->parent->set_left(replace_node);
                } else {
                    tar->parent->set_right(replace_node);
                }
            }
            replace_node->set_left(tar->left_child);
            replace_node->set_right(tar->right_child);
            balance(replace_node);
            root = replace_node->get_root_node();

            delete tar;
        }
        return true;
    }

    bool insert(Key key, T value) {
        if (find(key)) return false;
        node_ptr new_parent = search_parent(key);
        node_ptr new_node = new node<ft::pair<const Key, T> >(key, value);
        if (new_parent == NULL) {
            root = new_node;
            return true;
        }
        if (key < new_parent->get_key()) {
            new_parent->set_left(new_node);
        } else {
            new_parent->set_right(new_node);
        }
        balance(new_node);
        root = new_node->get_root_node();
        return true;
    }

    bool insert(const value_type& v) { return insert(v.first, v.second); }

    void print(std::string x) { std::cout << x << std::endl; }

    void print_tree() {
        print("-----------------");
        print("https://mermaid.live/edit");
        print("-----------------");
        print("```mermaid");
        print("graph TB;");
        root->print_node();
        print("```");
        print("-----------------");
    }

    iterator begin() { return iterator(root->get_min_node()); }
    iterator end() { return iterator(root->get_max_node()->get_next_node()); }
};

}  // namespace ft

#endif  // INCLUDE_TREE_HPP_
