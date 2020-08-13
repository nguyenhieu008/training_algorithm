#include "graph_generic.h"
#include <unistd.h>

namespace graph {

void GraphAlgorithm::mainGraph() {
    GraphAlgorithm g("data/match.inp", "data/graph.out", BIPARTITE);
    g.input();
    g.augmentingPath();
}
}
    
