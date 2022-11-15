#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;

int inf = 99999999;
int noParent = -1;

class flowNetwork {
    public: 
        int v;
        int e;
        int source;
        int sink;
        vector<int> *adj;
        int **capacity;

        flowNetwork() {
            
        }

        void inputNetwork() {
            cin>>v>>e;
            capacity = new int*[v];
            adj = new vector<int> [v];
            for(int i=0;i<v;i++) {
                capacity[i] = new int[v];
                for(int j=0;j<v;j++) {
                    capacity[i][j] = 0;
                }
            }
            for(int i=0;i<e;i++) {
                int a,b,c;
                cin>>a>>b>>c;
                adj[a].push_back(b);
                adj[b].push_back(a);
                capacity[a][b] = c;
            }
            cin>>source>>sink;
        }
};

int bfs(flowNetwork &g, int parent[]) {
    for(int i=0;i<g.v;i++) {
        parent[i] = noParent;
    }
    
    queue<pair<int,int> > q;
    parent[g.source] = g.source;
    q.push(make_pair(g.source,inf));
    int bottleneck;
    while(!q.empty()) {
        pair<int,int> cur = q.front();
        q.pop();
        bottleneck = cur.second;
        for(int next: g.adj[cur.first]) {
            if(parent[next] == noParent && g.capacity[cur.first][next] != 0) {
                parent[next] = cur.first;
                bottleneck = min(bottleneck, g.capacity[cur.first][next]);
                if(next == g.sink) {
                    return bottleneck;
                }
                else {
                    q.push(make_pair(next, bottleneck));
                }
            }
        }
    }
    return 0;
}

int edmonds_karp(flowNetwork &g) {
    int max_flow = 0;
    int par[g.v];
    int residual_flow = bfs(g,par);
    while(residual_flow) {
        int traverse = g.sink;
        while(traverse != g.source) {
            g.capacity[par[traverse]][traverse] -= residual_flow;
            g.capacity[traverse][par[traverse]] += residual_flow;
            traverse = par[traverse];
        }
        max_flow += residual_flow;
        residual_flow = bfs(g,par);
    }
    return max_flow;
}

int main() {
    flowNetwork g;
    g.inputNetwork();
    int f = edmonds_karp(g);
    cout<<f<<endl;
}

/*
6 9
0 1 7
0 2 4
2 1 3
2 4 2
1 4 3
1 3 5
4 3 3
4 5 5
3 5 8
0 5
*/