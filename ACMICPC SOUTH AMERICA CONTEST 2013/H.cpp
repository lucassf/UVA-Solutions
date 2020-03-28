#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> ii;
#define INF 1e9
#define MAXN 10009
#define _USE_MATH_DEFINES

struct point
{
    long long x, y;
    int idx;

    point() {}
    point(ll _x, ll _y)
    {
        x = _x, y = _y;
    }
    point(ll _x, ll _y, ll _idx)
    {
        x = _x, y = _y, idx = _idx;
    }

    point operator-(const point& other) const
    {
        return point(x - other.x, y - other.y, 0);
    }

    bool operator==(const point& other) const
    {
        return x == other.x && y == other.y;
    }
};

point kids[MAXN], p[3 * MAXN];
pair<point, point> walls[MAXN];
int S, K, W;
point pivot;

inline double polarAngle(ll x, ll y)
{
    double a = atan2(y, x);
    return a < 0 ? a + 2 * M_PI : a;
}

inline ll cross(point p1, point p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}

inline bool segIntersects(point a, point b, point p, point q)
{
    point u = b - a, v = q - p;

    double k1 = (cross(a, v) - cross(p, v)) * 1.0 / cross(v, u);
    double k2 = (cross(a, u) - cross(p, u)) * 1.0 / cross(v, u);
    return k1 >= 0 && k1 <= 1 && k2 >= 0 && k2 <= 1;
}

inline bool cmp(point a, point b)
{
    return polarAngle(a.x - pivot.x, a.y - pivot.y) < polarAngle(b.x - pivot.x, b.y - pivot.y);
}

inline bool cmp2(int a, int b)
{
    point u = walls[a].first, v = walls[a].second;
    point p = walls[b].first, q = walls[b].second;

    if (cross(u - pivot, p - pivot) > 0)
        return segIntersects(u, v, pivot, p) > 0;
    return segIntersects(u, pivot, p, q) < 1;
}

bool counted[MAXN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll x, y, xx, yy;

    while (cin >> S >> K >> W)
    {
        for (int i = 1; i <= K; i++)
        {
            cin >> x >> y;
            kids[i] = point(x, y, -i);
        }
        for (int i = 0; i < W; i++)
        {
            cin >> x >> y >> xx >> yy;
            walls[i] = make_pair(point(x, y, i), point(xx, yy, i));
        }

        int ans, N;
        for (int s = 1; s <= S; s++)
        {
            pivot = kids[s];

            N = ans = 0;
            memset(counted, false, sizeof counted);

            for (int i = 1; i <= K; i++)
            {
                if (i == s)
                    continue;
                p[N++] = kids[i];
            }
            for (int i = 0; i < W; i++)
            {
                p[N++] = walls[i].first;
                p[N++] = walls[i].second;
                if (cross(walls[i].first - pivot, walls[i].second - pivot) < 0)
                    swap(walls[i].first, walls[i].second);
            }
            sort(p, p + N, cmp);

            set<int, bool (*)(int, int)> ps(cmp2);
            set<int, bool (*)(int, int)>::iterator it;
            ps.clear();

            memset(counted, 0, sizeof counted);
            for (int i = 0; i < N; i++)
            {
                if (p[i].idx < 0)
                    continue;

                int a = p[i].idx;
                if (walls[a].first == p[i])
                    counted[a] = 1;
                else if (!counted[a])
                    ps.insert(a);
            }

            for (int i = 0; i < N; i++)
            {
                //cout<<p[i].idx<<" "<< (ps.empty() ? -1 : (*ps.begin()))<<endl;
                point u = p[i];

                if (u.idx < 0)
                {
                    if (ps.empty() || !segIntersects(kids[s], u,
                                                     walls[(*ps.begin())].first, walls[(*ps.begin())].second))
                        ans++;
                }
                else
                {
                    if (ps.count(u.idx))
                        ps.erase(u.idx);
                    else
                        ps.insert(u.idx);
                }
            }
            cout << ans << endl;
        }
    }
}
