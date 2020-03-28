#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define INF 1000000007
typedef long long int ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, S, C, ans, pos, c;
    while (cin >> N >> C >> S)
    {
        ans = 0, pos = 0, S--;
        for (int i = 0; i < C; i++)
        {
            cin >> c;
            if (pos == S)
                ans++;
            pos = (pos + c + N) % N;
        }
        if (pos == S)
            ans++;
        cout << ans << endl;
    }
}
