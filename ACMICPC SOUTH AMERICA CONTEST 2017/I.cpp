#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
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
typedef pair<int, ii> iii;

int N, M;
set<int> *q[MAXN];
iii e[MAXN];
int parent[MAXN] = {}, rk[MAXN] = {}, ans[MAXN], t[MAXN];

int Find(int i) {
	while(i != parent[i]) i = parent[i];
	return i;
}
int unionSet (int i, int j, int u) {
	int x = Find(i), y = Find(j);
	if (x == y) return 0;
	if (rk[x] < rk[y]) swap(x, y);
	parent[y] = x;
	if (rk[x] == rk[y]) rk[x]++;
	
	if (q[x]->size() < q[y]->size()) swap(q[x], q[y]);
	for (auto it : *q[y]){
		if (q[x]->count(it))q[x]->erase(it), ans[it] = u;
		else q[x]->insert(it);
	}
	delete q[y];
	
	return u;
}

int edmonds(){
	sort(e, e + M);
	iii aux;
	int u, v, r = 0;
	FOR(i, M){
		aux = e[i];
		u = aux.second.first, v = aux.second.second;
		r += unionSet(u, v, aux.first);
	}
	return r;
}

map<ii, int> pos;

int main(){
	scanf("%d%d", &N, &M);
	int a, b, c, Q;
	FOR(i, M){
		scanf("%d%d%d", &a, &b, &c); --a, --b;
		pos[ii(min(a, b), max(a, b))] = c;
		e[i] = {c, {a, b}};
	}
	FOR(i, N) {q[i] = new set<int>(); parent[i] = i;}
	scanf("%d", &Q);
	FOR(i, Q){
		scanf("%d%d", &a, &b);
		--a, --b;
		t[i] = pos[ii(min(a, b), max(a, b))];
		q[a]->insert(i), q[b]->insert(i);
	}
	a = edmonds();
	FOR(i, Q) printf("%d\n", a - ans[i] + t[i]);
}