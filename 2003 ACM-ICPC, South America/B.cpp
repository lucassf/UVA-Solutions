#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 1000000000
typedef pair<int,int> ii;

ii mines[MAXN];

int main(){
    int x1,y1,x2,y2,N,x,y,dx,dy,A,B,a,b,wmin,wmax,k;
    bool limi;

    while (scanf("%d%d%d%d",&x1,&y1,&x2,&y2)&&(x1!=0||x2!=0||y1!=0||y2!=0)){
        scanf("%d",&N);

        mines[0] = ii(x1,y1);
        for (int i=1;i<=N;i++){
            scanf("%d%d",&x,&y);
            mines[i] = ii(x1,y);
            mines[N+i] = ii(x,y);
        }
        mines[2*N+1] = ii(x2,y2);
        sort(mines,mines+2*N+1);
        A = B = 0;

        for (int i=0;i<=2*N;i++){
            wmin = y2;
            wmax = y1;
            x = mines[i].first, y = mines[i].second;
            limi = false;

            //printf("%d %d: ",x,y);

            for (int j=i+1;j<=2*N+1;j++){
                if (x==mines[j].first)continue;
                dx = mines[j].first-x;
                if (limi)dy = max(wmin-y,y-wmax);
                else dy = wmin-wmax;
                a = min(dx,dy), b = max(dx,dy);

                if (A<a||(A==a&&B<b))A = a, B = b;

                if (mines[j].second<y)wmax = max(wmax,mines[j].second);
                else if (mines[j].second>y)wmin = min(wmin,mines[j].second);
                else limi = true;
            }
            //printf("%d %d\n",A,B);
        }
        printf("%d %d\n",A,B);
    }
}
