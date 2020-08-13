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
            if (NO_NODE == trace[j] && bg[i][j] && j != matchX[i]) {
                trace[j] = i;
                if (NO_NODE == matchY[j]) {
                    return j;
                }
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

void GraphAlgorithm::augmentingPath() {

}
}