#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	int t, f, loc[2], coord[2][50000],u,qtt,dist[1005],nextdist[1005],mindist,idx[2];
	dist[0] = 0;
	for (scanf("%d", &t); t > 0; t--) {
		scanf("%d%d%d",&loc[0],&loc[1],&f);
		for (int i = 0; i < f; i++)scanf("%d%d",&coord[0][i],&coord[1][i]);
		for (int i = 0; i < 2; i++) {
			sort(coord[i], coord[i] + f);
			u = 0, mindist = 2000000000;
			for (int j = 1; j <= loc[i]; j++) {
				dist[j] = dist[j-1]+u;
				while (u<f&&coord[i][u] == j)u++;
			}u = f-1, nextdist[loc[i] + 1] = 0;
			for (int j = loc[i]; j >0; j--) {
				nextdist[j] = nextdist[j + 1] + f-u-1;
				if (dist[j] + nextdist[j]<=mindist)mindist= dist[j] + nextdist[j],idx[i]=j;
				while (u>0&&coord[i][u] == j)u--;
			}
		}printf("(Street: %d, Avenue: %d)\n",idx[0],idx[1]);
	}
}
