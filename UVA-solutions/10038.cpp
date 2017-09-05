#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,x,y,val;
    vector<bool> used;
    bool poss;
    while (cin>>n){
        used.assign(n,false);
        cin>>y;
        poss = true;
        for (int i=1;i<n;i++){
            cin>>x;
            val = abs(x-y);
            if (val>=n||used[val])poss=false;
            else used[val]=true;
            y = x;
        }
        if (poss)cout<<"Jolly"<<endl;
        else cout<<"Not jolly"<<endl;
    }
}
