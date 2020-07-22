//
//  dfs_stack.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/21/20.
//

#include <iostream>
#include <fstream>

using namespace std;

namespace dfs_stack {

const int MAX = 101;

ifstream fin("graph.inp");
ofstream fout("graph.out");

bool a[MAX][MAX] = {{false, }, };
//bool visited[MAX] = {false, };
int trace[MAX] = {0, };
int stack_[MAX], stackSize;
int n, m, s, f;

void input() {
    int u, v;
    fin >> n >> m >> s >> f;
    for (int i = 0 ; i < m; ++i) {
        fin >> u >> v;
        a[u][v] = a[v][u] = true;
    }
    stackSize = 0;
}

void push(int u){
    stack_[stackSize++] = u;
}
int pop() {
    return stack_[--stackSize];
}

void dfsStack() {
//    fout << s << ", ";
    push(s);
    trace[s] = -1;
//    visited[u] = true;
    while (stackSize > 0) {
        for (int i = 0; i < stackSize; ++i) cout << stack_[i] << " ";
        cout << endl;
        int u = pop();
//        fout << "u = " << u << endl;
        for (int v = 1; v <= n; ++v) {
//            fout  << "v = " << v << "trace[" << v << "] = " << trace[v] << "a[u][v] = " << a[u][v] << endl;
            if (0 == trace[v] && a[u][v]){
//                fout << v << ", ";
                push(u); push(v);
                trace[v] = u;
                break;
            }
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
//    trace[s] = -1;
    dfsStack();
    printResult();
    fin.close();
    fout.close();
    return 0;
}
}
