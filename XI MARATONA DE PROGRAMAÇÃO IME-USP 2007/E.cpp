#include <bits/stdc++.h>
using namespace std;

vector<int> adjList[101];
vector<int> pos;

bool dfs(int idx,int color){
    pos[idx]=color;
    int u,next_color = color==1?2:1;

    for (int i=0;i<(int)adjList[idx].size();i++){
        u = adjList[idx][i];
        if (pos[u]!=0){
            if (pos[u]!=next_color)return false;
        }
        else if (!dfs(u,next_color))return false;
    }
    return true;
}

int main(){
    int n,m,u,v,c=1;
    bool sol;

    while (cin>>n>>m){
        sol = true;
        for (int i=0;i<n;i++)adjList[i].clear();
        for (int i=0;i<m;i++){
            cin>>u>>v;
            u--,v--;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }
        pos.assign(n,0);
        for (int i=0;i<n;i++){
            if (!pos[i]&&!dfs(i,1)){
                sol = false;
                break;
            }
        }//for (int i=0;i<n;i++)cout<<pos[i]<<" ";
        //cout<<endl;
        cout<<"Instancia "<<c++;
        if (sol)cout<<"\nsim\n\n";
        else cout<<"\nnao\n\n";
    }
}
