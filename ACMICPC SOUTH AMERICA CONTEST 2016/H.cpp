#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF 1000000007
typedef long long int ll;
typedef pair<int, int> ii;

int N, K, P[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int ans;
    priority_queue<int> vals;
    while (cin >> N >> K)
    {
        ans = 0;

        while (!vals.empty())
            vals.pop();

        for (int i = 0; i < N; i++)
        {
            cin >> P[i];
            ans += P[i];
        }
        for (int i = N - 1; i >= K; i--)
        {
            vals.push(P[i]);
            if (i % (K + 1) == K)
            {
                ans -= vals.top();
                vals.pop();
            }
        }
        cout << ans << "\n";
    }
}
