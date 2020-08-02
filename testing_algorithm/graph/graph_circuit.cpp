//
//  graph_circuit.cpp
//  testing_algorithm
//
//  Created by Nguyen Trung Hieu on 8/2/20.
//

#include "graph_generic.h"

namespace graph {
bool GraphCircuit::canGoBack(const int &x, const int &y) {
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
void GraphCircuit::fleury() {
    fout << "Running fleury algorithm to find Euler circuit:" << endl;
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

void GraphCircuit::findEulerUsingStack() {
    fout << "Finding Euler circuit using stack:" << endl;
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
}
