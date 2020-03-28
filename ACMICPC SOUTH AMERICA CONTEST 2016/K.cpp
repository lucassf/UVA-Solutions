#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MAXM 10009
#define INF 1000000007
typedef long long int ll;

int N, a[MAXN], b[MAXN];
int ned, first[MAXN], work[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init()
{
    memset(first, -1, sizeof first);
    ned = 0;
}

void add(int u, int v, int f)
{
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;

    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int dfs(int u, int f, int s, int t)
{
    if (u == t)
        return f;
    int v, df;
    for (int &e = work[u]; e != -1; e = nxt[e])
    {
        v = to[e];
        if (dist[v] == dist[u] + 1 && cap[e] > 0)
        {
            df = dfs(v, min(f, cap[e]), s, t);
            if (df > 0)
            {
                cap[e] -= df;
                cap[e ^ 1] += df;
                return df;
            }
        }
    }
    return 0;
}

bool bfs(int s, int t)
{
    int u, v;
    memset(&dist, -1, sizeof dist);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        for (int e = first[u]; e != -1; e = nxt[e])
        {
            v = to[e];
            if (dist[v] < 0 && cap[e] > 0)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist[t] >= 0;
}

int dinic(int s, int t)
{
    int result = 0, f;
    while (bfs(s, t))
    {
        memcpy(work, first, sizeof work);
        while (f = dfs(s, INF, s, t))
            result += f;
    }
    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int ans;
    while (cin >> N)
    {
        ans = 0;
        for (int i = 1; i <= N; i++)
        {
            cin >> a[i] >> b[i];
        }

        int START = 0, FINISH = 2 * N + 1;

        for (int i = 1; i <= N; i++)
        {
            init();
            int k = 0;
            for (int j = 1; j <= N; j++)
            {
                if (i == j)
                    continue;
                if (a[j] == i || b[j] == i)
                    k++;
                else
                {
                    add(START, j, 1);
                    add(j, a[j] + N, 1);
                    add(j, b[j] + N, 1);
                }
            }
            for (int j = 1; j <= N; j++)
            {
                if (a[i] == j || b[i] == j)
                {
                    add(N + j, FINISH, k - 2);
                }
                else
                {
                    add(N + j, FINISH, k - 1);
                }
            }
            if (k <= 1 || dinic(START, FINISH) != N - k - 1)
                ans++;
        }
        cout << ans << endl;
    }
}
