#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef long long int ll;
#define MAXN 50009

int N, vis[MAXN], a[2];
vector<int> adjList[MAXN];
ii p[MAXN];

void dfs(int u, int cur){
	a[cur]++;
	vis[u] = 1;
	for (int i = 0; i < (int) adjList[u].size(); i++){
		int v = adjList[u][i];
		if (vis[v]) continue;
		
		dfs(v, (cur + 1) % 2);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int x, y, ans;
	map<ii, int> cnt;
	while (cin>>N){
		cnt.clear();
		for (int i = 0; i < N; i++){
			cin>>x>>y;
			cnt[ii(x, y)] = i;
			p[i] = ii(x, y);
			adjList[i].clear();
			vis[i] = 0;
		}
		for (int i = 0; i < N; i++){
			x = p[i].first, y = p[i].second;
			for (int dx = -5; dx <= 5; dx++){
				for (int dy = -5; dy <= 5; dy++){
					if (dx * dx + dy * dy <= 25 && cnt.count(ii(x + dx, y + dy)))
						adjList[i].push_back(cnt[ii(x + dx, y + dy)]);
				}
			}
		}
		ans = 0;
		for (int i = 0; i < N; i++){
			if (!vis[i]){
				a[0] = a[1] = 0;
				dfs(i, 0);
				ans += min(a[0], a[1]);
			}
		}
		cout<<ans<<endl;
	}
}
