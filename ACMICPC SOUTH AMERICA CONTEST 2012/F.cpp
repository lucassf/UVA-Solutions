#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int,int> ii;
typedef long double ld;
#define MAXN 1009
#define INF 1000000007
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define PMOD(a, m) ((a) % (m) + (m)) % (m)

char str[MAXN];
vector<int> adjList[MAXN * MAXN];
int vis[MAXN * MAXN];

void bfs(int u){
	queue<int> vals;
	vals.push(u);
	vis[u] = 1;	

	while (!vals.empty()){
		u = vals.front(); vals.pop();
		//cout<<u<<' ';
		for (int v : adjList[u]) if (!vis[v]){vals.push(v); vis[v] = 1;}
	}//cout<<'\n';
}

void add(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
}

int main(){
	
	int N;
	while (scanf("%d", &N) != EOF){
		int u = (2 * N + 1) * 2 * N;
		int l1, l2, l3, l4;
		FOR(i, u) adjList[i].clear(), vis[i] = 0; 
		FOR(i, 2 * N - 1) {
			cin>>str;

			if (i % 2) add(i * (2 * N + 1), (i + 1) * (2 * N + 1));
			else{
				add(i * (2 * N + 1) + 2 * N, (i + 1) * (2 * N + 1) + 2 * N);
			}

			FOR(j, N){
				if (i % 2) {
					l1 = i * (2 * N + 1) + 2 * j + 1, l2 = i * (2 * N + 1) + 2 * j + 2, l3 = (i + 1) * (2 * N + 1) + 2 * j + 1, l4 = (i + 1) * (2 * N + 1) + 2 * j + 2;
					
				}
				else {
					l1 = i * (2 * N + 1) + 2 * j, l2 = i * (2 * N + 1) + 2 * j + 1, l3 = (i + 1) * (2 * N + 1) + 2 * j, l4 = (i + 1) * (2 * N + 1) + 2 * j + 1;
					if (i == 0)add(l2, l2 + 1);
					if (i == 2 * N - 2) add(l4, l4 + 1);
				}

				if (str[j] == 'H'){
					add(l1, l2), add(l3, l4);
				}else{
					add(l1, l3), add(l2, l4);
				}
			}
		}
		int ans = 0;
		FOR(i, u) if (!vis[i]) {ans++; bfs(i);}
		cout<<ans - 1<<'\n';
	}
	
}