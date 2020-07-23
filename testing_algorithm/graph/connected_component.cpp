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
}