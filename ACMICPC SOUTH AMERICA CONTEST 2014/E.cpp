#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef long long int ll;
#define MAXN 10009

int I, S, C[MAXN];
vector<int> adjList[MAXN];
set<int> vals;
set<ii> vis;

inline int gcd(int a, int b){
	while (b != 0){
		int aux = b;
		b = a % b;
		a = aux;
	}
	return a;
}

void solve(int u, int c){
	vals.insert(c);
	vis.insert(ii(u, c));
	
	for (int i = 0; i < (int)adjList[u].size(); i++){
		int v = adjList[u][i];
		
		int p = gcd(c, C[v]);
		if (!vis.count(ii(v, p))) solve(v, p);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int a, b;
	while (cin>>I>>S){
		for (int i = 0; i < I; i++) {
			cin>>C[i];
			adjList[i].clear();
		}
		for (int i = 0; i < S; i++){
			cin>>a>>b;
			a--, b--;
			adjList[a].push_back(b);
			adjList[b].push_back(a);
		}
		vis.clear();
		vals.clear();
		for (int i = 0; i < I; i++){
			if (!vis.count(ii(i, C[i])))
				solve(i, C[i]);
		}
		cout<<vals.size()<<endl;
	}
}
