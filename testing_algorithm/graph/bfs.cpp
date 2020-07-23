#include "graph_generic.h"

namespace graph {
void GraphSearch::bfs() {
    fout << "Running BFS:" << endl;
    fout << "From " << s << " you can visit: " << endl;
    trace[s] = VIRTUAL_ROOT;
    pushQueue(s);

    while (!queueEmpty()) {
        int u = popQueue();
        fout << u << ", ";
        for (int v = 1; v <= n; ++v) {
            if (0 == trace[v] && a[u][v]) {
                trace[v] = u;
                pushQueue(v);
            }
        }
    }
    fout << endl;

    
}

void GraphSearch::loang(int t_old[], int t_new[]) {
    _newSize = 0;
    for (int i = 0; i < _oldSize; ++i) {
        int u = t_old[i];
        fout << u << ", ";
        for (int v = 1; v <= n; ++v) {
            if (0 == trace[v] && a[u][v]) {
                t_new[_newSize++] = v;
                trace[v] = u;
            }
        }
    }
}

void GraphSearch::bfsLoang() {
    fout << "Running BFS loang: " << endl;
    fout << "From " << s << " you can visit: " << endl;
    trace[s] = VIRTUAL_ROOT;
    _oldSize = 0;
    _x[_oldSize++] = s;
    bool flag = true;
     
    while (_oldSize > 0) {
        if (flag) loang(_x, _y);
        else loang(_y, _x);
        flag = !flag;
        _oldSize = _newSize;
    }
    fout << endl;
}
}