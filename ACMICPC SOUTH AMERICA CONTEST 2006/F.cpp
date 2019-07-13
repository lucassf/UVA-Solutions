#define _CRT_SECURE_NO_WARNINGS

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace std;

#define MAXN 40
#define INF 1e9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)

int N;

int main() {
	int a;

	while (scanf("%d", &N), N) {
		int maryodds = 0, johnodds = 0;
		int maryevens = 0, johnevens = 0;
		FOR(i, N) {
			scanf("%d", &a);
			maryodds += (a & 1);
		}
		maryevens = N - maryodds;
		FOR(i, N) {
			scanf("%d", &a);
			johnodds += (a & 1);
		}
		johnevens = N - johnodds;
		
		printf("%d\n", max(0, N - min(johnevens, maryodds) - min(johnodds, maryevens)));
	}
}
