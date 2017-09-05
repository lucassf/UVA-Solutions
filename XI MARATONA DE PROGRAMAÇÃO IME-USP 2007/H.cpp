#include <bits/stdc++.h>
using namespace std;
#define INF 100000000

int cost[101][100][100];

int main(){
    int n,m,q,u,v,w,c=1;
    while (cin>>n>>m){
        for (u=0;u<n;u++)for (v=0;v<n;v++)cost[0][u][v] = INF;
        for (int i=0;i<n;i++)cost[0][i][i] = 0;
        for (int i=0;i<m;i++){
            cin>>u>>v>>w;
            u--,v--;
            cost[0][u][v] = min(w,cost[0][u][v]);
        }
        for (int i=0;i<n;i++){
            for (u = 0;u<n;u++){
                for (v=0;v<n;v++){
                    cost[i+1][u][v] = min(cost[i][u][v],cost[i][u][i]+cost[i][i][v]);
                    //cout<<cost[i+1][u][v]<<" ";
                }
                //cout<<"\n";
            }//cout<<"\n";
        }
        cin>>q;
        cout<<"Instancia "<<c++<<"\n";
        for (int i=0;i<q;i++){
            cin>>u>>v>>w;
            u--,v--;
            if (cost[w][u][v]==INF)cout<<"-1\n";
            else cout<<cost[w][u][v]<<"\n";
        }
        cout<<"\n";
    }
}
