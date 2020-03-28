#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
#define MAXN 100000

ii arr[MAXN];

int main()
{
    int N, h, m, s, rem, cur, ans;
    char c;

    while (scanf("%d", &N) && N != 0)
    {
        rem = N / 2;
        for (int i = 0; i < N; i++)
        {
            scanf("%d:%d:%d %c", &h, &m, &s, &c);
            if (c == 'E')
                rem--;
            arr[i] = ii(h * 3600 + m * 60 + s, c == '?' ? 0 : (c == 'E' ? 1 : -1));
        }
        sort(arr, arr + N);
        ans = cur = 0;
        for (int i = 0; i < N; i++)
        {
            if (arr[i].second != 0)
                cur += arr[i].second;
            else
            {
                if (rem > 0)
                    cur++, rem--;
                else
                    cur--;
            }
            ans = max(ans, cur);
        }
        printf("%d\n", ans);
    }
}
