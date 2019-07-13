#include <bits/stdc++.h>
using namespace std;
#define MAXN 259
#define INF 1e9

int S,B,x[MAXN],y[MAXN];
int dp[MAXN][MAXN];

int main(){
    int ans;
    while (scanf("%d%d",&S,&B)&&S!=0){
        for (int i=0;i<S;i++){
            scanf("%d",&x[i]);
        }for (int i=0;i<B;i++){
            scanf("%d",&y[i]);
            y[i] = -y[i];
        }
        ans = -INF;
        int v;
        for (int i=0;i<S;i++){
            dp[0][i] = y[0]*(x[i]+x[(i+1)%S]);
            //cout<<dp[0][i]<<" ";
            for (int k=1;k<S;k++){
                v = (i+k)%S;
                dp[0][v] = max(y[0]*(x[v]+x[(v+1)%S]),dp[0][(v+S-1)%S]);
                //cout<<dp[0][v]<<" ";
            }//cout<<endl;
            for (int j=1;j<B;j++){
                for (int k=0;k<S;k++)dp[j][k] = -INF;
                for (int k=j*2;k<S-1;k++){
                    v = (i+k)%S;
                    dp[j][v] = max(y[j]*(x[v]+x[(v+1)%S])+dp[j-1][(v+S-2)%S],dp[j][(v+S-1)%S]);
                    //cout<<dp[j][v]<<" ";
                }
                //cout<<endl;
            }
            ans = max(ans,dp[B-1][(i+S-2)%S]);
            //cout<<endl;
        }
        printf("%d\n",ans);
    }
}
