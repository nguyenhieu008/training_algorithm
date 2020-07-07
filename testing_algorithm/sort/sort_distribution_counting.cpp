//
//  sort_distribution_counting.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/4/20.
//

#include "sort_generic.h"
#include <vector>

namespace sorting {
int Sort::maxKey() {
    int m = x[0];
    for (int i = 1; i < n; ++i) {
        if (x[i] > m) m = x[i];
    }
    return m;
}
void Sort::distributionCounting() {
    start = high_resolution_clock::now();
    
    int m = maxKey();
    std::vector<int> c(m + 1, 0);
    std::vector<int> temp(n, 0);
    for (int i = 0; i < n; ++i) c[x[i]]++;
    for (int i = 1; i <= m; ++i) c[i] += c[i-1];
    for (int i = n - 1; i >= 0; --i) {
        int t = x[i];
        temp[--c[t]] = t;
    }
    for (int i = 0; i < n; ++i) x[i] = temp[i];
    
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}
}
