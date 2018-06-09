#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;
typedef long double ld;
#define MAXN 100009
#define INF 1000000007
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define PMOD(a, m) ((a) % (m) + (m)) % (m)

int F[MAXN], h[MAXN], up[MAXN], dpt[MAXN], len[MAXN], pos[MAXN];
int sz[MAXN], nxt[MAXN], depth[MAXN];
vector<int> g[MAXN];

void dfs_sz(int v, int d, int p, int w, int par)
{
    sz[v] = 1;
    depth[v] = d;
    h[v] = p;
    up[v] = par;

    for(auto &u: g[v])
    {
	if (u == par) continue;
	pos[u] = pos[v];
        dfs_sz(u, d + 1, p, w, v);
        sz[v] += sz[u];
        if(sz[u] > sz[g[v][0]])
            swap(u, g[v][0]);
    }
}

void dfs_hld(int v, int n, int d, int par)
{
    dpt[v] = d;
    nxt[v] = n;
    for(auto u: g[v])
    {
	if (u == par) continue;
	if (g[v][0] == u) dfs_hld(u, nxt[v], d, v);
	else dfs_hld(u, u, d + 1, v);
    }
}

int lca(int u, int v){
    while (nxt[u] != nxt[v]){
	if (dpt[nxt[u]] < dpt[nxt[v]]) v = up[nxt[v]];
	else u = up[nxt[u]];
    }
    return depth[u] < depth[v] ? u : v;
}

void dfs(int u, int p){
	int v;
	while (!h[u]){
		v = u;
		h[u] = p;
		u = F[u];
	}
	int d = 0, w = u;
	len[p] = 0;
	while (true){
		pos[u] = d++;
		FOR(i, g[u].size()) if (g[u][i] == v){
			swap(g[u][i], g[u][g[u].size() - 1]);
			g[u].pop_back();
			break;
		}
		dfs_sz(u, 0, p, u, v); 
		dfs_hld(u, u, 0, v);
		v = u, u = F[u];
		len[p]++;
		if (u == w) break;
	}
}

int main(){
	
	int N, Q;
	while (scanf("%d", &N) != EOF){
		FOR(i, N) g[i].clear();
		FOR(i, N) {
			scanf("%d", &F[i]);
			F[i]--; h[i] = 0;
			g[F[i]].push_back(i);
		}
		int k = 1;
		FOR(i, N) if (!h[i])dfs(i, k++);
		scanf("%d", &Q);
		//FOR(i, N) printf("%d %d %d %d %d %d\n", depth[i], sz[i], nxt[i], up[i], h[i], pos[i]);
		while (Q--){
			int a, b;
			scanf("%d%d", &a, &b);
			--a, --b;
			if (h[a] != h[b]) printf("-1\n");
			else if (pos[a] == pos[b]) printf("%d\n", depth[a] + depth[b] - 2 * depth[lca(a, b)]);
			else{
				int va = abs(pos[a] - pos[b]);
				printf("%d\n", depth[a] + depth[b] + min(len[h[a]] - va, va));
			}	
		}
	}
	
}