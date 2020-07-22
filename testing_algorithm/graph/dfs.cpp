//
//  dfs.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/21/20.
//

#include "graph_generic.h"

namespace graph {

void Graph::dfs(int u) {
    fout << u << ", ";
    for (int v = 1; v <= n; ++v) {
        if (0 == trace[v] && a[u][v]) {
            trace[v] = u;
            dfs(v);
        }
    }
}

void Graph::push(int u){
    if (_stackSize >= n) {
        cerr << "Error: Push more than max size" << endl;
        exit(1);
    }
    _stack[_stackSize++] = u;
}
int Graph::pop() {
    if (_stackSize <= 0) {
        cerr << "Warning: Trying to pop empty stack" << endl;
        return NO_NODE;
    }
    return _stack[--_stackSize];
}

void Graph::dfsStack() {
    fout << "Running DFS using stack:" << endl;
    fout << "From " << s << " you can visit:" << endl;
    push(s);
    trace[s] = VIRTUAL_ROOT;
    fout << s << ", ";

    while (_stackSize > 0) {
        int u = pop();
        for (int v = 1; v <= n; ++v) {
            if (0 == trace[v] && a[u][v]){
                fout << v << ", ";
                push(u); push(v);
                trace[v] = u;
                break;
            }
        }
    }
    fout << endl;
}

void Graph::dfsBacktrack() {
    fout << "Running DFS using backtrack:" << endl;
    fout << "From " << s << " you can visit:" << endl;
    trace[s] = VIRTUAL_ROOT;
    int u = s;
    do {
        fout << u << ", ";
        u = findNext(u);
    } while (u != NO_NODE);
    fout << endl;
}

int Graph::findNext(int u) {
    while (u != VIRTUAL_ROOT) {
        for (int v = 1; v <= n; ++v) {
            if (NO_NODE == trace[v] && a[u][v]){
                trace[v] = u;
                return v;
            }
        }
        u = trace[u];
    }
    return NO_NODE;
}

}
