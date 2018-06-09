#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> ii;
#define MAXN 1009
#define INF 1000000007
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define PMOD(a, m) ((a) % (m) + (m)) % (m)

ll x[MAXN], w[MAXN], s[MAXN] = {}, c[MAXN] = {}, dp[2][MAXN];

inline double intersect(int i, int a, int b){
	ll p1 = dp[i][a - 1] - dp[i][b - 1] - c[a] + c[b];
	ll q1 = s[b] - s[a];
	return (double) p1 / q1;
}

int main(){
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);
	
	int N, K, idx;
	while (scanf("%d%d", &N, &K) != EOF){

		FOR(i, N) scanf("%lld%lld", &x[i], &w[i]);
		
		s[N] = c[N] = 0;
		for (int i = N - 1; i >= 0; --i){
			s[i] = s[i + 1] + w[i];
			c[i] = c[i + 1] + w[i] * x[i];
		}

		deque<int> vals;
		FOR(i, N) {
			dp[0][i] = x[i] * (s[0] - s[i]) - c[0] + c[i];
		}
		dp[0][0] = 0;
		FORN(i, 1, K){
			vals.push_front(i);
			FORN(j, i, N){
				while (vals.size() > 1 && intersect((i + 1) % 2, vals[0], vals[1]) <= x[j]) vals.pop_front();
				idx = vals.front();
				dp[i % 2][j] = dp[(i - 1) % 2][idx - 1] + x[j] * (s[idx] - s[j]) - c[idx] + c[j];

				while (vals.size() > 1 && intersect((i + 1) % 2, j + 1, vals[vals.size() - 1]) <= intersect((i + 1) % 2, j + 1, vals[vals.size() - 2])) vals.pop_back();
				vals.push_back(j + 1);
			}
			vals.clear();
		}
		printf("%lld\n", dp[(K - 1) % 2][N - 1]); 
	}
}