#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int qtt[2][14];
map<ii,int> dp;

inline int getPos(int idx,int q){
    if (q==1)return 1<<idx;
    return 1<<(idx+14);
}

int solve(int p,int idx,int used){
    if (idx==14)return 0;

    //cout<<used<<endl;
    if (dp.count(ii(idx,used)))return dp[ii(idx,used)];

    int ans = solve(p,idx+1,used);
    int nxt = used,nxt1,nxt2;
    if (qtt[p][idx]>=1){
        nxt=getPos(idx,qtt[p][idx]);
        qtt[p][idx]--;

        //cout<<idx<<": "<<endl;
        for (int i=idx;i<=13;i++){
            if (qtt[p][i]==0)continue;
            //cout<<i<<endl;
            nxt1=getPos(i,qtt[p][i]);
            qtt[p][i]--;
            for (int j=i;j<=13;j++){
                if (qtt[p][j]==0 || j>=i+idx)continue;
                //cout<<j<<endl;
                nxt2=getPos(j,qtt[p][j]);
                qtt[p][j]--;
                ans = max(ans,1+solve(p,idx,nxt|nxt1|nxt2|used));
                qtt[p][j]++;
            }
            qtt[p][i]++;
        }
        qtt[p][idx]++;
    }

    return dp[ii(idx,used)]=ans;
}

int main(){
    int N,x;
    int prem[2];

    while (scanf("%d",&N)&&N!=0){
        memset(qtt,0,sizeof(qtt));
        prem[0]=prem[1]=0;
        for (int i=0;i<N;i++){
            scanf("%d",&x);
            qtt[i%2][x]++;
            if (qtt[i%2][x]==3){
                qtt[i%2][x] = 0;
                prem[i%2]++;
            }
            //cout<<i<<endl;
        }
        if (prem[0]==prem[1]){
            dp.clear();
            prem[0] = solve(0,1,0);
            //cout<<"\n\n";
            dp.clear();
            prem[1] = solve(1,1,0);
        }
        //cout<<prem[0]<<" "<<prem[1]<<endl;
        printf("%d\n",prem[0]==prem[1]?0:(prem[0]>prem[1]?1:2));
    }
}
