#include <fstream>
#include <iostream>

using namespace std;
namespace graph {
static const int MAX = 501;
static const int MAX_EDGES = 1001;
static const int INFINITY = 100000000;
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
enum GraphWeightType {
    UNWEIGHT,
    WEIGHT
};

struct Edge {
    Edge() {
        u = v = c = 0;
    }
    Edge(int t_u, int t_v, int t_c) {
        u = t_u;
        v = t_v;
        c = t_c;
    }
    int u, v, c;
    bool mark = false;
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
    static void resetQueue();
    
    static inline int min(const int &x, const int &y) {
        return x < y? x : y;
    }
    
private:
    static int _stack[MAX], _stackSize;
    static int _queue[MAX], _first, _last;
};

class Graph {
public:
    Graph(const GraphDirectivityType &dType, const GraphNumerousType &nType, const GraphWeightType &wType) : 
        a{{0, }, }, _dType(dType), _nType(nType), _wType(wType), _m(0) {
    }
    virtual ~Graph() {
    }

    int& n() {
        return _n;
    }
    int& m() {
        return _m;
    }
    void setN(int n) {
        _n = n;
    }
    Edge& e(const int &i) {
        return _e[i];
    }
    
    int* operator[](const int &i) {
        return a[i];
    }
    int& header(const int &i) {
        return _header[i];
    }
    int& adj(const int &i) {
        return _adj[i];
    }
    long long& adjCost(const int &i) {
        return _adjCost[i];
    }
    
    GraphDirectivityType dType() {
        return _dType;
    }
    GraphNumerousType nType() {
        return _nType;
    }
    GraphWeightType wType() {
        return _wType;
    }

private:
    int _n, _m;
    GraphDirectivityType _dType;
    GraphNumerousType _nType;
    GraphWeightType _wType;
    int a[MAX][MAX];
    Edge _e[MAX_EDGES];
    int _adj[MAX_EDGES];
    long long _adjCost[MAX_EDGES];
    int _header[MAX+1];

};


class InputGraph {
public:
    InputGraph(const string &inFile, const string &outFile, const GraphDirectivityType &dType, const GraphNumerousType &nType, const GraphWeightType &wType);
    ~InputGraph() {
        fin.close();
        fout.close();
    }

    void input(const bool &finding = false, const bool &network = false);
    void printGraph();
    
protected:
    ifstream fin;
    ofstream fout;
    Graph g;
    bool _isFindingPath;
    bool _isNetworking;
    int s, f;
    int a, b; // source, sink of network
};

class GraphAlgorithm : public InputGraph {
public:
    GraphAlgorithm(const string &inFile = "graph.inp", const string &outFile = "graph.out", const GraphDirectivityType &type = UNDIRECTED, const GraphNumerousType &nType = SINGLE, const GraphWeightType &wType = UNWEIGHT);
    virtual ~GraphAlgorithm(){    
    }

    void dfs() {
        fout << "Running DFS:" << endl;
        fout << "From " << s << " you can visit:" << endl;
        trace[s] = VIRTUAL_ROOT;
        dfs(s);
        fout << endl;
    }

    // Graph search
    void dfsStack();
    void dfsBacktrack();
    void bfs();
    void bfsLoang();
    void listConnectedComponent();
    void printPath();

    // Graph connectivity
    void warshall();
    void tarjan();
    void detectBridges();
    void detectCutVertices();

    // Graph circuits
    void fleury();
    void findEulerUsingStack();
    void findAllHamiltonCircuits();

    // Shortest path;
    void fordBellman();
    void dijkstra();
    void dijkstraHeap();
    void topoOrdering();
    void floyd();

    // Minimum spanning tree
    void kruskal();
    void prim();
    
    // Max flow on network
    void maxFlow();
    
    static void mainGraph();

protected:
    int trace[MAX];
    int traceFloyd[MAX][MAX]; // floyd algo. Next vertice on the path from u->v
    bool _free[MAX];
    bool _mark[MAX]; // cut vertices, mark node is cut vertices?
    int nC[MAX]; // cut vertices, num of children
    int x[MAX]; // hamilton path
    int numbering[MAX], low[MAX], count, componentCount;
    long long d[MAX]; //shortest path
    int _heap[MAX]; // _heap[i] = u : index of node - g[u] - ordered by its d[u]
    int _pos[MAX]; // _pos[v] = i - index of node v in heap - heap[pos[v]] = v - pos[_heap[v]] = v
    int nHeap; // size of _heap
    int listTopo[MAX]; // Topo ordering
    int label[MAX]; // Kruskal. label[v] = u : u is parent of v in spanning tree
    int _f[MAX][MAX]; // flow of network
    int _gf[MAX][MAX]; // flow increment graph

    void dfs(int u);
    int findNext(int u); //dfs
    void loang(int t_old[], int t_oldSize, int t_new[], int &t_newSize); //bfs

    void visit(int u); //tarjan
    void directedEdges(int u); //detect edges
    void visitCutVertices(int u);

    bool canGoBack(const int &x, const int &y); // fleury
    void _try(int i); //euler stack
    void printHamiltonCircuit();

    void printShortestPath(); // Ford Bellman, Dijkstra
    void updateHeap(int v); // Dijkstra heap
    int popHeap(); // Dijkstra heap
    void numberize(); // Topo ordering
    void printShortestPathFloyd(); // Floyd

    int getRoot(int u); // Kruskal
    int unionTree(int r1, int r2); // Kruskal
    void adjustHeap(int r, int last); // Kruskal
    void printSpanningTree(bool isConnected); // Kruskal
    void printPrimResult(bool isConnected); // Prim
    
    void createGf();
    bool findNetworkPath();
    void increaseFlow();
    void printMaxFlow();
};
}
