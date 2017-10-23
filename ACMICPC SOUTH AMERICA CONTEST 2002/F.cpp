#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

struct message{
    int t1,t2;
    string a1,a2,a3;
    message(){}
    message(int _t1,int _t2,string _a1,string _a2,string _a3){
        t1 = _t1, t2 = _t2, a1 = _a1, a2 = _a2, a3 = _a3;
    }
} m[MAXN],aux;

int N,M;
vector<int> adjList[21];
set<int> mes[21];
vector<int> vis;

void dfs(int u,int M){
    mes[u].insert(M);
    vis[u] = 1;

    for (int i=0;i<(int)adjList[u].size();i++){
        int v = adjList[u][i];
        if (!vis[v])dfs(v,M);
    }
}

int main(){
    int a,t1,t2;
    string a1,a2,a3;

    while (cin>>N&&N!=0){
        M = 0;
        for (int i=1;i<=N;i++){
            adjList[i].clear();
            mes[i].clear();
            while (cin>>a&&a!=0)adjList[i].push_back(a);
        }while (cin>>a&&a!=0){
            cin>>t1>>t2>>a1>>a2>>a3;
            m[M] = message(t1,t2,a1,a2,a3);
            vis.assign(N+1,0);
            dfs(a,M);
            M++;
        }
        for (int i=1;i<=N;i++){
            cin>>a1;
            cout<<a1<<": ";
            int n;
            for (int j=0;j<M;j++){
                n = mes[i].count(j)?adjList[i].size():0;
                aux = m[j];
                if (n<aux.t1)cout<<aux.a1<<" ";
                else if (n<aux.t2)cout<<aux.a2<<" ";
                else cout<<aux.a3<<" ";
            }
            cout<<endl;
        }
    }
}
