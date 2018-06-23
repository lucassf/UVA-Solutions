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
typedef pair<ll, ll> ii;
typedef pair<ii, ll> iii;

int N;
ll val[MAXN];
iii p[MAXN];

const ll neutral = 0;
ll comp(ll a, ll b) {
	return max(a,b);
}

class SegmentTree {
	vector<ll> a;
	int n;
public:
	SegmentTree(int N) {
		int sz = N;
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral);
	}
	void update(int i, ll x) {
		a[i+n] = max(a[i + n], x); //substitui
		for (i += n, i >>= 1; i; i >>= 1)
			a[i] = comp(a[i<<1], a[1+(i<<1)]);
	}
	ll query(int l, int r) {
		ll ans = neutral;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = comp(ans, a[l++]);
			if (r & 1) ans = comp(ans, a[--r]);
		}
		return ans;
	}
};

int F[MAXN];
set<iii> v;
map<int, int> pos;

int main(){
	//ios_base::sync_with_stdio(false);
	//cin.tie(NULL);
	ll b, f, d;
	scanf("%d", &N);
	FOR(i, N){
		scanf("%lld%lld%lld", &b, &f, &d);
		F[i] = f;
		auto it = v.lower_bound({{b, f}, 0});
		if (it != v.end() && it->first == ii(b, f)){
			d += it->second;
			v.erase(it);
			v.insert({{b, f}, d});
		}
		else v.insert({{b, f}, d});		
	}
	int M = 0;
	for (auto it : v) p[M++] = it;
	sort(F, F + N);
	
	M = 0;
	pos[F[0]] = M++;
	FORN(i, 1, N){
		if (F[i] != F[i - 1])pos[F[i]] = M++;
	}
	SegmentTree st(N);
	
	int r;
	FOR(i, N){
		b = p[i].first.first;
		r = i;
		while (r < N && p[r].first.first == b){
			val[r] = p[r].second + st.query(0, pos[p[r].first.second] - 1);
			++r;
		}
		FORN(j, i, r) st.update(pos[p[j].first.second], val[j]);
		i = r - 1;
	}
	ll ans = 0;
	FOR(i, N) {
		ans = max(ans, val[i]);

	}
	printf("%lld\n", ans);
}