#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;

int NIL = -1;

class directedGraph {
        int v;
        int e;
        vector<int> *adj;
    public:
        directedGraph(int v,int e) {
            this->v = v;
            this->e = e;
            adj = new vector<int> [v];
        }
        directedGraph(const directedGraph &G) {
            this->v = G.v;
            this->e = G.e;
            this->adj = new vector<int> [v];
            for(int i=0;i<v;i++) {
                for(int x:G.adj[i]) {
                    this->adj[i].push_back(x);
                }
            }
        }
        int getV() {
            return v;
        }
        int getE() {
            return e;
        }
        void addEdge(int u, int v) {
            adj[u].push_back(v);
        }
        vector<int>* getAdjList() {
            return adj;
        }
        ~directedGraph() {
            delete [] adj;
        }
};

void transpose(directedGraph& G, directedGraph& g) {
    int n = G.getV();
    vector<int>* adj = G.getAdjList();
    for(int i=0;i<n;i++) {
        for(int v:adj[i]) {
            g.addEdge(v,i);
        }
    }
}

void dfs_visit(vector<int>* adj, int color[], int node, stack<int>& st) {
    color[node] = 1;
    for(int v:adj[node]) {
        if(color[v] == 0) {
            dfs_visit(adj,color,v,st);
        }
    }
    color[node] = 2;
    st.push(node);
}

vector<vector<int> > strong_Con_Comp(directedGraph& G) {
    int n = G.getV();
    vector<int>* adj = G.getAdjList();

    vector<vector<int> > scc;
    directedGraph gt(n,G.getE());
    transpose(G, gt);
    
    int color[n];
    stack<int> st;
    for(int i=0;i<n;i++) {
        color[i] = 0;
    }
    for(int i=0;i<n;i++) {
        if(color[i] == 0) {
            dfs_visit(adj, color, i, st);
        }
    }   

    for(int i=0;i<n;i++) {
        color[i] = 0;
    }
    vector<int>* adjT = gt.getAdjList();
    while(!st.empty()) {
        int u = st.top();
        st.pop();
        stack<int> t;
        if(color[u] == 0) {
            dfs_visit(adjT, color, u, t);
            vector<int> v;
            while(!t.empty()) {
                v.push_back(t.top());
                t.pop();
            }
            scc.push_back(v);
        }
    }
    return scc;
}

int main() {
    int n,m;
    cin>>n>>m;
    directedGraph g(n,m);
    for(int i=0;i<m;i++) {
        int a,b;
        cin>>a>>b;
        g.addEdge(a-1,b-1);
    }
    cout<<endl;
    vector<vector<int> > scc = strong_Con_Comp(g);
    for(vector<int> v:scc) {
        for(int x:v) {
            cout<<x<<" ";
        }
        cout<<endl;
    }
}