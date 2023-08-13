#ifndef HEAP_H
#define HEAP_H

#pragma once
#include <assert.h>
#include "deque.hpp"
#include "list.hpp"
#include "tree_node.hpp"

// In a max heap, for any given node C, if P is 
// a parent node of C, then the key (value) of P 
// is greater than the key (value) of C: P > C

// This structure implements a binary heap
template <typename T> class max_heap {
    private:
        int64_t heap_size;
        tree_node<T>* heap_root;

        void downheap();
        tree_node<T>* navigate(list<bool> navigation) const;
        tree_node<T>* node_at_index(int64_t index) const;
    public:
        heap(tree_node<T>* root = nullptr);

        heap(list<T> init);

        ~heap() {};

        void insert(T value);
        void insert(tree_node<T>* node);

        T push_pop(T value);
        T push_pop(tree_node<T>* node);

        T pop();
        tree_node<T>* root() const;
        tree_node<T>* search(T value) const;
        void clear();

        int64_t size() const;
        int64_t depth() const;
        bool is_empty() const;

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, heap<U>& heap);
};

template <typename T> void heap<T>::downheap() {
    tree_node<T>* current = this->heap_root;

    while (current != nullptr) {
        bool right = (current->right() == nullptr || 
                      current->value() > current->right()->value());

        bool left = (current->left() == nullptr ||
                     current->value() > current->left()->value());

        if (left && right) break;

        bool rgtl = (current->right()->value() >= current->left()->value());

        if (rgtl) {
            swap(current, current->right());
            current = current->right();
        } else {
            swap(current, current->left());
            current = current->left();
        }
    }
}

template <typename T> tree_node<T>* heap<T>::navigate(list<bool> navigation) const {
    tree_node<T>* current = this->heap_root;
    navigation.pop_front();

    while (!navigation.is_empty()) {
        current = (navigation.pop_front() ? current->right() : current->left());
    }

    return current;
}

template <typename T> tree_node<T>* heap<T>::node_at_index(int64_t index) const {
    tree_node<T>* current = this->heap_root;

    list<bool> bin = dec_to_bin(++index);

    return this->navigate(bin);
}

template <typename T> heap<T>::heap(tree_node<T>* root) : heap_root(root) {
    this->heap_size = 0;
    if (this->heap_root != nullptr) this->heap_size++;
}

template <typename T> heap<T>::heap(list<T> init) {
    for (int64_t i = 0; i < init.size(); i++) {
        this->insert(init[i]);
    }
}

template <typename T> void heap<T>::insert(tree_node<T>* node) {
    ++this->heap_size;
    if (this->heap_root == nullptr) this->heap_root = node;
    else {
        list<bool> navigation = dec_to_bin(this->heap_size);
        bool R = navigation.pop_back();

        tree_node<T>* parent_node = this->navigate(navigation);

        if (R) parent_node->right(node);
        else parent_node->left(node);

        tree_node<T>* current = node;

        while (current->parent() != nullptr) {
            if (current->value() > current->parent()->value()) {
                swap(current, current->parent());
            }
            current = current->parent();
        }
    }
}

template <typename T> void heap<T>::insert(T value) {
    tree_node<T>* node = new tree_node<T>(value);
    this->insert(node);
}

template <typename T> T heap<T>::push_pop(tree_node<T>* node) {
    if (this->heap_root == nullptr || (node->value() >= this->heap_root->value())) {
        return node->value(); 
    }

    T value = this->heap_root->value();
    this->heap_root->value(node->value());
    this->downheap();

    return value;
}

template <typename T> T heap<T>::push_pop(T value) {
    tree_node<T>* node = new tree_node<T>(value);

    return this->push_pop(node);
}

template <typename T> T heap<T>::pop() {
    if (this->root == nullptr) return static_cast<T>(0);

    tree_node<T>* last_node = this->node_at_index(this->heap_size-1);

    T value = this->heap_root->value();

    swap(this->heap_root, last_node);

    this->last_node->isolate();

    this->downheap();

    return value;
}

template <typename T> tree_node<T>* heap<T>::root() const {
    return this->heap_root;
}

template <typename T> tree_node<T>* heap<T>::search(T value) const {
    deque<tree_node<T>*> q;

    if (this->heap_root != nullptr) q.push_back(this->heap_root);

    while (!q.empty()) {
        tree_node<T>* node = q.pop_front();

        if (node->value() == value) return node;

        if (node->right() != nullptr) q.push_back(node->right());
        if (node->left() != nullptr) q.push_back(node->left());
    }

    return nullptr;
}

template <typename T> void heap<T>::clear() {
    this->heap_root = nullptr;
}

template <typename T> int64_t heap<T>::size() const { return this->heap_size; }

template <typename T> int64_t heap<T>::depth() const {
    return log2(this->heap_size) + 1;
}

template <typename T> bool heap<T>::is_empty() const {
    return (this->heap_root == nullptr);
}

template <typename T> std::ostream& operator<<(std::ostream& out, heap<T>& heap) {
    deque<tree_node<T>*> q;

    if (heap.heap_root != nullptr) q.push_back(heap.heap_root);

    while (!q.is_empty()) {
        tree_node<T>* node = q.pop_front();

        out << *node;

        if (node->left() != nullptr) q.push_back(node->left());
        if (node->right() != nullptr) q.push_back(node->right());
    }

    return out;
}

template <typename T> std::ostream& operator<<(std::ostream& out, const heap<T>* heap) {
    return out << *heap;
}

#endif
