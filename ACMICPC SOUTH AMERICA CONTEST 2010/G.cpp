#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXM 10009
#define MOD 1000000007
#define EPS 1e-7
#define FOR(x, n) for (int x = 0; x < n; x++)
#define FORN(x, i, n) for (int x = i; x < n; x++)
#define FOR1e(x, n) for (int x = 1; x <= n; x++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int trie[MAXN][26] = {}, link[MAXN] = {};
int a[MAXN] = {}, b[MAXM] = {};
int cnt = 1;

void add(int idx, string &s)
{
    int tam = s.size();
    int no = 0;
    for (int i = 0; i < tam; ++i)
    {
        int c = s[i] - 'a';
        if (!trie[no][c])
            trie[no][c] = cnt++;
        no = trie[no][c];
    }
    a[no] = idx;
}

int aho()
{
    queue<int> q;
    q.push(0);

    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        a[x] = max(a[x], a[link[x]]);

        for (int i = 0; i < 26; ++i)
        {
            if (trie[x][i])
            {
                int y = trie[x][i];
                q.push(y);
                link[y] = x ? trie[link[x]][i] : 0;
            }
            else
            {
                trie[x][i] = trie[link[x]][i];
            }
        }
    }
}

int solve(string &s)
{
    int ans = 0;
    int no = 0;

    for (char c : s)
    {
        no = trie[no][c - 'a'];
        ans = max(ans, max(b[a[no]], b[a[link[no]]]));
    }

    return ans + 1;
}

string str[MAXM];

bool sorte(string s1, string s2)
{
    return s1.size() < s2.size();
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;

    while (cin >> N && N)
    {
        cnt = 1;

        FOR(i, N)
        {
            cin >> str[i];
            b[i + 1] = 0;
        }
        sort(str, str + N, sorte);
        FOR(i, N)
        add(i + 1, str[i]);
        aho();

        int ans = 1;
        b[1] = 1;
        FORN(i, 1, N)
        {
            ans = max(ans, b[i + 1] = solve(str[i]));
        }
        cout << ans << '\n';
        FOR(i, cnt)
        {
            a[i] = link[i] = 0;
            FOR(j, 26)
            trie[i][j] = 0;
        }
    }
}