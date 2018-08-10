#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 1009
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, ii> iii;
const ll MOD = 1000000007;

ll val[MAXN];
ll adj[MAXN][16], rs[16];
int vis[MAXN], l[MAXN];
vector<int> ts[MAXN];
vector<int> g[MAXN], ps;

int dfs(int u){
	vis[u] = 1;
	adj[u][u / 64] |= (1LL<<(u & 63));
	for (auto v : g[u]){
		if (!vis[v]) dfs(v);
		val[u] += val[v];
		FOR(j, 16) adj[u][j] |= adj[v][j];
		adj[u][v / 64] |= (1LL<<(v & 63));
	}
	l[u] = ps.size();
	ps.pb(u);
}

bool cmp(int u, int v){
	return l[u] > l[v];
}

int main(){
	int N, E, p, q, a;

	while (scanf("%d%d", &N, &E), N){
		ps.clear();
		FOR(i, E) ts[i].clear();
		FOR(i, N){
			vis[i] = 0;
			FOR(j, 16) adj[i][j] = 0;
			scanf("%lld%d%d", &val[i], &p, &q);
			g[i].clear();
			FOR(j, p){
				scanf("%d", &a); --a;
				g[i].pb(a);
			}FOR(j, q){
				scanf("%d", &a); --a;
				ts[a].pb(i);
			}
		}
		FOR(i, N) if (!vis[i]) dfs(i);
		printf("*****\n");
		ll ans;
		FOR(i, E){
			FOR(j, 16) rs[j] = 0;
			sort(ts[i].begin(), ts[i].end(), cmp);
			ans = 0;
			for (auto u : ts[i]){
				if (rs[u / 64] & (1LL<<(u & 63))) continue;
				ans += val[u];
				FOR(j, 16) rs[j] |= adj[u][j];
			}
			printf("%d %lld\n", i + 1, ans);
		}
	}
}
