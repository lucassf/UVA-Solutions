#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> ii;
#define MAXN 1009

ll a[MAXN];

int main()
{
    int N, X, Y;

    ii c[MAXN];

    ll ans;
    int k;

    while (scanf("%d", &N) && N != 0)
    {
        ans = 0;
        for (int i = 0; i < N; i++)
        {
            scanf("%d%d", &X, &Y);
            c[i] = ii(X, Y);
        }
        for (int i = 0; i < N; i++)
        {
            k = 0;
            for (int j = 0; j < N; j++)
            {
                if (i == j)
                    continue;
                ll dx = c[i].first - c[j].first;
                ll dy = c[i].second - c[j].second;
                ll d = dx * dx + dy * dy;
                a[k++] = d;
            }
            sort(a, a + k);
            int cur = 1;
            ll prev = a[0];
            //cout<<a[0]<<" ";
            for (int j = 1; j < k; j++)
            {
                if (a[j] == prev)
                    ans += cur, cur++;
                else
                    cur = 1;
                //cout<<a[j]<<" ";
                prev = a[j];
            }
        }
        printf("%lld\n", ans);
    }
}
