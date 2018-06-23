#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<int, int> ii;
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define MAXN 500009
#define INF 1e12
#define EPS 1e-9
#define PMOD(a) (a % INF + INF) % INF
#define push_back pb
#define MOD 1000000007

int N, M, pos[MAXN];
int str[MAXN];

int RA[MAXN], tempRA[MAXN];
int tempSA[MAXN], c[MAXN], n, SA[MAXN];

void countingSort(int k, int SA[]) {
	int i, sum, maxi = max(302, n);
	memset(c, 0, sizeof c);
	for (i = 0; i < n; i++)  c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	for (i = 0; i < n; i++)  tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	for (i = 0; i < n; i++)  SA[i] = tempSA[i];
}

void constructSA() { // O(nlogn)
	int i, k, r; n = M;
	for (i = 0; i < n; i++) RA[i] = str[i];
	for (i = 0; i < n; i++) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {
		countingSort(k, SA);
		countingSort(0, SA);
		tempRA[SA[0]] = r = 0;
		for (i = 1; i < n; i++)  tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		for (i = 0; i < n; i++)  RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break;
	}
}

set<ii> vals;

ll pmod(ll a, ll b, ll m){
	ll ans = 1;
	while (b){
		if (b & 1) ans = ans * a % m;
		a = a * a % m;
		b >>= 1;
	}
	return ans;
}

int main(){
	int K;
	
	while (scanf("%d", &N) != EOF){
		int v;
		M = 0;
		FOR(i, N){
			scanf("%d", &K);
			pos[i] = M;
			FOR(j, K){
				scanf("%d", &v);
				str[M++] = v;
			}
			str[M++] = 301;
		}
		constructSA();
		
		ll ans = 0, d = 1;
		ll inv = pmod(365, MOD - 2, MOD);
		FOR(i, M - N) d = d * 365 % MOD;
		
		FOR(i, N) vals.insert(ii(RA[pos[i]], i));
		while (!vals.empty()){
			ii aux = *(vals.begin());
			vals.erase(vals.begin());
			
			int i = aux.second;
			ans = (ans + d * str[pos[i]] % MOD) % MOD;
			pos[i]++;
			if (str[pos[i]] <= 300) vals.insert(ii(RA[pos[i]], i));
			d = (d * inv) % MOD;
		}
		printf("%lld\n", ans);
	}
}