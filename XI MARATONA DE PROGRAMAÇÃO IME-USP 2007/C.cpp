#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

string s;

ll lpow(int a){
    if (a==0)return 1;
    ll aux = lpow(a/2);
    if (a%2==0)return aux*aux;
    return aux*aux*2;
}

int main(){
    int c=1,n;
    ll ans;
    while (cin>>s){
        ans = 0;
        n = s.size();
        for (int i=0;i<n;i++){
            if (s[i]=='b')ans+=lpow(n-i-1);
        }
        cout<<"Palavra "<<c++<<"\n";
        cout<<ans<<"\n\n";
    }
}
