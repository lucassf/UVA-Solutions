#include <bits/stdc++.h>
using namespace std;
#define MAXN 509

int arr[MAXN][MAXN], h[MAXN];

int main()
{
    int N, M, Q, L, R, ans;

    while (scanf("%d%d", &N, &M) && N != 0)
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                scanf("%d", &arr[i][j]);
        scanf("%d", &Q);
        while (Q-- > 0)
        {
            scanf("%d%d", &L, &R);
            int l = M - 1, r = M - 1;
            ans = 0;

            for (int i = 0; i < M; i++)
            {
                h[i] = i == 0 ? N - 1 : h[i - 1];
                while (h[i] >= 0 && arr[h[i]][i] > R)
                    h[i]--;
            }

            for (int i = 0; i < N; i++)
            {
                int prevl = l;
                while (l >= 0 && arr[i][l] >= L)
                    l--;
                while (r >= 0 && arr[i][r] > R)
                    r--;
                if (l == M - 1 || r == -1)
                    continue;
                while (ans <= r - l && ans + 1 <= min(r - l, h[ans + l + 1] - i + 1))
                    ans++;
            }
            printf("%d\n", ans);
        }
        printf("-\n");
    }
}
