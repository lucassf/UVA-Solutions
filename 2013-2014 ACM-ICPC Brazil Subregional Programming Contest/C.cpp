#include <bits/stdc++.h>
using namespace std;
#define MAXN 509
#define INF 1000000000
typedef set<int>::iterator sit;

int emp[MAXN],k[MAXN], pos[MAXN];
vector<int> adjList[MAXN];
set<int> vals[MAXN];
bool visited[MAXN] = {};

void preProc(int u){
    int v;
    if (visited[u])return;
    visited[u]=true;
    for (int i=0;i<(int) adjList[u].size();i++){
        v = adjList[u][i];
        preProc(v);
        vals[u].insert(v);
        for (sit it = vals[v].begin();it!=vals[v].end();it++){
            vals[u].insert(*it);
        }
    }
}

int main(){
    int n,m,I,x,y,ans;
    char com;
    while (scanf("%d%d%d",&n,&m,&I)!=EOF){
        for (int i=0;i<n;i++){
            scanf("%d",&k[i]),emp[i] = i,pos[i]=i;
            adjList[i].clear();
            vals[i].clear();
            visited[i] = false;
        }
        for (int i=0;i<m;i++){
            scanf("%d%d",&x,&y);
            x--,y--;
            adjList[y].push_back(x);
        }
        for (int i=0;i<n;i++)preProc(i);
        for (int i=0;i<I;i++){
            cin>>com;
            if (com=='T'){
                scanf("%d%d",&x,&y);
                x--,y--;
                swap(pos[x],pos[y]);
                emp[pos[x]] = x,emp[pos[y]] = y;
            }else{
                scanf("%d",&x);
                x--;
                x = pos[x];
                ans = INF;
                for (sit it = vals[x].begin();it!=vals[x].end();it++){
                    ans = min(k[emp[*it]],ans);
                }
                if (ans==INF)printf("*\n");
                else printf("%d\n",ans);
            }
        }
    }
}
