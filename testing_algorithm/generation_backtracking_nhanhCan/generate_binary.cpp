//
//  main.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/21/20.
//

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace generate_binary {

int MAX = 50;
int x[50] = {0, };
int n;

void printString() {
    for (int i = 0; i < n; ++i) cout << x[i];
    cout << endl;
}

void bookMethod() {
    int i;
    do {
        printString();
        i = n - 1;
        while (i >= 0 && x[i] == 1) --i;
        if (i >= 0) {
            x[i] = 1;
            for (int j = i + 1; j < n; ++j) x[j] = 0;
        }
    } while (i >= 0);
}


void recursionMethod(int i) {
    if (n == i) {
        printString();
        return;
    }
    x[i] = 0;
    recursionMethod(i + 1);
    
    x[i] = 1;
    recursionMethod(i+1);
}

int main_generate_binary(int argc, const char * argv[]) {
//    cin >> n;
    n = 15;
    
    auto start = high_resolution_clock::now();
    
//    bookMethod();
    recursionMethod(0);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken by function : " << duration.count() << " microseconds" << endl;
    
    return 0;
}

}
