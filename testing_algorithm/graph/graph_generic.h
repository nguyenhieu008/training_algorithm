#include <fstream>
#include <iostream>

using namespace std;
namespace graph {
class Graph {
public:
    Graph() : _stackSize(0) {

    }

    void input(const string &inFile, const string &outFile);
    void dfs() {
        fout << "Running DFS:" << endl;
        fout << "From " << s << " you can visit:" << endl;
        trace[s] = VIRTUAL_ROOT;
        dfs(s);
        fout << endl;
    }
    
    void dfsStack();
    void dfsBacktrack();
    void printPath();

    static void mainGraph();

private:
    static const int MAX = 101;
    static const int VIRTUAL_ROOT = -1;
    static const int NO_NODE = 0;

    ifstream fin;
    ofstream fout;
    int n, s, f;
    int a[MAX][MAX] = {{0, }, };
    int trace[MAX] = {NO_NODE, };
    int _stack[MAX], _stackSize;

    void push(int u);
    int pop();
    void dfs(int u);
    int findNext(int u);
}; 
}