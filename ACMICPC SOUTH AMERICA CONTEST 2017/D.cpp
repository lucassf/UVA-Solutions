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
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;

int L, C, N, qty[MAXN] = {};
set<iii> vals;

void update(int l, int r, int x){
	auto it = vals.lower_bound(iii(ii(l + 1, 0), 0));
	int l1, r1, c;
	it--;
	
	l1 = (it->first).first, r1 = (it->first).second,c = it->second;
	if (l1 < l) vals.insert(iii(ii(l1, l - 1), c)), qty[c] += l - l1;
	while (it != vals.end() && (it->first).first <= r){
		l1 = (it->first).first, r1 = (it->first).second,c = it->second;
		qty[c] -= (r1 - l1 + 1);
		auto it2 = it; it2++;
		vals.erase(it);
		it = it2;
	}
	if (r1 > r) vals.insert(iii(ii(r + 1, r1), c)), qty[c] += r1 - r;
	vals.insert({{l, r}, x});
	qty[x] += r - l + 1;
}

int main(){
	scanf("%d%d%d", &L, &C, &N);
	int x, p;
	ll a, b, s;
	qty[1] = L;
	vals.insert(iii(ii(0, L - 1), 1));	

	while (N--){
		scanf("%d%d%lld%lld", &x, &p, &a, &b);
		s = qty[x];
		int m1 = (s * s % L + a) % L;
		int m2 = ((s + b) * (s + b) % L + a) % L;
		update(min(m1, m2), max(m1, m2), p);
	}
	int ans = 0;
	FORN(i, 1, C + 1) ans = max(ans, qty[i]);
	printf("%d\n", ans);
}