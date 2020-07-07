#include <iostream>

using namespace std;

namespace list_combinations {

int MAX = 30;
int x[30] = {0, };
int n, k, i, j;

void printResult() {
        cout << "{";
        cout << x[1];
        for (int i = 2; i <= k; ++i) cout << ", " << x[i];
        cout << "}" << endl;    
}

void generationMethod() {
    for (int i = 1; i <= k; ++i) {
        x[i] = i;
    }

    do {
        printResult();

        i = k;
        while (i > 0 && x[i] == n - k + i) --i;
        if (i > 0) {
            ++x[i];
            for (j = i + 1; j <= k; ++j) x[j] = x[j - 1] + 1;
        }
    } while (i > 0);
}

void backTrackingMethod(int i) {
    if (i > k) {
        printResult();
        return;
    }

    for (int j = x[i - 1] + 1; j <= n - k + i; ++j) {
        x[i] = j;
        backTrackingMethod(i + 1);
    }
}

int main() {
    cout << "Enter n k: " << endl;
    cin >> n >> k;
    // n = 6; k = 3;
    backTrackingMethod(1);

    cin >> k;
    return 0;
}
}