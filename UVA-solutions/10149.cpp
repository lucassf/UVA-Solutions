#include <bits/stdc++.h>
using namespace std;
#define OK (1<<13)-1
typedef pair<int,int> ii;

int card[5];
int ponct[13][13];
int dp[13][64][OK];
ii nextVal[13][64][OK];

void compute(int index){
    int sum[7]={},duo = 0,trio = 0,four = 0,five = 0;
    for (int i=0;i<5;i++)sum[card[i]]++,ponct[index][i]=0;;
    ponct[index][6]=0;
    for (int i=1;i<=6;i++){
        duo+=(sum[i]==2?1:0);
        trio+=(sum[i]>=3?1:0);
        four+=(sum[i]>=4?1:0);
        five+=(sum[i]==5?1:0);
        ponct[index][i-1]=i*sum[i];
        ponct[index][6]+=card[i-1];
    }
    ponct[index][7] = (trio>0?ponct[index][6]:0);
    ponct[index][8] = (four>0?ponct[index][6]:0);
    ponct[index][9] = (five>0?50:0);
    ponct[index][10] = ((sum[1]&&sum[2]&&sum[3]&&sum[4])||
        (sum[2]&&sum[3]&&sum[4]&&sum[5])||
        (sum[3]&&sum[4]&&sum[5]&&sum[6]))?25:0;
    ponct[index][11] = ((sum[1]&&sum[2]&&sum[3]&&sum[4]&&sum[5])||
        (sum[2]&&sum[3]&&sum[4]&&sum[5]&&sum[6]))?35:0;
    ponct[index][12] = (((trio>0&&duo>0)||five>0)?40:0);
    //for (int i=0;i<13;i++)cout<<ponct[index][i]<<" ";
    //cout<<endl;
}

int recurse(int pos,int sum,int used){
    if (used==OK)return 0;
    if (dp[pos][sum][used]!=-1)return dp[pos][sum][used];
    bool poss = sum<63;
    int bit = OK&(~used),b,ans=-1,aux,index,u;

    while (bit!=0){
        b = bit&(-bit);
        bit-=b;
        index = log2((double)b);
        if (index<=5)u=sum+ponct[pos][index];
        else u =sum;
        aux = ponct[pos][index];
        if (u>=63){
            u =63;
            if (poss)aux+=35;
        }
        aux+=recurse(pos+1,u,used|b);

        if (aux>ans){
            ans=aux;
            nextVal[pos][sum][used]=ii(u,b);
        }
    }
    //cout<<pos<<" "<<sum<<" "<<used<<endl;
    return dp[pos][sum][used] = ans;
}

int main(){
    int x,used,sum,cat[13];
    while (cin>>card[0]){
        for (int i=0;i<13;i++)for (int j=0;j<64;j++)for (int k=0;k<OK;k++){
            dp[i][j][k]=-1;
        }
        for (int i=1;i<5;i++)cin>>card[i];
        compute(0);
        for (int j=1;j<13;j++){
            for (int i=0;i<5;i++)cin>>card[i];
            compute(j);
        }
        int ans = recurse(0,0,0);
        ii pos = ii(0,0);
        used=0;
        for (int i=0;i<13;i++){
            pos = nextVal[i][pos.first][used];
            used|=pos.second;
            sum = log2((double)pos.second);
            cat[sum] = ponct[i][sum];
            //cout<<pos.first<<" "<<pos.second<<endl;
        }for (int i=0;i<13;i++)cout<<cat[i]<<" ";
        cout<<(pos.first>=63?"35 ":"0 ")<<ans<<endl;
    }
}
