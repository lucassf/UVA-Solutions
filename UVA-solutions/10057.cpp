#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int lld;

lld qtt[66000] = {}, dist[66000], cdist[66000], wmin;

int main() {
	int n,u,idx,ncont,cont,smin = 0,smax = -1,a;
	while (scanf("%d", &n)!=EOF) {
		for (int i = smin; i <= smax; i++)qtt[i] = 0;
		smin = 66000, smax = -1;
		for (int i = 0; i < n; i++)scanf("%lld", &a), qtt[a]++, smin = min(a, smin), smax = max(a, smax);
		u = 0, dist[smin] = 0, u = qtt[smin];
		for (int i = smin+1; i <= smax; i++) {
			dist[i] = dist[i - 1] + u;
			u += qtt[i];
		}cdist[smax+1] = 0, u = 0, wmin = dist[smax]+1;
		for (int i = smax; i >= smin; i--) {
			cdist[i] = cdist[i + 1] + u;
			dist[i] += cdist[i];
			if (wmin > dist[i])wmin = dist[i],idx=i;
			u += qtt[i];
		}ncont = cont = 0;
		while (idx >= smin&&dist[idx] == wmin)ncont += qtt[idx--], cont++;
		printf("%d %d %d\n",idx+1,ncont,cont);
	}
}
