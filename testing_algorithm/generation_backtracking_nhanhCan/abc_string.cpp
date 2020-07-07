#include <iostream>

using namespace std;

namespace abc_string {

int n;
char x[110], best[110];
int minC, t[110];

bool checkContinuousStrings(int i, int l) {
    int j = i - l;
    for (int k = 0; k < l; ++k) {
        if (x[i-k] != x[j-k]) return true;
    }
    return false;
}

bool check(int i) {
    for (int l = 1; l <= i / 2; ++l) {
        if (!checkContinuousStrings(i, l)) return false;
    }
    return true;
}

void updateBest() {
    minC = t[n];
    for (int i = 1; i <= n; ++i) best[i] = x[i];
}

void printResult() {
    for (int i = 1; i <= n; ++i) cout << best[i];
    cout << endl;
    cout << "\"C\" Letter Count: " << minC << endl;
}

void suitableString(int i) {
    for (int j = 0; j < 3; ++j) {
        char c = 'A' + j;

        x[i] = c;
        if (!check(i)) continue;
        if ('C' == c) t[i] = t[i-1] + 1;
        else t[i] = t[i-1];

        // if (t[i] + (n - i) / 4 > minC) return;
        if (i == n) {
            if (t[i] < minC) updateBest();
        } 
        else {
            suitableString(i+1);
        }
    }
}

int main() {
    cout << "Enter n:" << endl;
    cin >> n;

    minC = n;
    t[0] = 0;

    suitableString(1);

    printResult();

    cin >> n;

    return 0;
}
}