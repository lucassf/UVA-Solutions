#include <bits/stdc++.h>
using namespace std;
#define MAXN 10

int main(){
    int p,s,t1,t2,t3,n,cur,d1,d2,win;
    int pos[MAXN],skip[MAXN];

    while (scanf("%d%d",&p,&s)&&p!=0){
        for (int i=0;i<p;i++)pos[i] = 0,skip[i] = 0;
        scanf("%d%d%d%d",&t1,&t2,&t3,&n);
        cur = 0, win = -1;

        for (int i=0;i<n;i++){
            while (skip[cur]){
                skip[cur] = 0;
                cur = (cur+1)%p;
            }
            scanf("%d%d",&d1,&d2);
            pos[cur]+=d1+d2;

            if (pos[cur]>s&&win<0)win=cur+1;
            if (pos[cur]==t1||pos[cur]==t2||pos[cur]==t3)skip[cur] = 1;

            cur = (cur+1)%p;
        }
        printf("%d\n",win);
    }
}
