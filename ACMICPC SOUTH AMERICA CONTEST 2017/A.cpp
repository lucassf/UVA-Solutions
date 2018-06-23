#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> ii;

#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define MAXN 14
#define INF 1e12
#define EPS 1e-9
#define PMOD(a) (a % INF + INF) % INF

int N, K;
double H, D[MAXN][MAXN], Lmax[MAXN], Lmin[MAXN];
double dp[1<<MAXN][MAXN];

struct point{
	double x, y;
	point operator -(const point& other) const{
		return point{x - other.x, y - other.y};
	}
	point operator +(const point& other) const{
		return point{x + other.x, y + other.y};
	}
};

typedef vector<point> polygon;
polygon P[MAXN];

inline double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

inline double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

inline bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

inline bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

inline bool segIntersects(point a, point b, point p, point q) {
    point u = b-a, v = q-p;
    if (fabs(cross(v, u)) < EPS)
		return between(a, p, b) || between(a, q, b);
    double k1 = (cross(a, v) - cross(p, v)) / cross(v, u);
    double k2 = (cross(a, u) - cross(p, u)) / cross(v, u);
    return k1 >= 0 && k1 <= 1 && k2 >= 0 && k2 <= 1;
}

inline bool intersects(polygon &p1, polygon &p2){
	int j = p2.size() - 1, i = 0;
	while (true){
		if (segIntersects(p1[i], p1[i + 1], p2[j], p2[j - 1])) return true;
		if (p1[i + 1].y > p2[j - 1].y) --j;
		else ++i;
		if (abs(p1[i].y - H) < EPS || abs(p2[j].y - H) < EPS) break;
	}
	return false;
}

inline double GetDist(polygon &p1, polygon &p2, double qd){
	double l = 0, r = qd;
	while (r - l > 1e-6){
		
		double mid = (r + l) / 2;
		for(point &p: p2) p.x += mid;
		if (intersects(p1, p2)) l = mid;
		else r = mid;
		for(point &p: p2) p.x -= mid;
	}
	return l;
}

int main(){
	scanf("%d", &N);
	int x, y, xmin, xmax;;
	
	FOR(i, N){
		scanf("%d", &K);
		xmax = -1000000000, xmin = 1000000000;
		FOR(j, K){
			scanf("%d%d", &x, &y);
			P[i].push_back(point{x, y});
			xmax = max(xmax, x), xmin = min(xmin, x);
		}
		P[i].push_back(P[i][0]);
		Lmax[i] = xmax, Lmin[i] = -xmin;
	}H = -1;
	for (auto it : P[0]) H = max(H, it.y);
	FOR(i, N)FOR(j, N){if (i == j) continue; D[i][j] = GetDist(P[i], P[j], Lmax[i] + Lmin[j]);}
	
	double best = INF;
	int M = (1 << N), p, j, u, k, rem;
	
	FOR(i, M) FOR(j, N) dp[i][j] = INF;
	FOR(i, N) dp[1 << i][i] = Lmin[i];
	FOR(i, M){
		int u = i;
		while (u){
			j = u & (-u);
			u -= j;
			k = i - j;
			j = log2(j);
			rem = k;
			while (rem){
				p = rem & (-rem);
				rem -= p;
				p = log2(p);
				dp[i][j] = min(dp[i][j], dp[k][p] + D[p][j]);
			}
		}
	}
	FOR(i, N) best = min(best, dp[M - 1][i] + Lmax[i]);
	
	printf("%.3lf\n", best);
}