#ifndef _MAP_H
#define _MAP_H

#pragma once
#include "pair.hpp"
#include "rb_tree.hpp"

template <typename K, typename V> class map : public rb_tree<pair<K,V>> {
    public:
        void insert(K k, V v);
        void remove(K k);
        void remove(K k, V v);

        rb_node<pair<K,V>>* search(K k) const;
};

template <typename K, typename V> 
void map<K,V>::insert(K k, V v) {
    pair<K,V> p(k,v);
    rb_node<pair<K,V>> *s = rb_tree<pair<K,V>>::search(p);

    if (s == nullptr) {
        rb_node<pair<K,V>> *node = new rb_node<pair<K,V>>(p);
        rb_tree<pair<K,V>>::insert(node);
    } else {
        s->value(p);
    }
}

template <typename K, typename V> 
void map<K,V>::remove(K k) {
    rb_node<pair<K,V>> *node = this->search(k);

    if (node == nullptr) 
        return;

    rb_tree<pair<K,V>>::remove(node);
}


template <typename K, typename V> 
void map<K,V>::remove(K k, V v) {
    rb_node<pair<K,V>> *node = rb_tree<pair<K,V>>::search(k);

    if (node == nullptr)
        return;

    rb_tree<pair<K,V>>::remove(node);
}


template <typename K, typename V> 
rb_node<pair<K,V>>* map<K,V>::search(K k) const {
    rb_node<pair<K,V>> *current = rb_tree<pair<K,V>>::root();

    while (current != nullptr && current->value().key() != k) {
        bool direction = (current->value().key() <= k);

        current = (direction ? current->right() : current->left());
    }

    return current;
}

#endif
