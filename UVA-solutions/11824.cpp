#include <cstdio>
#include <algorithm>

int pow(int a, int n) {
	if (n == 1)return a;
	int u = pow(a, n / 2);
	if (n % 2 == 0)return u*u;
	return u*u*a;
}

bool cmp(int a, int b) {
	return a > b;
}

int main() {
	int t,n,val;
	long long int a[40];
	bool possible;
	for (scanf("%d", &t); t > 0; t--) {
		n = 0, possible = true;
		while (scanf("%lld", &a[n]) && a[n] != 0)n++;
		val = 0;
		std::sort(a, a + n,cmp);
		for (int i = 0; i < n&&possible; i++) {
			val += 2*pow(a[i], i + 1);
			if (val > 5000000)possible = false;
		}if (possible)printf("%d\n",val);
		else printf("Too expensive\n");
	}
}
