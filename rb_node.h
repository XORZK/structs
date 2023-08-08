#ifndef RB_NODE_H
#define RB_NODE_H

#pragma once
#include <iostream>

#define node_color(N) ( N == nullptr ? BLACK : N->color() )

enum rb_color_t { BLACK, RED };

template <typename K, typename V> class rb_node {
    private:
        K k;
        V v;
        rb_color_t c;
        rb_node<K,V> *left_node, *right_node, *parent_node;
    public:
        rb_node(K key, 
                V value,
                rb_node<K, V> *l = nullptr, 
                rb_node<K, V> *r = nullptr, 
                rb_node<K, V> *p = nullptr);

        ~rb_node() {}

        void key(K v);
        K key() const;

        void value(V v);
        V value() const;

        void right(rb_node<K,V>* right);
        rb_node<K,V>* right() const;

        void left(rb_node<K,V>* left);
        rb_node<K,V>* left() const;

        void parent(rb_node<K,V>* parent);
        rb_node<K,V>* parent() const;

        void child(rb_node<K,V>* node, int D);
        rb_node<K,V>* child(int D) const;

        rb_node<K,V>* grandparent() const;
        rb_node<K,V>* sibling() const;
        rb_node<K,V>* uncle() const;

        bool is_right_node() const;

        bool operator==(rb_node<K,V> node) const;

        void color(rb_color_t c);
        rb_color_t color() const;

        void isolate();

        int children();

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const rb_node<K,V> node);
};

template <typename K, typename V> rb_node<K,V>::rb_node(K key, 
                                                        V value,
                                                        rb_node<K,V>* l,
                                                        rb_node<K,V>* r,
                                                        rb_node<K,V>* p) {
    this->k = key;
    this->v = value;
    this->left(l);
    this->right(r);
    this->parent(p);
}

template <typename K, typename V> void rb_node<K,V>::key(K v) { this->k = v; }
template <typename K, typename V> K rb_node<K,V>::key() const { return this->k; }

template <typename K, typename V> void rb_node<K,V>::value(V v) { this->v = v; }
template <typename K, typename V> V rb_node<K,V>::value() const { return this->v; }

template <typename K, typename V> void rb_node<K,V>::right(rb_node<K,V>* right) {
    this->right_node = right;
}

template <typename K, typename V> rb_node<K,V>* rb_node<K,V>::right() const {
    return this->right_node;
}

template <typename K, typename V> void rb_node<K,V>::left(rb_node<K,V>* left) {
    this->left_node = left;
}

template <typename K, typename V> rb_node<K,V>* rb_node<K,V>::left() const {
    return this->left_node;
}

template <typename K, typename V> void rb_node<K,V>::parent(rb_node<K,V>* parent) {
    this->parent_node = parent;
}

template <typename K, typename V> rb_node<K,V>* rb_node<K,V>::parent() const {
    return this->parent_node;
}

template <typename K, typename V> bool rb_node<K,V>::is_right_node() const {
    return (this->parent_node == nullptr ? false : (this->parent()->right() == this));
}

template <typename K, typename V> rb_node<K,V>* rb_node<K,V>::grandparent() const {
    return (this->parent_node == nullptr ? nullptr : this->parent_node->parent());
}

template <typename K, typename V> rb_node<K,V>* rb_node<K,V>::sibling() const {
    return (this->parent_node == nullptr ? nullptr : 
            this->is_right_node() ? this->parent_node->left() : 
                                    this->parent_node->right());
}

template <typename K, typename V> rb_node<K,V>* rb_node<K,V>::uncle() const {
    return (this->parent_node == nullptr ? nullptr
                                         : this->parent_node->sibling());
}

template <typename K, typename V> void rb_node<K,V>::child(rb_node<K,V>* node, int D) {
    if (D) this->right_node = node;
    else this->left_node = node;
}

template <typename K, typename V> rb_node<K,V>* rb_node<K,V>::child(int D) const {
    return (D == 0 ? this->left_node : this->right_node);
}

template <typename K, typename V> bool rb_node<K,V>::operator==(rb_node<K,V> node) const {
    return (this->key() == node.key() && this->value() == node.value());
}

template <typename K, typename V> void rb_node<K,V>::color(rb_color_t c) { this->c = c; }
template <typename K, typename V> rb_color_t rb_node<K,V>::color() const { return this->c; }

template <typename K, typename V> void rb_node<K,V>::isolate() {
    this->parent_node = this->left_node = this->right_node = nullptr;
}

template <typename K, typename V> int rb_node<K, V>::children() {
    return ((this->left_node != nullptr) + (this->right_node != nullptr));
}

template <typename K, typename V> 
std::ostream& operator<<(std::ostream& out, const rb_node<K,V> node) {
    out << '<' << node.key() << ':' << node.value() << ',' << (node.color() == BLACK ? 'B' : 'R') << '>';

    return out;
}

template <typename K, typename V> 
std::ostream& operator<<(std::ostream& out, const rb_node<K, V>* node) {
    return out << *node;
}

template <typename K, typename V> void swap(rb_node<K,V>* a, rb_node<K,V>* b) {
    K tk = a->key();
    V tv = a->value();

    a->key(b->key());
    b->key(tk);
    a->value(b->value());
    b->value(tv);
}

template <typename K, typename V> rb_node<K,V>* minimum(rb_node<K,V>* node) {
    rb_node<K,V>* current = node;

    while (current->left() != nullptr) 
        current = current->left();
    
    return current;
}

template <typename K, typename V> rb_node<K,V>* inorder_successor(rb_node<K,V>* node) {
    if (node->right() != nullptr)
        return minimum(node->right());

    rb_node<K,V> *parent = node->parent(), 
                 *current = node;

    while (parent != nullptr && current->is_right_node()) {
        node = parent;
        parent = parent->parent();
    }

    return parent;
}

#endif
