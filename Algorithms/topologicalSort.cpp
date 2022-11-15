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

bool dfs_visit(vector<int>* adj, int col[], int pred[], int disc[], int fin[],int &time, int node, vector<int>& sorted) {
    time++;
    col[node] = 1;
    disc[node] = time;
    for(int v:adj[node]) {
        if(col[v] == 0) {
            pred[v] = node;
            int f = dfs_visit(adj,col,pred,disc,fin,time,v, sorted);
            if(!f) {
                return false;
            }
        }
        if(col[v] == 1) {
            return false;
        }
    }
    sorted.push_back(node);
    col[node] = 2;
    time++;
    fin[node] = time;
    return true;
}

bool dfs(directedGraph G, vector<int>& sorted) {
    // 0 = white
    // 1 = gray
    // 2 = black
    int n = G.getV();
    int time = 0;
    int color[n];
    int finish[n];
    int discover[n];
    int predecessor[n];
    vector<int>* adj = G.getAdjList();
    for(int i=0;i<n;i++) {
        color[i] = 0;
        predecessor[i] = NIL;
        discover[i] = NIL;
        predecessor[i] = NIL;
    }
    for(int i=0;i<n;i++) {
        if(color[i] == 0) {
            int f = dfs_visit(adj, color, predecessor, discover, finish, time, i, sorted);
            if(!f) {
                return false;
            }
        }
    }
    return true;
}

vector<int> topologicalSort(directedGraph G) {
    vector<int> sorted;
    int n = G.getV();
    bool f = dfs(G,sorted);
    if(f) {
        //reverse(sorted.begin(), sorted.end());
        for(int v:sorted) {
            cout<<v+1<<" ";
        }
    }
    else {
        cout<<"Not a DAG.";
    }
    cout<<endl;
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
    topologicalSort(g);
}