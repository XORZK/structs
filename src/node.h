#ifndef LINKED_NODE_H
#define LINKED_NODE_H

#pragma once
#include <iostream>

template <typename T> class linked_node {
    private:
        T v;
        linked_node<T> *next_node, *prev_node;
    public:
        linked_node() : v(0), next_node(nullptr), prev_node(nullptr) {}
        linked_node(T v) : v(v), next_node(nullptr), prev_node(nullptr) {}
        linked_node(T v, linked_node* n) : v(v), next_node(n), prev_node(nullptr) {}
        linked_node(T v, linked_node* n, linked_node* p) : v(v), next_node(n), prev_node(p){}

        ~linked_node() {}

        void value(T v);
        T value() const;

        void next(linked_node* n, bool set_prev = true);
        linked_node<T>* next() const;

        void prev(linked_node* p, bool set_next = true);
        linked_node<T>* prev() const;

        bool operator==(linked_node<T> node) const;
        bool operator==(linked_node<T>* node) const;

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const linked_node<U>& h);
};

template <typename T> void linked_node<T>::value(T new_value) { 
    this->v = new_value; 
}

template <typename T> T linked_node<T>::value() const { 
    return this->v; 
}

template <typename T> void linked_node<T>::next(linked_node* n, bool set_prev) {
    this->next_node = n; 
    if (this->next_node != nullptr && set_prev) { 
        this->next_node->prev(this, false); 
    }
}

template <typename T> linked_node<T>* linked_node<T>::next() const { 
    return this->next_node; 
}

template <typename T> void linked_node<T>::prev(linked_node* p, bool set_next) {
    this->prev_node = p;
    if (this->prev_node != nullptr && set_next) { 
        this->prev_node->next(this);
    }
}

template <typename T> linked_node<T>* linked_node<T>::prev() const {
    return this->prev_node;
}

template <typename T> bool linked_node<T>::operator==(linked_node<T> node) const {
    return (this->value() == node.value());
}

template <typename T> bool linked_node<T>::operator==(linked_node<T>* node) const {
    return (node == nullptr ? 0 : this->value() == node->value());
}

template <typename T> std::ostream& operator<<(std::ostream& out, const linked_node<T>& h) {
    out << "[" << h.value() << "]";
    return out;
}

template <typename T> std::ostream& operator<<(std::ostream& out, const linked_node<T>* h) {
    out << *h;
    return out;
}

template <typename T> inline void swap(linked_node<T>* first, linked_node<T>* second) {
    T tmp = first->value();

    first->value(second->value());
    second->value(tmp);
}

#endif
