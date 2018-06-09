#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;
typedef long double ld;
#define MAXM 51
#define MAXN 2609
#define INF 1000000007
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define PMOD(a, m) ((a) % (m) + (m)) % (m)

char t[MAXM][MAXM];
int val[MAXM][MAXM];

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN];
bool vis[MAXN];
int m, n;

bool dfs(int u)
{
    vis[u] = true;
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i) {
        v = adjU[u][i];
        if (!vis[pairV[v]] && dfs(pairV[v])) {
            pairV[v] = u; pairU[u] = v;
            return true;
        }
    }
    return false;
}

int hungarian()
{
    FOR(i, m + 1) pairU[i] = pairV[i] = 0;
    int result = 0;
    for (int u = 1; u <= m; u++) {
        FOR(i, m + 1) vis[i] = 0;
        if (pairU[u]==0 && dfs(u))
            result++;
    }
    return result;
}

int movx[4] = {0, 0, 1, -1};
int movy[4] = {1, -1, 0, 0};
int R, C;

int dfs(int i, int j, int p){
	val[i][j] = (p % 2) ? ++m : ++n;

	FOR(k, 4){
		int x = movx[k] + i, y = movy[k] + j;

		if (x >= 0 && x < R && y >= 0 && y < C && t[x][y] == '.'){
			if (!val[x][y]) dfs(x, y, p + 1);
			if (p % 2) adjU[val[i][j]].push_back(val[x][y]);
		}
	}
}

int main(){
	while (scanf("%d%d", &R, &C) != EOF){
		FOR(i, R) {
			scanf("%s", &t[i]);
			FOR(j, C) val[i][j] = 0;
		}
		int win = 1;
		FOR(i, R) {FOR(j, C){
			if (!val[i][j] && t[i][j] == '.'){
				m = 0, n = 0;
				dfs(i, j, 1);
				if (m != n || hungarian() != m) win = 0;
				FOR(i, m + 1) adjU[i].clear();
				if (!win) break;				
			}

		} if (!win) break;}
		printf("%d\n", win + 1);
	}
}