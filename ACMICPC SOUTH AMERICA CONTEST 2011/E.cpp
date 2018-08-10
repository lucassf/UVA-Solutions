#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 109
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, ii> iii;
const ll MOD = 1000000007;

int N, Q, values[MAXN][2], component[MAXN];
vector<ii> g[MAXN];
map<int, int> val;

void dfs(int u, int pos, int sum, int c){
	component[u] = c;
	values[u][pos] = sum;
	pos = (pos + 1) % 2;

	for (ii aux : g[u]){
		int v = aux.first, a = aux.second;
		if (values[v][pos] != INF) continue;
		
		dfs(v, pos, sum + a * (pos % 2 ? 1 : -1), c);
	}
}

int main(){
	int x, y, a, M = 0;
	while (scanf("%d%d", &N, &Q), N){
		FOR(i, M) g[i].clear();
		val.clear();
		M = 0;

		FOR(i, N){
			scanf("%d%d%d", &x, &y, &a);
			if (!val.count(x)) val[x] = M++;
			if (!val.count(y)) val[y] = M++;
			x = val[x], y = val[y];
			if (x == y) a <<= 1;
			g[x].pb(ii(y, a)), g[y].pb(ii(x, a));
		}
		FOR(i, M) values[i][0] = values[i][1] = INF;
		int c = 0;
		FOR(i, M) if (values[i][0] == INF && values[i][1] == INF) dfs(i, 0, 0, c++);
		//FOR(i, M) printf("%d %d\n", values[i][0], values[i][1]);
		while (Q--){
			scanf("%d%d", &x, &y);
			int pos = 1, ans;
			if (!val.count(x) || !val.count(y)) pos = 0;
			else {
				x = val[x], y = val[y];
				if (component[x] != component[y]) {
					if (values[x][0] != INF && values[x][1] != INF && values[y][1] != INF && values[y][0] != INF) ans = (values[x][1] - values[x][0] + values[y][1] - values[y][0]) / 2;
					else pos = 0;
				}
				else if (values[x][0] != INF && values[y][1] != INF) ans = values[y][1] - values[x][0];
				else if (values[x][1] != INF && values[y][0] != INF) ans = values[x][1] - values[y][0];
				else pos = 0;
			}	
			if (pos) printf("%d\n", x == y ? ans / 2 : ans);
			else printf("*\n");
		}
		printf("-\n");
	}
}
