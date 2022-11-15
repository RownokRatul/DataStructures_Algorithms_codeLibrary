#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int inf = 99999999;

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

void djikstra(directedWeightedgraph g, double dis[], int parent[],int s) {
    int visited[g.v];
    for(int i=0;i<g.v;i++) {
        dis[i] = -1;
        parent[i] = i;
        visited[i] = 0;
    }
    dis[s] = 0;
    priority_queue<pair<double,int> > q;
    q.push(make_pair(0,s)); // (weight,vertex)
    while(!q.empty()) {
        pair<double,int> p = q.top();
        q.pop();
        visited[p.second] = 1;
        for(pair<int,double> neighbour: g.adj[p.second]) {
            if(!visited[neighbour.first]) {
                if((dis[neighbour.first] == -1) || (dis[neighbour.first] > dis[p.second]+neighbour.second)) {
                    dis[neighbour.first] = dis[p.second]+neighbour.second;
                    parent[neighbour.first] = p.second;
                    q.push(make_pair(-1*dis[neighbour.first],neighbour.first));
                }
            }
        }
    }
}

bool bellman_ford(directedWeightedgraph g) {
    
}

void print_path(int p[], int cur) {
    if(p[cur] != cur) {
        print_path(p, p[cur]);
    }
    cout<<cur<<" ";
}


int main() {
    directedWeightedgraph g;
    g.inputGraph();
    double dis[g.v];
    int parent[g.v];
    int s,t;
    cin>>s>>t;
    djikstra(g,dis,parent,s);
    cout<<"Shortest Path Cost: "<<dis[t]<<'\n';
    print_path(parent,t);
    return 0;
}
/*
9 17
0 7 60
7 1 150
4 8 70
6 4 80
5 1 4000
8 0 100000 2 3 200
8 2 1000
0 3 300
3 8 50000 3 7 200
2 5 120
6 3 1500
4 0 90
5 7 50
1 6 100
4 1 90
0 5
*/