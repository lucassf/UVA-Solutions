#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define MAXM 19
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, ii> iii;
	
char str[MAXM];
int N;
int qty[MAXN * MAXM] = {}, nxt[MAXN * MAXM][26] = {}, num = 1;
ll dp[MAXN * MAXM][MAXN][26][2][2];

void add(){
	int u = 0;
	for (char *c = str; *c; ++c){
		++qty[u];
		int n = (*c) - 'A';
		if (!nxt[u][n]) nxt[u][n] = num++;
		u = nxt[u][n];
	}
	++qty[u];
}

ll solve(int u, int z, int n1, int n2, int f1, int f2){
	if (f1 && f2) return 0;
	while (z < 26 && !nxt[u][z]) ++z;
	if (z == 26) return 0;

	ll &ans = dp[u][n1][z][f1][f2];
	if (ans != -1) return ans;
	
	ans = INF;
	int m = nxt[u][z], p = min(n1, qty[m]) + 1;
	FORN(i, max(0, qty[m] - n2), p){
		int j = qty[m] - i;
		ans = min(ans, (!f1) * i + (!f2) * j + solve(m, 0, i, j, i <= 1, j <= 1) +
			solve(u, z + 1, n1 - i, n2 - j, f1, f2));
	}
	return ans;
}

int main(){
	scanf("%d", &N);
	FOR(i, 2 * N){
		scanf("%s", str);
		add();
	}
	FOR(i, num) FOR(j, N + 1)FOR(k, 26) FOR(p, 2) FOR(q, 2) dp[i][j][k][p][q] = -1;
	printf("%lld\n", solve(0, 0, N, N, 0, 0) * N);
}
