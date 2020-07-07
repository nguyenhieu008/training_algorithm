#include <iostream>
#include <fstream>

using namespace std;

namespace travelingSalesman {

int n, m;
int c[25][25];
int x[25];
int d[25];
int free_[25];
int bestConfig[25];
int bestD;

void input() {
    // cout << "Enter n, m: " << endl;
    ifstream myfile("travelingSalesman.inp");
    myfile >> n >> m;

    for (int i = 1; i <= n; ++i) {
        fill(c[i], c[i] + n + 1, INT_MAX);
        c[i][i] = 0;
    }
    fill(free_, free_ + n + 1, true);

    for (int i = 0; i < m; ++i) {
        int t1, t2, t;
        myfile >> t1 >> t2 >> t;
        c[t1][t2] = c[t2][t1] = t;
    }

    for (int i = 1; i <= n ; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
}

void printResult() {
    cout << bestConfig[1];
    for (int i = 2; i <= n; ++i) {
        cout << "->" << bestConfig[i];
    }
    cout << "->" << bestConfig[1] << endl;
    cout << "Cost: " << bestD << endl;
}

void updateBestConfig() {
    for (int i = 2; i <= n; ++i) {
        bestConfig[i] = x[i];
    }
    bestD = d[n] + c[x[n]][1];
}

void travelingSalesman(int i) {
    for (int j = 2; j <= n; ++j) {
        int prev = x[i-1];
        if (free_[j] && c[prev][j] < INT_MAX) {
            x[i] = j;
            d[i] = d[i-1] + c[prev][j];
            if (i == n && c[j][1] < INT_MAX && d[i] + c[j][1] < bestD) {
                updateBestConfig();
            }
            else if (i < n && d[i] < bestD) {
                free_[j] = false;
                travelingSalesman(i + 1);
                free_[j] = true;
            }
        }
    }
}

int main() {
    input();

    x[1] = 1;
    d[1] = 0;
    free_[1] = false;
    bestConfig[1] = 1;
    bestD = INT_MAX;

    travelingSalesman(2);

    printResult();
    cin >> n;
    return 0;
}
}