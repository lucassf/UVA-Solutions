#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef long long int ll;

char str[MAXN];
int n;
int RA[MAXN], tempRA[MAXN];
int SA[MAXN], tempSA[MAXN];
int c[MAXN];

void countingSort(int k)
{
    int i, sum, maxi = max(300, n);
    memset(c, 0, sizeof(c));
    for (i = 0; i < n; i++)
    {
        c[i + k < n ? RA[i + k] : 0]++;
    }
    for (i = sum = 0; i < maxi; i++)
    {
        int t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++)
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++)
        SA[i] = tempSA[i];
}

void constructSA()
{
    int i, k, r;
    for (i = 0; i < n; i++)
        RA[i] = str[i];
    for (i = 0; i < n; i++)
        SA[i] = i;
    for (k = 1; k < n; k <<= 1)
    {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        for (i = 1; i < n; i++)
            tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        for (i = 0; i < n; i++)
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break;
    }
}

int Phi[MAXN];
int LCP[MAXN], PLCP[MAXN];

void computeLCP()
{
    int i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < n; i++)
        Phi[SA[i]] = SA[i - 1];
    for (i = L = 0; i < n; i++)
    {
        if (Phi[i] == -1)
        {
            PLCP[i] = 0;
            continue;
        }
        while (str[i + L] == str[Phi[i] + L])
            L++;
        PLCP[i] = L;
        L = max(L - 1, 0);
    }
    for (i = 0; i < n; i++)
        LCP[i] = PLCP[SA[i]];
}

int main()
{
    ll ans;
    while (scanf("%s", &str) && str[0] != '*')
    {
        strcat(str, "$");
        n = strlen(str);
        constructSA();
        computeLCP();

        int prev = 0;
        ans = 0;
        for (int i = 1; i < n; i++)
        {
            if (LCP[i] > prev)
                ans += LCP[i] - prev;
            prev = LCP[i];
        }
        printf("%lld\n", ans);
    }
}
