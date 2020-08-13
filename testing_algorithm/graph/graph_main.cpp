#include "graph_generic.h"
#include <unistd.h>

namespace graph {

void GraphAlgorithm::mainGraph() {
    GraphAlgorithm g("data/match.inp", "data/graph.out", BIPARTITE, DIRECTED, SINGLE, WEIGHT);
    g.input();
}
}
    
