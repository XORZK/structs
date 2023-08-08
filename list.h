#ifndef LIST_H
#define LIST_H

#pragma once
#include "node.h"
#include <assert.h>
#include <stdint.h>

template <typename T> class list {
    private:
        int64_t s;
        linked_node<T> *head, *tail;
    public:
        list() : s(0), head(nullptr), tail(nullptr) {}
        list(linked_node<T> node) : s(1), head(&node), tail(&node) {}
        list(T value) : s(1) {
            linked_node<T> node(value);
            this->head = this->tail = &node;
        }

        ~list() {}

        void push_front(linked_node<T>* node);
        void push_front(T value);

        void push_back(linked_node<T>* node);
        void push_back(T value);

        void insert(int64_t idx, linked_node<T>* node);
        void insert(int64_t idx, T value);

        T pop_front();
        T pop_back();
        void remove(int64_t idx);
        void remove(T value);
        void clear();
        void resize(int64_t new_size);

        int64_t index(T data) const;
        int64_t size() const;
        bool is_empty() const;

        void reverse();
        void sort();
        list<T> merge(list<T> ll) const;

        linked_node<T>* front() const;
        linked_node<T>* back() const;
        linked_node<T> get(int64_t idx) const;
        linked_node<T>* get_ptr(int64_t idx) const;

        linked_node<T>* operator[](int64_t idx);

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const list<U>& l);
};

template <typename T> void list<T>::push_front(linked_node<T>* node) {
    if (this->is_empty()) {
        this->head = this->tail = node;
    } else {
        node->next(this->head);
        this->head = node;
    }
    ++this->s;
}

template <typename T> void list<T>::push_front(T value) {
    linked_node<T>* node = new linked_node<T>(node);
    this->push_front(node);
}

template <typename T> void list<T>::push_back(linked_node<T>* node) {
    if (this->is_empty()) {
        this->head = this->tail = node;
    } else {
        node->prev(this->tail);
        this->tail = node;
    }
    ++this->s;
}

template <typename T> void list<T>::push_back(T value) {
    linked_node<T>* node = new linked_node<T>(value);
    this->push_back(node);
}

template <typename T> void list<T>::insert(int64_t idx, linked_node<T>* node) {
    assert(idx >= 0 && idx < this->s);

    if (idx == 0) this->push_front(node);
    else if (idx == this->s-1) this->push_back(node);
    else {
        linked_node<T>* loc = this->get_ptr(idx);
        loc->prev()->next(node);
        loc->prev(node);
    }
    ++this->s;
}

template <typename T> void list<T>::insert(int64_t idx, T value) { 
    linked_node<T> node(value);
    this->insert(idx, node);
}

template <typename T> T list<T>::pop_front() {
    if (!this->is_empty()) {
        linked_node<T>* removed_front = this->head;
        this->head = this->head->next();
        if (--this->s == 0) {
            this->tail = nullptr;
        }

        return removed_front->value();
    }

    return static_cast<T>(0);
}

template <typename T> T list<T>::pop_back() {
    if (!this->is_empty()) {
        linked_node<T>* removed_back = this->tail;

        this->tail = this->tail->prev();
        this->tail->next(nullptr);

        if (--this->s == 0) {
            this->head = nullptr;
        }

        return removed_back->value();
    }

    return static_cast<T>(0);
}

template <typename T> void list<T>::remove(int64_t idx) {
    assert(idx >= 0 && idx < this->s);

    if (idx == 0) this->pop_front();
    else if (idx == this->s-1) this->pop_back();
    else {
        linked_node<T>* removed = this->get_ptr(idx);
        
        removed->prev()->next(removed->next());

        --this->s;
    }
}

template <typename T> void list<T>::remove(T value) {
    int64_t idx = this->index(value);
    if (idx == -1) return;
    else this->remove(idx);
}

template <typename T> void list<T>::clear() {
    this->head = this->tail = nullptr;
    this->s = 0;
}

