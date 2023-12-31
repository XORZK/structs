#ifndef SET_H
#define SET_H

#pragma once
#include "pair.hpp"
#include "rb_tree.hpp"

template <typename T> class set : public rb_tree<T> {
    public:
        set(rb_node<T>* root = nullptr);

        set(set<T>& copy);

        ~set() {}

        set<T>& operator=(set<T> copy);
        set<T> operator+(set<T>& w);
        set<T> operator-(set<T>& w);
        set<T> operator-(T value);
        set<T> operator+(T value);

        template <typename K> set<pair<T,K>> operator*(set<K>& w);

        void insert(T value);
};

template <typename T> set<T>::set(rb_node<T>* root) : rb_tree<T>(root) {}

template <typename T> set<T>::set(set<T>& copy) {
    list<T> order = level_order_traversal(copy);

    while (!order.is_empty()) {
        this->insert(order.pop_front());
    }
}

template <typename T> void set<T>::insert(T value) {
    rb_node<T> *s = this->search(value),
               *n = new rb_node<T>(value);

    if (s == nullptr) 
        rb_tree<T>::insert(n);
}

template <typename T> set<T>& set<T>::operator=(set<T> copy) {
    if (this == &copy) 
        return *this;

    this->clear();

    list<T> order = level_order_traversal(copy);

    while (!order.is_empty()) {
        this->insert(order.pop_front());
    }

    return *this;
}

template <typename T> set<T> set<T>::operator+(set<T>& w) { 
    set<T> u = *this;

    list<T> order = level_order_traversal(w);

    while (!order.is_empty()) {
        u.insert(order.pop_front());
    }

    return order;
}

template <typename T> set<T> set<T>::operator-(set<T>& w) {
    set<T> d;

    list<T> first_order = inorder_traversal(*this),
            second_order = inorder_traversal(w);

    if (first_order.size() == 0 || second_order.size() == 0)
        return d;

    for (int64_t k = 0; k < first_order.size(); k++) {
        if (binary_search(second_order, first_order[k]) == -1) 
            d.insert(first_order[k]);
    }

    return d;
}

template <typename T> set<T> set<T>::operator-(T value) {
    set<T> d = *this;
    d.remove(value);
    return d;
}

template <typename T> set<T> set<T>::operator+(T value) {
    set<T> i = *this;
    i.insert(value);
    return i;
}

template <typename T> template <typename K>
set<pair<T,K>> set<T>::operator*(set<K>& w) { 
    set<pair<T,K>> p;

    list<T> first_order = inorder_traversal(*this);
    list<K> second_order = inorder_traversal(w);

    for (int64_t k = 0; k < first_order.size(); k++) {
        for (int64_t i = 0; i < second_order.size(); i++) {
            pair<T,K> t(first_order[k], second_order[i]);
            p.insert(t);
        }
    }

    return p;
}

template <typename T> set<T> set_union(set<T> w, set<T> v) { return (w + v); }

template <typename T> set<T> set_difference(set<T> w, set<T> v) { return (w - v); }

template <typename T, typename K> 
set<pair<T,K>> cartesian_set_product(set<T> w, set<K> v) { return (w * v); }

template <typename T> set<T> set_intersection(set<T> w, set<T> v) {
    set<T> i;

    list<T> first_order = inorder_traversal(w), 
            second_order = inorder_traversal(v);

    if (first_order.size() == 0 || second_order.size() == 0) 
        return i;

    for (int64_t k = 0; k < first_order.size(); k++) {
        if (binary_search(second_order, first_order[k]) != -1) {
            i.insert(first_order[k]);
        }
    }

    return i;
}

template <typename T> set<T> symmetric_difference(set<T> w, set<T> v) {
    return (w-v) + (v-w);
}

template <typename T> std::ostream& operator<<(std::ostream& out, set<T> s) {
    list<T> order = inorder_traversal(s);

    out << '{';

    for (int64_t k = 0; k < order.size(); k++) {
        out << order[k] << (k != order.size()-1 ? "," : "");
    }

    return out << '}';
}

#endif
