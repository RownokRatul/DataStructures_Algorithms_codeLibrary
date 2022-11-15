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

void bfs(undirectedGraph G, int s) {
    // 0 = white
    // 1 = gray
    // 2 = black
    vector<int> *adj = G.getAdjList();
    int n = G.getV();
    int color[n];
    int predecessor[n];
    int distance[n];
    for(int i=0;i<n;i++) {
        color[i] = 0;
        predecessor[i] = NIL;
    }
    queue<int> q;
    q.push(s);
    color[s] = 1;
    distance[s] = 0;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v:adj[u]) {
            if(color[v] == 0) {
                color[v] = 1;
                distance[v] = distance[u]+1;
                predecessor[v] = u;
                q.push(v);
            }
        }
        color[u] = 2;
    }
}

int main() {
    
}