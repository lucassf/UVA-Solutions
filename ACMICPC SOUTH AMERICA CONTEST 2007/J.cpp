#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009

int canuse[MAXN];
vector<int> adjList[MAXN];
int value[MAXN],numelem,N,R,cnt[MAXN];
stack<int> bestwishes;
bool poss;

bool insertElem(int u){
    if (canuse[u]!=numelem)return false;

    for (int i=0;i<(int)adjList[u].size();i++){
        canuse[adjList[u][i]]++;
    }
    numelem++;
    value[u] = 1;
    return true;
}

void removeElem(int u){
    for (int i=0;i<(int)adjList[u].size();i++){
        int v = adjList[u][i];
        canuse[v]--;
    }
    value[u] = 0;
    numelem--;
}

bool notInSet(int u){
    cnt[u] = 0;
    for (int i=0;i<(int)adjList[u].size();i++){
        if (value[adjList[u][i]]==1)continue;
        if (!insertElem(adjList[u][i])){return false;}
        bestwishes.push(adjList[u][i]),cnt[u]++;
    }
    value[u]= 2;
    return true;
}

void removeFromSet(int u){
    while (cnt[u]>0){
        removeElem(bestwishes.top());
        bestwishes.pop();
        cnt[u]--;
    }
    value[u] = 0;
}

bool solve(int u){
    if (u==N)return true;

    if (value[u]!=0)return solve(u+1);
    if (insertElem(u)){
        if (solve(u+1))return true;
        removeElem(u);
    }
    if (notInSet(u)&&(solve(u+1)))return true;

    removeFromSet(u);
    value[u] = 0;
    return false;
}

int main(){
    int a,b;
    while (scanf("%d%d",&N,&R)&&N!=0){
        for (int i=0;i<N;i++){
            adjList[i].clear();
            value[i] = canuse[i] = 0;
        }while (!bestwishes.empty()){
            bestwishes.pop();
        }
        numelem = 0;
        for (int i=0;i<R;i++){
            scanf("%d%d",&a,&b);
            a--, b--;
            adjList[a].push_back(b);
            adjList[b].push_back(a);
        }
        if (solve(0))printf("Y\n");
        else printf("N\n");
    }
}
