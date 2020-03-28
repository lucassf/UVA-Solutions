#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF 1000000007
typedef long long int ll;
typedef pair<int, int> ii;

int N, M, A, B, deg[MAXN];
vector<int> adjList[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, y;
    set<ii> vals;
    while (cin >> N >> M >> A >> B)
    {
        memset(deg, 0, sizeof deg);

        for (int i = 0; i < N; i++)
            adjList[i].clear();
        for (int i = 0; i < M; i++)
        {
            cin >> x >> y;
            x--, y--;
            adjList[x].push_back(y);
            adjList[y].push_back(x);
            deg[x]++, deg[y]++;
        }
        for (int i = 0; i < N; i++)
            vals.insert(ii(deg[i], i));
        bool done = false;
        while (!done && !vals.empty())
        {

            int u = vals.begin()->second;
            done = true;

            for (int i = 0; i < 2; i++)
            {
                if (deg[u] < A || deg[u] > N - B - 1)
                {
                    N--;
                    vals.erase(ii(deg[u], u));
                    deg[u] = -1;

                    for (int j = 0; j < (int)adjList[u].size(); j++)
                    {
                        int v = adjList[u][j];
                        if (deg[v] < 0)
                            continue;

                        vals.erase(ii(deg[v], v));
                        deg[v]--;
                        vals.insert(ii(deg[v], v));
                    }
                    done = false;
                }
                if (vals.empty())
                    break;
                u = vals.rbegin()->second;
            }
        }
        cout << N << endl;
    }
    return 0;
}
