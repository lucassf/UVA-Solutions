#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int N,K;
string S,ans;
int pd[MAXN][MAXN];

int solve(int idx,int val){
    if (idx==K){
        if (val==0)return 1;
        return 0;
    }
    //cout<<idx<<" "<<val<<endl;
    if (pd[idx][val]!=-1)return pd[idx][val];

    if (S[idx]!='?')return solve(idx+1,(val*10+S[idx]-'0')%N);
    else{
        int i = idx==0?1:0;
        for (;i<=9;i++){
            if (solve(idx+1,(val*10+i)%N)){
                ans[idx] = i+'0';
                return 1;
            }
        }
    }

    return pd[idx][val] = false;
}

int main(){
    cin>>S>>N;
    K = S.size();
    ans = S;
    memset(pd,-1,sizeof(pd));
    if (!solve(0,0))cout<<"*"<<endl;
    else cout<<ans<<endl;
}
