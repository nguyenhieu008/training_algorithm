#include "graph_generic.h"
#include <unistd.h>

namespace graph {

void GraphAlgorithm::mainGraph() {
    GraphAlgorithm g("data/minpath.inp", "data/graph.out", DIRECTED, SINGLE, WEIGHT);
    g.input(true);
    g.topoOrdering();
}
}
    
