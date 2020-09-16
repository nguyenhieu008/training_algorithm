//
//  sort_heap.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/4/20.
//

#include "sort_generic.h"

namespace sorting {
//void Sort::adjust(int t_root, int t_end) {
////    cout << "Adjusting from " << t_root << " to " << t_end << endl;
//    while (t_root * 2 + 1 <= t_end) {
//        int c = t_root * 2 + 1;
//        if (c + 1 <= t_end && x[c] < x[c+1]) c++;
//        if (x[t_root] < x[c]) {
////            cout << "Swapping x[" << t_root << "] = " << x[t_root] << " with x[" << c << "] = " << x[c] << endl;
//            swap(t_root, c);
//            t_root = c;
//        }
//        else break;
//    }
//
//}
//
//void Sort::heapSort() {
//    start = high_resolution_clock::now();
//
//    for (int r = (n - 2) / 2; r >= 0; --r) adjust(r, n - 1);
////    for (int i = 0; i < n; ++i) cout << x[i] << " ";
////    cout << endl << endl;
//    int c = n - 1;
//    while (c > 0) {
////        cout << "Swapping c = " << c << endl;
//        swap(0, c--);
////        for (int i = 0; i < n; ++i) cout << x[i] << " ";
////        cout << endl;
//        adjust(0, c);
////        for (int i = 0; i < n; ++i) cout << x[i] << " ";
////        cout << endl << endl;
//    }
//
//    stop = high_resolution_clock::now();
//    dur = duration_cast<microseconds>(stop - start);
//}

void Sort::adjust(int t_root, int t_end) {
    int temp = x[t_root];
    while (t_root * 2 + 1 <= t_end) {
        int c = t_root * 2 + 1;
        if (c < t_end && x[c+1] > x[c]) ++c;
        
        if (x[c] > temp) {
            x[t_root] = x[c];
            t_root = c;
        }
        else break;
    }
    x[t_root] = temp;
}

void Sort::heapSort() {
    for (int i = n / 2 - 1; i >= 0; --i) adjust(i, n - 1);
    
    int end = n - 1;
    while (end > 0) {
        swap(0, end--);
        adjust(0, end);
    }
}
}
