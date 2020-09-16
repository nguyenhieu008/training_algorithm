//
//  sort_generic.h
//  training_algorithm
//
//  Created by Nguyen Trung Hieu on 6/27/20.
//

#ifndef sort_generic_h
#define sort_generic_h

#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace sorting {

#define MAX_SIZE 1000000

class Sort {
public:
    Sort() : n(0), x(new int[MAX_SIZE]){
    }

    ~Sort() {
        delete[] x;
    }
    
    void input(ifstream &fin) {
        fin >> n;
        if (n > MAX_SIZE) {
            cout << "Error! Size too large" << endl;
            exit(1);
        }
        for (int i = 0; i < n; ++i) {
            fin >> x[i];
        }
    }
    
    void swap(int i, int j) {
        int temp = x[i];
        x[i] = x[j];
        x[j] = temp;
    }
    
    void printResult(ofstream &fout, int t) {
        fout << "Case " << t << " takes " << dur.count() << " microseconds:" << endl;
        for (int i = 0; i < n; ++i) {
            fout << x[i] << " ";
        }
        fout << endl;
    }
    
    void selectionSort();
    void bubbleSort();
    void insertionSort();
    void quickSort();
    void heapSort();
    void distributionCounting();
    void exchangeRadixSort();
    void straightRadixSort();
    void mergeSort();
    
private:
    int n, *x;
    time_point<high_resolution_clock> start, stop;
    microseconds dur;
    
    void partition(int l, int r);
    void partitionExchangeRadixSort(int l, int r, int z);
    bool checkBit(int number, int b);
    void adjust(int t_root, int t_end);
    int maxKey();
    int getNumerical(int val, int radix, int radixPow);
    void mergeByLength(int a[], int b[], int l);
    void merge(int a[], int b[], int r, int s, int t);
};

}


#endif /* sort_generic_h */
