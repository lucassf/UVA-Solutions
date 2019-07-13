#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

#define MAXN 10009
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)

int N, C, P[MAXN];
int X[MAXN], Y[MAXN];
vector<int> g[MAXN];

int solve(int u = 0) {
	int ans = 0;
	for (int v : g[u]) {
		ans += solve(v);
		P[u] += P[v];
	}
	if (P[u] >= C) ans++, P[u] = 0;
	return ans;
}

int main() {

	while (scanf("%d%d", &N, &C), N, C) {
		FOR(i, N) {
			scanf("%d%d%d", &X[i], &Y[i], &P[i]);
			double dist = INF;
			int idx = -1;

			FOR(j, i) {
				double newdist = hypot(X[i] - X[j], Y[i] - Y[j]);
				if (newdist < dist) {
					dist = newdist;
					idx = j;
				}
			}
			g[i].clear();
			if (idx >= 0) g[idx].push_back(i);
		}
		printf("%d\n", solve());
	}
}
