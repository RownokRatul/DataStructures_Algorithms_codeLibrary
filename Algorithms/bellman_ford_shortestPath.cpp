#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int inf = INT_MAX;

class directedWeightedgraph {
    public:
        int v;
        int e;
        vector<pair<int,double> > *adj;

        directedWeightedgraph() {

        }

        directedWeightedgraph(const directedWeightedgraph &obj) {
            v = obj.v;
            e = obj.e;
            adj = new vector<pair<int,double> > [v];
            for(int i=0;i<v;i++) {
                for(pair<int,double> p: obj.adj[i]) {
                    adj[i].push_back(make_pair(p.first,p.second));
                }
            }
        }

        void inputGraph() {
            cin>>v>>e;
            adj = new vector<pair<int,double> > [v];
            for(int i=0;i<e;i++) {
                int a,b;
                double w;
                cin>>a>>b>>w;
                adj[a].push_back(make_pair(b,w));
            }
        }

};

bool bellman_ford(directedWeightedgraph g,double dis[],int parent[],int s) {
    for(int i=0;i<g.v;i++) {
        dis[i] = inf;
        parent[i] = i;
    }
    dis[s] = 0;
    for(int i=0;i<g.v-1;i++) {
        for(int i=0;i<g.v;i++) {
            for(pair<int,double> p : g.adj[i]) {
                if(dis[p.first] > dis[i]+p.second) {
                    dis[p.first] = dis[i]+p.second;
                    parent[p.first] = i;
                }
            }
        }
    }
    for(int i=0;i<g.v-1;i++) {
        for(pair<int,double> p : g.adj[i]) {
            if(dis[p.first] > dis[i]+p.second) {
                return false;
            }
        }
    }
    return true;
}

void print_path(int p[], int cur) {
    if(p[cur] != cur) {
        print_path(p, p[cur]);
    }
    cout<<cur<<" ";
}

int main() {
    //freopen("input.txt","r",stdin);
    directedWeightedgraph g;
    g.inputGraph();
    double dis[g.v];
    int parent[g.v];
    int s,t;
    cin>>s>>t;
    bool f = bellman_ford(g,dis,parent,s);
    if(!f) {
        cout<<"The graph contains a reachable cycle reachable from source vertex\n";
    }
    else {
        cout<<"Shortest Path Cost: "<<dis[t]<<'\n';
        print_path(parent,t);
    }
    return 0;
}
