#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define EPS 1e-9
#define INF 1e9
typedef long long int ll;
typedef pair<double, int> di;

int N, Q;
vector<int> vals[MAXN];

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int m, n;

//Vértices enumerados de 1 a m em U e de 1 a n em V!!!!
bool bfs() {
    queue<int> q;
    for (int u=1; u<=m; u++) {
        if (pairU[u]==0) {
            dist[u] = 0;
            q.push(u);
        }
        else dist[u] = INF;
    }
    dist[0] = INF;
    int u, v;
    while (!q.empty()) {
        u = q.front(); q.pop();
        if (dist[u] < dist[0]) {
            for (int i=0; i<(int)adjU[u].size(); ++i) {
                v = adjU[u][i];
                if (dist[pairV[v]] == INF){
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u) {
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i) {
        v = adjU[u][i];
        if (dist[pairV[v]] == dist[u]+1) {
            if (dfs(pairV[v])) {
                pairV[v] = u; pairU[u] = v;
                return true;
            }
        }
    }
    dist[u] = INF;
    return false;
}

//O(E*sqrt(V))
int hopcroftKarp() {
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    while (bfs()) {
        for (int u=1; u<=m; u++) {
            if (pairU[u]==0 && dfs(u))
                result++;
        }
    }
    return result;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int qtt;
	int a, poss;
	set<int> hasp;
	
	while (cin>>N>>Q){
		m = n = N;
		for (int i = 0; i < N; i++){
			vals[i].clear();
			cin>>qtt;
			for (int j = 0; j < qtt; j++){
				cin>>a;
				vals[i].push_back(a);
			}
		}
		while (Q-- > 0){
			cin>>qtt;
			hasp.clear();
			
			for (int i = 1; i <= N; i++) adjU[i].clear();
			for (int i = 0; i < qtt; i++){
				cin>>a;
				hasp.insert(a);
			}
			
			poss = 1;
			for (int i = 0; i < N && poss; i++){
				int cnt = 0;
				for (int j = 0; j < (int) vals[i].size(); j++){
					int v = vals[i][j];
					if (hasp.count(v)){
						cnt = 1;
						adjU[i + 1].push_back(v);
					}
				}
				if (!cnt && vals[i].size() == N) poss = 0;
			}
			
			if (poss && hopcroftKarp() != qtt) poss = 0;
			
			if (poss) cout<<"Y\n";
			else cout<<"N\n";
		}
	}
}