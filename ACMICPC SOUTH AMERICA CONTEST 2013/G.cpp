#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long int ll;
#define INF 1000000009
#define MAXN 100009

int h[MAXN], N;
ii H[MAXN];

const int neutral[2] = {0, INF};
int comp(int a, int b, int idx)
{
    return idx == 0 ? max(a, b) : min(a, b);
}

class SegmentTree
{
private:
    vector<int> st;
    int size, idx;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)

    void build(int p, int l, int r, int *A)
    {
        if (l == r)
        {
            st[p] = A[l];
        }
        else
        {
            build(left(p), l, (l + r) / 2, A);
            build(right(p), (l + r) / 2 + 1, r, A);
            st[p] = comp(st[left(p)], st[right(p)], idx);
        }
    }
    int find(int p, int l, int r, int a, int b)
    {
        if (a > r || b < l)
            return neutral[idx];
        if (l >= a && r <= b)
            return st[p];
        int p1 = find(left(p), l, (l + r) / 2, a, b);
        int p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
        return comp(p1, p2, idx);
    }

public:
    void reset(int *begin, int *end, int idx)
    {
        this->idx = idx;
        size = (int)(end - begin);
        st.assign(4 * size, neutral[idx]);
        build(1, 0, size - 1, begin);
    }
    int query(int a, int b)
    {
        return find(1, 0, size - 1, a, b);
    }
};

SegmentTree st2;
int L, R;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int ans[MAXN], idx;

    while (cin >> N)
    {
        for (int i = 0; i < N; i++)
        {
            cin >> h[i];
            H[i] = ii(-h[i], i);
        }
        st2.reset(h, h + N, 1);
        sort(H, H + N);

        idx = 0;
        set<int> ids;
        set<int>::iterator it;

        ids.clear();

        for (int i = 0, j; i < N;)
        {
            if (H[i].second == 0 || H[i].second == N - 1)
            {
                i++;
                continue;
            }

            int a = H[i].first;
            j = i;

            while (j < N && H[j].first == a)
            {
                int v = 0, u = N - 1;
                it = ids.lower_bound(H[j].second);
                if (it != ids.begin())
                {
                    it--;
                    v = *it;
                }
                it = ids.upper_bound(H[j].second);
                if (it != ids.end())
                    u = *it;

                L = st2.query(v, H[j].second);
                R = st2.query(H[j].second, u);
                if (-H[j].first - max(L, R) >= 150000)
                    ans[idx++] = H[j].second + 1;
                j++;
            }
            while (i < j)
                ids.insert(H[i++].second);
        }

        if (idx > 0)
        {
            sort(ans, ans + idx);
            cout << ans[0];
        }
        for (int i = 1; i < idx; i++)
            cout << " " << ans[i];
        cout << "\n";
    }
}
