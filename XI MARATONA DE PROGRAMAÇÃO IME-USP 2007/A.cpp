#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,c=1,arr,acum,idx,val;
    while (cin>>n){
        acum = 0,idx = -1;
        for (int i=0;i<n;i++){
            cin>>arr;
            if (arr==acum&&idx==-1)idx = i,val = arr;
            acum+=arr;
        }
        cout<<"Instancia "<<c++<<"\n";
        if (idx==-1)cout<<"nao achei\n\n";
        else cout<<val<<"\n\n";
    }
}
