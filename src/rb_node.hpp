#ifndef RB_NODE_H
#define RB_NODE_H

#pragma once
#include <iostream>

#define node_color(N) ( N == nullptr ? BLACK : N->color() )

enum rb_color_t { BLACK, RED };

template <typename T> class rb_node {
    private:
        T v;
        rb_color_t c;
        rb_node<T> *left_node, *right_node, *parent_node;
    public:
        rb_node(T v,
                rb_node<T> *l = nullptr, 
                rb_node<T> *r = nullptr, 
                rb_node<T> *p = nullptr);

        ~rb_node() {}

        void value(T v);
        T value() const;

        void right(rb_node<T>* right);
        rb_node<T>* right() const;

        void left(rb_node<T>* left);
        rb_node<T>* left() const;

        void parent(rb_node<T>* parent);
        rb_node<T>* parent() const;

        void child(rb_node<T>* node, int D);
        rb_node<T>* child(int D) const;

        rb_node<T>* grandparent() const;
        rb_node<T>* sibling() const;
        rb_node<T>* uncle() const;

        bool is_right_node() const;

        bool operator==(rb_node<T> node) const;

        void color(rb_color_t c);
        rb_color_t color() const;

        void isolate();

        int children();

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const rb_node<T> node);
};

template <typename T> rb_node<T>::rb_node(T value,
                                          rb_node<T>* l,
                                          rb_node<T>* r,
                                          rb_node<T>* p) {
    this->v = value;
    this->left(l);
    this->right(r);
    this->parent(p);
}

template <typename T> void rb_node<T>::value(T v) { this->v = v; }
template <typename T> T rb_node<T>::value() const { return this->v; }

template <typename T> void rb_node<T>::right(rb_node<T>* right) {
    this->right_node = right;
}

template <typename T> rb_node<T>* rb_node<T>::right() const {
    return this->right_node;
}

template <typename T> void rb_node<T>::left(rb_node<T>* left) {
    this->left_node = left;
}

template <typename T> rb_node<T>* rb_node<T>::left() const {
    return this->left_node;
}

template <typename T> void rb_node<T>::parent(rb_node<T>* parent) {
    this->parent_node = parent;
}

template <typename T> rb_node<T>* rb_node<T>::parent() const {
    return this->parent_node;
}

template <typename T> bool rb_node<T>::is_right_node() const {
    return (this->parent_node == nullptr ? false : (this->parent()->right() == this));
}

template <typename T> rb_node<T>* rb_node<T>::grandparent() const {
    return (this->parent_node == nullptr ? nullptr : this->parent_node->parent());
}

template <typename T> rb_node<T>* rb_node<T>::sibling() const {
    return (this->parent_node == nullptr ? nullptr : 
            this->is_right_node() ? this->parent_node->left() : 
                                    this->parent_node->right());
}

template <typename T> rb_node<T>* rb_node<T>::uncle() const {
    return (this->parent_node == nullptr ? nullptr
                                         : this->parent_node->sibling());
}

template <typename T> void rb_node<T>::child(rb_node<T>* node, int D) {
    if (D) this->right_node = node;
    else this->left_node = node;
}

template <typename T> rb_node<T>* rb_node<T>::child(int D) const {
    return (D == 0 ? this->left_node : this->right_node);
}

template <typename T> bool rb_node<T>::operator==(rb_node<T> node) const {
    return (this->value() == node.value());
}

template <typename T> void rb_node<T>::color(rb_color_t c) { this->c = c; }
template <typename T> rb_color_t rb_node<T>::color() const { return this->c; }

template <typename T> void rb_node<T>::isolate() {
    this->parent_node = this->left_node = this->right_node = nullptr;
}

template <typename T> int rb_node<T>::children() {
    return ((this->left_node != nullptr) + (this->right_node != nullptr));
}

template <typename T> 
std::ostream& operator<<(std::ostream& out, const rb_node<T> node) {
    out << '<' << node.value() << ',' << (node.color() == BLACK ? 'B' : 'R') << '>';

    return out;
}

template <typename T> 
std::ostream& operator<<(std::ostream& out, const rb_node<T>* node) {
    return out << *node;
}

template <typename T> void swap(rb_node<T>* a, rb_node<T>* b) {
    T v = a->value();

    a->value(b->value());
    b->value(v);
}

template <typename T> rb_node<T>* minimum(rb_node<T>* node) {
    rb_node<T>* current = node;

    while (current->left() != nullptr) 
        current = current->left();
    
    return current;
}

template <typename T> rb_node<T>* inorder_successor(rb_node<T>* node) {
    if (node->right() != nullptr)
        return minimum(node->right());

    rb_node<T> *parent = node->parent(), 
               *current = node;

    while (parent != nullptr && current->is_right_node()) {
        node = parent;
        parent = parent->parent();
    }

    return parent;
}

#endif
