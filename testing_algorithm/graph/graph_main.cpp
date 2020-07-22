#include "graph_generic.h"

namespace graph {

void Graph::mainGraph() {
    Graph g;
    g.input("graph.inp", "graph.out");
    g.dfsBacktrack();
    g.printPath();
}
}
    