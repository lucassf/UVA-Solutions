#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll dist[2009],dp[2009];
int n,c,N;
ll t1,t2;

ll getSol(int first,ll acum){
    int id = upper_bound(dist,dist+N,acum)-dist;

    if (id-first>=n)return 0;
    if (dp[id]!=-1)return dp[id];

    int aux = min(t1+getSol(first,t1+dist[id]),t2+getSol(first,t2+dist[id]));
    return dp[id] = aux;
}

int main(){
    int ans;
    while (cin>>n>>c>>t1>>t2){
        for (int i=0;i<n;i++){
            cin>>dist[i];
        }N = 2*n;
        ans = c;
        for (int i=n;i<=2*n;i++)dist[i] = dist[i-n]+c;
        for (int i=0;i<n;i++){
            memset(dp,-1,sizeof(dp));
            int aux = getSol(i,dist[i]-1);
            ans = min(ans,aux);
            //cout<<aux<<endl;
        }
        cout<<ans<<endl;
    }
}
