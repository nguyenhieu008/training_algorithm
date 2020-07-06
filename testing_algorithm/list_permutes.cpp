//
//  main.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/22/20.
//



#include <iostream>

using namespace std;

namespace list_permutes {

int n;
int x[13] = {0, };
int i, k, s, e;

inline void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    cout << "Enter n:" << endl;
    cin >> n;
    
    for (i = 1; i <= n; ++i) x[i] = i;
    
    do {
        for (i = 1; i <= n; ++i) cout << x[i] << " ";
        cout << endl;
        
        i = n - 1;
        while (i > 0 && x[i] > x[i + 1]) --i;
        if (i > 0) {
            k = n;
            while (x[k] < x[i]) {
//                cout << "aaa" << endl;
                --k;
            }
            swap(x[i], x[k]);
            s = i + 1;
            e = n;
            while (s < e) {
//                cout << "bbb" << endl;
                swap(x[s], x[e]);
                ++s;
                --e;
            }
        }
    } while (i > 0);
    
    return 0;
}
}
