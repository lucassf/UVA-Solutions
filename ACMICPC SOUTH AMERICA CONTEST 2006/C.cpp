#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace std;

#define MAXN 40
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)

typedef long long int ll;

int N, M;

int golden[MAXN][MAXN][MAXN];
int nlen[MAXN], artist[MAXN];
int result[MAXN][1 << 6];
ll dp[MAXN][1 << 6];
char str[MAXN][MAXN], auxstr[MAXN];
map<string, int> artistsToInt;

void getGolden(int index1, int index2) {
	FOR(i, nlen[index1]) {
		int best = 1;
		FOR(j, nlen[index2]) {
			int cnt = 0;
			while (cnt + i < nlen[index1] && cnt + j < nlen[index2] &&
				str[index1][cnt + i] == str[index2][cnt + j]) ++cnt;
			best = max(best, cnt + 1);
		}
		if (best > nlen[index1] - i) best = INF;
		golden[index1][index2][i] = best;
	}
}

void getGolden() {
	FOR(i, M + N) {
		FORN(j, i + 1, M + N) {
			getGolden(i, j);
			getGolden(j, i);
		}
	}
}

void getResults() {
	FOR(mask, 1 << M) {
		FOR(i, M + N) {
			result[i][mask] = INF;
			FOR(k, nlen[i]) {
				int res = 0;
				FOR(j, N) {
					res = max(res, golden[i][j][k]);
				} FOR(j, M) {
					if ((1 << j) & mask) res = max(res, golden[i][j + N][k]);
				}
				result[i][mask] = min(result[i][mask], res);
			}
		}
	}
}

ll recsolve(int index, const int mask, int curmask) {
	if (index == N) return 0;
	if (dp[index][curmask] != -1) return dp[index][curmask];
	ll& ans = dp[index][curmask] = result[index][mask] + recsolve(index + 1, mask, curmask);

	if (mask & (~curmask) & (1 << artist[index])) {
		ans = min(ans, result[artist[index] + N][mask] +
			recsolve(index + 1, mask, curmask | (1 << artist[index])));
	}
	return ans;
}

int main() {
	while (scanf("%d", &N), N) {
		M = 0;
		artistsToInt.clear();

		FOR(i, N) {
			scanf("%s", str[i]);
			nlen[i] = strlen(str[i]);
			scanf("%s", auxstr);

			int pos;

			if (artistsToInt.count(auxstr)) pos = artistsToInt[auxstr];
			else {
				strcpy(str[N + M], auxstr);
				nlen[N + M] = strlen(str[N + M]);
				pos = artistsToInt[auxstr] = M++;
			}
			artist[i] = pos;
		}
		getGolden();
		getResults();
		
		ll ans = INF;
		FOR(i, 1 << M) {
			memset(dp, -1, sizeof dp);
			ans = min(ans, recsolve(0, i, 0));
		}
		printf("%lld\n", ans);
	}
}
