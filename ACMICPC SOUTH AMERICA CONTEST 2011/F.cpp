#include <bits/stdc++.h>
using namespace std;
#define MAXN 600069
#define MAXM 100009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
#define pb push_back
#define L(N) N<<1
#define R(N) (N<<1) + 1
typedef long long int ll;
typedef pair<int, long> ii;
typedef pair<ii, ll> iii;
const ll MOD = 1000000007;

string str;
ll pos[MAXN];
ii vals[2 * MAXN];
int rem[MAXN];
int RA[MAXN], tempRA[MAXN], SA[MAXN];
int tempSA[MAXN], c[MAXN], n;
int LCP[MAXN]; //para LCP

void countingSort(int k) { // O(n)
	int i, sum, maxi = max(300, n);
	memset(c, 0, sizeof c);
	for (i = 0; i < n; i++) c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	for (i = 0; i < n; i++)
		tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	for (i = 0; i < n; i++) SA[i] = tempSA[i];
}

void constructSA() { // O(nlogn)
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = str[i];
	for (i = 0; i < n; i++) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		for (i = 1; i < n; i++) 
			tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		for (i = 0; i < n; i++) RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break;
	}
}

void computeLCP() { // O(n)
	int i, L;
	tempRA[SA[0]] = -1;
	for (i = 1; i < n; i++)  tempRA[SA[i]] = SA[i-1];
	for (i = L = 0; i < n; i++) {
		if (tempRA[i] == -1) {
			RA[i] = 0; continue;
		}
		while (str[i + L] == str[tempRA[i] + L]) L++;
		RA[i] = L;
		L = max(L-1, 0);
	}
	for (i = 0; i < n; i++) LCP[i] = RA[SA[i]];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int F;
	string s;
	while (cin>>F && F){
		str = "";
		n = 0;
		FOR(i, F){
			cin>>s;
			FOR(j, s.size()){
				pos[j + n] = 1LL<<i;
				rem[j + n] = s.size() - j;
			}
			str += s + "$";
			n = str.size();
		}
		constructSA();
		computeLCP();

		int p = -1;
		set<ll> ans; ans.clear();
		
		LCP[n] = 0, SA[n] = n, pos[n] = 0, rem[n] = 0;

		FORN(i, F, n) LCP[i] = min(LCP[i], rem[SA[i]]);

		FORN(i, F, n + 1){
			int u = SA[i];
			int lcp = LCP[i];

			if (i < n && rem[u] > max(LCP[i], LCP[i + 1]))  ans.insert(pos[u]);

			ll acum = 0;
			while (p >= 0 && lcp < vals[p].first){
				int lcp1 = vals[p].first;
				while (lcp1 == vals[p].first) acum |= vals[p--].second;
				ans.insert(acum | vals[p].second);
			}
			if (p >= 0) vals[++p] = ii(lcp, acum);
			vals[++p] = ii(lcp, pos[u]);
		}
		cout<<(int)ans.size()<<'\n';
	}
}
