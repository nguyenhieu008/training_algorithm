#include "graph_generic.h"
#include <unistd.h>

namespace graph {

void GraphAlgorithm::mainGraph() {
    GraphAlgorithm g("data/mintree.inp", "data/graph.out", UNDIRECTED, SINGLE, WEIGHT);
    g.input();
    g.prim();
}
}
    
