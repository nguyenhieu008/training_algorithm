#include <iostream>

using namespace std;

namespace queens {

int n;
int x[30];
bool freeCol[30], freeDiag1[60], freeDiag2[60];

inline void printCell(int i) {
    cout << "(" << i << ", " << x[i] << ")";
}

void printResult() {
    printCell(1);
    for (int i = 2; i <= n; ++i) {
        cout << ", ";
        printCell(i);
    }
    cout << endl;
}

void queens(int i) {
    for (int j = 1; j <= n; ++j) {
        // cout << "i = " << i << " j = " << j << endl;
        if (freeCol[j] && freeDiag1[i + j] && freeDiag2[i - j + n]) {
            x[i] = j;
            if (i == n) {
                printResult();
                return;
            }
            
            freeCol[j] = false; freeDiag1[i + j] = false; freeDiag2[i - j + n] = false;
            queens(i + 1); 
            freeCol[j] = true; freeDiag1[i + j] = true; freeDiag2[i - j + n] = true;
        }
    }
}

int main() {
    cout << "Enter n" << endl;
    cin >> n;

    fill(freeCol, freeCol + n + 1, true);
    fill(freeDiag1, freeDiag1 + 2 * n + 1, true);
    fill(freeDiag2, freeDiag2 + 2 * n + 1, true);

    queens(1);

    cin >> n;

    return 0;
}
}