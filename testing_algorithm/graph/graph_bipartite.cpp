#include "graph_generic.h"

namespace graph {
int GraphAlgorithm::findAugmentingPath() {
    Util::resetQueue();
    for (int i = 1; i <= MAX; ++i) trace[i] = 0;

    for (int i = 1; i <= bg.m(); ++i) {
        if (NO_NODE == matchX[i]) {
            Util::pushQueue(i);
        }
    }

    while (!Util::queueEmpty()) {
        int i = Util::popQueue();
        for (int j = 1; j <= bg.n(); ++j) {
//            fout << "Try edge: " << i << "->" << j << endl;
            if (NO_NODE == trace[j] && bg[i][j] && j != matchX[i]) {
                trace[j] = i;
//                fout << "Add the edge " << i << "->" << j << " to path. ";
                if (NO_NODE == matchY[j]) {
//                    fout << "This node is unmatched node." << endl;
                    return j;
                }
//                fout << "Push X = " << matchY[j] << " to queue." << endl;
                Util::pushQueue(matchY[j]);
            }
        }
    }
    return NO_NODE;
}

void GraphAlgorithm::enlarge(int f) {
    int x, next;
    do {
        x = trace[f];
        next = matchX[x];
        matchX[x] = f;
        matchY[f] = x;
        f = next;
    } while (NO_NODE != f);
}

void GraphAlgorithm::printMaximumMatching() {
    int count = 1;
    fout << "Match:" << endl;
    for (int i = 1; i <= bg.m(); ++i) {
        if (NO_NODE != matchX[i]) {
            fout << count++ << ") X[" << i << "] - Y[" << matchX[i] << "]" << endl;
        }
    }
}

void GraphAlgorithm::augmentingPath() {
    fout << "Running augmenting path algorithm to find maximum matching on bipartite graph:" << endl;
    if (BIPARTITE != _pType) {
        fout << "ERROR: This algorithm runs on bipartite graph only!" << endl;
        return;
    }
    int count = 1;
    int finish = 0;
    do {
        finish = findAugmentingPath();
        if (NO_NODE != finish) enlarge(finish);
//        fout << "Matching after step " << count++ << ". ";
//        printMaximumMatching();
//        fout << endl;
    } while (NO_NODE != finish);
    
    printMaximumMatching();
}
}
