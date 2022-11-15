#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;

int NIL = -1;

class undirectedGraph {
        int v;
        int e;
        vector<int> *adj;
    public:
        undirectedGraph(int v,int e) {
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
        void addEdge(int u,int v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int>* getAdjList() {
            return adj;
        }
        ~undirectedGraph() {
            delete [] adj;
        }
};

void dfs(undirectedGraph G) {
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
            dfs_visit(adj, color, predecessor, discover, finish, time, i);
        }
    }
}

void dfs_visit(vector<int>* adj, int col[], int pred[], int disc[], int fin[],int &time, int node) {
    time++;
    col[node] = 1;
    disc[node] = time;
    for(int v:adj[node]) {
        if(col[v] == 0) {
            pred[v] = node;
            dfs_visit(adj,col,pred,disc,fin,time,v);
        }
    }
    col[node] = 2;
    time++;
    fin[node] = time;
}

int main() {

}