#include "graph_generic.h"

namespace graph {

void Graph::mainGraph() {
    GraphAlgorithm g("data/hamilton.inp", "data/graph.out", UNDIRECTED, SINGLE);
    g.input();
    g.findAllHamiltonCircuits();
}
}
    
