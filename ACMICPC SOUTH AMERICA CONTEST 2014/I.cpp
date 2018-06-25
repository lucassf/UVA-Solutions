#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef long long int ll;
#define MAXN 100009
#define INF 1000000009

int N, F, U, isf[MAXN];
vector<ii> adjList[MAXN];

int dfs(int u){
	int ans = 0;
	for (int i = 0; i < (int) adjList[u].size(); i++){
		int v = adjList[u][i].first;
		int c = adjList[u][i].second;
		
		int k = dfs(v);
		if (k > 0 || isf[v])ans += c + k;
	}
	return ans;
}

int solve(int u, int acum){
	int ans = isf[u]? U - acum : U;
	
	for (int i = 0; i < (int) adjList[u].size(); i++){
		int v = adjList[u][i].first;
		int c = adjList[u][i].second;
		
		ans = min(ans, solve(v, acum + c));
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int a, b, c;
	while (cin>>N>>F){
		for (int i = 0; i < N; i++) adjList[i].clear(), isf[i] = 0;
		for (int i = 0; i < N - 1; i++){
			cin>>a>>b>>c;
			a--, b--;
			adjList[a].push_back(ii(b, c));
		}
		for (int i = 0; i < F; i++){
			cin>>a;
			a--;
			isf[a] = 1;
		}
		U = dfs(0);
		cout<<solve(0, 0)<<endl;
	}
}
