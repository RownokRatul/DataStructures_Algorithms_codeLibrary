#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int inf = 999999999;

void copyMatrix(int **from, int **to, int dim) {
    for(int i=0;i<dim;i++) {
        for(int j=0;j<dim;j++) {
            to[i][j] = from[i][j];
        }
    }
}

class directedWeightedgraph {
    public:
        int v;
        int e;
        int **adj;

        directedWeightedgraph() {

        }

        directedWeightedgraph(const directedWeightedgraph& obj) {
            v = obj.v;
            e = obj.e;
            adj = new int*[v];
            for(int i=0;i<v;i++) {
                adj[i] = new int[v];
                for(int j=0;j<v;j++) {
                    adj[i][j] = obj.adj[i][j];
                }
            }
        }

        void inputGraph() {
            cin>>v>>e;
            adj = new int*[v];
            for(int i=0;i<v;i++) {
                adj[i] = new int[v];
                for(int j=0;j<v;j++) {
                    adj[i][j] = (i == j) ? 0 : inf ;
                }
            }
            for(int i=0;i<e;i++) {
                int a,b;
                double w;
                cin>>a>>b>>w;
                adj[a-1][b-1] = w;
            }
        }
};

void floydWarshall(directedWeightedgraph& g, int **mat) {
    int **matprev;
    matprev =  new int*[g.v];
    for(int i=0;i<g.v;i++) {
        matprev[i] = new int[g.v];
    }
    copyMatrix(g.adj,mat,g.v);
    for(int k=0;k<g.v;k++) {
        copyMatrix(mat,matprev,g.v);
        for(int i=0;i<g.v;i++) {
            for(int j=0;j<g.v;j++) {
                mat[i][j] = min(matprev[i][j], matprev[i][k] + matprev[k][j]);
            }
        }
    }
}

int main() {
    directedWeightedgraph g;
    g.inputGraph();
    int** shortestPath;
    shortestPath = new int*[g.v];
    for(int i=0;i<g.v;i++) {
        shortestPath[i] = new int[g.v];
    }
    floydWarshall(g,shortestPath);
    cout<<"Shortest Distance Matrix: \n";
    for(int i=0;i<g.v;i++) {
        for(int j=0;j<g.v;j++) {
            if(shortestPath[i][j] != inf) {
                cout<<shortestPath[i][j]<<"\t";
            }
            else {
                cout<<"INF\t";
            }
        }
        cout<<'\n';
    }
    return 0;
}