#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

#define MAXN 2009
#define MAXM 501
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
typedef pair<int, pair<int, int> > iii;

void print(iii a) {
	printf("%d %d %d\n", a.first, a.second.first, a.second.second);
}

struct line {
	int x1, y1, x2, y2;

	bool operator <(const line& other) const {
		if (x1 != other.x1) return x1 < other.x1;
		return y1 < other.y1;
	}

	void print() {
		printf("%d %d %d %d\n", x1, y1, x2, y2);
	}
};

int N, M;
vector<int> g[MAXN];
iii vert[MAXN], hor[MAXN];
line best[MAXN];

void joinLines(iii* arr) {
	sort(arr, arr + N);

	int k = 0;
	FOR(i, N) {
		int fixed = arr[i].first;
		int first = arr[i].second.first;
		int last = arr[i].second.second;

		while (i < N && arr[i + 1].first == fixed &&
			arr[i + 1].second.first == last) {
			last = arr[i + 1].second.second;
			++i;
		}
		arr[k++] = { fixed, {first, last} };
	}
}

int split(int xmin, int ymin, int xmax, int ymax, const iii* arr, int n, iii* res) {
	int v = 0;
	FOR(i, n) {
		auto& val = arr[i];
		int X = val.first, Y1 = val.second.first, Y2 = val.second.second;

		if (X > xmin && X < xmax && Y1 < ymax && Y2 > ymin) {
			res[v++] = { X, {max(Y1, ymin), min(Y2, ymax)} };
		}
	}
	return v;
}

iii vvert[MAXN][MAXN], vhor[MAXN][MAXN];

int recurse(int xmin, int ymin, int xmax, int ymax, const iii* vertpv, int n, const iii* horpv, int m) {
	auto& vert = vvert[M];
	auto& hor = vhor[M];
	int v = split(xmin, ymin, xmax, ymax, vertpv, n, vert);
	int h = split(ymin, xmin, ymax, xmax, horpv, m, hor);

	if (v == 0 && h == 0) return -1;
	int u = M++;

	bool found = false;
	int u1 = -1, u2 = -1;
	FOR(i, h) {
		if (hor[i].second.first == xmin && hor[i].second.second == xmax) {
			found = true;
			best[u] = { xmin, hor[i].first, xmax, hor[i].first };
			u1 = recurse(xmin, ymin, xmax, hor[i].first, vert, v, hor, h);
			u2 = recurse(xmin, hor[i].first, xmax, ymax, vert, v, hor, h);
			break;
		}
	}
	if (!found) {
		FOR(i, v) {
			if (vert[i].second.first == ymin && vert[i].second.second == ymax) {
				found = true;
				best[u] = { vert[i].first, ymin, vert[i].first, ymax };
				u1 = recurse(xmin, ymin, vert[i].first, ymax, vert, v, hor, h);
				u2 = recurse(vert[i].first, ymin, xmax, ymax, vert, v, hor, h);
				break;
			}
		}
	}

	if (u1 >= 0) g[u].push_back(u1);
	if (u2 >= 0) g[u].push_back(u2);

	return u;
}

void dfsPrint(int u) {
	set<pair<line, int> > inuse = { {best[u], u} };

	while (!inuse.empty()) {
		auto cur = *inuse.begin();
		inuse.erase(inuse.begin());

		cur.first.print();
		u = cur.second;

		for (auto v : g[u]) {
			inuse.insert({ best[v], v });
		}
	}
}

int main() {
	int X1, Y1, X2, Y2, xmin, xmax, ymin, ymax;

	while (scanf("%d", &N), N) {
		xmin = ymin = INF;
		xmax = ymax = -INF;

		FOR(i, N) {
			scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
			vert[i] = { X2, {Y1, Y2} };
			hor[i] = { Y2, {X1, X2} };
			xmin = min(xmin, X1);
			xmax = max(xmax, X2);
			ymin = min(ymin, Y1);
			ymax = max(ymax, Y2);
			g[i].clear();
		}
		joinLines(vert);
		joinLines(hor);

		M = 0;
		recurse(xmin, ymin, xmax, ymax, vert, N, hor, N);
		dfsPrint(0);
		printf("\n");
	}
}