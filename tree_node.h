#ifndef TREE_NODE_H
#define TREE_NODE_H

#pragma once
#include <iostream>
#include <stdint.h>

// Implementation of a 2-ary Node.
template <typename T> class tree_node {
    private:
        int64_t node_depth = 0;
        T v;
        tree_node<T> *left_node, *right_node, *parent_node;
        bool node_right = true;
    public:
        tree_node(T value = 0, tree_node<T>* l = nullptr, tree_node<T>* r = nullptr, int64_t d = 0);

        ~tree_node() {}

        void value(T v);
        T value() const;

        void right(tree_node<T>* right, bool set_parent = true);
        tree_node<T>* right() const;

        void left(tree_node<T>* left, bool set_parent = true);
        tree_node<T>* left() const;

        void parent(tree_node<T>* parent);
        tree_node<T>* parent() const;

        void depth(int64_t d);
        int64_t depth() const;
        int64_t children() const;

        void is_right_node(bool right);
        bool is_right_node() const;

        bool operator==(tree_node<T> node) const;
        bool operator==(tree_node<T>* node) const;

        void isolate();

        template <typename U> 
        friend std::ostream& operator<<(std::ostream& out, const tree_node<T>& n);

};

template <typename T> tree_node<T>::tree_node(T value, 
                                              tree_node<T>* l, 
                                              tree_node<T>* r, 
                                              int64_t d) : v(value), node_depth(d) {
    this->left(l, true);
    this->right(r, true);
}

template <typename T> void tree_node<T>::value(T new_value) { 
    this->v = new_value;
}

template <typename T> T tree_node<T>::value() const {
    return this->v;
}

template <typename T> void tree_node<T>::right(tree_node<T>* right, bool set_parent) {
    this->right_node = right;

    if (this->right_node != nullptr) {
        this->right_node->is_right_node(true);
        if (set_parent) this->right_node->parent(this);
    }
}

template <typename T> tree_node<T>* tree_node<T>::right() const {
    return this->right_node;
}

template <typename T> void tree_node<T>::left(tree_node<T>* left, bool set_parent) {
    this->left_node = left;

    if (this->left_node != nullptr) {
        this->left_node->is_right_node(false);
        if (set_parent) this->left_node->parent(this);
    }
}

template <typename T> tree_node<T>* tree_node<T>::left() const {
    return this->left_node;
}

template <typename T> void tree_node<T>::parent(tree_node<T>* parent) {
    this->parent_node = parent;

    if (this->parent_node != nullptr) {
        this->depth(this->parent_node->depth() + 1);
    }
}

template <typename T> tree_node<T>* tree_node<T>::parent() const {
    return this->parent_node;
}

template <typename T> void tree_node<T>::depth(int64_t d) {
    this->node_depth = d;
}

template <typename T> int64_t tree_node<T>::depth() const {
    return this->node_depth;
}

template <typename T> int64_t tree_node<T>::children() const {
    return ((this->right() != nullptr) + (this->left() != nullptr));
}

template <typename T> void tree_node<T>::is_right_node(bool right) {
    this->node_right = right;
}

template <typename T> bool tree_node<T>::is_right_node() const {
    return this->node_right;
}

template <typename T> void tree_node<T>::isolate() {
    this->right_node = this->left_node = this->parent_node = nullptr;
}

template <typename T> bool tree_node<T>::operator==(tree_node<T> node) const {
    return (this->value == node.value());
}

template <typename T> bool tree_node<T>::operator==(tree_node<T>* node) const {
    return (node == nullptr ? 0 : this->value() == node->value());
}

template <typename T> tree_node<T>* minimum(tree_node<T>* node) {
    tree_node<T>* current = node;

    while (current->left() != nullptr) 
        current = current->left();

    return current;
}

template <typename T> tree_node<T>* inorder_successor(tree_node<T>* node) {
    if (node->right() != nullptr)
        return minimum(node->right());

    tree_node<T>  *parent = node->parent(),
                  *current = node;

    while (parent != nullptr && is_right_node(current)) {
        node = parent;
        parent = parent->parent();
    }

    return parent;
}

template <typename T> void swap(tree_node<T>* first, tree_node<T>* second) {
    T tmp = first->value();
    first->value(second->value());
    second->value(tmp);
}

template <typename T> std::ostream& operator<<(std::ostream& out, const tree_node<T>& n) {
    out << "<" << n.value() << ">";
    return out;
}

template <typename T> std::ostream& operator<<(std::ostream& out, const tree_node<T>* n) {
    out << *n;
    return out;
}

#endif
