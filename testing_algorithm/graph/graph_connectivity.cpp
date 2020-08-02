#include "graph_generic.h"

namespace graph {
void GraphSearch::listConnectedComponent() {
    int connected = 1;
    for (int u = 1; u <= g.n(); ++u) {
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
    for (int k = 1; k <= g.n(); ++k) {
        for (int u = 1; u <= g.n(); ++u) {
            for (int v = 1; v <= g.n(); ++v) {
                g[u][v] = g[u][v] || g[u][k] && g[k][v];
            }
        }
    }
    int count = 1;
    for (int u = 1; u <= g.n(); ++u) {
        if (_free[u]) {
            fout << "Connected component " << count++ << ": " << endl;
            for (int v = 1; v <= g.n(); ++v) {
                if (g[u][v]) {
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
    Util::push(u);
    for (int v = 1; v <= g.n(); ++v) {
        if (g[u][v] && _free[v]) {
            if (numbering[v]) low[u] = min(low[u], numbering[v]); 
            else {
                visit(v);
                low[u] = min(low[u], low[v]);
            }
        }
    }
    if (numbering[u] == low[u] && u) {
        fout << "Connected component " << componentCount++ << ":" << endl;
        for (int v = Util::pop(); v != u; v = Util::pop()) {
            _free[v] = false;
            fout << v << ", ";
        }
        fout << u << endl;
        _free[u] = false;
    }
}

void GraphConnectivity::tarjan() {
    fout << "Running tarjan algorithm:" << endl;
    for (int i = 1; i <= g.n(); ++i) {
        g[0][i] = true;
    }
    Util::push(0);
    visit(0);
}

void GraphConnectivity::directedEdges(int u) {
    numbering[u] = count++;
    low[u] = INFINITY;
    for (int v = 1; v <= g.n(); ++v) {
        if (g[u][v]) {
            g[v][u] = false;
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
    for (int u = 1; u <= g.n(); ++u) {
        if (0 == numbering[u]) directedEdges(u);
    }
    fout << "Directed edges:" << endl;
    for (int u = 1; u <= g.n(); ++u) {
        for (int v = 1; v <= g.n(); ++v) {
            if (g[u][v]) fout << u << "->" << v << endl;
        }
    }
}

void GraphConnectivity::visitCutVertices(int u) {
    numbering[u] = count++;
    low[u] = numbering[u];
    for (int v = 1; v <= g.n(); ++v) {
        if (g[u][v]) {
            if (numbering[v]) low[u] = min(low[u], numbering[v]);
            else {
                ++nC[u];
                visitCutVertices(v);
                low[u] = min(low[u], low[v]);
                if (low[v] >= numbering[u]) {
                    _mark[u] = true;
                }
            }
        }
    }
}

void GraphConnectivity::detectCutVertices() {
    fout << "Detecting cut vertices:" << endl;
    for (int u = 1; u <= g.n(); ++u) {
        if (0 == numbering[u]) {
            visitCutVertices(u);
            
            if (nC[u] < 2) _mark[u] = false;
        }
    }
    fout << "Cut vertices:" << endl;
    for (int u = 1; u <= g.n(); ++u) {
        if (_mark[u]) fout << u << ", ";
    }
}
}
