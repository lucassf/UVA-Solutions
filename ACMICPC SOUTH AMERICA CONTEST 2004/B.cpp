#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <map>
#include <string>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAXN 21
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)

struct point {
	double x, y;
	int player;

	bool operator==(const point& other) {
		return abs(x - other.x) < EPS && abs(y - other.y) < EPS;
	}

	point move(double d, double theta) {
		return { x + d * cos(theta), y + d * sin(theta), player };
	}

	double dist(const point& other) {
		return hypot(x - other.x, y - other.y);
	}
};

char names[2][21];
point placed[10];
int M;

point throwBall(double x, double y, double theta, double d, int player = -1, int placedIndex = -1) {
	point p = { x, y, player };
	double dist = d;
	int index = -1;

	FOR(i, M) {
		if (i == placedIndex) continue;

		double newdist = p.dist(placed[i]);

		if (newdist < dist && p.move(newdist, theta) == placed[i]) {
			index = i;
			dist = newdist;
		}
	}
	p = p.move(dist, theta);

	if (index >= 0) {
		placed[index] = throwBall(p.x, p.y, theta, d - dist, placed[index].player, index);
	}
	return p;
}

double mindist[2];
int thrown[2];

void computeMinDists() {
	mindist[0] = mindist[1] = INF;
	FORN(i, 1, M) {
		int player = placed[i].player;
		mindist[player] = min(mindist[player], placed[0].dist(placed[i]));
	}
}

void printResults() {
	computeMinDists();

	int best = mindist[0] < mindist[1] ? 0 : 1;
	int score = 0;
	FORN(i, 1, 7) {
		score += best == placed[i].player && placed[0].dist(placed[i]) < mindist[best ^ 1];
	}
	printf("%s %d\n", names[best], score);
}

int main() {
	int T, X, Y, D;
	double theta;
	int nextplayer = -1;

	scanf("%d", &T);
	while (T--) {
		scanf("%s%s", names[0], names[1]);
		M = 0;
		thrown[0] = thrown[1] = 0;

		FOR(i, 7) {
			scanf("%d%d%lf%d", &X, &Y, &theta, &D);
			theta = theta * M_PI / 180;

			placed[i] = throwBall(X, Y, theta, D, nextplayer);
			++M;

			computeMinDists();
			if ((mindist[1] > mindist[0] && thrown[1] < 3) || thrown[0] == 3) {
				nextplayer = 1;
			}
			else nextplayer = 0;

			thrown[nextplayer]++;
		}
		printResults();
	}
}