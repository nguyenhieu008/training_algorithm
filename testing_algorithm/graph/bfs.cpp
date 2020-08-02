#include "graph_generic.h"

namespace graph {
void GraphSearch::bfs() {
    fout << "Running BFS:" << endl;
    fout << "From " << s << " you can visit: " << endl;
    trace[s] = VIRTUAL_ROOT;
    Util::pushQueue(s);

    while (!Util::queueEmpty()) {
        int u = Util::popQueue();
        fout << u << ", ";
        for (int v = 1; v <= g.n(); ++v) {
            if (0 == trace[v] && g[u][v]) {
                trace[v] = u;
                Util::pushQueue(v);
            }
        }
    }
    fout << endl;

    
}

void GraphSearch::loang(int t_old[], int t_oldSize, int t_new[], int &t_newSize) {
    int newSize = 0;
    for (int i = 0; i < t_oldSize; ++i) {
        int u = t_old[i];
        fout << u << ", ";
        for (int v = 1; v <= g.n(); ++v) {
            if (NO_NODE == trace[v] && g[u][v]) {
                t_new[newSize++] = v;
                trace[v] = u;
            }
        }
    }
    t_newSize = newSize;
}

void GraphSearch::bfsLoang() {
    fout << "Running BFS loang: " << endl;
    fout << "From " << s << " you can visit: " << endl;
    
    int _x[MAX], _y[MAX];
    int _oldSize = 0, _newSize;
    bool flag = true;
    
    trace[s] = VIRTUAL_ROOT;
    _x[_oldSize++] = s;
     
    while (_oldSize > 0) {
        if (flag) loang(_x, _oldSize, _y, _newSize);
        else loang(_y, _oldSize, _x, _newSize);
        flag = !flag;
        _oldSize = _newSize;
    }
    fout << endl;
}
}
