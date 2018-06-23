#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> ii;
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define MAXN 100009
#define INF 1e12
#define EPS 1e-9
#define PMOD(a) (a % INF + INF) % INF
#define push_back pb

char str[MAXN];
int N, cnt[MAXN];
set<char> v = {'a', 'e', 'i', 'o', 'u'};

int main(){
	while (scanf("%s", str) != EOF){
		N = strlen(str);
		
		int u = 0, aux = 0;
		FOR(i, N){
			if (v.count(str[i])) cnt[u++] = aux, aux = 0;
			else aux++;
		}
		cnt[u++] = aux;
		if (u > 1 && !v.count(str[0])) printf("0\n");
		else if (u == 1) printf("1\n");
		else printf("%d\n", cnt[u / 2] + 1);
	}
}