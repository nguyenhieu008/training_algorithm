#include <iostream>

using namespace std;

namespace list_arranges {

int n, k;
int x[30] = {0, };
bool free_[30];

void printResult() {
    for (int i = 1; i <= k; ++i) {
        cout << x[i] << " ";
    }
    cout << endl;
}

void backTrackingMethod(int i) {
    if (i > k) {
        printResult();
        return;
    }

    for (int j = 1; j <= n; ++j) {
        if (free_[j]) {
            x[i] = j;
            free_[j] = false;
            backTrackingMethod(i + 1);
            free_[j] = true;   
        }
    }
}

int main() {
    cout << "Enter n k:" << endl;
    cin >> n >> k;

    fill_n(free_, 30, true);

    backTrackingMethod(1);

    cin >> k;

    return 0;
}
}