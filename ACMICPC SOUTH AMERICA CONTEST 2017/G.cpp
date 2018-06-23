#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 10009
#define MOD 1000000007
#define EPS 1e-7
#define FOR(x,n) for(int x=0; x<n; x++)
#define FORN(x,k,n) for(int x=k; x<n; x++)
#define FOR1e(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
#define MOD 1000000007
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;

int N;
int x[MAXN], y[MAXN], f[MAXN];
ll dp[MAXN][2][2];

ll solve(int u, int e, int p){
	if (u == 0) return e == p;
	if (dp[u][e][p] != -1) return dp[u][e][p];
	if (f[u] >= 0 && e != f[u]) return 0;
	ll ans = 0;
	
	vector<ii> v1, v2;
	if (p == 0) v2.pb(ii(1, 1));
	else v2.pb(ii(0, 1)), v2.pb(ii(0, 0)), v2.pb(ii(1, 0));
	if (f[u] >= 0) v1.pb(ii(0, 1)), v1.pb(ii(0, 0)), v1.pb(ii(1, 0)), v1.pb(ii(1, 1));
	else if (e == 0) v1.pb(ii(1, 1));
	else v1.pb(ii(0, 1)), v1.pb(ii(0, 0)), v1.pb(ii(1, 0));
		
	for (ii a : v1) for (ii b : v2) ans = (ans + solve(x[u], a.first, b.first) * solve(y[u], a.second, b.second) % MOD) % MOD;

	return dp[u][e][p] = ans;
}

int main(){
	scanf("%d", &N);
	FORN(i, 1, N + 1){
		scanf("%d%d%d", &x[i], &y[i], &f[i]);
		FOR(j, 2) FOR(k, 2) dp[i][j][k] = -1;
	}
	printf("%lld\n", (solve(1, 0, 1) + solve(1, 1, 0)) % MOD);
}
