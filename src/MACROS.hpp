#ifndef MACROS_H
#define MACROS_H

#pragma once
#include "list.hpp"
#include <stdint.h>

#define MAX(x,y) ((x > y) ? x : y)
#define MIN(x,y) ((x < y) ? x : y)

inline int64_t log2(int64_t x) {
    int64_t result = 0;
    while (x >>= 1) ++result;
    return result;
}

inline list<bool> dec_to_bin(int64_t N) {
    int64_t k = 0;

    list<bool> binary_list;

    while (N > 0) {
        int64_t P = (N%(1<<(k+1))) / (1<<k);
        N -= (1<<k++) * P;
        if (N > 0 || P == 1) binary_list.push_back(P == 1);
    }

    binary_list.reverse();

    return binary_list;
}

#endif 
