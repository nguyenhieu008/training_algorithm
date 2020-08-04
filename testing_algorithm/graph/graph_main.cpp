#include "graph_generic.h"

namespace graph {

void Graph::mainGraph() {
    GraphAlgorithm g("data/minpath.inp", "data/graph.out", DIRECTED, SINGLE, WEIGHT);
    g.input(true);
    g.dijkstra();
}
}
    
