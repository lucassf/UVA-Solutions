#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 1000000007
#define EPS 1e-9
#define _USE_MATH_DEFINES
typedef long long int ll;
typedef pair<ll, ll> ii;

ii P[MAXN];
map<ii, int> qtt;
ll C[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll ans[MAXN];
    int N;

    for (int n = 0; n < MAXN; n++)
    {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; k++)
        {
            C[n][k] = (C[n - 1][k] + C[n - 1][k - 1]) % INF;
        }
    }

    while (cin >> N)
    {
        qtt.clear();
        for (int i = 0; i < N; i++)
        {
            cin >> P[i].first >> P[i].second;
            qtt[ii(2 * P[i].first, 2 * P[i].second)]++;
            ans[i] = 0;
        }
        ans[N] = 0;
        for (int i = 1; i < N; i++)
        {
            for (int j = 0; j < i; j++)
            {
                qtt[ii(P[i].first + P[j].first, P[i].second + P[j].second)] += 2;
            }
        }
        for (auto it = qtt.begin(); it != qtt.end(); it++)
        {
            int u = it->second;

            int n = u / 2;

            for (int j = 1; j <= n; j++)
            {
                ans[j * 2] += C[n][j];
                ans[j * 2] %= INF;
                if (u % 2)
                {
                    ans[j * 2 + 1] += C[n][j];
                    ans[j * 2 + 1] %= INF;
                }
            }
        }
        cout << N;
        for (int i = 2; i <= N; i++)
            cout << " " << ans[i];
        cout << "\n";
    }
}
