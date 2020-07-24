#include "graph_generic.h"

namespace graph {

void Graph::mainGraph() {
    GraphConnectivity g("graph_connectivity_bridges.inp", "graph_connectivity.out", UNDIRECTED);
    g.detectBridges();
}
}
    