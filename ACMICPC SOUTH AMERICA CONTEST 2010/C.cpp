#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

struct point
{
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator<(point other) const
    {
        if (fabs(x - other.x) > EPS)
            return x < other.x;
        else
            return y < other.y;
    }
    bool operator==(point other) const
    {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
    point operator+(point other) const
    {
        return point(x + other.x, y + other.y);
    }
    point operator-(point other) const
    {
        return point(x - other.x, y - other.y);
    }
    point operator*(double k) const
    {
        return point(x * k, y * k);
    }
    double norm()
    {
        return hypot(x, y);
    }
};

struct circle
{
    point c;
    double r;
    circle() {}
    circle(point _c, double _r) { c = _c, r = _r; }
    bool operator==(circle other) const
    {
        return other.c == c && abs(r - other.r) < EPS;
    }
    bool operator<(circle other) const
    {
        if (!(other.c == c))
            return c < other.c;
        return r < other.r;
    }
};

circle circ[1000000];

int getAns(int cnt)
{
    int left = 0, right = 100, mid;
    while (left < right)
    {
        mid = (left + right) / 2;
        if ((mid * (mid - 1) * (mid - 2)) / 6 >= cnt)
            right = mid;
        else
            left = mid + 1;
    }
    return right;
}

int main()
{
    int n, x, y, m, ans, cnt;
    point p[101], p1, p2, v1, v2, c;
    double r, k1;

    while (cin >> n && n != 0)
    {
        m = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> x >> y;
            p[i] = point(x, y);
            for (int j = 0; j < i; j++)
            {
                for (int k = 0; k < j; k++)
                {
                    p1 = (p[i] + p[j]) * 0.5f;
                    p2 = (p[i] + p[k]) * 0.5f;
                    v1 = p[j] - p[i], v2 = p[k] - p[i];
                    v1 = point(v1.y, -v1.x);
                    v2 = point(v2.y, -v2.x);

                    r = v2.y * v1.x - v1.y * v2.x;

                    if (abs(r) < EPS)
                        continue;
                    k1 = ((p1.y - p2.y) * v2.x - v2.y * (p1.x - p2.x)) / r;
                    c = p1 + v1 * k1;
                    r = (p[i] - c).norm();
                    circ[m++] = circle(c, r);
                }
            }
        }
        if (m > 0)
            sort(circ, circ + m);

        ans = 2, cnt = m > 0 ? 1 : 0;
        for (int i = 1; i < m; i++)
        {
            if (circ[i] == circ[i - 1])
                cnt++;
            else
            {
                ans = max(ans, getAns(cnt));
                cnt = 1;
            }
        }
        ans = max(ans, getAns(cnt));
        cout << ans << endl;
    }
}
