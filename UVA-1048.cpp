#include <cstdio>
#include <algorithm>

int main() {
	int n=0, a[10000],c1,c2;
	while (scanf("%d", &a[n++]) != EOF) {
		std::nth_element(a, a+n / 2, a + n);
		if (n % 2 == 0) {
			std::nth_element(a, a + n / 2-1, a + n);
			printf("%d\n", (a[n / 2 - 1] + a[n / 2]) / 2);
		}
		else printf("%d\n", a[n / 2]);
	}
}
