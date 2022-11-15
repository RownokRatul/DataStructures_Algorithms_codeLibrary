#include<iostream>
#include<vector>
using namespace std;

typedef long long ll;

ll globalTime = 0;
ll inf = 999999999;

int dfsArticulationPoint(vector<int> adj[], int ap[], int disc[], int low[], int cur, int parent) {
	int childCount = 0;
	disc[cur] = low[cur] = ++globalTime;
	for(int u : adj[cur]) {
		if(u != parent) {
			if(!disc[u]) {
				childCount++;
				dfsArticulationPoint(adj, ap, disc, low, u, cur);
				if(disc[cur] <= low[u]) {
					ap[cur] = 1;
				}
				low[cur] = min(low[u], low[cur]);
			}
			else {
				low[cur] = min(low[cur], disc[u]);
			}
		}
	}
	return childCount;
}
void articulationPointSet(vector<int> adj[], int n, int ap[]) {
	int low[n];
	int disc[n];
	for(int i=0;i<n;i++) {
		low[i] = inf;
		disc[i] = 0;
		ap[i] = 0;
	}
	for(int i=0;i<n;i++) {
		if(!disc[i]) {
			ap[i] = dfsArticulationPoint(adj, ap, disc, low, i, i) > 1;
		}
	}
} 

int main() {
	int n, e, a, b;
	cin>>n>>e;
	vector<int> v[n];
	int ap[n];
	for(int i=0;i<e;i++) {
		cin>>a>>b;
		v[a-1].push_back(b-1);
		v[b-1].push_back(a-1);
	}
	articulationPointSet(v, n, ap);
	cout<<"Articulation Point: "<<"\n";
	for(int i =0;i<n;i++) {
		if(ap[i]) {
			cout<<i<<" ";
		}
	}
	cout<<"\n";
	return 0;
}