#include "graph_generic.h"
#include <cstring>

namespace graph {

InputGraph::InputGraph(const string &inFile, const string &outFile, const GraphDirectivityType &dType, const GraphNumerousType &nType, const GraphWeightType &wType) : 
    fin(inFile), fout(outFile), g(dType, nType, wType), _isFindingPath(false) {
    if (MULTIPLE == g.nType() && WEIGHT == g.wType()) {
        fout << "ERROR: Dont support weighted multiple graph!";
        exit(1);
        return;
    }
    fin >> g.n();
    if (WEIGHT == g.wType()) {
        for (int i = 1; i <= g.n(); ++i) {
            g[i][i] = 0;
            for (int j = 1; j <= g.n(); ++j) {
                if (i != j) g[i][j] = INFINITY;
            }
        }
    }
    for (int i = 1; i <= g.n(); ++i) {
        g.header(i) = 0;
    }
}

GraphAlgorithm::GraphAlgorithm(const string &inFile, const string &outFile, const GraphDirectivityType &dType, const GraphNumerousType &nType, const GraphWeightType &wType) : 
    InputGraph(inFile, outFile, dType, nType, wType), trace{NO_NODE, }, numbering{0, }, count(0), componentCount(1), nC{0, }, _mark{false, }, x{NO_NODE, } {
    memset(_free, true, sizeof(_free));
    
    for (int i = 1; i <= g.n(); ++i) {
        d[i] = INFINITY;
        _pos[i] = NO_NODE;
    }
    nHeap = 0;  
}
void InputGraph::input(const bool &finding) {
    _isFindingPath = finding;
    int m = 0;

    if (SINGLE == g.nType()) {
        int u, v, c;
        fin >> m;
        
        if (_isFindingPath) fin >> s >> f;

        for (int i = 0 ; i < m; ++i) {
            fin >> u >> v;
            ++g.header(u);
            if (UNDIRECTED == g.dType()) ++g.header(v);
            if (WEIGHT == g.wType()) {
                fin >> c;
                g[u][v] = c;
                if (UNDIRECTED == g.dType()) g[v][u] = c;
            }
            else {
                g[u][v] = true;
                if (UNDIRECTED == g.dType()) g[v][u] = true;
            }
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

    for (int i = 2; i <= g.n(); ++i) {
        g.header(i) += g.header(i-1);
    }
    
    for (int i = 1; i <= g.n(); ++i) {
        for (int j = 1; j <= g.n(); ++j) {
            if (0 != g[i][j] && INFINITY != g[i][j]) {
//                fout << "Reduce header i = " << i << " j = " << j << endl;
                g.adj(g.header(i)) = j;
                if (WEIGHT == g.wType()) g.adjCost(g.header(i)) = g[i][j];
                --g.header(i);
            }
        }
    }
    g.header(g.n()+1) = m;
    
//    fout << "Header: ";
//    for (int i = 1; i <= g.n() + 1; ++i) {
//        fout << g.header(i) << " ";
//    }
//    fout << endl;

    printGraph();
}


void GraphAlgorithm::printPath() {
    if (!_isFindingPath) {
        fout << "Warning: Trying to print path but not enable searching!" << endl;
        return;
    }
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


void InputGraph::printGraph() {
    fout << "Printing " << (UNDIRECTED == g.dType()? "Undirected, " : "Directed, ") << (SINGLE == g.nType()? "Single, " : "Multiple, ") << (UNWEIGHT == g.wType()? "Unweighted " : " Weighted ") <<  "graph: " << endl;
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
