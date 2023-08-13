#ifndef PAIR_H
#define PAIR_H

template <typename K, typename V> class pair {
    private:
        K k;
        V v;
    public:
        pair() {};

        pair(K key, V value);

        ~pair() {};

        void key(K k);
        K key() const;

        void value(V v);
        V value() const;

        bool operator==(const K k) const;
        bool operator==(const pair<K,V> p) const;
        bool operator>(const pair<K,V> p) const;
        bool operator<(const pair<K,V> p) const;
        bool operator<=(const pair<K,V> p) const;
        bool operator>=(const pair<K,V> p) const;
        bool operator!=(const pair<K,V> p) const;
};

template <typename K, typename V> 
pair<K,V>::pair(K key, V value) : k(key), v(value) {}

template <typename K, typename V> void pair<K,V>::key(K k) { this->k = k; }
template <typename K, typename V> K pair<K,V>::key() const { return this->k; }

template <typename K, typename V> void pair<K,V>::value(V v) { this->v = v; }
template <typename K, typename V> V pair<K,V>::value() const { return this->v; }

template <typename K, typename V> 
bool pair<K,V>::operator==(const K k) const { return this->k == k; }

template <typename K, typename V> 
bool pair<K,V>::operator==(const pair<K,V> p) const { return (this->k == p.key() && this->v == p.value()); }

template <typename K, typename V> 
bool pair<K,V>::operator>(const pair<K,V> p) const { return this->k > p.key(); }

template <typename K, typename V> 
bool pair<K,V>::operator<(const pair<K,V> p) const { return this->k < p.key(); }

template <typename K, typename V> 
bool pair<K,V>::operator<=(const pair<K,V> p) const { return this->k <= p.key(); }

template <typename K, typename V> 
bool pair<K,V>::operator>=(const pair<K,V> p) const { return this->k >= p.key(); }

template <typename K, typename V> 
bool pair<K,V>::operator!=(const pair<K,V> p) const { return (this->k != p.key() || this->v != p.value()); }


template <typename K, typename V> 
std::ostream& operator<<(std::ostream& out, const pair<K,V> pair) {
    out << '(' << pair.key() << ',' << pair.value() << ')';

    return out;
}

template <typename K, typename V> 
std::ostream& operator<<(std::ostream& out, const pair<K,V> *pair) {
    return out << *pair;
}


#endif
