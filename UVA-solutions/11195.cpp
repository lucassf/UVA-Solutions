#include <bits/stdc++.h>
using namespace std;

int canplace[16],n;

int recurse(int col,int row,int updiag,int downdiag){
    if (col==n)return 1;
    int pos = ((1<<n)-1)&(~(row|updiag|downdiag));
    int ans = 0;
    while (pos!=0){
        int bit = pos&-pos;
        pos-=bit;
        if ((canplace[col]&bit)==0)
            ans+=recurse(col+1,row|bit,(updiag|bit)>>1,(downdiag|bit)<<1);
    }
    return ans;
}

int main(){
    char mp[16];
    int t=1;
    while(cin>>n&&n!=0){
        for (int i=0;i<n;i++)canplace[i]=0;
        for (int i=0;i<n;i++){
            cin>>mp;

            for (int j=0;j<n;j++){
                if (mp[j]=='*')canplace[j]+=1<<i;
            }
        }
        cout<<"Case "<<t++<<": "<<recurse(0,0,0,0)<<endl;
    }
}
