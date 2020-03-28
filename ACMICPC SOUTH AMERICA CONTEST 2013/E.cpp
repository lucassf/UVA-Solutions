#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long int ll;
#define INF 1000000007
#define MAXN 109

char str[MAXN];
int N, P, qtt[10], NLIM, K;
ll C[MAXN][MAXN], pd[MAXN][MAXN][MAXN];

ll comb(int n, int k)
{
    if (n == 0 || n == k || k == 0)
        return 1;
    if (C[n][k] != -1)
        return C[n][k];
    return C[n][k] = (comb(n - 1, k) + comb(n - 1, k - 1)) % INF;
}

ll solve(int num, int acum, int n, int k)
{
    if (k < 0 || (n == 0 && acum != P))
        return 0;
    if (num == 10)
    {
        return acum == P && n == 0;
    }
    if (pd[num][n][acum] != -1)
        return pd[num][n][acum];

    ll ans = 0;

    for (int i = 0; i <= qtt[num]; i++)
    {
        if ((num == 0 && i > n - 1) || i > n)
            break;
        if (num == 0)
            ans += comb(n - 1, i) * comb(k, qtt[num] - i) % INF *
                   solve(num + 1, (acum + num * i) % 11, n - i, k - qtt[num] + i) % INF;
        else
            ans += comb(n, i) * comb(k, qtt[num] - i) % INF *
                   solve(num + 1, (acum + num * i) % 11, n - i, k - qtt[num] + i) % INF;
        ans %= INF;
    }
    return pd[num][n][acum] = ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    memset(C, -1, sizeof C);
    while (cin >> str)
    {
        N = strlen(str);
        P = 0;
        n = N % 2 == 0 ? N / 2 : N / 2 + 1;

        memset(qtt, 0, sizeof qtt);

        for (int i = 0; i < N; i++)
        {
            qtt[str[i] - '0']++;
            P = (P + str[i] - '0') % 11;
        }
        if (P % 2 == 0)
            P /= 2;
        else
            P = (P + 11) / 2;
        memset(pd, -1, sizeof pd);
        NLIM = n, K = N - NLIM;
        cout << solve(0, 0, n, N - n) << endl;
    }
}
