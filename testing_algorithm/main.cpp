#include <iostream>
#include <fstream>
#include <vector>
//#include <unordered_map>
//#include <unordered_set>
//#include <list>
#include <climits>
#include <queue>
#include <array>

using namespace std;

ifstream fin("e.inp");
//ofstream fout("e.out");
int T;

typedef array<int, 3> AdjVer;

//#define AdjVer array<int, 3>

//#define INF 1<<30
int n, m, s, f;
vector<vector<AdjVer>> g;
priority_queue<AdjVer, vector<AdjVer>, greater<AdjVer>> heap;
int u, v, c;
vector<int> d;
vector<int> trace;

void input() {
    fin >> n >> m >> s >> f;
    g.resize(n);
    d.resize(n, INT_MAX);
    trace.resize(n, -1);
    
    for (int col = 0; col < m; ++col) {
        fin >> u >> v >> c;
        g[u].push_back({c, u, v});
    }
}

void solve() {
    d[s] = 0;
    heap.push({0, -2, s});
    
    while (!heap.empty()) {
        const AdjVer ver = heap.top();
        heap.pop();
        
        int u = ver[1], v = ver[2];
        if (trace[v] != -1) continue;
        trace[v] = u;
//        cout << "1. Add v = " << v << " from u = " << u << ", d[" << v << "] = " << ver[0] << " trace[v] = " << trace[v] << endl;
        
        for (auto p : g[v]) {
            int next = p[2], c = p[0];
            if (trace[next] != -1) continue;
            if (d[next] > d[v] + c) {
                d[next] = d[v] + c;
                heap.push({d[next], v, next});
//                cout << "2. Add v = " << next << " from u = " << v << ", d[" << next << "] = " << d[next] << " trace[v] = " << trace[next] << endl;
            }
        }
    }
    
    while (f != -2) {
        cout << f << "<-";
        f = trace[f];
    }
    cout << endl;
    
}

int main() {
    ios::sync_with_stdio(false);
    fin.tie(nullptr);
    
    fin >> T;

    while (T--) {
        input();
        solve();
        break;
    }

//    fin.close();
//
//    fout.close();

    return 0;

}
