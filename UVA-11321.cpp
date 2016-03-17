#include <algorithm>
#include <cstdio>

int m;

bool sor(int a, int b) {
	if (a%m != b%m)return a%m < b%m;
	if (abs(a) % 2 != abs(b) % 2)return abs(a) % 2 > abs(b) % 2;
	if (abs(a) % 2 == 1)return a > b;
	return a < b;
}

int main() {
	int n,a[10000];
	while (scanf("%d%d", &n, &m) && n != 0) {
		for (int i = 0; i < n; i++)scanf("%d",&a[i]);
		std::sort(a, a + n, sor);
		printf("%d %d\n",n,m);
		for (int i = 0; i < n; i++)printf("%d\n",a[i]);
	}printf("0 0\n");
}
