#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int cnt[MAXN];

int main()
{
    int N, B, a[MAXN];
    while (scanf("%d%d", &N, &B), N)
    {
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < B; i++)
        {
            scanf("%d", &a[i]);
            for (int j = 0; j <= i; j++)
            {
                cnt[abs(a[i] - a[j])] = 1;
            }
        }
        bool poss = true;
        for (int i = 0; i <= N; i++)
        {
            if (!cnt[i])
            {
                poss = false;
                break;
            }
        }
        if (poss)
            printf("Y\n");
        else
            printf("N\n");
    }
}
