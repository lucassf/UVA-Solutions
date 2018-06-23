#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define MAXN 1009

ii qtt[MAXN];
int n,k;

bool isPossible(){
    int q = qtt[1].first;
    for (int i = 2;i <= k; i++){
        if (q != qtt[i].first)return false;
    }
    return true;
}

int main(){
    int a;
    cin>>k>>n;

    for (int i = 1; i <= k; i++)qtt[i] = ii(0, i);

    for (int i = 0; i < n; i++){
        cin>>a;
        qtt[a] = ii(qtt[a].first+1, a);
    }

    sort(qtt + 1,qtt + k + 1);

    qtt[1] = ii(qtt[1].first+1, qtt[1].second);
    if (isPossible()){
        cout<<"+"<<qtt[1].second<<endl;
        return 0;
    }

    qtt[k] = ii(qtt[k].first-1, qtt[k].second);
    if (isPossible()){
        cout<<"-"<<qtt[k].second<<" +"<<qtt[1].second<<endl;
        return 0;
    }

    qtt[1] = ii(qtt[1].first-1, qtt[1].second);
    if (isPossible()){
        cout<<"-"<<qtt[k].second<<endl;
        return 0;
    }
    cout<<"*"<<endl;
    return 0;
}
