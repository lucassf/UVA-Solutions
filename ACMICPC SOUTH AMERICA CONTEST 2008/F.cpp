#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    while (cin>>n && n){
        int ans = 0;
        for (int i = 1; i <= n; i++){
            ans += i*i;
        }
        cout<<ans<<endl;
    }
}
