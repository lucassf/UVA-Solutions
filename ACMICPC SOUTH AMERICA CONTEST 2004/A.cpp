#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define INF 1e9

int arr[MAXN],pd[MAXN][MAXN];

int main(){
    int N;
    double F;
    while (scanf("%d%lf",&N,&F)&&N!=0){
        for (int i=0;i<N;i++){
            scanf("%d",&arr[i]);
            pd[0][i] = 0;
        }
        int val,ans,acum;
        for (int i=1;i<N;i++){
            for (int j=0;j<N;j++){
                val = 0;
                ans = INF;
                int u = (i+j)%N;
                for (int k=j;;k=(k+1)%N){
                    val+=arr[k];
                    if (k==u)break;
                }
                u = j;
                acum = 0;
                for (int k=0;k<i;k++){
                    acum+=arr[u];
                    ans = min(ans,pd[k][j]+pd[i-k-1][(j+k+1)%N]+max(val-acum,acum));
                    u = (u+1)%N;
                }
                pd[i][j] = ans;
            }
        }
        ans = INF;
        for (int i=0;i<N;i++)ans = min(ans,pd[N-1][i]);
        printf("%.2lf\n",(double)F*ans);
    }
}
