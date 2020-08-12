#include "graph_generic.h"
#include <unistd.h>

namespace graph {

void GraphAlgorithm::mainGraph() {
    GraphAlgorithm g("data/flow.inp", "data/graph.out", DIRECTED, SINGLE, WEIGHT);
    g.input(false, true);
    g.fordFulkerson();
}
}
    
