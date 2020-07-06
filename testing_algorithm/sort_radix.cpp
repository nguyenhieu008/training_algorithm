//
//  sort_radix.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/4/20.
//

#include "sort_generic.h"

namespace sorting {

bool Sort::checkBit(int number, int b) {
    return ((number >> b) & 1) == 1;
}

void Sort::partitionExchangeRadixSort(int l, int r, int z) {
    if (l >= r) return;
    int i = l, j = r;
    while (i < j) {
        while (i < j && !checkBit(x[i], z)) ++i;
        while (i < j && checkBit(x[j], z)) --j;
        swap(i, j);
    }
    if (!checkBit(x[j], z)) ++j;
    if (z > 0) {
        partitionExchangeRadixSort(l, j - 1, z - 1);
        partitionExchangeRadixSort(j, r, z - 1);
    }
}

void Sort::exchangeRadixSort() {
    start = high_resolution_clock::now();
    
    int max = x[0];
    for (int i = 1; i < n; ++i) if (x[i] > max) max = x[i];
    int z = 1;
    while (max >>= 1 != 0) ++z;
    
    partitionExchangeRadixSort(0, n - 1, z - 1);
    
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}

void Sort::straightRadixSort() {
    int radix = 16;
    int m = maxKey();
    int digits = 1;
    while (m /= radix > 0) ++digits;
    
    start = high_resolution_clock::now();
    
    
    
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}
}
