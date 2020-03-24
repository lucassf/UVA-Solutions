#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

#define MAXN 2009
#define MAXM 501
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)

struct wall {
	int x1, y1, x2, y2, h;
} walls[MAXN];

int g[MAXN][MAXN][4], vis[MAXN][MAXN];
int N;
int dirx[4] = { 1, 0, -1, 0 };
int diry[4] = { 0, 1, 0, -1 };

void addWall(int x1, int x2, int y1, int y2) {
	if (x1 == x2) {
		FORN(i, y1, y2) {
			g[x1 - 1][i][0] = 0;
			g[x1][i][2] = 0;
		}
	}
	else {
		FORN(i, x1, x2) {
			g[i][y1 - 1][1] = 0;
			g[i][y1][3] = 0;
		}
	}
}

int getArea(int xmin, int xmax, int ymin, int ymax) {
	int cov = 0, x, y;
	queue<pair<int, int> > inuse;
	inuse.push({ xmin, ymin });

	vis[xmin][ymin] = 1;

	while (!inuse.empty()) {
		auto p = inuse.front();
		inuse.pop();

		x = p.first, y = p.second;
		cov++;

		FOR(k, 4) {
			int nxtx = x + dirx[k], nxty = y + diry[k];

			if (nxtx >= xmin && nxtx <= xmax && nxty >= ymin && nxty <= ymax &&
				!vis[nxtx][nxty] && g[x][y][k]) {
				vis[nxtx][nxty] = 1;
				inuse.push({ nxtx, nxty });
			}
		}
	}

	return (xmax - xmin + 1) * (ymax - ymin + 1) - cov;
}

int main() {
	int x1, x2, y1, y2, h, xmin, xmax, ymin, ymax;

	FOR(i, MAXN) FOR(j, MAXN) FOR(k, 4) g[i][j][k] = 1;

	while (scanf("%d", &N), N) {
		xmin = ymin = INF;
		xmax = ymax = 0;

		FOR(i, N) {
			scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
			if (x1 > x2) swap(x1, x2);
			if (y1 > y2) swap(y1, y2);
			walls[i] = { x1 + MAXM, y1 + MAXM, x2 + MAXM, y2 + MAXM, h };
			xmin = min(xmin, x1 + MAXM - 1);
			ymin = min(ymin, y1 + MAXM - 1);
			xmax = max(xmax, x2 + MAXM + 1);
			ymax = max(ymax, y2 + MAXM + 1);
		}
		scanf("%d", &h);
		FOR(i, N) {
			if (walls[i].h >= h)
				addWall(walls[i].x1, walls[i].x2, walls[i].y1, walls[i].y2);
		}
		printf("%d\n", getArea(xmin, xmax, ymin, ymax));
		FORN(i, xmin, xmax + 1) FORN(j, ymin, ymax + 1) FOR(k, 4) {
			g[i][j][k] = 1;
			vis[i][j] = 0;
		}
	}
}