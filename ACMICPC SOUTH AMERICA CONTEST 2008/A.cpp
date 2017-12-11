#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define MAXN 509
#define INF 1e9

int N, M, S, D;
int adjList[MAXN][MAXN];
int vis[MAXN];
vector<int> bestPrev[MAXN];

inline int djkstra(){
    priority_queue<ii> inuse;
    inuse.push(ii(0,S));
    int vals[MAXN];

    for (int i = 0; i < N; i++)vals[i] = INF;
    vals[S] = 0;

    while (!inuse.empty()){
        int u = inuse.top().second;
        int c = -inuse.top().first;
        inuse.pop();

        if (u == D)break;
        if (c > vals[u])continue;

        for (int v = 0; v < N; v++){
            if (adjList[u][v] == INF)continue;

            int cv = adjList[u][v] + c;
            if (cv < vals[v]){
                vals[v] = cv;
                bestPrev[v].clear();
                bestPrev[v].push_back(u);
                inuse.push(ii(-cv,v));
            }else if (cv == vals[v]){
                bestPrev[v].push_back(u);
            }
        }
    }
    return vals[D];
}

int main(){
    int u,v,p;

    while (scanf("%d%d", &N, &M),N){
        scanf("%d%d",&S, &D);
        for (int i = 0; i < N; i++)for (int j = 0; j < N; j++){
            adjList[i][j] = INF;
            bestPrev[i].clear();
        }
        for (int i = 0; i<M; i++){
            scanf("%d%d%d", &u, &v, &p);
            adjList[u][v] = p;
        }
        djkstra();

        queue<int> todel;
        todel.push(D);
        memset(vis, 0, sizeof(vis));

        while (!todel.empty()){
            int u = todel.front();
            todel.pop();
            vis[u] = 1;

            for (int i = 0; i < (int)bestPrev[u].size(); i++){
                int v = bestPrev[u][i];
                adjList[v][u] = INF;
                if (!vis[v])todel.push(v);
            }
        }

        int ans = djkstra();
        if (ans < INF)printf("%d\n",ans);
        else printf("-1\n");
    }

}
