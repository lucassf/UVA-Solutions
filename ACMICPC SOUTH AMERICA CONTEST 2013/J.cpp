#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long int ll;
#define INF 1e9
#define MAXN 40009

int N, Q, d[2][MAXN], d1[MAXN], maxdepth, s;
vector<int> adjList[2][MAXN];

void dfs(int idx, int u, int p, int depth)
{
    d1[u] = depth;
    if (depth >= maxdepth)
        s = u, maxdepth = depth;

    for (int i = 0; i < (int)adjList[idx][u].size(); i++)
    {
        int v = adjList[idx][u][i];
        if (v == p)
            continue;
        dfs(idx, v, u, depth + 1);
    }
}

inline int solve(int idx, int n)
{
    maxdepth = 0;
    dfs(idx, 0, -1, 0);

    maxdepth = 0;
    dfs(idx, s, -1, 0);
    for (int i = 0; i < n; i++)
        d[idx][i] = d1[i];

    dfs(idx, s, -1, 0);
    for (int i = 0; i < n; i++)
        d[idx][i] = max(d[idx][i], d1[i]);

    return d[idx][s];
}

ll sum[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    while (cin >> N >> Q)
    {
        for (int i = 0; i < N; i++)
            adjList[0][i].clear();
        for (int i = 0; i < Q; i++)
            adjList[1][i].clear();

        for (int i = 0; i < N - 1; i++)
        {
            cin >> a >> b;
            a--, b--;
            adjList[0][a].push_back(b);
            adjList[0][b].push_back(a);
        }
        for (int i = 0; i < Q - 1; i++)
        {
            cin >> a >> b;
            a--, b--;
            adjList[1][a].push_back(b);
            adjList[1][b].push_back(a);
        }
        int len = max(solve(0, N), solve(1, Q));

        sort(d[1], d[1] + Q);

        ll ans = 0;

        sum[Q] = 0;
        for (int i = Q - 1; i >= 0; i--)
            sum[i] = sum[i + 1] + d[1][i] + 1;

        for (int i = 0; i < N; i++)
        {
            int u = upper_bound(d[1], d[1] + Q, len - d[0][i] - 1) - d[1];
            ans += sum[u] + len * u + d[0][i] * (Q - u);
        }
        printf("%.3lf\n", 1.0 * ans / (N * Q));
    }
}