template <typename T> void list<T>::resize(int64_t new_size) {
    if (new_size < this->s && new_size > 0) {
        linked_node<T>* new_tail = this->get_ptr(new_size-1);
        this->tail = new_tail;
        this->s = new_size;
    } else if (new_size == 0) {
        this->clear();
    }
}

template <typename T> int64_t list<T>::index(T data) const {
    int64_t idx = 0;
    linked_node<T> *ptr = this->head;

    while (ptr != nullptr) {
        if (ptr->value() == data) {
            return idx;
        }

        ptr = ptr->next();
        idx++;
    }

    return -1;
}

template <typename T> int64_t list<T>::size() const { return (this->s); } 

template <typename T> bool list<T>::is_empty() const { return (this->head == nullptr); }

template <typename T> linked_node<T>* list<T>::get_ptr(int64_t idx) const {
    assert(idx >= 0 && idx < this->s);
    linked_node<T> *ptr = this->head;

    for (int64_t k = 0; k < idx; k++) {
        ptr = (ptr->next());
    }

    return ptr;
}

template <typename T> linked_node<T>* list<T>::operator[](int64_t idx) {
    return this->get_ptr(idx);
}

// <A> -> <B> -> <C> ... -> <N>
// <A> <- <B> <- <C> ... <- <N>
//
template <typename T> void list<T>::reverse() {
    linked_node<T> *front = this->head, *back = this->tail;

    for (uint64_t k = 0; k <= (this->s/2 - (this->s+1)%2) && front != nullptr && back != nullptr; k++) {
        swap(front, back);
        front = front->next();
        back = back->prev();
    }
}

template <typename T> inline void quicksort(list<T>& l, int64_t lo, int64_t hi) {
    if (lo >= hi || lo < 0) {
        return;
    }

    int64_t p = partition(l, lo, hi);

    quicksort(l, lo, p-1);
    quicksort(l, p+1, hi);
}

template <typename T> int64_t partition(list<T>& l, int64_t lo, int64_t hi) {
    // high_node->value() is the pivot
    linked_node<T> *curr_node = l[lo], *high_node = l[hi];

    int64_t k = lo-1;

    linked_node<T>* swap_node = (k < 0 || k >= l.size() ? nullptr : l[k]);

    for (int64_t j = lo; j < hi; j++) {
        if (curr_node->value() <= high_node->value()) {
            ++k;

            swap_node = (swap_node == nullptr ? l[k] : swap_node->next());

            swap(curr_node, swap_node);
        }

        curr_node = curr_node->next();
    }

    ++k;

    swap_node = (swap_node == nullptr ? l[k] : swap_node->next());

    swap(swap_node, high_node);

    return k;
}

// Quicksort
template <typename T> void list<T>::sort() {
    quicksort(*this, 0, this->s-1);
}

template <typename T> list<T> list<T>::merge(list<T> ll) const {
    list<T> merged;

    linked_node<T>* first = this->head, second = ll.front();

    for (int64_t k = 0; k < this->s; k++) {
        merged.push_back(first->value());
        first = first->next();
    }

    for (int64_t k = 0; k < ll.size(); k++) {
        merged.push_back(second->value());
        second = second->next();
    }

    return merged;
}

template <typename T> linked_node<T>* list<T>::front() const {
    return this->head;
}

template <typename T> linked_node<T>* list<T>::back() const {
    return this->tail;
}

template <typename T> linked_node<T> list<T>::get(int64_t idx) const {
    assert(idx >= 0 && idx < this->s);

    return *(this->get_ptr());
}

template <typename T> std::ostream& operator<<(std::ostream& out, const list<T>& l) {
    linked_node<T>* current = l.head;

    while (current != nullptr) {
        out << current;
        current = current->next();
    }

    return out;
}

template <typename T> std::ostream& operator<<(std::ostream& out, const list<T>* l) {
    out << *l;
    return out;
}

#endif
