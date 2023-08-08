#ifndef RB_TREE_H
#define RB_TREE_H

#pragma once
#include "deque.h"
#include "rb_node.h"
#include <stdint.h>

template <typename K, typename V> class rb_tree {
    private:
        int64_t tree_size;
        rb_node<K,V> *tree_root;

        void rotate(rb_node<K,V>* node, bool right);
        void maintain_properties_insertion(rb_node<K,V>* node);
        void maintain_properties_deletion(rb_node<K,V>* node);

        void replace_node_child(rb_node<K,V>* P, rb_node<K,V>* O, rb_node<K,V>* N);
        rb_node<K,V>* non_double_removal(rb_node<K,V>* node);
    public:
        rb_tree(rb_node<K,V>* root = nullptr);

        ~rb_tree() {}

        void insert(K key, V value);
        void insert(rb_node<K, V>* node);

        void remove(K key);
        void remove(rb_node<K,V>* node);

        V get(K key) const;
        rb_node<K,V>* search(K key) const;
        rb_node<K,V>* root() const;

        int64_t size() const;
};

template <typename K, typename V> void rb_tree<K,V>::maintain_properties_insertion(rb_node<K,V>* node) {
    rb_node<K,V> *P = node->parent(), 
                 *U = node->uncle(), 
                 *G = node->grandparent();

    if (node_color(P) == BLACK)
        return;

    // case 2: red parent, parent == root.
    if (node_color(P) == RED && P == this->tree_root) {
        P->color(BLACK); 
    // case 3: red parent, and red uncle
    } else if (node_color(P) == RED && node_color(U) == RED) {
        // recolor parent & uncle red
        // recolor grandparent black
        // call maintain properties recursively on grandparent node
        P->color(BLACK);
        U->color(BLACK);
        G->color(RED);

        this->maintain_properties_insertion(G);
    } else if (node->is_right_node() != P->is_right_node()) {
        bool nrc = node->is_right_node(), prc = P->is_right_node();

        this->rotate(P, prc);
        this->rotate(G, !prc);

        node->color(BLACK);
        G->color(RED);
    } else if (node_color(U) == BLACK && node_color(P) == RED &&
               node->is_right_node() == P->is_right_node()) {
        this->rotate(G, !node->is_right_node());
        P->color(BLACK);
        G->color(RED);
    }
}

template <typename K, typename V> void rb_tree<K,V>::maintain_properties_deletion(rb_node<K,V>* node) {
    if (node == this->tree_root) {
        node->color(BLACK);
        return;
    } 

    rb_node<K,V>* sibling = node->sibling();

    if (node_color(sibling) == RED) {
        sibling->color(BLACK);
        node->parent()->color(RED);

        this->rotate(node->parent(), node->is_right_node());
        sibling = node->sibling();
    }

    if (node_color(sibling->right()) == BLACK && 
        node_color(sibling->left()) == BLACK) {
        sibling->color(RED);
    
        if (node_color(node->parent()) == RED) {
            node->parent()->color(BLACK);
        } else {
            maintain_properties_deletion(node->parent());
        }
    } else {
        int D = node->is_right_node();

        if (node_color(sibling->child(1-D)) == BLACK) {
            sibling->color(RED);
            sibling->child(D)->color(BLACK);
            rotate(sibling, 1-D);
            sibling = node->parent()->child(1-D);
        }

        sibling->color(node->parent()->color());
        node->parent()->color(BLACK);

        sibling->child(1-D)->color(BLACK);
        rotate(node->parent(), D);
    }
}

template <typename K, typename V> void rb_tree<K,V>::rotate(rb_node<K,V>* N, bool dir) {
    int D = static_cast<int>(dir);

    rb_node<K,V> *G = N->parent(),
                 *Y = N->child(1-D),
                 *C;

    if (Y == nullptr)
        return;

    C = Y->child(D);
    N->child(C, 1-D);

    if (C != nullptr)
        C->parent(N);

    Y->child(N, dir);
    N->parent(Y);
    Y->parent(G);

    if (G == nullptr) { this->tree_root = Y; }
    else { G->child(Y, N == G->right() ? 1 : 0); }
}

