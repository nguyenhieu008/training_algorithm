//
//  sort_generic.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/27/20.
//

#include "sort_generic.h"

namespace sorting {
void Sort::bubbleSort() {
    start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = n; j > i; --j) {
            if (x[j] < x[i]) swap(i, j);
        }
    }
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}
}
