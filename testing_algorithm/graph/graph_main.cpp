#include "graph_generic.h"

namespace graph {

void Graph::mainGraph() {
    GraphCircuit g("euler.inp", "euler.out");
    g.findEulerUsingStack();
}
}
    
