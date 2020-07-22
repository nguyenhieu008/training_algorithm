//============================================================================
// Name        : Test.cpp
// Author      : Hieu Trung Nguyen
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>

using namespace std;

namespace test_{
//ifstream cin("input");
int t, T, n, k;
int a[100001], b[100001];
long long f[100001];
int minItv, maxItv;

void input() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    f[0] = 0;
    
    if ((n - k) % 2 == 1) minItv = (n - k + 1) / 2;
    else minItv = (n - k) / 2;
    maxItv = (n + k) / 2;
}

void dp() {
    long long prev1 = 0, prev2 = 0;
    for (int i = 1; i <= n; ++i) {
        int minIdx = (i - maxItv) > 0 ? i - maxItv : 0;
        int maxIdx = i < maxItv ? i : maxItv;
        for (int j = minIdx; j <= maxIdx; ++j) {
            // cout << "i = " << i << " j = " << j << endl;
            if (0 == j) {
                prev1 = f[j];
                f[j] += b[i];
            }
            else if (i == j) f[j] = prev1 + a[i];
            else {
                prev2 = f[j];
                f[j] = max(f[j] + b[i], prev1 + a[i]);
                prev1 = prev2;
            }
        }
    }
}

void printResult() {
    if (t) cout << endl;

    long long maxVal = f[minItv];
    for (int i = minItv + 1; i <= maxItv; ++i) {
        if (f[i] > maxVal) maxVal = f[i];
    }
    cout << maxVal;
}

int main() {
    cin >> T;

    for (t = 0; t < T; ++t) {
        // cout << "t = " << t << endl;
        input();
        dp();
        printResult();
    }

    // cin >> T;
    return 0;
}
}
