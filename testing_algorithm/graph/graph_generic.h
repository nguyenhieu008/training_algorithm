#include <fstream>
#include <iostream>

using namespace std;
namespace graph {
static const int MAX = 101;
static const int INFINITY = MAX + 1;
static const int VIRTUAL_ROOT = -1;
static const int NO_NODE = 0;
enum GraphDirectivityType{
    UNDIRECTED,
    DIRECTED
};
enum GraphNumerousType {
    SINGLE,
    MULTIPLE
};

class Util {
public:
    static void push(int u);
    static int pop();
    static int get();
    static bool empty();
    
    static void pushQueue(int u);
    static int popQueue();
    static bool queueEmpty();
    
    inline int min(const int &x, const int &y) {
        return x < y? x : y;
    }
    
private:
    static int _stack[MAX], _stackSize;
    static int _queue[MAX], _first, _last;

};

class Graph {
public:
    Graph(const GraphDirectivityType &dType, const GraphNumerousType &nType) : a{{0, }, }, _dType(dType), _nType(nType) {
    }
    virtual ~Graph() {
    }

    static void mainGraph();
    int& n() {
        return _n;
    }
    void setN(int n) {
        _n = n;
    }
    
    int* operator[](const int &i) {
        return a[i];
    }
    
    GraphDirectivityType dType() {
        return _dType;
    }
    GraphNumerousType nType() {
        return _nType;
    }

private:
    int _n;
    GraphDirectivityType _dType;
    GraphNumerousType _nType;
    int a[MAX][MAX];
};


class InputGraph {
public:
    InputGraph(const string &inFile, const string &outFile, const GraphDirectivityType &dType, const GraphNumerousType &nType) : fin(inFile), fout(outFile), g(dType, nType) {
        fin >> g.n();
    }
    virtual void input();
    void printGraph();
    
    
protected:
    ifstream fin;
    ofstream fout;
    Graph g;
};

class GraphSearch : public InputGraph {
public:
    GraphSearch(const string &inFile = "graph.inp", const string &outFile = "graph.out") : InputGraph(inFile, outFile, UNDIRECTED, SINGLE), trace{NO_NODE, }{
        input();
        printGraph();
    }
    virtual ~GraphSearch(){
        
    }
    virtual void input();

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
    int trace[MAX];

    void dfs(int u);
    int findNext(int u);
    void loang(int t_old[], int t_oldSize, int t_new[], int &t_newSize);
};

class GraphConnectivity : public InputGraph {
public:
    GraphConnectivity(const string &inFile = "graph_connectivity.inp", const string &outFile = "graph_connectivity.out", const GraphDirectivityType &type = UNDIRECTED);
    void warshall();

    void tarjan();
    void detectBridges();
    void detectCutVertices();
    
    
private:
    void visit(int u);
    void directedEdges(int u);
    void visitCutVertices(int u);
    
    bool _free[MAX], _mark[MAX];
    int numbering[MAX], low[MAX], count, componentCount;
    int nC[MAX];

};

class GraphCircuit : public InputGraph {
public:
    GraphCircuit(const string &inFile = "graph_circuit.inp", const string &outFile = "graph_circuit.out", const GraphDirectivityType &dType = UNDIRECTED, const GraphNumerousType &nType = MULTIPLE);
    
    void fleury();
    void findEulerUsingStack();

private:
    bool canGoBack(const int &x, const int &y);
};
}
