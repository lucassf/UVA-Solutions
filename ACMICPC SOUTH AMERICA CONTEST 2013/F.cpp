#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef unsigned long long int ull;
#define INF 1e9
#define MAXN 100009
#define MAXM 100009

int N, G, val[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int S, R, ans;

    while (cin >> N >> G)
    {
        ans = 0;
        for (int i = 0; i < N; i++)
        {
            cin >> S >> R;
            val[i] = R - S;
        }
        int i = 0, qtt2 = 0, qtt = 0, v;
        sort(val, val + N);

        while (i < N && val[i] < 0)
            ans += 3, i++;
        while (i < N && val[i] == 0)
            qtt2++, i++, ans++;
        v = min(G, qtt2) * 2;

        while (i < N && G >= val[i])
        {
            int u = max(0, min(G - val[i] - 1, qtt2)) * 2 + qtt * 3 + (G == val[i] ? 1 : 3);
            v = max(v, u);
            G -= (val[i] + 1);
            i++, qtt++;
            ;
        }
        cout << ans + v << endl;
    }
}
