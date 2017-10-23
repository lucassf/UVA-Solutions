#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF  1e18

int N,M;
int prods[109];
double price[MAXN];
int id[MAXN];
double dp[2][MAXN];


int main(){
    double val;

    while(scanf("%d%d",&M,&N)&&M!=0){
        for (int i=0;i<M;i++)scanf("%d",&prods[i]);
        for (int i=0;i<N;i++)scanf("%d%lf",&id[i],&price[i]);

        for (int i=0;i<2;i++)for (int j=0;j<=N;j++)dp[i][j] = INF;

        for (int j=N-1;j>=0;j--){
            val = id[j]==prods[M-1]?price[j]:INF;
            dp[(M-1)%2][j] = min(val,dp[(M-1)%2][j+1]);
            //cout<<dp[(M-1)%2][j]<<" ";
        }//cout<<endl;

        for (int i=M-2;i>=0;i--){
            int u = prods[i];
            for (int j=N-1;j>=0;j--){
                val = id[j]==u?price[j]:INF;
                dp[i%2][j] = min(dp[i%2][j+1],val+dp[(i+1)%2][j+1]);
                //cout<<dp[i%2][j]<<" ";
            }
            //cout<<endl;
        }
        if (dp[0][0]>=INF-1)printf("Impossible\n");
        else printf("%.2lf\n",dp[0][0]);
    }
}
