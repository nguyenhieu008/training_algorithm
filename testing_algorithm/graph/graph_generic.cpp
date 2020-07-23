#include "graph_generic.h"
#include <cstring>

namespace graph {
void Graph::input() {
    fin >> n >> m;
}

void SingleGraph::input() {
    int u, v;
    for (int i = 0 ; i < m; ++i) {
        fin >> u >> v;
        a[u][v] = a[v][u] = true;
    }
}

void SingleGraph::printGraph() {
    fout << "Printing Graph: " << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            fout << a[i][j];
        }
        fout << endl;
    }
    fout << endl;
}

void GraphSearch::input() {
    Graph::input();
    fin >> s >> f;
    SingleGraph::input();
}

void GraphConnectivity::input() {
    Graph::input();
    for (int i = 1; i <= n; ++i) a[i][i] = true;
    memset(_free, true, sizeof(_free));
    SingleGraph::input();
}


void GraphSearch::printPath() {
    fout << "Path from " << s << " to " << f << ": ";
    if (0 == trace[f]) fout << "not found!" << endl;
    else {
        while (f != s) {
            fout << f << "<-";
            f = trace[f];
        }
        fout << s << endl;
    }
}

void GraphSearch::push(int u){
    if (_stackSize >= n) {
        cerr << "Error: Push more than max size" << endl;
        exit(1);
    }
    _stack[_stackSize++] = u;
}
int GraphSearch::pop() {
    if (_stackSize <= 0) {
        cerr << "Warning: Trying to pop empty stack" << endl;
        return NO_NODE;
    }
    return _stack[--_stackSize];
}

void GraphSearch::pushQueue(int u) {
    if (_last >= n) {
        cerr << "Error: Queue is at max. Cannot push" << endl;
        exit(2);
    }  
    _queue[_last++] = u;
}
int GraphSearch::popQueue() {
    if (_first >= _last) {
        cerr << "Warning: Queue is empty" << endl;
        return NO_NODE;
    }
    return _queue[_first++];
}

bool GraphSearch::queueEmpty() {
    return _first >= _last;
}

}