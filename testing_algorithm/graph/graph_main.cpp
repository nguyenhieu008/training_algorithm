#include "graph_generic.h"
#include <unistd.h>

namespace graph {

void GraphAlgorithm::mainGraph() {
    GraphAlgorithm g("data/assign.inp", "data/graph.out", BIPARTITE, UNDIRECTED, SINGLE, WEIGHT);
    g.input();
    g.hungariImproved();
//    g.augmentingPath();
}
}
    
