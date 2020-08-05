#include "graph_generic.h"

namespace graph {

int GraphAlgorithm::getRoot(int u) {
    while (label[u] > 0) {
        u = label[u];
    }
    return u;
}

int GraphAlgorithm::unionTree(int r1, int r2) {
    int x = label[r1] + label[r2];
    if (label[r1] > label[r2]) {
        label[r2] = x; // negative of number of nodes in tree root r2
        label[r1] = r2;
    }
    else {
        label[r1] = x;
        label[r2] = r1;
    }
    return -1 * x;
}

void GraphAlgorithm::adjustHeap(int r, int last) {
    Edge key = g.e(r);
    while (r * 2 <= last) {
        int child = r * 2;
        if (child < last && g.e(child).c > g.e(child+1).c) ++child;

        if (key.c < g.e(child).c) break;
        Edge te = g.e(r);
        g.e(r) = g.e(child);

        r = child;
    }
    g.e(r) = key;
}

void GraphAlgorithm::kruskal() {
    fout << "Running Kruskal algorithm to find minimum spanning tree:" << endl;
    if (WEIGHT != g.wType()) {
        fout << "Error: Graph is not weighted" << endl;
        return;
    }
    if (SINGLE != g.nType()) {
        fout << "Error: Graph is not single" << endl;
        return;
    }
    bool connected = false;
    for (int i = g.m() / 2; i >= 1; --i) adjustHeap(i, g.m());
    for (int i = g.m(); i >= 1; --i) {
        Edge temp = g.e(1);
        g.e(1) = g.e(i);
        g.e(i) = temp;
        adjustHeap(1, i - 1);

        int u = temp.u, v = temp.v;
        u = getRoot(u); v = getRoot(v);
        if (u != v) {
            g.e(i).mark = true;
            int num = unionTree(u, v);
            if (num == g.n()) {
                connected = true;
                break;
            } ;
        }
    }
    printSpanningTree(connected);  
}

void GraphAlgorithm::printSpanningTree(bool isConnected) {
    if (!isConnected) {
        fout << "Error: Graph is not connected!";
    }
    else {
        fout << "Minimal spanning tree: " << endl;

        int weight = 0;
        int count = 0;
        for (int i = 1; i <= g.m(); ++i) {
            Edge e = g.e(i);
            if (e.mark) {
                fout << "(" << e.u << ", " << e.v << ") = " << e.c << endl;
                weight += g.e(i).c;
                ++count;
            }
            if (count == g.n() - 1) break;
        }
        fout << "Weight = " << weight << endl;
    }
}

void GraphAlgorithm::prim() {
    fout << "Running Prim algorithm to find minimum spanning tree:" << endl;
    if (WEIGHT != g.wType()) {
        fout << "Error: Graph is not weighted" << endl;
        return;
    }
    if (SINGLE != g.nType()) {
        fout << "Error: Graph is not single" << endl;
        return;
    }
    bool connected = true;
    d[1] = 0;
    trace[1] = VIRTUAL_ROOT;
    
    for (int i = 1; i <= g.n(); ++i) {
        int min = INFINITY;
        int u = 0;
        for (int j = 1; j <= g.n(); ++j) {
            if (_free[j] && d[j] < min) {
                min = d[j];
                u = j;
            }
        }
        if (INFINITY == min) {
            connected = false;
            break;
        }
        _free[u] = false;
        for (int v = 1; v <= g.n(); ++v) {
            if (_free[v] && d[v] > d[u] + g[u][v]) {
                d[v] = d[u] + g[u][v];
                trace[v] = u;
            }
        }
    }
    printPrimResult(connected);
}

void GraphAlgorithm::printPrimResult(bool isConnected) {
    if (!isConnected) {
        fout << "Error: Graph is not connected!" << endl;
    }
    else {
        fout << "Mininal spanning tree:" << endl;
        int weight = 0;
        for (int v = 2; v <= g.n(); ++v) {
            fout << "(" << trace[v] << ", " << v << ") = " << g[trace[v]][v] << endl;
            weight += g[trace[v]][v];
        }
        fout << "Weight = " << weight << endl;
    }
}
}