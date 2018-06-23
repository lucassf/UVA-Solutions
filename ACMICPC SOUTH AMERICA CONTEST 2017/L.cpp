#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> ii;

#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define MAXN 100009
#define INF 1e9
#define EPS 1e-9
#define PMOD(a) (a % INF + INF) % INF

int N, D[2][MAXN], L[2][MAXN], R[2][MAXN], acum[2][MAXN];
int s1[2], s2[2], ds[2];

inline int compute(){
	int j = ds[0] < ds[1] ? 0 : 1;
	int dx = abs(ds[0] - ds[1]) / 2;
	
	int ans = dx * 10;
	if (R[j][s1[j]] >= 0 && R[j][s1[j]] <= s2[j]) ans = 2 * dx;
	if (L[j][s1[j]] >= 0) {
		int dl = s1[j] - L[j][s1[j]];
		if (dx > dl){
			ans = min(ans, 10 * dl + 2 * (dx - dl));
		}
	}if (R[j][s2[j]] >= 0) {
		int dr = R[j][s2[j]] - s2[j];
		if (dx > dr){
			ans = min(ans, 10 * dr + 2 * (dx - dr));
		}
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (cin>>N){
		FOR(j, 2){
			acum[j][0] = 0;
			FOR(i, N - 1) cin>>D[j][i], acum[j][i + 1] = acum[j][i] + D[j][i];
			L[j][0] = R[j][N - 1] = -1;
			FORN(i, 1, N) L[j][i] = D[j][i - 1] == 1? i : L[j][i - 1];
			for(int i = N - 2; i >= 0; --i) R[j][i] = D[j][i] == 1? i : R[j][i + 1];
		}
		int Q;
		cin>>Q;
		while (Q--){
			cin>>s1[0]>>s1[1]>>s2[0]>>s2[1];
			int ans = 0;
			FOR(j, 2) {
				s1[j]--, s2[j]--;
				if (s1[j] > s2[j]) swap(s1[j], s2[j]);
				ds[j] = s2[j] - s1[j];
				ans += acum[j][s2[j]] - acum[j][s1[j]];
			}
			ans += compute();
			cout<<ans<<'\n';
		}
	}
}