#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long int ll;
#define INF 1e9
#define MAXN 10009

int C, P;
vector<int> adjList[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b, prev[MAXN];

    while (cin >> C >> P)
    {

        for (int i = 1; i <= C; i++)
        {
            prev[i] = i;
            adjList[i].clear();
        }
        for (int i = 0; i < P; i++)
        {
            cin >> a >> b;
            if (a > b)
                swap(a, b);
            adjList[b].push_back(a);
        }

        int ans = C * (C - 1) / 2;

        for (int i = 3; i <= C; i++)
        {

            int u = i;
            for (int j = 0; j < (int)adjList[i].size(); j++)
            {
                int v = prev[adjList[i][j]];
                if (j == 0)
                    u = v;
                else if (u != v)
                    u = 1;
            }
            prev[i] = u == 1 ? i : u;
        }

        sort(prev + 1, prev + C + 1);

        for (int i = 1; i <= C;)
        {
            while (i <= C && prev[i] == 1)
                i++;
            int u = i;
            while (i <= C && prev[u] == prev[i])
                i++;

            u = i - u;
            ans -= u * (u - 1) / 2;
        }
        cout << ans << endl;
    }
}
