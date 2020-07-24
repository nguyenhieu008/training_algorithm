#include "graph_generic.h"

namespace graph {
void GraphSearch::listConnectedComponent() {
    int connected = 1;
    for (int u = 1; u <= n; ++u) {
        if (NO_NODE == trace[u]) {
            fout << "The connected component number " << connected << " contains: " << endl;
            s = u;
            bfsLoang();
            fout << endl;
            ++connected;
        }
    }
}

void GraphConnectivity::warshall() {
    fout << "Running warshall algorithm:" << endl;
    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                a[u][v] = a[u][v] || a[u][k] && a[k][v];
            }
        }
    }
    int count = 1;
    for (int u = 1; u <= n; ++u) {
        if (_free[u]) {
            fout << "Connected component " << count++ << ": " << endl;
            for (int v = 1; v <= n; ++v) {
                if (a[u][v]) {
                    fout << v << ", ";
                    _free[v] = false;
                }
            }
            fout << endl;
        }
    }
}

void GraphConnectivity::visit(int u) {
    low[u] = numbering[u] = count++;
    push(u);
    for (int v = 1; v <= n; ++v) {
        if (a[u][v] && _free[v]) {
            if (numbering[v]) low[u] = min(low[u], numbering[v]); 
            else {
                visit(v);
                low[u] = min(low[u], low[v]);
            }
        }
    }
    if (numbering[u] == low[u] && u) {
        fout << "Connected component " << componentCount++ << ":" << endl;
        for (int v = pop(); v != u; v = pop()) {
            _free[v] = false;
            fout << v << ", ";
        }
        fout << u << endl;
        _free[u] = false;
    }
}

void GraphConnectivity::tarjan() {
    fout << "Running tarjan algorithm:" << endl;
    for (int i = 1; i <= n; ++i) {
        a[0][i] = true;
    }
    push(0);
    visit(0);
}

void GraphConnectivity::directedEdges(int u) {
    numbering[u] = count++;
    low[u] = INFINITY;
    for (int v = 1; v <= n; ++v) {
        if (a[u][v]) {
            a[v][u] = false;
            if (numbering[v]) low[u] = min(low[u], numbering[v]);
            else {
                directedEdges(v);
                low[u] = min(low[u], low[v]);
                if (numbering[u] < low[v]) {
                    fout << "(" << u << ", " << v << ")" << endl;
                }
            }
        }
    };
}

void GraphConnectivity::detectBridges() {
    fout << "Detecting bridges using directing edges DFS:" << endl;
    fout << "Bridges:" << endl;
    for (int u = 1; u <= n; ++u) {
        if (0 == numbering[u]) directedEdges(u);
    }
    fout << "Directed edges:" << endl;
    for (int u = 1; u <= n; ++u) {
        for (int v = 1; v <= n; ++v) {
            if (a[u][v]) fout << u << "->" << v << endl;
        }
    }
}
}