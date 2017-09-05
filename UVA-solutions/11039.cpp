#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;

ii f[500000];

int main() {
	int a,n,p,qtt,cur;
	for (scanf("%d", &p); p > 0;p--) {
		scanf("%d",&n);
		for (int i = 0; i < n; i++) {
			scanf("%d",&a);
			f[i]=ii(abs(a),a<0?0:1);
		}sort(f,f+n);
		qtt = 1, cur = f[0].second;
		for (int i = 1; i < n; i++)if (f[i].second != cur)cur = f[i].second, qtt++;
		printf("%d\n",qtt);
	}
}
