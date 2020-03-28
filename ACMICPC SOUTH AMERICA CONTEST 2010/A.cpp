#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef pair<int, int> ii;
typedef long long int ll;

int par[MAXN], sz[MAXN];
vector<ii> adjList[MAXN];
int root, N, up[MAXN], fson[MAXN];
vector<int> chain[MAXN];
int nchs, nchain[MAXN], id[MAXN], depth[MAXN];
ll val[MAXN];

int sizedfs(int u, int p, ll qtt)
{
    sz[u] = 1;
    fson[u] = -1;
    par[u] = p;
    int msz = 0;
    val[u] = qtt;

    for (int i = 0; i < (int)adjList[u].size(); i++)
    {
        int v = adjList[u][i].first;
        if (v == p)
            continue;
        sz[u] += sizedfs(v, u, qtt + adjList[u][i].second);

        if (sz[v] > msz)
        {
            fson[u] = v;
            msz = sz[v];
        }
    }
    return sz[u];
}

void builddfs(int u, int ch, int h)
{
    nchain[u] = ch;
    id[u] = chain[ch].size();
    chain[ch].push_back(u);
    for (int i = 0; i < (int)adjList[u].size(); i++)
    {
        int v = adjList[u][i].first;
        if (v == par[u])
            continue;
        if (v == fson[u])
            builddfs(v, ch, h + 1);
        else
        {
            up[nchs] = u;
            depth[nchs] = h;
            chain[nchs].clear();
            builddfs(v, nchs++, h + 1);
        }
    }
}

void heavylight(int _root)
{
    root = _root;
    sizedfs(root, -1, 0);
    nchs = 0;
    chain[0].clear();
    up[nchs] = -1;
    depth[nchs] = 0;
    builddfs(root, nchs++, 1);
}

int LCA(int u, int v)
{
    int cu = nchain[u], cv = nchain[v];
    while (cu != cv)
    {
        if (depth[cu] > depth[cv])
            u = up[cu];
        else
            v = up[cv];
        cu = nchain[u];
        cv = nchain[v];
    }
    if (id[u] < id[v])
        return u;
    return v;
}

int main()
{
    int Q, l, a, b, c;
    vector<ll> ans;
    while (scanf("%d", &N) && N != 0)
    {
        for (int i = 0; i < N; i++)
            adjList[i].clear();
        for (int i = 1; i < N; i++)
        {
            scanf("%d%d", &a, &l);
            adjList[a].push_back(ii(i, l));
        }
        heavylight(0);
        scanf("%d", &Q);

        ans.clear();
        while (Q-- > 0)
        {
            scanf("%d%d", &a, &b);
            c = LCA(a, b);
            ans.push_back(val[a] + val[b] - 2 * val[c]);
        }
        printf("%lld", ans[0]);
        for (int i = 1; i < (int)ans.size(); i++)
        {
            printf(" %lld", ans[i]);
        }
        printf("\n");
    }
}
