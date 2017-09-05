#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 1200
#define MAXM 900000
using namespace std;

int N, M, ned, first[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;

    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	int v, df;
	for(int e = first[u]; e!=-1; e = nxt[e]){
        v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0) {
			df = dfs(v, min(f, cap[e]), s, t);
			if (df > 0) {
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	while (!q.empty()) {
		u = q.front(); q.pop();
		for(int e = first[u]; e!=-1; e = nxt[e]){
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t] >= 0;
}

//O(EV^2)
int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

int main(){
    int n,m,k,c,u,v,t=1;
    while (cin>>n>>m>>k){
        init();
        for (int i=1;i<=n;i++){
            cin>>c;
            add(0,i,c);
        }
        for (int i=1;i<=m;i++){
            add(i+100,201,1);
        }
        for (int i=0;i<k;i++){
            cin>>u>>v;
            add(u,v+100,1);
        }
        cout<<"Instancia "<<t++<<"\n";
        cout<<dinic(0,201)<<"\n\n";
    }
}
