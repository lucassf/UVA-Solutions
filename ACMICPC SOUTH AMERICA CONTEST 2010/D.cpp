#include <bits/stdc++.h>
using namespace std;

int pd[12] = {};

int getCount(int N, int dig)
{
    int ans = 0, pot = 1, Nleft = 0, prev = 0;

    while (N > 0)
    {
        int d = N % 10;
        N /= 10;

        ans += d * prev * pot / 10;
        if (d > dig)
            ans += pot;
        else if (d == dig)
            ans += Nleft + 1;

        Nleft += pot * d;
        pot *= 10;
        prev++;
    }
    if (dig == 0)
        ans -= (pot - 1) / 9;
    return ans;
}

int main()
{
    int A, B;
    memset(pd, -1, sizeof(pd));
    while (scanf("%d%d", &A, &B) && A != 0)
    {
        for (int i = 0; i < 9; i++)
        {
            printf("%d ", getCount(B, i) - getCount(A - 1, i));
        }
        printf("%d\n", getCount(B, 9) - getCount(A - 1, 9));
    }
}
