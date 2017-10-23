#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009

int n,m,k;
int c[MAXN],sum[MAXN];
int dp[MAXN][MAXN];

bool solve(int pos,int rem){
    int rem2 = m+n-sum[pos-1]-rem;
    //cout<<pos<<" "<<rem<<endl;

    if (rem2<0||rem<0)return false;
    if (pos>k)return true;

    if (dp[pos][rem]!=-1)return dp[pos][rem];
    int best = 0;
    bool poss = false;

    if (solve(pos+1,rem-c[pos]))best = 0,poss=true;
    else if (solve(pos+1,rem))best = 1,poss = true;

    dp[pos][rem] = best;

    return poss;
}

int main(){
    int ans[MAXN],qtt;

    while (scanf("%d%d",&n,&m)!=EOF&&(n!=0||m!=0)){
        scanf("%d",&k);
        sum[0] = 0;

        for (int i=1;i<=k;i++){
            scanf("%d",&c[i]);
            sum[i] = sum[i-1]+c[i];
        }
        memset(dp,-1,sizeof dp);
        if (!solve(1,n)){
            printf("Impossible to distribute\n");
            continue;
        }int rem = n;
        qtt = 0;
        for (int i=1;i<=k;i++){
            if (dp[i][rem]==0)rem-=c[i],ans[qtt++] = i;
        }printf("%d",qtt);
        for (int i=0;i<qtt;i++)printf(" %d",ans[i]);
        printf("\n");
    }
}
