#include <cstdio>

int main() {
	int x, r, c, n, m, freq[27] = {},g,qtt;
	char grid[20][21];
	scanf("%d",&x);
	for (int k = 1; k <= x; k++) {
		scanf("%d%d%d%d",&r,&c,&m,&n);
		for (int i = 0; i < r; i++) {
			scanf("%s",&grid[i]);
			for (int j = 0; j < c; j++)freq[grid[i][j]-'A']++;
		}g = qtt = 0;
		for (int i = 0; i < 27; i++) {
			if (freq[i] > g)g = freq[i], qtt = 1;
			else if (freq[i] == g)qtt++;
			freq[i] = 0;
		}qtt*=g;
		printf("Case %d: %d\n",k,qtt*m+(r*c-qtt)*n);
	}
}
