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
    }
}

void GraphAlgorithm::dijkstraHeap() {
    fout << "Running Dijkstra heap to find shortest path (no negative weighted edge):" << endl;
    if (!_isFindingPath) {
        fout << "ERROR: Did not enable searching mode" << endl;
        return;
    }
    d[s] = 0;
}

}