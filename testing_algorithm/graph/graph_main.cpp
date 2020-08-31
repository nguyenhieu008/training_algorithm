#include "graph_generic.h"
#include <unistd.h>

namespace graph {

void GraphAlgorithm::mainGraph() {
    GraphAlgorithm g("data/gmatch.inp", "data/graph.out", NORMAL, UNDIRECTED, SINGLE, UNWEIGHT);
    g.input();
    g.edmonds();
//    g.augmentingPath();
}
}
    
