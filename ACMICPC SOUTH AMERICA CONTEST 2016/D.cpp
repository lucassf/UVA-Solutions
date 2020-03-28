#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF 1000000007
#define _USE_MATH_DEFINES
typedef long long int ll;

int arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, ans, val[2];
    while (cin >> N)
    {
        for (int i = 0; i < N; i++)
            cin >> arr[i];
        sort(arr, arr + N);
        ans = 0;
        val[0] = val[1] = arr[N - 1];

        for (int i = N - 2; i >= 0; i--)
        {
            int u = i % 2;
            ans += arr[i] * val[u];
            val[u] = arr[i];
        }
        ans += val[0] * val[1];

        printf("%.3lf\n", sin(2 * M_PI / N) * ans / 2);
    }
}
