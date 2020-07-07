//
//  sort_selection.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/27/20.
//

#include "sort_generic.h"

namespace sorting {
void Sort::selectionSort() {
    start = high_resolution_clock::now();
    for (int i = 0; i < n - 1; ++i) {
        int minVal = x[i+1], minIdx = i + 1;
        for (int j = i + 2; j < n; ++j) {
            if (x[j] < minVal) {
                minVal = x[j];
                minIdx = j;
            }
        }
        if (minVal < x[i]) swap(i, minIdx);
    }
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}
}
