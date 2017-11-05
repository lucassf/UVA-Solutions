#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define INF 1e9

int N;
string codes[MAXN];
int dp[MAXN][59];

struct value{
    int idx,pos,d;
    value(){}
    value(int i,int p,int d1){idx = i,pos = p,d = d1;}

    bool operator<(value other)const{
        return d>other.d;
    }
};

bool isSuffix(int idx,int pos,int idx2){
    int i,j;
    for (i=pos,j = 0;i<(int)codes[idx].size()&&j<(int)codes[idx2].size();i++,j++){
        if (codes[idx][i]!=codes[idx2][j])return false;
    }
    return true;
}

int solve(){
    priority_queue<value> inuse;
    value aux;
    int pos,idx,d,d1;

    for (int i=0;i<N;i++){
        inuse.push(value(i,0,0));
        dp[i][0] = 0;
    }

    while (!inuse.empty()){
        aux = inuse.top();
        inuse.pop();

        pos = aux.pos, idx = aux.idx, d = aux.d;

        //cout<<pos<<" "<<idx<<" "<<d<<endl;
        if (d>dp[idx][pos])continue;
        if (pos==codes[idx].size())return d;

        int m = (int)codes[idx].size()-pos;
        for (int i=0;i<N;i++){
            if (pos==0 && idx==i)continue;
            if (isSuffix(idx,pos,i)){
                if (m<codes[i].size()){
                    d1 = d+m;
                    if (dp[i][m]>d1)dp[i][m] = d1, inuse.push(value(i,m,d1));
                }
                else {
                    d1 = d+codes[i].size();
                    int v = pos+codes[i].size();
                    if (dp[idx][v]>d1)dp[idx][v] = d1, inuse.push(value(idx,v,d1));
                }
            }
        }
    }
    return INF;
}

int main(){
    int ans;
    while(cin>>N&&N!=0){
        for (int i=0;i<N;i++){
            cin>>codes[i];
            for (int j=0;j<=50;j++)dp[i][j] = INF;
        }
        ans = solve();

        if (ans==INF)cout<<-1<<endl;
        else cout<<ans<<endl;
    }
}
