#include "graph_generic.h"
#include <unordered_set>
//using namespace std;

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
        fout << "New match X[" << x << "] - Y[" << f << "] next Y = " << next << endl;
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
//    int count = 1;
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

void GraphAlgorithm::initHungary() {
    for (int i = 1; i <= k; ++i) {
        fx[i] = INF;
        for (int j = 1; j <= k; ++j) {
            if (bg[i][j] < fx[i]) fx[i] = bg[i][j];
        }
    }
    for (int j = 1; j <= k; ++j) {
        fy[j] = INF;
        for (int i = 1; i <= k; ++i) {
            if (bg[i][j] - fx[i] < fy[j]) fy[j] = bg[i][j] - fx[i];
        }
    }
}

int GraphAlgorithm::getC(int i, int j) {
    return bg[i][j] - fx[i] - fy[j];
}

int GraphAlgorithm::findAugmentingPath(int s) {
    for (int j = 1; j <= k; ++j) trace[j] = NO_NODE;
    Util::resetQueue();
    
    Util::pushQueue(s);
    while (!Util::queueEmpty()) {
        int i = Util::popQueue();
        for (int j = 1; j <= k; ++j) {
//            fout << "Try edge: " << i << "->" << j << endl;
            if (NO_NODE == trace[j] && 0 == getC(i, j)) {
                trace[j] = i;
                fout << "Add the edge " << i << "->" << j << " to path. ";
                if (NO_NODE == matchY[j]) {
                    fout << "Node j = " << j << " is unmatched node." << endl;
                    return j;
                }
                else {
                    fout << "Push X = " << matchY[j] << " to queue." << endl;
                    Util::pushQueue(matchY[j]);
                }

            }
        }
    }
    return NO_NODE;
}

void GraphAlgorithm::subX_addY(int s) {
    unordered_set<int> visitedX, visitedY;
    int delta = INF;
    visitedX.insert(s);
    for (int j = 1; j <= k; ++j) {
        if (trace[j]) {
            visitedY.insert(j);
            visitedX.insert(matchY[j]);
        }
    }
    
    fout << "Visited x: ";
    for (auto x : visitedX) fout << x << ", ";
    fout << endl << "Visited y: ";
    for (auto y : visitedY) fout << y << ", ";
    
    for (int i = 1; i <= k; ++i) {
        if (visitedX.find(i) != visitedX.end()) {
            for (int j = 1; j <= k; ++j) {
                if (visitedY.find(j) == visitedY.end() && getC(i, j) < delta) {
                    delta = getC(i, j);
                }
            }
        }
    }
    fout << endl << "Delta = " << delta << endl;
    
    for (int t = 1; t <= k; ++t) {
        if (visitedX.find(t) != visitedX.end()) fx[t] += delta;
        if (visitedY.find(t) != visitedY.end()) fy[t] -= delta;
    }
}

void GraphAlgorithm::printHungariGraph() {
    fout << "Printing Hungari Graph: " << endl;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) {
            fout << getC(i, j) << "\t";
        }
        fout << "\t" << fx[i] << endl;;
    }
    fout << endl;
    for (int j = 1; j <= k; ++j) {
        fout << fy[j] << "\t";
    }
    fout << endl;
}

void GraphAlgorithm::printHungariResult() {
    fout << "Optimal assignment:" << endl;
    int y, w = 0, count = 0;
    
    for (int x = 1; x <= bg.m(); ++x) {
        y = matchX[x];
        if (bg[x][y] < INF) {
            fout << "\t" << ++count << ") X[" << x << "] - Y[" << y << "] " << bg[x][y] << endl;
            w += bg[x][y];
        }
    }
    fout << "Cost: " << w << endl;
}

void GraphAlgorithm::hungari() {
    fout << "Running Hungari algorithm to find maximum matching with minimum weight on bipartite graph:" << endl;
    if (BIPARTITE != _pType) {
        fout << "ERROR: This algorithm runs on bipartite graph only!" << endl;
        return;
    }
    if (WEIGHT != g.wType()) {
        fout << "ERROR: This algorithm runs on weight graph only!" << endl;
        return;
    }
    
    initHungary();
    printHungariGraph();
    for (int x = 1; x <= k; ++x) {
        int s = x, f;
        do {
            f = findAugmentingPath(s);
            if (NO_NODE == f) {
                fout << "Not found unmatched Y. Rotating Hungari graph" << endl;
                subX_addY(s);
                printHungariGraph();
            }
        } while (NO_NODE == f);
        fout << "Found unmatched f = " << f << endl;
        enlarge(f);
        printHungariGraph();
    }
    printHungariResult();
}
}
