#include <bits/stdc++.h>
using namespace std;
#define MAXN 509
#define UNVISITED -1
typedef pair<int,int> ii;

int N, C, pos[MAXN], num[MAXN], low[MAXN], parent[MAXN], counter,
    rootChildren, isBridge[MAXN], vis[MAXN], root;
vector<ii> adjList[MAXN];
vector<int> cities[MAXN];

int idx[2];

void tarjan(int u){
    low[u] = num[u] = counter++;

    for (int j = 0; j < (int)cities[u].size(); j++)
        vis[cities[u][j]] = 1;

    for (int j = 0, v; j < (int)adjList[u].size(); j++){
        v = adjList[u][j].first;
        int a = adjList[u][j].second;
        vis[a] = 1;

        if (num[v] == UNVISITED){
            parent[v] = a;
            if (u == root)rootChildren++;
            tarjan(v);
            if (low[v] > num[u]){
                isBridge[a] = 1;
            }
            low[u] = min(low[u], low[v]);
        }
        else if (a != parent[u]){
            low[u] = min(low[u], num[v]);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K, a, ans;
    bool poss;

    while (cin>>N>>C, N){
        poss = true;
        memset(pos, -1, sizeof(pos));

        for (int i = 0; i < C; i++){
            cin>>K;
            adjList[i].clear();
            cities[i].clear();

            for (int j = 0; j < K; j++){
                cin>>a;
                cities[i].push_back(a);
                if (pos[a] >= 0){
                    adjList[i].push_back(ii(pos[a], a));
                    adjList[pos[a]].push_back(ii(i, a));
                }
                pos[a] = i;
            }
        }
        int odds = 0;
        for (int i = 0; i < C; i++){
            if (((int)adjList[i].size()) % 2 == 1)idx[odds%2] = i, odds++;
        }
        if (odds != 0 && odds != 2)
            poss = false;
        else{
            memset(num, UNVISITED, sizeof num);
            memset(low, 0, sizeof low);
            memset(parent, 0, sizeof parent);
            memset(isBridge, 0, sizeof isBridge);
            memset(vis, 0, sizeof vis);

            for (int k = 0; k < C; k++){
                if ((int)cities[k].size() > 0){
                    counter = rootChildren = 0;
                    root = k;
                    tarjan(k);
                    break;
                }
            }

            for (int i = 0; i < N; i++){
                //printf("%d ",isBridge[i]);
                if (!vis[i]){
                    poss = false;
                    break;
                }
            }
            //printf("\n\n");
            if (poss){
                if (!odds)ans = 0;
                else{
                    ans = N;
                    for (int k = 0; k < 2; k++){
                        int i = idx[k];
                        if (cities[i].size() == 1){
                            ans = min(cities[i][0], ans);
                            continue;
                        }
                        for (int j = 0; j < (int)cities[i].size(); j++){
                            a = cities[i][j];
                            if (!isBridge[a])ans = min(ans, a);
                        }
                    }
                }
            }
        }
        if (!poss)cout<<"-1\n";
        else cout<<ans<<"\n";
    }
}
