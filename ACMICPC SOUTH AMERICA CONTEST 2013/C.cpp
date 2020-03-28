#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef unsigned long long int ull;
#define INF 1e9
#define MAXN 100009
#define MAXM 100009

inline ull getVal(ull a)
{
    ull prev, ans = 0;
    ull one = 1;
    ull n = one << 63, b = 63;

    while (a > 0)
    {
        while (n > a)
            n >>= 1, b--;
        if (n > 0)
            ans += (n >> 1) * b;
        a -= n;
        ans += a + 1;
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ull A, B;
    while (cin >> A >> B)
    {
        cout << getVal(B) - getVal(A - 1) << endl;
    }
}
