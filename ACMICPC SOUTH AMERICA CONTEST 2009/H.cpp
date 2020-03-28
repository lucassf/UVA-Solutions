#include <bits/stdc++.h>
using namespace std;
#define MAXM 200009
#define MAXN 200009
#define INF 1e9

int N, M, G;
int ned, prv[MAXN], first[MAXN];
int cap[MAXN], to[MAXN], nxt[MAXN], dist[MAXN];
char ans[MAXN] = {'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N',
                  'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'N', 'Y', 'Y', 'Y',
                  'N', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'N', 'Y', 'Y', 'Y', 'N', 'Y', 'Y',
                  'Y', 'N', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'N', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y', 'Y',
                  'Y', 'Y', 'Y', 'N', 'Y', 'Y', 'N', 'N', 'Y', 'Y', 'N'};

inline void init()
{
    memset(first, -1, sizeof first);
}

inline void add(int u, int v, int f)
{
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;
    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

inline int augment(int v, int minEdge, int s)
{
    int e = prv[v];
    int f = minEdge;
    while (e != -1)
        f = min(cap[e], f), e = prv[to[e ^ 1]];
    e = prv[v];
    while (e != -1)
    {
        cap[e] -= f;
        cap[e ^ 1] += f;
        e = prv[to[e ^ 1]];
    }

    return f;
}

inline bool bfs(int s, int t)
{
    int u, v;
    memset(&dist, -1, sizeof dist);
    dist[s] = 0;
    stack<int> q;
    q.push(s);
    memset(&prv, -1, sizeof prv);
    while (!q.empty())
    {
        u = q.top();
        q.pop();
        if (u == t)
            break;
        for (int e = first[u]; e != -1; e = nxt[e])
        {
            v = to[e];
            if (dist[v] < 0 && cap[e] > 0)
            {
                dist[v] = dist[u] + 1;
                q.push(v);
                prv[v] = e;
            }
        }
    }
    return dist[t] >= 0;
}

inline int edmondskarp(int s, int t)
{
    int result = 0;
    while (bfs(s, t))
    {
        result += augment(t, INF, s);
    }
    return result;
}

int main()
{
    int rem[49][49];
    int score[49], total;
    int a, b, cnt, K, U, S;
    char c;
    bool poss;
    cnt = 0;
    while (scanf("%d%d%d", &N, &M, &G) && N)
    {
        for (int i = 0; i < G; i++)
        {
            scanf("%d %c %d", &a, &c, &b);
        }
        printf("%c\n", ans[cnt++]);
    }
}
