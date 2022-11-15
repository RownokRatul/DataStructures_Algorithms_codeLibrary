#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<utility>
using namespace std;

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
        undirectedGraph(const undirectedGraph &G) {
            this->v = G.v;
            this->e = G.e;
            adj = new vector<int> [v];
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
            adj = new vector<int> [v];
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

class undirectedWeightedGraph{
        int v;
        int e;
        vector<pair<int,int> > *adj;
    public:
        undirectedWeightedGraph(int v,int e) {
            this->v = v;
            this->e = e;
            adj = new vector<pair<int,int> > [v];
        }
        undirectedWeightedGraph(const undirectedWeightedGraph &G) {
            this->v = G.v;
            this->e = G.e;
            adj = new vector<pair<int,int> > [v];
            for(int i=0;i<v;i++) {
                for(pair<int,int> x:G.adj[i]) {
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
        void addEdge(int u,int v,int w) {
            adj[u].push_back(make_pair(v,w));
            adj[v].push_back(make_pair(u,w));
        }
        vector<pair<int,int> >* getAdjList() {
            return adj;
        }
        ~undirectedWeightedGraph() {
            delete [] adj;
        }
};

class directedWeightedGraph {
        int v;
        int e;
        vector<pair<int,int> > *adj;
    public: 
        directedWeightedGraph(int v,int e) {
            this->v = v;
            this->e = e;
            adj = new vector<pair<int,int> > [v];
        }
        directedWeightedGraph(const directedWeightedGraph &G) {
            this->v = G.v;
            this->e = G.e;
            adj = new vector<pair<int,int> > [v];
            for(int i=0;i<v;i++) {
                for(pair<int,int> x:G.adj[i]) {
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
        void addEdge(int u,int v,int w) {
            adj[u].push_back(make_pair(v,w));
        }
        vector<pair<int,int> >* getAdjList() {
            return adj;
        }
        ~directedWeightedGraph() {
            delete [] adj;
        }
};

int main() {

}