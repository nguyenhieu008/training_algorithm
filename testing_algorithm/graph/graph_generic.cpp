#include "graph_generic.h"

namespace graph {
void Graph::input(const string &inFile, const string &outFile) {
    fin.open(inFile);
    fout.open(outFile);
    int m, u, v;
    fin >> n >> m >> s >> f;
    for (int i = 0 ; i < m; ++i) {
        fin >> u >> v;
        a[u][v] = a[v][u] = 1;
    }
}

void Graph::printPath() {
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
}