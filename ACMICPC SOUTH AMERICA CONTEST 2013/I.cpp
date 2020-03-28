#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long int ll;
#define INF 1e9
#define MAXN 59

int N;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll qtt[MAXN], a, u, prev;
    vector<ll> vals[MAXN];

    while (cin >> N)
    {
        memset(qtt, 0, sizeof qtt);

        u = 0;
        for (int i = 0; i < MAXN; i++)
            vals[i].clear();
        for (int i = 0; i < N; i++)
        {
            cin >> a;
            qtt[a]++;
            vals[a].push_back(1);
            u = max(u, a);
        }

        ll ans = 0;
        prev = 1;

        while (u > 0)
        {
            ans += qtt[u] * prev;
            prev = vals[u][vals[u].size() - 1];

            for (int i = 0; i < vals[u - 1].size(); i++)
            {
                vals[u - 1][i] = prev;
            }
            for (int i = 0; i < vals[u].size(); i += 2)
            {
                vals[u - 1].push_back(vals[u][i] + vals[u][i + 1]);
            }

            u--;
        }
        cout << ans << endl;
    }
}
