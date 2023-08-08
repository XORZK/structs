#ifndef MAP_H
#define MAP_H

#pragma once
#include "rb_tree.h"

template <typename K, typename V> class map : public rb_tree<K, V> {};

#endif
