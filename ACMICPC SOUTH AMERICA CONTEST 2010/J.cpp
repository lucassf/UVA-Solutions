#include <bits/stdc++.h>
using namespace std;

int b[2][3];
bool cons[3];

bool solve(int idx, int win)
{
    if (idx == 3)
        return win >= 2;

    for (int i = 0; i < 3; i++)
    {
        if (cons[i])
            continue;
        cons[i] = true;
        if (!solve(idx + 1, win + (b[1][idx] > b[0][i] ? 1 : 0)))
            return false;
        cons[i] = false;
    }
    return true;
}

int main()
{
    while (scanf("%d%d%d%d%d", &b[0][0], &b[0][1], &b[0][2], &b[1][0], &b[1][1]), b[0][0])
    {
        int i;
        bool poss;
        for (i = 1; i <= 52; i++)
        {
            poss = true;
            for (int k = 0; k < 3; k++)
                if (b[0][k] == i)
                    poss = false;
            for (int k = 0; k < 2; k++)
                if (b[1][k] == i)
                    poss = false;
            if (!poss)
                continue;
            b[1][2] = i;
            memset(cons, false, sizeof cons);
            if (solve(0, 0))
                break;
        }
        if (i == 53)
            printf("-1\n");
        else
            printf("%d\n", i);
    }
}
