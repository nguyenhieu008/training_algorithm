#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

namespace gen_data{

int main() {
    ofstream fout("input");
    fout << 50 << endl;
    int n, k, temp;
    for (int i = 0; i < 50; ++i) {
        n = (rand() % 90000) + 3;
        k = (rand() % (n - 10)) + 1;
        // k = k > n - 2? n - 2 : k;
        fout << n << " " << k << endl;

        for (int j = 0; j < n; ++j) {
            temp = (rand() % 990000) + 1;
            fout << temp << " ";
        }
        fout << endl;
        for (int j = 0; j < n; ++j) {
            temp = (rand() % 990000) + 1;
            fout << temp << " ";
        }
        fout << endl;
    }
    fout.close();
    return 0;
}
}