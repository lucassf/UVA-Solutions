#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
typedef long long int ll;

int D, P, R, B, dp[MAXN];
int cost[2 * MAXN], C[2 * MAXN], vis[2 * MAXN], a, sum[2 * MAXN];
vector<int> adjList[2 * MAXN];

int pd[2][2 * MAXN][MAXN * MAXN];

void dfs(int u, int acum, int pos){
	vis[u] = 1;
	sum[a] += pos == 1 ? 1 : -1;
	cost[a] += C[u];
	
	for (int i = 0; i < (int) adjList[u].size(); i++){
		int v = adjList[u][i];
		if (!vis[v]) dfs(v, acum + cost[v], (pos + 1) % 2);
	}
}

int solve(int idx, int rem, int dir){
	if (idx == a) return 0;
	
	int acum = dir * sum[idx];
	int d = dir == 1 ? 0 : 1;
	
	if (pd[d][idx][rem] != -1) return pd[d][idx][rem];
	
	int ans = solve(idx + 1, rem, dir);
	if (acum > 0 && rem >= cost[idx]) ans = max(ans, acum + solve(idx + 1, rem - cost[idx], dir));
	
	return pd[d][idx][rem] = ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int X, Y;
	while (cin>>D>>P>>R>>B){
		for (int i = 0; i < D; i++) {
			cin>>C[i];
			adjList[i].clear();
		}
		for (int i = 0; i < P; i++){
			cin>>C[i + D];
			adjList[i + D].clear();
		}
		
		for (int i = 0; i < R; i++){
			cin>>X>>Y;
			X--, Y--;
			adjList[X].push_back(Y + D);
			adjList[Y + D].push_back(X);
		}
		a = 0;
		memset(vis, 0, sizeof vis);
		memset(sum, 0, sizeof sum);
		memset(cost, 0, sizeof cost);
		
		for (int i = 0; i < D; i++){
			if (!vis[i]) {
				dfs(i, 0, 0);
				a++;
			}
		}
		for (int i = 0; i < P; i++){
			if (!vis[i + D]) {
				dfs(i + D, 0, 1);
				a++;
			}
		}
		//for (int idx = 0; idx < a; idx++)cout<<cost[idx]<<" "<<sum[idx]<<endl;
		
		memset(pd, -1, sizeof pd);
		cout<<D + solve(0, B, 1)<<" "<<P + solve(0, B, -1)<<"\n";
	}
}