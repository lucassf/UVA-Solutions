#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
#define FOR(N, M, i) for (i = N; i < M; i++)
#define MAXN 509
	
int R, C, N;
int a[MAXN][MAXN], c[MAXN][MAXN], r[MAXN][MAXN], nxt[MAXN][MAXN];
ii q[5], s, t;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int i, j, k, x, y, ans;
	bool found;
	set<iii> inuse;
	
	while (cin>>R>>C>>N){
		FOR(0, R, i){
			FOR (0, C, j){
				cin>>a[i][j];
			}
		}
		FOR(0, R, i)FOR (0, C, j){
			cin>>r[i][j];
		}
		FOR(0, R, i)FOR (0, C, j){
			cin>>c[i][j];
		}
		FOR(0, N, i) {
			cin>>x>>y;
			q[i] = ii(x - 1, y - 1);
		}
		
		FOR(0, N - 1, k){
			FOR(0, R + 1, i)FOR (0, C + 1, j)nxt[i][j] = j;
			s = q[k], t = q[k + 1];
			
			inuse.clear();
			inuse.insert(iii(a[s.first][s.second], ii(s.first, s.second)));
			nxt[s.first][s.second] = s.second + 1;
			
			found = false, ans = -1;
			
			while (!inuse.empty() && !found){
				int cost = (*inuse.begin()).first;
				int u = (*inuse.begin()).second.first;
				int v = (*inuse.begin()).second.second;
				
				inuse.erase(inuse.begin());
				
				if (u == t.first && v == t.second) {
					ans = cost - a[u][v];
					break;
				}
				
				int U = min(u + r[u][v] + 1, R);
				int V = min(v + c[u][v] + 1, C);
				FOR (max(0, u - r[u][v]), U, i){
					FOR (max(0, v - c[u][v]), V, j){
						int u = i, v = j;
						while (nxt[i][v] != v){
							v = nxt[i][v];
						}
						while (true){
							int auxj = nxt[i][j];
							nxt[i][j] = max(v, V);
							if (auxj == j) break;
							j = auxj;
						}
						if (j >= V) break;
						
						inuse.insert(iii(a[i][j] + cost, ii(i, j)));
						if (i == t.first && j == t.second) {
							ans = cost;
							found = true; break;
						}
					}
					if (found) break;
				}
			}
			if (k > 0)cout<<" ";
			cout<<ans;
		}
		cout<<"\n";
	}
}
