//#include "graph/graph_generic.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;
using namespace std::chrono;

namespace _2019a {

ifstream fin("a.inp");
//ofstream fout("a.out");
int T;
int N;
int x, y;
unordered_map<int, unordered_set<int>> verticals;
//unordered_map<int, unordered_set<int>> horizontals;

bool res;

int main() {
    ios::sync_with_stdio(false);
    fin.tie(nullptr);

    time_point<high_resolution_clock> start, stop;
    microseconds dur;

    start = high_resolution_clock::now();

    fin >> T;

    while (T--) {
        res = true;
        verticals.clear();
//        horizontals.clear();
        fin >> N;
        for (int i = 0; i < N; ++i) {
            fin >> x >> y;
            auto temp = verticals[x].insert(y);
            if (!temp.second) res = false;
//            temp = horizontals[y].insert(x);
//            if (!temp.second) res = false;
        }

//        for (auto tempit = verticals.begin(); tempit != verticals.end(); ++tempit) {
//            cout << "Vertical " << tempit->first << ": ";
//            for (auto inner = tempit->second.begin(); inner!= tempit->second.end(); ++inner) {
//                cout << *inner << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;

        auto it = verticals.begin();
        while (next(it) != verticals.end()) {
            if (it->second != next(it)->second) {
                res = false;
                break;
            }
            ++it;
        }

        if (res) cout << "BALANCED" << endl;
        else cout << "NOT BALANCED" << endl;
    }

    fin.close();

    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
    cout << "Running in: " << dur.count() << " microseconds." << endl;
//    fout.close();

    return 0;

}


//#include <iostream>
//#include <vector>
//#include <set>
//#include <fstream>
//#include <chrono>
//
//using namespace std::chrono;
//using namespace std;
//ifstream fin("a.inp");
//bool balanced(vector<int> &x, vector<int> &y) {
//    int n = x.size();
//set<int> sx(x.begin(), x.end());
//set<int> sy(y.begin(), y.end());
//return n == (int)sx.size() * (int)sy.size();
//}
//int main(void) {
//    cout.sync_with_stdio(false);
//
//cin.tie(nullptr);
//    int nTests;
//
//        time_point<high_resolution_clock> start, stop;
//        microseconds dur;
//
//        start = high_resolution_clock::now();
//    fin >> nTests;
//    while (nTests--) {
//        int n;
//        fin >> n;
//        vector<int> x(n), y(n);
//        for (int i = 0; i < n; ++i)
//                fin >> x[i] >> y[i];
//        cout << (balanced(x, y)? "BALANCED": "NOT BALANCED") << '\n';
//
//
//
//
//    }
//    fin.close();
//    stop = high_resolution_clock::now();
//    dur = duration_cast<microseconds>(stop - start);
//    cout << "Running in: " << dur.count() << " microseconds." << endl;
//    return 0;
//}
}
