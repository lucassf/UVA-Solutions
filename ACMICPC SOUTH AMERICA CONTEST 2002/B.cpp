#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
typedef pair<int,int> ii;

int N;
vector<ii> adjList[MAXN];
int visit[MAXN];
int nxt[MAXN];

bool poss;
int numf,numt;

void dfs(int u,int ver,int f){
    if (visit[u]==1){
        if (f%2==1)poss=false;
        return;
    }
    visit[u] = 1;
    numt+=1-ver;
    numf+=ver;

    for (int i=0;i<(int)adjList[u].size();i++){
        int v = adjList[u][i].first;
        int d = adjList[u][i].second;

        //cout<<v<<" "<<d<<endl;

        dfs(v,d!=ver?1:0,d+f);
    }
}

int main(){
    int x,dir,ans;
    char valid[10];

    while (scanf("%d",&N)&&N!=0){
        poss = true;
        for (int i=0;i<N;i++)adjList[i].clear(),nxt[i] = -1;
        for (int i=0;i<N;i++){
            scanf("%s %d %s %s",&valid,&x,&valid,&valid);
            dir = valid[0]=='f'?1:0;
            nxt[i] = x-1;
            adjList[x-1].push_back(ii(i,dir));
            visit[i] = 0;
        }
        ans = 0;
        for (int i=0;i<N && poss;i++){
            if (visit[i])continue;
            visit[i] = 2;
            int u = i;
            while (nxt[u]!=-1&&!visit[nxt[u]]){u = nxt[u],visit[u] = 2;}
            numf = numt = 0;
            dfs(u,0,0);
            ans+=max(numf,numt);
        }
        if (!poss)printf("Inconsistent\n");
        else printf("%d\n",ans);
    }
}
