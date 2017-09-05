#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector<ll> adjList;
ll allused;
int maxval,nval;
int n;

void compute(int pos,ll used,int qtt){
    //cout<<pos<<" "<<used<<endl;
    if (used==allused){
        maxval = max(maxval,qtt);
        nval++;
        return;
    }for (int i=pos;i<n;i++){
        if (!(used&(1ll<<i)))compute(i+1,used|adjList[i],qtt+1);
    }

}

int main(){
    int m,t,a,b;
    cin>>t;
    while (t>0){
        cin>>n>>m;
        adjList.assign(n,0);
        for (int i=0;i<n;i++)adjList[i]=1ll<<i;
        for (int i=0;i<m;i++){
            cin>>a>>b;
            adjList[a]|=(1ll<<b);
            adjList[b]|=(1ll<<a);
        }maxval = -1;
        nval=0;
        allused = (1ll<<n)-1;
        compute(0,0,0);
        cout<<nval<<endl<<maxval<<endl;
        t--;
    }
}
