#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define MAXN 1009

int N,P,K;
int numAdj[MAXN];
vector<int> adjList[MAXN];
vector<bool> vis;

int dfs(int u){
    vis[u] = true;
    int ret = 1,v;

    for (int i=0;i<(int)adjList[u].size();i++){
        v = adjList[u][i];
        if (numAdj[v]>0&&!vis[v])ret+=dfs(v);
    }
    return ret;
}

int main(){
    map<ii,bool> used;
    stack<int> discard;

    int u,v,ans;
    while (scanf("%d%d%d",&N,&P,&K),N){
        used.clear();
        ans = 0;
        memset(numAdj,0,sizeof(numAdj));
        for (int i=0;i<N;i++)adjList[i].clear();

        for (int i=0;i<P;i++){
            scanf("%d%d",&u,&v);
            u--, v--;
            if (used[ii(min(u,v),max(u,v))])continue;
            used[ii(min(u,v),max(u,v))] = true;
            numAdj[u]++;
            numAdj[v]++;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        for (int i=0;i<N;i++)if (numAdj[i]<K){
            discard.push(i);
            numAdj[i] = 0;
        }

        while (!discard.empty()){
            u = discard.top();
            discard.pop();

            for (int i=0;i<adjList[u].size();i++){
                v = adjList[u][i];
                if (numAdj[v]>0){
                    numAdj[v]--;
                    if (numAdj[v]<K){discard.push(v);numAdj[v] = 0;}
                }
            }
        }
        vis.assign(N,0);
        for (int i=0;i<N;i++){
            if (!vis[i]&&numAdj[i]>0)ans = max(ans,dfs(i));
        }
        printf("%d\n",ans);
    }
}
