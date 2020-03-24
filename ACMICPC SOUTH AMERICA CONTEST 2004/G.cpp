#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
typedef pair<int,int> ii;

ii player[MAXN];

int main(){
    int N,M,a;
    while (scanf("%d%d",&N,&M)&&N!=0){
        for (int i=0;i<MAXN;i++)player[i] = ii(0,i);
        for (int i=0;i<N;i++){
            for (int j=0;j<M;j++){
                scanf("%d",&a);
                player[a] = ii(player[a].first-1,a);
            }
        }
        sort(player,player+MAXN);
        int score = player[1].first;
        printf("%d ",player[1].second);
        for (int i=2;i<MAXN&&score==player[i].first;i++){
            printf("%d ",player[i].second);
        }
        printf("\n");
    }
}
