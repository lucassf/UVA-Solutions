#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;
typedef long double ld;
#define MAXN 1000009
#define INF 1000000007
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define PMOD(a, m) ((a) % (m) + (m)) % (m)

int nxt[MAXN][26], sol[MAXN], nmax;

void add(const char *s){
	int node = 0;
	int n = strlen(s);
	FOR(i, n){
		int u = s[i] - 'a';
		if (!nxt[node][u]){
			sol[nmax] = 0; 
			FOR(i, 26) nxt[nmax][i] = 0;
			nxt[node][u] = nmax++;
		}
		node = nxt[node][u];
	}
	sol[node]++;
}

int bfs(){
	queue<ii> vals;
	int ans = 0;

	int u = 0, cnt, v;
	while (!sol[u]){
		int cnt = 0;
		FOR(i, 26) if (nxt[u][i]) cnt++, v = nxt[u][i];
		if (cnt != 1) break;
		u = v;
	}
	vals.push(ii(u, u ? 1 : 0));

	while (!vals.empty()){
		int u = vals.front().first;
		int qty = vals.front().second;
		vals.pop();

		while (!sol[u] && u){
			cnt = 0;
			FOR(i, 26) if (nxt[u][i]) cnt++, v = nxt[u][i];
			if (cnt != 1) break;
			u = v;
		}
		ans += sol[u] * qty;
		FOR(i, 26) if (nxt[u][i]) vals.push(ii(nxt[u][i], qty + 1));
	}
	return ans;
}

char str[MAXN];

int main(){
	
	int N;

	while (scanf("%d", &N) != EOF){
		nmax = 1;
		sol[0] = 0;
		FOR(i, 26) nxt[0][i] = 0;
		FOR(i, N) {scanf("%s", str); add(str);}
		printf("%.2lf\n", (double)bfs() / N);
	}
}