#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long int lld;

int main() {
	int n,t=1,k;
	lld c, r,p, ans[100000];
	for (scanf("%d", &n); n > 0; n--) {
		scanf("%lld%lld",&c,&r);
		p = c-r;
		k = 0;
		for (lld i = 1; i*i <= p; i++) {
			if (p%i == 0) {
				ans[k++] = i;
				if (i*i != p)ans[k++] = p / i;
			}
		}sort(ans, ans + k);
		printf("Case #%d:", t++);
		if (c == r)printf(" 0");
		for (int i = 0; i < k; i++) {
			if (ans[i] > r)printf(" %lld",ans[i]);
		}
		printf("\n");
	}
}
