#include <iostream>

using namespace std;

namespace analyse_int {

int n;
int x[30], t[30];

void printResult(int m) {
    cout << n << " = " << x[1];
    for (int i = 2; i <= m; ++i) {
        cout << " + " << x[i];
    }
    cout << endl;
}

void analyse(int i) {
    // cout << "analyse " << i << endl;
    for (int j = x[i - 1]; j <= (n - t[i - 1]) / 2; ++j) {
        x[i] = j;
        t[i] = t[i - 1] + x[i];
        analyse(i + 1);
    }

    x[i] = n - t[i - 1];
    printResult(i);
}

int main() {
    cout << "Enter n" << endl;
    cin >> n;

    x[0] = 1; t[0] = 0;

    analyse(1);

    cin >> n;

    return 0;
}
}