template <typename K, typename V> void rb_tree<K,V>::replace_node_child(rb_node<K,V>* P,
                                                                        rb_node<K,V>* O,
                                                                        rb_node<K,V>* N) {
    if (O == nullptr)
        return;

    bool right = (O->is_right_node());

    if (P == nullptr) 
        this->tree_root = N;
    else if (right) 
        P->right(N);
    else 
        P->left(N);
    
    if (N != nullptr)
        N->parent(P);

    O->isolate();
}

template <typename K, typename V> rb_node<K,V>* rb_tree<K,V>::non_double_removal(rb_node<K,V>* node) {
    if (node == nullptr)
        return nullptr;

    rb_node<K,V>* moved = (node->right() != nullptr ? node->right() :
                           node->left() != nullptr ? node->left() : nullptr);

    this->replace_node_child(node->parent(), node, moved);

    return moved;
}

template <typename K, typename V> rb_tree<K,V>::rb_tree(rb_node<K,V>* root) : tree_root(root),
                                                                              tree_size(0) {
    if (tree_root != nullptr) 
        ++this->tree_size;                                                   
}

template <typename K, typename V> void rb_tree<K,V>::insert(rb_node<K,V>* node) {
    if (node == nullptr)
        return;

    node->color(this->tree_root == nullptr ? BLACK : RED);

    if (this->tree_root == nullptr) {
        this->tree_root = node;
        return;
    }

    // Standard BST insertion
    rb_node<K,V>* parent = this->tree_root;

    while (true) {
        bool direction = (parent->key() <= node->key());


        if ((direction && parent->right() == nullptr) ||
            (!direction && parent->left() == nullptr)) {

            (direction ? parent->right(node) : parent->left(node));
            break;
        }

        parent = (direction ? parent->right() : parent->left());
    }

    node->parent(parent);

    this->maintain_properties_insertion(node);

    ++this->tree_size;
}

template <typename K, typename V> void rb_tree<K,V>::insert(K key, V value) {
    rb_node<K,V>* s = this->search(key);

    if (s == nullptr)
        this->insert(new rb_node<K,V>(key, value));
    else 
        s->value(value);
}

template <typename K, typename V> void rb_tree<K,V>::remove(rb_node<K,V>* node) {
    if (node == nullptr)
        return;

    rb_node<K,V> *moved_node = nullptr;
    rb_color_t deleted_color;

    if (node->children() <= 1) {
        deleted_color = node_color(node);
        moved_node = this->non_double_removal(node);
    } else {
        rb_node<K,V>* successor = inorder_successor(node);
        swap(successor, node);

        deleted_color = node_color(successor);
        moved_node = this->non_double_removal(successor);
    }

    if (deleted_color == BLACK) {
        this->maintain_properties_deletion(moved_node);
    }

    --this->tree_size;
}

template <typename K, typename V> void rb_tree<K,V>::remove(K key) {
    rb_node<K,V>* node = this->search(key);

    if (node == nullptr)
        return;

    this->remove(node);
}

template <typename K, typename V> V rb_tree<K,V>::get(K key) const {
    rb_node<K,V> *node = this->search(key);

    assert(node != nullptr);

    return (node->value());
}

template <typename K, typename V> rb_node<K,V>* rb_tree<K,V>::search(K key) const {
    rb_node<K,V>* current = this->tree_root;

    while (current != nullptr && current->key() != key) {
        bool R = (current->key() <= key);

        current = (R ? current->right() : current->left());
    }

    return current;
}

template <typename K, typename V> rb_node<K,V>* rb_tree<K,V>::root() const {
    return this->tree_root;
}

template <typename K, typename V> int64_t rb_tree<K,V>::size() const {
    return this->tree_size;
}

template <typename K, typename V> std::ostream& operator<<(std::ostream& out, const rb_tree<K,V> tree) {
    deque<rb_node<K,V>*> q;

    if (tree.root() != nullptr) q.push_back(tree.root());

    while (!q.is_empty()) {
        rb_node<K,V>* node = q.pop_front();

        out << *node;

        if (node->left() != nullptr) q.push_back(node->left());
        if (node->right() != nullptr) q.push_back(node->right());
    }

    return out;
}

template <typename K, typename V> std::ostream& operator<<(std::ostream& out, rb_tree<K,V>* tree) {
    return out << *tree;
}

#endif
