#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace _2019b {

ifstream fin("b3.inp");
ofstream fout("b3.out");
int T;
int n, v, d, r1, r2, m, anchor, i;
bool res;

int gcd(int a, int b) {
    if (0 == b) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios::sync_with_stdio(false);
    fin.tie(nullptr);

    time_point<high_resolution_clock> start, stop;
    microseconds dur;

    start = high_resolution_clock::now();

    fin >> T;

    while (T--) {
        fin >> n;
        fin >> anchor;
        m = 0;

        for (i = 1; i < n; ++i) {
            fin >> v;
            m = abs(v - anchor);
            if (m > 0) {
                ++i;
                break;
            }
        }

        for (; i < n; ++i) {
            fin >> v;
            // fout << v << " ";
            d = abs(v - anchor);
            r1 = d % m;
            r2 = m - r1;
            m = gcd(m, r1);
            m = gcd(m, r2);
            if (1 == m) break;
        }
        // fout << endl;
        
        if (0 < m) {
            fout << m << endl;
        }
        else fout << "INFINITY" << endl;
    }

    fin.close();

    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
    fout << "Running in: " << dur.count() << " microseconds." << endl;
    fout.close();

    return 0;

}
}