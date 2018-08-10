#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
#define MAXN 10009
#define UNVISITED -1
int N, M, Q;

vector<int> adjList[MAXN], nxtList[MAXN];
int num[MAXN], low[MAXN], parent[MAXN], counter, rootChildren, root;

void tarjan(int u){
	low[u] = num[u] = counter++;
	for (int j = 0; j < (int)adjList[u].size(); j++){
		int v = adjList[u][j];
		if (num[v] == UNVISITED){
			parent[v] = u;
			if (u == root) rootChildren++;
			tarjan(v);
			if (low[v] > num[u]){
				nxtList[v].push_back(u);
				nxtList[u].push_back(v);
			}
			low[u] = min(low[u], low[v]);
		}
		else if (v != parent[u])
			low[u] = min(low[u], num[v]);
	}
}

int component[MAXN];

void dfs(int n){
	component[n] = counter;
	num[n] = 1;
	
	for (int i = 0; i < (int)nxtList[n].size(); i++){
		int v = nxtList[n][i];
		if (num[v] == UNVISITED){
			dfs(v);
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int a, b;
	while (cin>>N>>M>>Q, N){
		for (int i = 0; i < N; i++){
			adjList[i].clear();
			nxtList[i].clear();
		}
		
		for (int i = 0; i < M; i++){
			cin>>a>>b;
			a--, b--;
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}
		counter = 0;
		memset(num, UNVISITED, sizeof num);
		memset(low, 0, sizeof low);
		memset(parent, 0, sizeof parent);
		for (int i = 0; i < N; i++){
			if (num[i] == UNVISITED){
				root = i; rootChildren = 0; tarjan(i);
			}
		}
		counter = 0;
		memset(num, UNVISITED, sizeof num);
		for (int i = 0; i < N; i++){
			if (num[i] == UNVISITED){
				dfs(i);
				counter++;
			}
		}
		while (Q-- > 0){
			cin>>a>>b;
			a--, b--;
			if (component[a] == component[b])cout<<"Y\n";
			else cout<<"N\n";
		}
		cout<<"-\n";
	}
}
