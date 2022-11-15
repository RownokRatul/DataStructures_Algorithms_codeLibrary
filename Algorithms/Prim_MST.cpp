#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

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

class compareClassLess {
    public:
        bool operator() (weightedUndirectedEdge a, weightedUndirectedEdge b) {
            return a.w > b.w;
        }
};

class compareClassGreater {
    public:
        bool operator() (weightedUndirectedEdge a, weightedUndirectedEdge b) {
            return a.w < b.w;
        }
};

class undirectedWeightedGraph {
    public: 
        int v;
        int e;
        vector<pair<int,double> > *adj;
        vector<weightedUndirectedEdge> edges;

        void inputGraph() {
            cin>>v>>e;
            adj = new vector<pair<int,double> > [v];
            for(int i=0;i<e;i++) {
                int a,b;
                double w;
                cin>>a>>b>>w;
                edges.push_back(weightedUndirectedEdge(a,b,w));
                adj[a].push_back(make_pair(b,w));
                adj[b].push_back(make_pair(a,w));
            }
        }

        undirectedWeightedGraph() {

        }

        undirectedWeightedGraph(const undirectedWeightedGraph& obj) {
            this->v = obj.v;
            this->e = obj.e;
            for(int i=0;i<e;i++) {
                this->edges.push_back(obj.edges[i]);
            }
            adj = new vector<pair<int, double> > [v];
            for(int i=0;i<v;i++) {
                for(pair<int,double> p: obj.adj[i]) {
                    adj[i].push_back(p);
                }
            }
        }
};


vector<weightedUndirectedEdge> prim_MST(undirectedWeightedGraph g) {
    int visited[g.v];
    fill(visited,visited+g.v,0);
    vector<weightedUndirectedEdge> mst;
    
    priority_queue<weightedUndirectedEdge,vector<weightedUndirectedEdge>, compareClassLess> q;
    for(pair<int,double> p: g.adj[0]) {
        q.push(weightedUndirectedEdge(0,p.first,p.second));
    }
    visited[0] = 1;

    while(!q.empty()) {
        weightedUndirectedEdge edge = q.top();
        q.pop();
        if(!visited[edge.v1] || !visited[edge.v2]) {
            mst.push_back(edge);
            int node = !visited[edge.v1] ? edge.v1 : edge.v2;
            visited[node] = 1; 
            for(pair<int,double> p: g.adj[node]) {
                if(!visited[p.first]) {
                    q.push(weightedUndirectedEdge(node,p.first,p.second));
                }
            }
        }
    }
    return mst;
}
