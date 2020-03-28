#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int arr[MAXN];

int gcd(int a, int b)
{
    while (b != 0)
    {
        int aux = a;
        a = b;
        b = aux % b;
    }
    return a;
}

int main()
{
    int T, Q, i, g, s, d;
    bool poss;
    vector<char> ans;

    while (scanf("%d%d", &T, &Q), T)
    {
        for (i = 0; i < T; i++)
        {
            scanf("%d", &arr[i]);
        }
        sort(arr, arr + T);
        if (T > 1)
            g = arr[1] - arr[0];
        for (int i = 2; i < T; i++)
            g = gcd(arr[i] - arr[i - 1], g);
        ans.clear();

        while (Q-- > 0)
        {
            scanf("%d%d", &s, &d);
            poss = false;
            if ((s & 1) == (d & 1))
            {
                if (T == 1)
                {
                    poss = (d + s == 2 * arr[0]);
                }
                else if (((d - s) / 2) % g == 0)
                    poss = true;
                else
                {
                    d = (d + s) / 2;
                    for (int i = 0; i < T; i++)
                    {
                        if (d - arr[i] % g == 0)
                        {
                            poss = true;
                            break;
                        }
                    }
                }
            }
            if (poss)
                ans.push_back('Y');
            else
                ans.push_back('N');
        }
        for (int i = 0; i < ans.size() - 1; i++)
            printf("%c ", ans[i]);
        printf("%c\n", ans[ans.size() - 1]);
    }
}
