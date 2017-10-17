#include <bits/stdc++.h>
using namespace std;

int sum[100009];

int main(){
    int N,a,ans,j,k,goal;
    cin>>N;
    sum[0] = ans = 0;
    for (int i=1;i<=N;i++){
        cin>>a;
        sum[i] = a+sum[i-1];
    }
    j = 1,k = 2;
    goal = sum[N]/3;
    if (sum[N]%3==0){
        for (int i=0;i<N;i++){
            while (k<N&&sum[k]-sum[i]<goal)k++;
            while (j<N&&sum[j]-sum[k]<goal)j++;
            if (j<N&&k<N&&sum[j]-sum[k]==goal&&sum[k]-sum[i]==goal)ans++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
