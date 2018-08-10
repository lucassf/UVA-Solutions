#include <bits/stdc++.h>
using namespace std;
#define MAXN 10
#define MAXM 100009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
#define pb push_back
#define L(N) N<<1
#define R(N) (N<<1) + 1
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, ll> iii;
const ll MOD = 1000000007;

int str[MAXN][MAXN], N, M, u;
int r[MAXN][MAXN], c[MAXN][MAXN], adj[MAXN][MAXN], hastovisit[209] = {};
int ans, vis[209] = {}, rem[209];
int movx[4] = {0, 0, 1, -1};
int movy[4] = {1, -1, 0, 0};

void st(int x, int y, int dx){
	int row = r[x][y], col = c[x][y];
	vis[row] ^= 1, vis[col] ^= 1;
	str[x][y] = 6 - dx;
	FOR(j, 4){
		int x1 = movx[j] + x, y1 = movy[j] + y;
		if (str[x1][y1] < 0 || str[x1][y1] > 4) continue;
		str[x1][y1] += dx;
	}	
}

void print(){
	FORN(i, 1, N) {FORN(j, 1, M) cout<<str[i][j]<<' '; cout<<'\n';}
}

void recurse(int x, int y, int acum){
	if (acum >= ans) return;
	if (x == N){ans = min(ans, acum); return;}
	if (y == M) return recurse(x + 1, 1, acum);
	if (str[x][y] < 5) return recurse(x, y + 1, acum);

	int row = r[x][y], col = c[x][y];
	bool canplace = !vis[row] && !vis[col], canignore = true;

	//cout<<x<<' '<<y<<' '<<rem[row]<<' '<<rem[col]<<'\n';
	//print();

	if (hastovisit[row] && !vis[row] && rem[row] == 1) canignore = false;
	if (hastovisit[col] && !vis[col] && rem[col] == 1) canignore = false;

	FOR(j, 4){
		int x1 = movx[j] + x, y1 = movy[j] + y;
		if (str[x1][y1] < 0 || str[x1][y1] > 4) continue;
		if (str[x1][y1] > adj[x1][y1] || !str[x1][y1]) canplace = false;
		if (str[x1][y1] >= adj[x1][y1]) canignore = false;
		adj[x1][y1]--;
	}

	rem[row]--, rem[col]--;
	//cin>>u;

	if (canplace){
		st(x, y, -1);
		recurse(x, y + 1, acum + 1);
		st(x, y, 1);
	}
	if (canignore){
		if (hastovisit[row] || hastovisit[col] || vis[row] || vis[col]) recurse(x, y + 1, acum);
		else {
			if (rem[col]){
				hastovisit[col] = 1;
				recurse(x, y + 1, acum);
				hastovisit[col] = 0;
			}if (rem[row]){
				hastovisit[row] = 1;
				recurse(x, y + 1, acum);
				hastovisit[row] = 0;
			}
		}
	}

	FOR(j, 4){
		int x1 = movx[j] + x, y1 = movy[j] + y;
		if (str[x1][y1] < 0 || str[x1][y1] > 4) continue;
		adj[x1][y1]++;
	}
	rem[row]++, rem[col]++;
}

int main(){
	int B, x, y, k;
	while (scanf("%d%d%d", &N, &M, &B), N){
		memset(str, -1, sizeof str);
		memset(rem, 0, sizeof rem);
		memset(adj, 0, sizeof adj);

		++N, ++M;
		FORN(i, 1, N)FORN(j, 1, M) str[i][j] = 5;

		FOR(i, B){
			scanf("%d%d%d", &x, &y, &k);
			str[x][y] = k;
		}
		int t = 0, poss = 1;
		FOR(i, N)FOR(j, M){
			if (str[i][j] < 5) {
				++t;
				FOR(k, 4){
					int x = movx[k] + i, y = movy[k] + j;
					if (str[x][y] == 5) adj[i][j]++;
				}
				if (str[i][j] > adj[i][j]) poss = 0;
			}
			else r[i][j] = t, rem[t]++;
		}
		FOR(j, M)FOR(i, N){
			if (str[i][j] < 5) ++t;
			else c[i][j] = t, rem[t]++;
		}
		ans = INF;
		if (poss) recurse(1, 1, 0);
		if (ans == INF) printf("No solution\n");
		else printf("%d\n", ans);
	}
}
