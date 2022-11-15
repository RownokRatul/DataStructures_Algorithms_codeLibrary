#include<iostream>
#include<vector>
using namespace std;

class disjointSet {
        int n;
        int* parent;
        int* rank;

    public:
        disjointSet() {

        }
        disjointSet(int n) {
            makeSet(n);
        }
        disjointSet(const disjointSet &obj) {
            this->n = obj.n;
            this->parent = new int[n];
            this->rank = new int[n];
            for(int i=0;i<n;i++) {
                this->parent[i] = obj.parent[i];
                this->rank[i] = obj.parent[i];
            }
        }
        void makeSet(int n) {
            this->n = n;
            parent = new int[n];
            rank = new int[n];
            for(int i=0;i<n;i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        void unionSet(int x, int y) {
            int px = findSet(x);
            int py = findSet(y);
            if(px != py) {
                if(rank[px] > rank[py]) {
                    parent[py] = px;
                }
                else {
                    parent[px] = py;
                    rank[py] = (rank[px] == rank[py]) ? rank[py]+1 : rank[py];
                }
            }
        }
        int findSet(int idx) {
            if(idx != parent[idx]) {
                parent[idx] = findSet(parent[idx]);
            }
            return parent[idx];
        }
};

class weightedUndirectedEdge {
    public: 
        int v1,v2;
        double w;
        weightedUndirectedEdge(int a,int b,double wei) {
            v1 = a;
            v2 = b;
            w = wei;
        }
};

class undirectedWeightedgraph {
    public:
        int v;
        int e;
        vector<weightedUndirectedEdge> edges;

        void inputGraph() {
            cin>>v>>e;
            for(int i=0;i<e;i++) {
                int a,b;
                double w;
                cin>>a>>b>>w;
                edges.push_back(weightedUndirectedEdge(a,b,w));
            }
        }
};

bool compareE(weightedUndirectedEdge a, weightedUndirectedEdge b) {
    return a.w <= b.w;
}

vector<weightedUndirectedEdge> kruskal_MST(undirectedWeightedgraph g) {
    vector<weightedUndirectedEdge> mst;
    disjointSet dsu;
    dsu.makeSet(g.v);
    sort(g.edges.begin(), g.edges.end(), compareE );
    for(int i=0;i<g.e;i++) {
        if(dsu.findSet(g.edges[i].v1) != dsu.findSet(g.edges[i].v2)) {
            mst.push_back(g.edges[i]);
            dsu.unionSet(g.edges[i].v1, g.edges[i].v2);
        }
    }
    return mst;
}

int main() {
    undirectedWeightedgraph g;
    g.inputGraph();
    vector<weightedUndirectedEdge> v = kruskal_MST(g);
    int cost = 0;
    for(weightedUndirectedEdge x: v) {
        cout<<x.v1<<" "<<x.v2<<endl;
        cost += x.w;
    }
    cout<<cost<<endl;
    return 0;
}