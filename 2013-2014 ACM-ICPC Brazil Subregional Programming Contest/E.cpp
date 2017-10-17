#include <bits/stdc++.h>
using namespace std;

int main(){
    int r[10009] = {},p;
    int N,R;
    while (cin>>N>>R){
        for (int i=1;i<=N;i++)r[i] = 0;
        for (int i=0;i<R;i++){
            cin>>p;
            r[p] = 1;
        }
        if (N==R)cout<<"*"<<endl;
        else{
            for (int i=1;i<=N;i++){
                if (r[i])continue;
                cout<<i<<" ";
            }cout<<endl;
        }
    }
}
