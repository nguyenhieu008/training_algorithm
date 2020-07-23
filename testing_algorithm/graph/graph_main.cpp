#include "graph_generic.h"

namespace graph {

void Graph::mainGraph() {
    GraphConnectivity g("graph_connectivity.inp", "graph_connectivity.out");
    g.warshall();
}
}
    