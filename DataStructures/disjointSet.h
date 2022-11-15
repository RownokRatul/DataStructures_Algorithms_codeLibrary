#include<iostream>
#include<vector>
using namespace std;

class disjointSet {
        int n;
        int* parent;
        int* rank;

    public:
        disjointSet() {

        }
        disjointSet(int n) {
            makeSet(n);
        }
        disjointSet(const disjointSet &obj) {
            this->n = obj.n;
            this->parent = new int[n];
            this->rank = new int[n];
            for(int i=0;i<n;i++) {
                this->parent[i] = obj.parent[i];
                this->rank[i] = obj.parent[i];
            }
        }
        void makeSet(int n) {
            this->n = n;
            parent = new int[n];
            rank = new int[n];
            for(int i=0;i<n;i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
        void unionSet(int x, int y) {
            int px = findSet(x);
            int py = findSet(y);
            if(px != py) {
                if(rank[px] > rank[py]) {
                    parent[py] = px;
                }
                else {
                    parent[px] = py;
                    rank[py] = (rank[px] == rank[py]) ? rank[py]+1 : rank[py];
                }
            }
        }
        int findSet(int idx) {
            if(idx != parent[idx]) {
                parent[idx] = findSet(parent[idx]);
            }
            return parent[idx];
        }
};
