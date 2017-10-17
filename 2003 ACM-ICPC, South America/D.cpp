#include <bits/stdc++.h>
using namespace std;

int main(){
    int k,n,m,ages[129],ans;
    double r;
    while (scanf("%d%lf",&k,&r)&&k!=0){
        for (int i=0;i<k;i++){
            scanf("%d%d",&n,&m);
            ages[i] = n;
        }sort(ages,ages+k);
        ans = 0;
        for (int i=0;i<k;i++){
            int wmin = ages[i];
            i++,ans++;
            while (i<k&&floor(r*wmin)>=ages[i])i++;
            i--;
        }printf("%d\n",ans);
    }
}
