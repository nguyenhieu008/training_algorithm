#include "sort_generic.h"

namespace sorting {
void Sort::merge(int a[], int b[], int r, int s, int t) {
    int p = r, i = r, j = s;
    while (i < s && j < t) {
        if (a[i] < a[j]) b[p++] = a[i++];
        else b[p++] = a[j++];
    }
    while(i < s) b[p++] = a[i++];
    while(j < t) b[p++] = a[j++];
}

void Sort::mergeByLength(int a[], int b[], int l) {
    int r = 0, s = l, t = 2 * l;
    while (t <= n) {
        merge(a, b, r, s, t);
        r += 2 * l;  s += 2 * l; t += 2 * l;
    }
    if (s < n) merge (a, b, r, s, n);
    else for (int i = r; i < n; ++i) b[i] = a[i];
}
void Sort::mergeSort() {
    start = high_resolution_clock::now();
    int length = 1;
    int *y = new int[n];
    bool flag = true;

    while (length < n) {
        if (flag) mergeByLength(x, y, length);
        else mergeByLength(y, x, length);
        flag = !flag;
        length *= 2;
    }
    if (!flag) for (int i = 0; i < n; ++i) x[i] = y[i];
    delete[] y;
    
    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
}
}
