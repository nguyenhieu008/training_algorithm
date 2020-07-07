//
//  sort_selection.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 6/27/20.
//

#include "sort_generic.h"

using namespace sorting;

//namespace sorting {

int main() {
    ifstream fin("sort_data.inp.1");
    ofstream fout("sort_result.out.1");
    
    Sort s;
    int T, t;
    
    fin >> T;
    
    fout << "Running exchange radix sort!" << endl;
    for (t = 1; t <= T; ++t) {
        s.input(fin);
        s.exchangeRadixSort();
        s.printResult(fout, t);
    }
    
    fin.close();
    fout.close();
    
    return 0;
}

//}
