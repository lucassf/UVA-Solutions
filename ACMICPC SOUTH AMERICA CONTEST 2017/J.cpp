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

int N, vis[MAXN] = {}, ans;
char s[MAXN];

void solve(int u){
	FOR(i, u) {
		int r = i;
		while (r < N && s[r] == 'R') r += u;
		if (r >= N) {
			for (int j = u; j < N; j += u){
				if (!vis[j]) ++ans;
				vis[j] = 1;
			}
			return;
		}
	}
}

int main(){
	scanf("%s", s);
	N = strlen(s);

	ans = 0;

	for (int i = 1; i * i <= N; ++i){
		if (N % i == 0){
			int u = N / i;
			if (!vis[i]) solve(i); 
			if (!vis[u]) solve(u);
		}
	}
	printf("%d\n", ans);
}