//
//  dfs.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 7/21/20.
//

#include "graph_generic.h"

namespace graph {

void GraphAlgorithm::dfs(int u) {
    fout << u << ", ";
    for (int v = 1; v <= g.n(); ++v) {
        if (0 == trace[v] && g[u][v]) {
            trace[v] = u;
            dfs(v);
        }
    }
}

void GraphAlgorithm::dfsStack() {
    fout << "Running DFS using stack:" << endl;
    fout << "From " << s << " you can visit:" << endl;
    Util::push(s);
    trace[s] = VIRTUAL_ROOT;
    fout << s << ", ";

    while (!Util::empty()) {
        int u = Util::pop();
        for (int v = 1; v <= g.n(); ++v) {
            if (0 == trace[v] && g[u][v]){
                fout << v << ", ";
                Util::push(u); Util::push(v);
                trace[v] = u;
                break;
            }
        }
    }
    fout << endl;
}

void GraphAlgorithm::dfsBacktrack() {
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

int GraphAlgorithm::findNext(int u) {
    while (u != VIRTUAL_ROOT) {
        for (int v = 1; v <= g.n(); ++v) {
            if (NO_NODE == trace[v] && g[u][v]){
                trace[v] = u;
                return v;
            }
        }
        u = trace[u];
    }
    return NO_NODE;
}

}
