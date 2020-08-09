//
//  graph_network_flow.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 8/9/20.
//

#include "graph_generic.h"

namespace graph {
void GraphAlgorithm::createGf() {
    int u, v;
    for (u = 1; u <= g.n(); ++u) {
        for (v = 1; v <= g.n(); ++v) {
            _gf[u][v] = INFINITY;
        }
    }
    for (u = 1; u <= g.n(); ++u) {
        for (v = 1; v <= g.n(); ++v) {
            if (g[u][v]) {
                if (_f[u][v] < g[u][v]) {
                    _gf[u][v] = g[u][v] - _f[u][v];
                }
                if (_f[u][v] > 0) {
                    _gf[v][u] = -_f[u][v] ;
                }
            }
        }
    }
    
    fout << "Current flow: " << endl;
    for (u = 1; u <= g.n(); ++u) {
        for (v = 1; v <= g.n(); ++v) {
            fout << _f[u][v] << "\t";
        }
        fout << endl;
    }
    fout << "Adjusted increment flow graph:" << endl;
    for (u = 1; u <= g.n(); ++u) {
        for (v = 1; v <= g.n(); ++v) {
            fout << (_gf[u][v] == INFINITY? "INF" : to_string(_gf[u][v])) << "\t";
        }
        fout << endl;
    }
}

bool GraphAlgorithm::findNetworkPath() {
    Util::resetQueue();
    for (int i = 1; i <= g.n(); ++i) _free[i] = true;
    Util::pushQueue(a);
    _free[a] = false;
    while (!Util::queueEmpty()) {
        int u = Util::popQueue();
        for (int v = 1; v <= g.n(); ++v) {
            if (_free[v] && INFINITY != _gf[u][v]) {
                trace[v] = u;
                if (b == v) {
                    return true;
                }
                _free[v] = false;
                Util::pushQueue(v);
            }
        }
    }
    return false;
}

void GraphAlgorithm::increaseFlow() {
    int u, v = b, incVal = INFINITY;
    fout << "Increment path: " << endl;
    fout << v ;
    for (v = b; a != v; v = u) {
        u = trace[v];
        fout << "<-" << u;
        if (abs(_gf[u][v]) < incVal) incVal = abs(_gf[u][v]);
    }
    fout << endl;
    for (v = b; a != v; v = u) {
        u = trace[v];
        if (_gf[u][v] > 0) _f[u][v] += incVal;
        else _f[v][u] -= incVal;
    }
}

void GraphAlgorithm::printMaxFlow() {
    int m = 0;
    
    for (int u = 1; u <= g.n(); ++u) {
        for (int v = 1; v <= g.n(); ++v) {
            if (g[u][v]) {
                fout << "f(" << u << ", " << v << ") = " << _f[u][v] << endl;
                if (a == u) {
                    m += _f[a][v];
                }
            }
        }
    }
    fout << "Max flow: " << m << endl;
}

void GraphAlgorithm::maxFlow() {
    fout << "Running max flow algorithm: " << endl;
    if (!_isNetworking) {
        fout << "Graph is not a network!" << endl;
        return;
    }
    if (WEIGHT != g.wType() || DIRECTED != g.dType()) {
        fout << "This type of graph not supported!" << endl;
        return;
    }
    
    for (int i = 1; i <= g.n(); ++i) {
        for (int j = 1; j <= g.n(); ++j) {
            _f[i][j] = 0;
        }
    }
    do {
        createGf();
        if (!findNetworkPath()) break;
        increaseFlow();
    } while (true);
    printMaxFlow();
}
}
