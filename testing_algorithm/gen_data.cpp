//
//  gen_data.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/28/20.
//

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace gen_data {

int main() {
    ofstream fout("sort_data.inp");
    int t = 2;
    fout << t << endl;
    
    int n = 200;
    fout << n << endl;
    for (int i = 0; i < n; ++i) {
        fout << rand() % 10000 << " ";
    }
    n = 100000;
    fout << n << endl;
    for (int i = 0; i < n; ++i) {
        fout << rand() % 10000 << " ";
    }
    return 0;
}
}
