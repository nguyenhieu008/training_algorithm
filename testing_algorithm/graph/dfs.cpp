//
//  dfs.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/21/20.
//

#include <iostream>
#include <fstream>

using namespace std;

namespace dfs {

const int MAX = 101;

ifstream fin("graph.inp");
ofstream fout("graph.out");

bool a[MAX][MAX] = {{false, }, };
//bool visited[MAX] = {false, };
int trace[MAX] = {0, };
int n, m, s, f;

void input() {
    int u, v;
    fin >> n >> m >> s >> f;
    for (int i = 0 ; i < m; ++i) {
        fin >> u >> v;
        a[u][v] = a[v][u] = true;
    }
}

void dfs(int u) {
    fout << u << ", ";
//    visited[u] = true;
    for (int v = 1; v <= n; ++v) {
        if (0 == trace[v] && a[u][v]) {
            trace[v] = u;
            dfs(v);
        }
    }
}

void printResult() {
    fout << endl << "Path from " << s << " to " << f << ": ";
    if (0 == trace[f]) fout << "not found";
    else {
        while (f != s) {
            fout << f << "<-";
            f = trace[f];
        }
        fout << s << endl;
    }
}

int main() {
    input();
    fout << "From " << s << " you can visit:" << endl;
    trace[s] = -1;
    dfs(s);
    printResult();
    fin.close();
    fout.close();
    return 0;
}
}
