#include <cstdio>
#include <algorithm>


const int MAXN = 2023;
const int MAXX = 11;

int dp[MAXN][MAXX];
int eggThrow[MAXN][MAXX];


int f(int n, int x) {
	if (x == 1 || n == 0) return n;
	if (dp[n][x] != -1)
		return dp[n][x];
	int best = n;
	for (int i = 1; i <= n; ++i) {
		int result = 1 + std::max(f(i - 1, x - 1), f(n - i, x));
		if (result < best) {
			best = result;
			eggThrow[n][x] = i;
		}
	}
	return dp[n][x] = best;
}

int main()
{
	memset(dp, -1, sizeof(dp));
	f(2022, 10);
	printf("Best for 100: %d, %d\nBest for 2022: %d, %d", dp[100][2], eggThrow[100][2], dp[2022][10], eggThrow[2022][10]);
}
