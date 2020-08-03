//
//  graph_circuit.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 8/2/20.
//

#include "graph_generic.h"

namespace graph {
bool GraphAlgorithm::canGoBack(const int &x, const int &y) {
//    cout << "Trying edge: " << x << "->" << y << endl;
    --g[x][y]; --g[y][x];
    bool visited[MAX] = {false, };
    visited[y] = true;
    
    Util::pushQueue(y);
//    cout << "BFS from " << y << ":" << endl;
    while (!Util::queueEmpty()) {
        int u = Util::popQueue();
//        cout << "Check " << u << endl;
        for (int v = 1; v <= g.n(); ++v) {
            if (!visited[v] && g[u][v]) {
                visited[v] = true;
                Util::pushQueue(v);
//                cout << "Pushing " << v << endl;
                if (x == v) {
//                    cout << "Reach " << x << ". End current loop of " << u << endl;
                    break;
                }
            }
        }
    }
    
    ++g[x][y]; ++g[y][x];
    return visited[x];
}
void GraphAlgorithm::fleury() {
    fout << "Running fleury algorithm to find Euler circuit:" << endl;
    if (DIRECTED == g.dType()) {
        cerr << "Unable to work on directed graph!" << endl;
        exit(4);
    }
    int current, next;
    current = 1;
    fout << current << " ";
    
    do {
        next = NO_NODE;
        for (int v = 1; v <= g.n(); ++v) {
            if (g[current][v]) {
                next = v;
//                cout << (temp ? "Can " : "Cannot ");
//                cout << "go back from " << next << " to " << current << endl;
                if (canGoBack(current, next)) break;
            }
        }
        if (NO_NODE != next) {
            --g[current][next]; --g[next][current];
            fout << next << " ";
//            cout << "Choosing path: " << current << "->" << next << endl;
            current = next;
        }
    } while(NO_NODE != next);
}

void GraphAlgorithm::findEulerUsingStack() {
    fout << "Finding Euler circuit using stack:" << endl;
    if (DIRECTED == g.dType()) {
        cerr << "Unable to work on directed graph!" << endl;
        exit(4);
    }
    Util::push(1);
    while (!Util::empty()) {
        int u = Util::get();
        for (int v = 1; v <= g.n(); ++v) {
            if (g[u][v]) {
                --g[u][v]; --g[v][u];
                Util::push(v);
                break;
            }
        }
        if (u == Util::get()) {
            fout << Util::pop() << " ";
        }
    }
}

void GraphAlgorithm::printHamiltonCircuit() {
    for (int i = 1; i <= g.n(); ++i) fout << x[i] << " ";
    fout << x[1] << endl;
}

void GraphAlgorithm::_try(int i) {
    for (int j = 1; j <= g.n(); ++j) {
        if (_free[j] && g[x[i-1]][j]) {
            x[i] = j;
            if (i < g.n()) {
                _free[j] = false;
                _try(i + 1);
                _free[j] = true;
            }
            else {
                if (g[j][x[1]]) {
                    printHamiltonCircuit();
                }
            }
        }
    }
}

void GraphAlgorithm::findAllHamiltonCircuits() {
    fout << "Listing Hamilton circuits using backtracking:" << endl;
    if (DIRECTED == g.dType()) {
        cerr << "Unable to work on directed graph!" << endl;
        exit(4);
    }
    x[1] = 1; _free[1] = false;
    _try(2);
}

}
