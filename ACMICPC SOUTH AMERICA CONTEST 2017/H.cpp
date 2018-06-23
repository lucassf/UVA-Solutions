#include <bits/stdc++.h>
using namespace std;

int main(){
    int a[3],b[3];
    for (int i=0;i<3;i++)cin>>a[i];
    for (int i=0;i<3;i++)cin>>b[i];
    int ans = 0;
    for (int i=0;i<3;i++){
        if (b[i]>a[i])ans+=b[i]-a[i];
    }
    cout<<ans<<endl;
}
