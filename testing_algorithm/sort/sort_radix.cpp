//
//  sort_radix.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/4/20.
//

#include "sort_generic.h"
#include <cmath>
#include <vector>

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

int Sort::getNumerical(int val, int radix, int radixPow) {
    return val / radixPow % radix;
}

void Sort::straightRadixSort() {
    int radix = 16;
    int count[radix];
    
    int m = maxKey();
    int digits = 1;
    while ((m /= radix) > 0) ++digits;
    
    start = high_resolution_clock::now();
    
    int temp = 1;
    bool flag = true;
    vector<int> y(n);
    
//    cout << "Before: n = " << n << endl;
//    for (int i = 0; i < n; ++i) {
//        cout << x[i] << " ";
//    }
    
    for (int d = 0; d < digits; ++d) {
//        cout << "d = " << d << endl;
        for (int i = 0; i < radix; ++i) count[i] = 0;
        for (int i = 0; i < n; ++i) {
            ++count[getNumerical(x[i], radix, temp)];
        }
        for (int i = 1; i < radix; ++i) count[i] += count[i-1];
//        cout << "count: ";
//        for (int i = 0; i < radix; ++i) {
//            cout << count[i] << " ";
//        }
//        cout << endl;
        for (int i = n - 1; i >= 0; --i){
            int t = --count[getNumerical(flag? x[i] : y[i], radix, temp)];
//            cout << "t = " << t << " x[ " << i << "] = " << x[i] << endl;
            if (flag) y[t] = x[i];
            else x[t] = y[i];
        }
//        cout << "ccc. n = " << n << endl;
        flag = !flag;
        temp *= radix;
    }
    
    if (!flag) for (int i = 0; i < n; ++i) x[i] = y[i];
//    cout << "After: n = " << n << endl;
//    for (int i = 0; i < n; ++i) {
//        cout << x[i] << " ";
//    }
    
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}
}
