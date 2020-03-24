#include <bits/stdc++.h>
using namespace std;

#define MAXN 21
#define MAXM 1 << 20
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
typedef long long int ll;
const ll MOD = 1000000007;

int t[MAXN];
int g[MAXN][MAXN];
int dp[MAXM];

int N, M, ans;

void solve(int mask, int i, int qty){
	if (ans == N) return;
	if (ans < qty) ans = qty;
	int u = ((1 << N) - 1) & (~mask);

	while (u){
		int j = log2(u & (-u));
		int newmask = (mask | (1 << j));
		if (dp[mask] - g[i][j] - t[j] > dp[newmask]) {
			dp[newmask] = dp[mask] - g[i][j] - t[j];
			solve(newmask, j, qty + 1);
			
		}
		u -= (1 << j);
	}
}

int main(){

	while (scanf("%d", &N), N){
		FOR(i, N) scanf("%d", &t[i]);
		FOR(i, N) FOR(j, N) scanf("%d", &g[i][j]);
		FOR(k, N) FOR(i, N) FOR(j, N) g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		
		M = (1 << N);
		FOR(i, M) dp[i] = -1;
		ans = 0;
		FOR(i, N) if (t[i] <= 420) {
			dp[1 << i] = 420 - t[i];
			solve(1 << i, i, 1);
		}

		printf("%d\n", ans);
	}

}