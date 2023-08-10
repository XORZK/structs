#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#pragma once
#include <iostream>
#include <stdint.h>
#include "deque.hpp"
#include "tree_node.hpp"
#include "MACROS.hpp"

template <typename T> class binary_tree {
    private:
        tree_node<T>* tree_root;
        int64_t tree_size;

        void update_depths();
    public:
        binary_tree(tree_node<T>* root = nullptr);

        ~binary_tree() {}

        void insert(T value);
        void insert(tree_node<T>* node);

        void remove(T value);
        void remove(tree_node<T>* node);

        tree_node<T>* search(T value) const;

        int64_t size() const;
        int64_t depth() const;

        T minimum() const;
        T maximum() const;

        tree_node<T>* root() const;

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, binary_tree<U>& tree);
};

template <typename T> void binary_tree<T>::update_depths() {
    deque<tree_node<T>*> q;

    if (this->tree_root != nullptr) {
        this->tree_root->depth(1);
        q.push_back(this->tree_root);
    }

    while (!q.is_empty()) {
        tree_node<T>* node = q.pop_front();

        int64_t children_depth = node->depth()+1;

        if (node->right() != nullptr) {
            node->right()->depth(children_depth);
            q.push_back(node->right());
        }

        if (node->left() != nullptr) {
            node->left()->depth(children_depth);
            q.push_back(node->left());
        }
    }
}

template <typename T> binary_tree<T>::binary_tree(tree_node<T>* root) : tree_root(root) {
    this->tree_size = 0;
    if (this->tree_root != nullptr) ++this->tree_size;
}

template <typename T> void binary_tree<T>::insert(tree_node<T>* node) {
    if (node == nullptr) return;

    if (this->tree_root == nullptr) this->tree_root = node;
    else {
        tree_node<T>* current = this->tree_root;

        while (true) {
            bool direction = (current->value() < node->value());

            if ((direction && current->right() == nullptr) ||
                (!direction && current->left() == nullptr)) {

                if (direction) {
                    current->right(node, true);
                } else {
                    current->left(node, true);
                }
                break;
            }

            current = (direction ? current->right() : current->left());
        }
    }

    ++this->tree_size;
}

template <typename T> void binary_tree<T>::insert(T value) {
    tree_node<T>* node = new tree_node<T>(value);
    this->insert(node);
}

// Assume the input node is a node contained within the Binary Tree.
template <typename T> void binary_tree<T>::remove(tree_node<T>* node) {
    if (node == nullptr) 
        return;

    int64_t count = node->children();
    bool right_node = node->is_right_node(),
         null_parent = (node->parent() == nullptr);

    if (count == 0) {
        if (!null_parent) {
            if (right_node) 
                node->parent()->right(nullptr);
            else 
                node->parent()->left(nullptr);
        }

        node->isolate();
        --this->tree_size;
    } else if (count == 1) {
        if (!null_parent) {
            tree_node<T>* C = (node->right() != nullptr ? node->right() : 
                                                          node->left());
            if (right_node)
                node->parent()->right(C);
            else 
                node->parent()->left(C);
        }

        node->isolate();
        --this->tree_size;
    } else {
        tree_node<T>* successor = inorder_successor(node);

        swap(successor, node);

        this->remove(successor);
    }
}

template <typename T> void binary_tree<T>::remove(T value) {
    this->remove(this->search(value));
}

// Values larger than or equal to the current value will be placed on the right.
template <typename T> tree_node<T>* binary_tree<T>::search(T value) const {
    if (this->tree_root == nullptr) return nullptr;

    tree_node<T>* current = this->tree_root;

    while (current != nullptr) {
        if (current->value() == value) return current;

        current = (current->value() < value) ? current->right() : current->left(); 
    }

    return nullptr;
}

template <typename T> int64_t binary_tree<T>::size() const {
    return this->tree_size;
}

template <typename T> int64_t max_depth(tree_node<T>* node) {
    if (node == nullptr) return -1;
    if (node != nullptr && node->children() == 0) return node->depth();

    if (node->right() != nullptr) node->right()->depth(node->depth()+1);
    if (node->left() != nullptr) node->left()->depth(node->depth()+1);

    return MAX(max_depth(node->right()), max_depth(node->left()));
}

template <typename T> int64_t binary_tree<T>::depth() const {
    int64_t max_depth = -1;
    deque<tree_node<T>*> q;

    this->update_depths();

    if (this->tree_root != nullptr) q.push_back(this->tree_root);

    while (!q.is_empty()) {
        tree_node<T>* node = q.pop_front();

        max_depth = MAX(max_depth, node->depth());

        if (node->right() != nullptr) q.push_back(node->right());
        if (node->left() != nullptr) q.push_back(node->left());
    }

    return max_depth;
}

template <typename T> T binary_tree<T>::maximum() const {
    if (this->tree_root == nullptr) return nullptr;

    tree_node<T>* node = this->tree_root;

    while (node->right() != nullptr) node = node->right();

    return node->value();
}

template <typename T> T binary_tree<T>::minimum() const {
    if (this->tree_root == nullptr) return nullptr;

    tree_node<T>* node = this->tree_root;

    while (node->left() != nullptr) node = node->left();

    return node->value();
}

template <typename T> tree_node<T>* binary_tree<T>::root() const {
    return this->tree_root;
}

// Standard BFS
template <typename T> std::ostream& operator<<(std::ostream& out, binary_tree<T>& tree) {
    deque<tree_node<T>*> q;

    if (tree.tree_root != nullptr) q.push_back(tree.tree_root);

    while (!q.is_empty()) {
        tree_node<T>* node = q.pop_front();

        out << *node;

        if (node->left() != nullptr) q.push_back(node->left());
        if (node->right() != nullptr) q.push_back(node->right());
    }

    return out;
}

template <typename T> std::ostream& operator<<(std::ostream& out, const binary_tree<T>* tree) {
    return out << *tree;
}

#endif
