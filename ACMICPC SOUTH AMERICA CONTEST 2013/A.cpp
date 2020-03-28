#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long int ll;
#define INF 1e9
#define MAXN 100009
#define MAXM 100009

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
    memset(dist, -1, sizeof dist);
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

    int N, cnt, val[109][109], P;
    char mp[109][109];
    while (cin >> N)
    {
        init();
        cnt = 1;
        add(0, 1, 1);
        P = 100000;

        for (int i = 0; i < N; i++)
        {
            cin >> mp[i];
            for (int j = 0; j < N; j++)
            {
                if (mp[i][j] == 'X')
                {
                    cnt++;
                    add(0, cnt, 1);
                }
                else
                    val[i][j] = cnt;
            }
            cnt++;
            add(0, cnt, 1);
        }
        cnt++;
        add(cnt, P, 1);
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                if (mp[i][j] == 'X')
                {
                    cnt++;
                    add(cnt, P, 1);
                }
                else
                {
                    add(val[i][j], cnt, 1);
                }
            }
            cnt++;
            add(cnt, P, 1);
        }
        cout << dinic(0, P) << endl;
    }
}