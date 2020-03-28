#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define INF 1000000007
typedef long long int ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, c, d;
    while (cin >> a >> b >> c >> d)
    {
        int w = min(abs(a + b - c - d), min(abs(a + c - b - d), abs(a + d - b - c)));
        cout << w << endl;
    }
}
