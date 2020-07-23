#include <fstream>
#include <iostream>

using namespace std;
namespace graph {
class Graph {
public:
    enum GraphType{
        UNDIRECTED,
        DIRECTED
    };
    Graph(const string &inFile, const string &outFile) {
        fin.open(inFile);
        fout.open(outFile);
    }
    virtual ~Graph() {
        fin.close();
        fout.close();
    }

    virtual void input() = 0;

    static void mainGraph();

protected:
    static const int MAX = 101;
    static const int VIRTUAL_ROOT = -1;
    static const int NO_NODE = 0;

    ifstream fin;
    ofstream fout;
    int n, m;
}; 

class SingleGraph : public Graph {
public:
    SingleGraph(const string &inFile, const string &outFile, const GraphType &type = UNDIRECTED) : Graph(inFile, outFile), type(type) {

    }
    virtual void input() = 0;
    void printGraph();
protected:
    bool a[MAX][MAX] = {{false, }, };
    GraphType type;
};

class GraphSearch : public SingleGraph {
    GraphSearch(const string &inFile = "graph.inp", const string &outFile = "graph.out") : SingleGraph(inFile, outFile), _stackSize(0), _first(0), _last(0), _oldSize(0), _newSize(0) {
        input();
    }
    virtual ~GraphSearch();

    void input();

    void dfs() {
        fout << "Running DFS:" << endl;
        fout << "From " << s << " you can visit:" << endl;
        trace[s] = VIRTUAL_ROOT;
        dfs(s);
        fout << endl;
    }
    void dfsStack();
    void dfsBacktrack();

    void bfs();
    void bfsLoang();

    void printPath();

    void listConnectedComponent();

protected:
    int s, f;
    int trace[MAX] = {NO_NODE, };
    int _stack[MAX], _stackSize;
    int _queue[MAX], _first, _last;
    int _oldSize, _newSize;
    int _x[MAX], _y[MAX];

    void push(int u);
    int pop();
    void pushQueue(int u);
    int popQueue();
    bool queueEmpty();

    void dfs(int u);
    int findNext(int u);
    void loang(int o[], int n[]);
};

class GraphConnectivity : public SingleGraph {
public:
    GraphConnectivity(const string &inFile = "graph_connectivity.inp", const string &outFile = "graph_connectivity.out") : SingleGraph(inFile, outFile), _free{true, } {

    }
    void input();
    void warshall();
private:
    bool _free[MAX];
};
}