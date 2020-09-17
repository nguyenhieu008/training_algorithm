#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <list>

using namespace std;
using namespace std::chrono;

ifstream fin("e.inp");
ofstream fout("e.out");
int T;
int n;
string s;

void solve() {
    string s;
    fin >> s;
 
    int N = s.size();
 
    vector<bool> hs(1 << 26, false);
    list<int> alphabet;
 
    int ans = 0;
    int num;
    for (int i = 0; i < N; ++i) {
        num = int(s[i] - 'A');
 
        int base = 1 << num;
        fout << "s[" << i << "] = " << s[i] << " base = " << base;
        if (!hs[base]) {
            fout << ". Adding.";
            hs[base] = true;
            ans += 1;
        }
        fout << endl;
        for (list<int>::iterator it=alphabet.begin(); it!=alphabet.end(); ) {
            if (*it == (1 << num)) {
                it = alphabet.erase(it);
                continue;
            }
            base |= *it;
            fout << "New base = " << base  << ". ";
            if (!hs[base]) {
                hs[base] = true;
                fout << "Adding. ";
                ans += 1;
            }
            fout << endl;

            ++it;
        }
        alphabet.emplace_front(1 << num);
        for (auto it : alphabet) {
            fout << it <<",";
        }
        fout << endl;
    }
    fout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    time_point<high_resolution_clock> start, stop;
    microseconds dur;

    start = high_resolution_clock::now();

    fin >> T;

    while (T--) {
        solve();
    }

    fin.close();

    stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(stop - start);
    fout << "Running in: " << dur.count() << " microseconds." << endl;
//    fout.close();

    return 0;

}