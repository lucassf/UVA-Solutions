#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int N, R, C, K;
int h[2][MAXN][MAXN];
int movx[4] = {0, 0, 1, -1};
int movy[4] = {1, -1, 0, 0};

int main()
{
    while (scanf("%d%d%d%d", &N, &R, &C, &K) && N != 0)
    {
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                scanf("%d", &h[0][i][j]);
            }
        }
        for (int k = 0; k < K; k++)
        {
            for (int i = 0; i < R; i++)
            {
                for (int j = 0; j < C; j++)
                {
                    int u = h[k % 2][i][j];
                    h[(k + 1) % 2][i][j] = u;
                    for (int p = 0; p < 4; p++)
                    {
                        int vi = movx[p] + i, vj = movy[p] + j;

                        if (vi < 0 || vi >= R || vj < 0 || vj >= C)
                            continue;
                        int v = h[k % 2][vi][vj];

                        if (u == (v + 1) % N)
                        {
                            h[(k + 1) % 2][i][j] = v;
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < R; i++)
        {
            printf("%d", h[K % 2][i][0]);
            for (int j = 1; j < C; j++)
            {
                printf(" %d", h[K % 2][i][j]);
            }
            printf("\n");
        }
    }
}
