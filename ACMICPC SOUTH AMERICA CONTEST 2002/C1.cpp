#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int N,M;
int mp[MAXN][MAXN];
int movx[2] = {0,1};
int movy[2] = {1,0};

int recurse(int x,int y){
    if (y == M)return recurse(x+1,0);
    if (x == N)return 0;

    if (mp[x][y]!=0)return recurse(x,y+1);

    int found = 0;
    int ans = 0;
    for (int j=0;j<2;j++){
        int ux = x + movx[j];
        int uy = y + movy[j];

        if (ux<N && uy<M && mp[ux][uy]==0){
            //cout<<ux<<" "<<uy<<endl;
            mp[ux][uy] = 1;
            ans = max(ans,1+recurse(x,y+1));
            mp[ux][uy] = 0;
            found++;
        }
    }
    if (found==0)ans = recurse(x,y+1);
    return ans;
}

int main(){
    int k,x,y;
    while (scanf("%d%d",&N,&M)&&N!=0){
        scanf("%d",&k);
        memset(mp,0,sizeof(mp));
        for (int i=0;i<k;i++){
            scanf("%d%d",&x,&y);
            x--,y--;
            mp[x][y] = 1;
        }
        printf("%d\n",recurse(0,0));
    }
}
