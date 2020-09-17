#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

ifstream fin("c.inp");
ofstream fout("c.out");
int T;
int n, m;
bool res;

int main() {
    ios::sync_with_stdio(false);
    fin.tie(nullptr);

    time_point<high_resolution_clock> start, stop;
    microseconds dur;

    start = high_resolution_clock::now();

    fin >> T;

    while (T--) {
        fin >> n >> m;
        int maxIdx = sqrt(2 * m);
        while (maxIdx > n - 1 || (maxIdx * (maxIdx + 1)) > (2 * m)) {
            --maxIdx;
        }
        fout << "maxIdx = " << maxIdx << endl;
        int r = m - maxIdx * (maxIdx + 1) / 2;
        int temp = 0;
        for (int left = 0; left <= maxIdx; ++left) {
            if (r > 0) {
                fout << maxIdx + 2 - left << " ";
                --r;
            }
            else {
                if (r == 0) {
                    temp = maxIdx + 2 - left;
                    --r;
                }
                fout << maxIdx + 1 - left << " ";
            }
        }
        if (maxIdx < n - 1) {
            fout << temp << " ";
        }

        int res = maxIdx + 3, resIdx = maxIdx + 2;
        while (resIdx < n) {
            fout << res++ << " ";
            resIdx++;
        }
        fout << endl;
    }

    fin.close();

    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
    fout << "Running in: " << dur.count() << " microseconds." << endl;
    fout.close();

    return 0;

}