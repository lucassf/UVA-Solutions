#include <bits/stdc++.h>
using namespace std;
#define INF 4000

int time1[109];

bool sorte(int a,int b){
    return time1[a]<time1[b];
}

int main(){
    vector<int> teams[11];
    int N,P,fails,solved,failed[109];
    char t[10];

    while (scanf("%d%d",&N,&P)&&N!=0){
        for (int i=0;i<=P;i++)teams[i].clear();
        for (int i=0;i<N;i++){
            solved = time1[i] = 0;
            failed[i] = 0;

            for (int j=0;j<P;j++){
                scanf("%d/%s",&fails,&t);
                if (t[0]!='-'){
                    solved++;
                    failed[i]+=fails-1;
                    time1[i]+=atoi(t);
                    //cout<<time[i]<<endl;
                }
            }
            time1[i]+=20*failed[i];
            teams[solved].push_back(i);
        }
        int wmin,wmax;
        wmin = 1, wmax = INF;

        for (int i=0;i<=P;i++){
            if (teams[i].empty())continue;
            sort(teams[i].begin(),teams[i].end(),sorte);
            for (int j=1;j<(int)teams[i].size();j++){
                int u = teams[i][j-1];
                int v = teams[i][j];
                if (failed[u]==failed[v])continue;
                if (time1[u]==time1[v]){
                    wmin = wmax = 20;
                }else{
                    while (time1[u]-time1[v]>=(failed[v]-failed[u])*(wmin-20))wmin++;
                    while (time1[u]-time1[v]>=(failed[v]-failed[u])*(wmax-20))wmax--;
                }
            }
        }

        printf("%d",wmin);
        if (wmax==INF)printf(" *\n");
        else printf(" %d\n",wmax);
    }
}
