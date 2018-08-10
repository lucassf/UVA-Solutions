#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define MAXN 1009
#define INF 1000000009

int N;
map<string,int> cities;
vector<ii> points[MAXN];
vector<int> adjList[MAXN];
vector<int> vis;
double dp[MAXN][51];

inline double dist(ii p1,ii p2){
	return hypot(p1.first-p2.first,p1.second-p2.second);
}

void dfs(int u,int parent){
	int v;
	double d;

	vis[u] = 1;

	for (int j=0;j<(int)points[u].size();j++)dp[u][j] = 0;

	//cout<<u<<endl;

	for (int i=0;i<(int)adjList[u].size();i++){
		v = adjList[u][i];
		if (v==parent) continue;

		if (!vis[v])dfs(v,u);


		for (int j=0;j<(int)points[u].size();j++){
			d = INF;
			for (int k=0;k<(int)points[v].size();k++){
				d = min(d,dp[v][k]+dist(points[u][j],points[v][k]));
			}
			dp[u][j]+=d;
			//cout<<dp[u][j]<<" ";
		}
		//cout<<endl;
	}
}

int main(){
	int C,x,y,u,v;
	string s,s1;
	double ans;

	while (cin>>N,N){
		cities.clear();
		for (int i=0;i<N;i++){
			cin>>s;
			cities[s] = i;
			cin>>C;
			adjList[i].clear();
			points[i].clear();
			for (int j=0;j<C;j++){
				cin>>x>>y;
				points[i].push_back(ii(x,y));
			}
		}
		for (int i=1;i<N;i++){
			cin>>s>>s1;
			u = cities[s], v = cities[s1];
			adjList[u].push_back(v), adjList[v].push_back(u);
		}
		vis.assign(N,0);
		dfs(0,-1);

		ans = INF;
		for (int i=0;i<(int)points[0].size();i++)ans = min(ans,dp[0][i]);
		printf("%.1lf\n",ans);
	}
}

