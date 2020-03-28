#include <bits/stdc++.h>
using namespace std;

int K, W, nxt[3], QTT;
map<int, set<int>> adjList;
map<int, int> vis;
set<int>::iterator it;

bool dfs(int idx, int qtt)
{
    QTT = 0;
    int u = idx, par = -1;
    while (true)
    {
        QTT++;
        vis[u] = 1;
        for (it = adjList[u].begin(); it != adjList[u].end(); it++)
        {
            if (*it != par)
                break;
        }
        if (it == adjList[u].end())
            return true;
        par = u;
        u = *it;
        if (u == idx)
            break;
    }
    return QTT == K;
}

int main()
{
    int a, b;
    bool poss;
    while (scanf("%d%d", &K, &W), K)
    {
        adjList.clear();
        poss = true;
        for (int i = 0; i < W; i++)
        {
            scanf("%d%d", &a, &b);
            //a = i, b = i+1;
            adjList[a].insert(b);
            adjList[b].insert(a);
            if (adjList[a].size() > 2)
                poss = false;
            if (adjList[b].size() > 2)
                poss = false;
        }

        if (poss)
        {
            vis.clear();

            for (map<int, set<int>>::iterator it = adjList.begin(); it != adjList.end(); it++)
            {
                int u = (*it).first;
                if (!vis[u] && !dfs(u, 1))
                {
                    poss = false;
                    break;
                }
            }
        }
        if (poss)
            printf("Y\n");
        else
            printf("N\n");
    }
}
