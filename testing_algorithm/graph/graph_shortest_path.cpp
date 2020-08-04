#include "graph_generic.h"

namespace graph {
void GraphAlgorithm::fordBellman() {
    fout << "Running Ford Bellman algorithm to find shortest path:" << endl;
    if (!_isFindingPath) {
        fout << "ERROR: Did not enable searching mode" << endl;
        return;
    }
    if (UNDIRECTED == g.dType()) {
        fout << "Did not test correctiveness of this algo on undirected graph!" << endl;
        return;
    }
    d[s] = 0;
    for (int loopCount = 1; loopCount <= g.n() - 1; ++loopCount) {
        bool stop = true;
        // fout << "Loop count " << loopCount << ":" << endl;
        for (int i = 1; i <= g.n(); ++i) {
            // fout << "i = " << i << ":" << endl;
            for (int j = 1; j <= g.n(); ++j) {
                // fout << "Current d[" << j << "] = " << d[j] << " new_d[" << j << "] = " << d[i] + g[i][j] << endl;
                if (d[j] > d[i] + g[i][j]) {
                    d[j] = d[i] + g[i][j];
                    // fout << "Updating d[" << j << "] = " << d[j] << endl;
                    trace[j] = i;
                    stop = false;
                }
            }
        }
        // fout << endl;
        if (stop) break;
    }

    printShortestPath();
}

void GraphAlgorithm::printShortestPath() {
    if (!_isFindingPath) {
        fout << "ERROR: Did not enable searching mode" << endl;
        return;
    }
    if (INFINITY == d[f]) {
        fout << "Path from " << s << " to " << f << " not found!";
    }
    else {
        fout << "Distance from " << s << " to " << f << ": " << d[f] << endl;
        while (f != s) {
            fout << f << "<-";
            f = trace[f];
        }
        fout << s << endl;
    }
}

void GraphAlgorithm::dijkstra() {
    fout << "Running Dijkstra algorithm to find shortest path (no negative weighted edge):" << endl;
    if (!_isFindingPath) {
        fout << "ERROR: Did not enable searching mode" << endl;
        return;
    }
    d[s] = 0;
    int u, v, min;

    do {
        u = NO_NODE;
        min = INFINITY;
        for (int i = 1; i <= g.n(); ++i) {
            if (_free[i] && d[i] < min) {
                min = d[i];
                u = i;
            }
        }
        if (NO_NODE == u || f == u) break;

        _free[u] = false;
        for (int v = 1; v <= g.n(); ++v) {
            if (_free[v] && d[v] > d[u] + g[u][v]) {
                d[v] = d[u] + g[u][v];
                trace[v] = u;
            }
        }
    } while (true);
    printShortestPath();
}

void GraphAlgorithm::updateHeap(int v) {
    int parent, child;
    child = _pos[v];
    if (NO_NODE == child) {
        child = ++nHeap;
    }
    parent = child / 2;
    while (parent > 0 && (d[_heap[parent]] > d[v])) {
        _heap[child] = _heap[parent];
        _pos[_heap[child]] = child;
        child = parent;
        parent = child / 2;
    }
    _heap[child] = v;
    _pos[v] = child;
}

int GraphAlgorithm::popHeap() {
    int ret = _heap[1];
    int r, c, v;
    v = _heap[nHeap--];
    r = 1;
    while (r * 2 <= nHeap) {
        c = r * 2;
        if (c < nHeap && (d[_heap[c+1]] < d[_heap[c]])) ++c;
        if (d[v] <= d[_heap[c]]) break;
        _heap[r] = _heap[c];
        _pos[_heap[r]] = r;
        r = c;
    }
    _heap[r] = v;
    _pos[v] = r;
    return ret;
}

void GraphAlgorithm::dijkstraHeap() {
    fout << "Running Dijkstra heap to find shortest path (no negative weighted edge):" << endl;
    if (!_isFindingPath) {
        fout << "ERROR: Did not enable searching mode" << endl;
        return;
    }
    d[s] = 0;
    updateHeap(s);
    do {
        int u = popHeap();
//        fout << "Stablize node " << u << endl;
        if (f == u) break;
        _free[u] = false;
//        fout << "header[" << u << "] = " << g.header(u) << " header[" << u+1 << "] = " << g.header(u+1) << endl;
        for (int iv = g.header(u) + 1; iv <= g.header(u+1); ++iv) {
            int v = g.adj(iv);
//            fout << "Checking adjacent node " << v << endl;
            if (_free[v] && d[v] > d[u] + g.adjCost(iv)) {
                d[v] = d[u] + g.adjCost(iv);
//                fout << "Updating d[" << v << "] = " << d[v] << endl;
                trace[v] = u;
                updateHeap(v);
            }
        }
//        fout << endl;
    } while (0 != nHeap);
    printShortestPath();
}

void GraphAlgorithm::numberize() {
    int deg[MAX] = {0, };
    for (int u = 1; u <= g.n() - 1; ++u) {
        for (int v = u + 1; v <= g.n(); ++v) {
            if (g[u][v] < INFINITY) ++deg[v];
            if (g[v][u] < INFINITY) ++deg[u];
        }
    }
    count = 0;
    for (int u = 1; u <= g.n(); ++u) {
        if (0 == deg[u]) {
            listTopo[++count] = u;
        }
    }
    
    int front = 1;
    int u;
    while (front <= count) {
        u = listTopo[front++];
        for (int v = 1; v <= g.n(); ++v) {
            if (INFINITY != g[u][v]) {
                --deg[v];
                if (0 == deg[v]) {
                    listTopo[++count] = v;
                }
            }
        }
    }
}

void GraphAlgorithm::topoOrdering() {
    d[s] = 0;
    
    numberize();
    for (int i = 1; i <= g.n() - 1; ++i) {
        for (int j = i + 1; j <= g.n(); ++j) {
            int u = listTopo[i];
            int v = listTopo[j];
//            fout << "i = " << i << " j = " << j << " u = " << u << " v = " << v << endl;
            if (d[v] > d[u] + g[u][v]) {
                d[v] = d[u] + g[u][v];
                fout << "Optimize " << v << " from " << u << ". New d[" << v << "] = " << d[v] << endl;
                trace[v] = u;
            }
        }
    }
    printShortestPath();
}

}
