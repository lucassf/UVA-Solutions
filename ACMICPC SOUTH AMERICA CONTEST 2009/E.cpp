#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 1000000009

inline ll getC(ll cost)
{
    if (cost <= 200)
        return cost / 2;
    if (cost <= 29900)
        return (cost + 100) / 3;
    if (cost <= 4979900)
        return (cost + 20100) / 5;
    return (cost + 2020100) / 7;
}

inline ll getCost(ll c)
{
    if (c <= 100)
        return 2 * c;
    if (c <= 10000)
        return 3 * c - 100;
    if (c <= 1000000)
        return 5 * c - 20100;
    return 7 * c - 2020100;
}

int main()
{
    int A, B;
    while (scanf("%d%d", &A, &B) && A != 0)
    {
        ll c = getC(A);
        ll l = 0, r = c;
        while (l < r)
        {
            ll mid = (l + r) >> 1;
            if (getCost(c - mid) - getCost(mid) > B)
                l = mid + 1;
            else
                r = mid;
        }
        printf("%lld\n", getCost(l));
    }
}
