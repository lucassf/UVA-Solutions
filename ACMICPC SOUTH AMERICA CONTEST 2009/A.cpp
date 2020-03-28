#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

vector<int> adjList[MAXN];
vector<int> vals[MAXN];
int N, T;

int solve(int u)
{
    int n = adjList[u].size();
    if (n == 0)
        return 1;
    int qtt = ceil((double)(n * T) / 100);
    int ans = 0;

    for (int i = 0; i < (int)adjList[u].size(); i++)
    {
        int v = adjList[u][i];
        vals[u].push_back(solve(v));
    }
    sort(vals[u].begin(), vals[u].end());
    for (int i = 0; i < qtt; i++)
        ans += vals[u][i];
    vals[u].clear();
    return ans;
}

int main()
{
    int a;
    while (scanf("%d%d", &N, &T) && N != 0)
    {
        for (int i = 0; i <= N; i++)
            adjList[i].clear();
        for (int i = 1; i <= N; i++)
        {
            scanf("%d", &a);
            adjList[a].push_back(i);
        }
        printf("%d\n", solve(0));
    }
}
