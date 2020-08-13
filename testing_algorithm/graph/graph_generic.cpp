#include "graph_generic.h"
#include <cstring>

namespace graph {

InputGraph::InputGraph(const string &inFile, const string &outFile, const GraphPartitionType &bType, const GraphDirectivityType &dType, const GraphNumerousType &nType, const GraphWeightType &wType) : 
    fin(inFile), fout(outFile), g(dType, nType, wType), _isFindingPath(false) {
    if (MULTIPLE == g.nType() && WEIGHT == g.wType()) {
        fout << "ERROR: Dont support weighted multiple graph!";
        exit(1);
        return;
    }
    _bType = bType;
    if (NORMAL == bType) {
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
    else {
        fin >> bg.m() >> bg.n();
    }
}

GraphAlgorithm::GraphAlgorithm(const string &inFile, const string &outFile, const GraphPartitionType &bType, const GraphDirectivityType &dType, const GraphNumerousType &nType, const GraphWeightType &wType) : 
    InputGraph(inFile, outFile, bType, dType, nType, wType), trace{NO_NODE, }, numbering{0, }, count(0), componentCount(1), nC{0, }, _mark{false, }, x{NO_NODE, } {
    memset(_free, true, sizeof(_free));

    if (NORMAL == _bType) {
        _f = new int*[MAX];
        _gf = new int*[MAX];
        traceFloyd = new int*[MAX];
        for (int i = 1; i < MAX; ++i) {
            _f[i] = new int[MAX];
            _gf[i] = new int[MAX];
            traceFloyd[i] = new int[MAX];
        }

        for (int i = 1; i <= g.n(); ++i) {
            d[i] = INFINITY;
            _pos[i] = NO_NODE;
            label[i] = -1; // negative number of node in tree root i
        }
        nHeap = 0;
        for (int i = 1; i <= g.n(); ++i) {
            for (int j = 1; j <= g.n(); ++j) {
                traceFloyd[i][j] = j;
                _f[i][j] = 0;
            }
        }
    }    
    else {
        for (int i = 1; i <= bg.m(); ++i) matchX[i] = NO_NODE;
        for (int i = 1; i <= bg.n(); ++i) matchY[i] = NO_NODE;
    }
}

void InputGraph::input(const bool &finding, const bool &network) {
    if (NORMAL == _bType) {
        if (finding && network) {
            fout << "ERROR: Do not support searching path along with finding max flow of network!" << endl;
            exit(5);
        }
        _isFindingPath = finding;
        _isNetworking = network;

        if (SINGLE == g.nType()) {
            int u, v, c;
            fin >> g.m();
            
            if (_isFindingPath) fin >> s >> f;
            else if (_isNetworking) {
                fin >> a >> b;
                for (int ii = 1; ii <= g.n(); ++ii) {
                    for (int jj = 1; jj <= g.n(); ++jj) {
                        g[ii][jj] = 0;
                    }
                }
            }

            for (int i = 1; i <= g.m(); ++i) {
                fin >> u >> v;
                c = 1;

                if (WEIGHT == g.wType()) {
                    fin >> c;
                    g[u][v] = c;
                }
                
                g[u][v] = c;
                ++g.header(u);
                if (UNDIRECTED == g.dType()) {
                    g[v][u] = c;    
                    ++g.header(v);
                } 
                
                Edge e(u, v, c);
                g.e(i) = e;
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
        g.header(g.n()+1) = g.m();
    }
    else {
        int u = 0, v = 0;
        while (fin >> u) {
            fin >> v;
            bg[u][v] = true;
        }
    }

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
    if (NORMAL == _bType) {
        fout << "Printing Normal, " << (UNDIRECTED == g.dType()? "Undirected, " : "Directed, ") << (SINGLE == g.nType()? "Single, " : "Multiple, ") << (UNWEIGHT == g.wType()? "Unweighted " : " Weighted ") <<  "graph: " << endl;
        for (int i = 1; i <= g.n(); ++i) {
            for (int j = 1; j <= g.n(); ++j) {
                fout << g[i][j] << "\t";
            }
            fout << endl;
        }
        fout << endl;
    }
    else {
        fout << "Printing Bipartite Graph: " << endl;
        for (int i = 1; i <= bg.m(); ++i) {
            for (int j = 1; j <= bg.n(); ++j) {
                fout << bg[i][j] << "\t";
            }
            fout << endl;
        }
        fout << endl;
    }

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

void Util::resetQueue() {
    Util::_first = 0;
    Util::_last = 0;
}

}
