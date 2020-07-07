//
//  sort_insertion.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/29/20.
//

#include "sort_generic.h"

namespace sorting {
void Sort::insertionSort() {
    start = high_resolution_clock::now();
    for (int i = 1; i < n; ++i) {
        int j, temp = x[i];
        for (j = i - 1; x[j] > temp && j >= 0; --j) {
            x[j+1] = x[j];
        }
        x[j+1] = temp;
    }
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}
}
