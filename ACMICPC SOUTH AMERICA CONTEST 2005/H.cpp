#include <bits/stdc++.h>
using namespace std;
#define MAXN 29

int lane[MAXN], pos[MAXN], val[MAXN], ans[MAXN * MAXN];

int main(){
    int N, a, M;
    bool poss;

    while (scanf("%d",&N) && N){
        poss = true;
        memset(lane, 0, sizeof(lane));
        for (int i = 1; i <= N; i++){
            scanf("%d",&a);
            if (lane[a])poss = false;
            lane[a] = i;
            pos[i] = i;
            val[i] = i;
        }
        if (!poss){
            printf("No solution\n");
            continue;
        }
        M = 0;
        for (int i = 1; i <= N; i++){
            a = pos[lane[i]];

            while (a > i){
                val[a] = val[a - 1];
                pos[val[a]]++;
                ans[M++] = a - 1;
                a--;
            }
        }
        printf("%d", M);
        for (int i = 0; i < M; i++)printf(" %d",ans[i]);
        printf("\n");
    }
}

