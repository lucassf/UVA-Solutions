#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF 1e9

int main()
{
    int N, a, best, wmin, wmax, kx;
    vector<int> arr[MAXN];
    while (scanf("%d", &N) && N != 0)
    {
        wmin = INF, wmax = -INF;
        for (int i = 0; i < N; i++)
        {
            scanf("%d", &kx);
            arr[i].clear();
            for (int j = 0; j < kx; j++)
            {
                scanf("%d", &a);
                wmin = min(wmin, a);
                wmax = max(wmax, a);
                arr[i].push_back(a);
            }
            sort(arr[i].begin(), arr[i].end());
        }
        best = INF;

        for (int t = wmin; t <= wmax; t++)
        {
            int acum = 0;
            for (int i = 0; i < N; i++)
            {
                int u = lower_bound(arr[i].begin(), arr[i].end(), t) - arr[i].begin();
                int k = arr[i].size();
                //cout<<u<<" "<<k<<endl;
                acum += abs(k - 2 * u);
            }
            best = min(acum, best);
        }
        printf("%d\n", best);
    }
}
