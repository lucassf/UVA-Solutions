#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009
#define INF 1000000007
typedef long long int ll;
typedef pair<int, int> ii;

int P[MAXN], T[MAXN], PF[MAXN], TF[MAXN], N, M;
char str1[MAXN];
int b[MAXN];

class KMP
{
public:
    KMP()
    {
        b[0] = -1;

        for (int i = 0, j = -1; i < M;)
        {
            int u = j - TF[i] < 0 ? -1 : TF[i];
            while (j >= 0 && (u != TF[j]))
            {
                j = b[j];
                u = j - TF[i] < 0 ? -1 : TF[i];
            }
            i++;
            j++;
            b[i] = j;
        }
    }
    int match(int *T)
    {
        int ans = 0;

        for (int i = 0, j = 0; i < N;)
        {
            int u = j - T[i] < 0 ? -1 : T[i];
            while (j >= 0 && u != TF[j])
            {
                j = b[j];
                u = j - T[i] < 0 ? -1 : T[i];
            }
            i++;
            j++;
            if (j == M)
            {
                ans++;
                j = b[j];
            }
        }
        return ans;
    }
};

void setS(int *str, int *num, int n)
{
    int pos[27];

    memset(pos, -1, sizeof pos);

    for (int i = 0; i < n; i++)
    {
        int p = pos[str[i]];

        if (p == -1)
            num[i] = -1;
        else
            num[i] = i - p;
        pos[str[i]] = i;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> str1 >> M)
    {
        N = strlen(str1);
        for (int i = 0; i < N; i++)
        {
            P[i] = str1[i] - 'a';
        }
        for (int i = 0; i < M; i++)
        {
            cin >> T[i];
        }
        setS(P, PF, N);
        setS(T, TF, M);

        KMP kmp;
        cout << kmp.match(PF) << "\n";
    }
}
