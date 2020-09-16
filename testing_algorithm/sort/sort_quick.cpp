//
//  sort_quick.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/28/20.
//

#include "sort_generic.h"

namespace sorting {
void Sort::quickSort() {
    start = high_resolution_clock::now();
    
    partition(0, n - 1);
    
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}

void Sort::partition(int l, int r) {
    if (l >= r) return;
    
    int i = l, j = r;
    
    int pivot = x[i];
    
    while (i <= j) {
        while (x[i] < pivot) ++i;
        while (x[j] > pivot) --j;
        if (i <= j) {
            swap(i, j);
            ++i; --j;
        }
    }
    partition(l, j);
    partition(i, r);
}

//void Sort::partition(int l, int r) {
////    cout << "Initial:" << endl;
////    for (int k = l; k <= r; ++k) {
////        cout << x[k] << " ";
////    }
////    cout << endl << "Partition from " << l << " to " << r << endl;
//    if (l >= r) return;
//    int pivot = x[l];
//    int i = l, j = r;
//    while (i <= j) {
//        for (; x[i] < pivot; ++i);
//        for (; x[j] > pivot; --j);
//        if (i <= j) {
//            if (i < j) swap(i, j);
//            ++i; --j;
//        }
//    }
////    cout << "After:" << endl;
////    for (int k = l; k <= r; ++k) {
////        cout << x[k] << " ";
////    }
////    cout << endl;
////    cout << "Left: " << endl;
////    for (int k = l; k <= j; ++k) {
////        cout << x[k] << " ";
////    }
////    cout << endl;
////    cout << "Right: " << endl;
////    for (int k = i; k <= r; ++k) {
////        cout << x[k] << " ";
////    }
////    cout << endl;
//    partition(l, j);
//    partition(i, r);
//}
}
