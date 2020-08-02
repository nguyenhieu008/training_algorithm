#include "graph_generic.h"
#include <cstring>

namespace graph {

GraphConnectivity::GraphConnectivity(const string &inFile, const string &outFile, const GraphDirectivityType &dType) : InputGraph(inFile, outFile, dType, SINGLE), numbering{0, }, count(0), componentCount(1), nC{0, }, _mark{false, } {
    memset(_free, true, sizeof(_free));
    if (DIRECTED == g.dType()) for (int i = 1; i <= g.n(); ++i) g[i][i] = true;
    input();
}

GraphCircuit::GraphCircuit(const string &inFile, const string &outFile, const GraphDirectivityType &dType, const GraphNumerousType &nType) : InputGraph(inFile, outFile, dType, nType) {
    input();
    printGraph();
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

void InputGraph::input() {
    if (SINGLE == g.nType()) {
        int u, v, m;
        fin >> m;
        for (int i = 0 ; i < m; ++i) {
            fin >> u >> v;
            g[u][v] = true;
            if (UNDIRECTED == g.dType()) g[v][u] = true;
        }
    }
    else if (MULTIPLE == g.nType()) {
        int temp1, temp2 = 0;
        int u = 0, v = 0, k;
        while (fin >> temp1) {
            if (0 == temp2) u = temp1;
            else if (1 == temp2) v = temp1;
            else if (2 == temp2){
                k = temp1;
                g[u][v] = k;
                if (UNDIRECTED == g.dType()) g[v][u] = k;
            }
            ++temp2 %= 3;
        }
    }
    else {
        fout << "ERROR: Wrong directivity type of graph!";
        exit(3);
    }
}

void GraphSearch::input() {
    int m, u, v;
    fin >> m >> s >> f;
    for (int i = 0 ; i < m; ++i) {
        fin >> u >> v;
        g[u][v]++;
        if (UNDIRECTED == g.dType()) g[v][u]++;
    }
}

void InputGraph::printGraph() {
    fout << "Printing " << (UNDIRECTED == g.dType()? "Undirected" : DIRECTED == g.dType()? "Directed" : "Undefined") <<  " Graph: " << endl;
    for (int i = 1; i <= g.n(); ++i) {
        for (int j = 1; j <= g.n(); ++j) {
            fout << g[i][j];
        }
        fout << endl;
    }
    fout << endl;
}

int Util::_stackSize = 0;
int Util::_first = 0, Util::_last = 0;
int Util::_queue[] = {};
int Util::_stack[] = {};

void Util::push(int u){
    if (_stackSize >= MAX) {
        cerr << "Error: Push more than max size" << endl;
        exit(1);
    }
    _stack[_stackSize++] = u;
}
int Util::pop() {
    if (_stackSize <= 0) {
        cerr << "Warning: Trying to pop empty stack" << endl;
        return NO_NODE;
    }
    return _stack[--_stackSize];
}

int Util::get() {
    if (_stackSize <= 0) {
        cerr << "Warning: Trying to get empty stack" << endl;
        return NO_NODE;
    }
    return _stack[_stackSize-1];
}

bool Util::empty() {
    return _stackSize <= 0;
}

void Util::pushQueue(int u) {
    if (_last >= MAX) {
        cerr << "Error: Queue is at max. Cannot push" << endl;
        exit(2);
    }  
    _queue[_last++] = u;
}
int Util::popQueue() {
    if (_first >= _last) {
        cerr << "Warning: Queue is empty" << endl;
        return NO_NODE;
    }
    return _queue[_first++];
}

bool Util::queueEmpty() {
    return _first >= _last;
}

}
