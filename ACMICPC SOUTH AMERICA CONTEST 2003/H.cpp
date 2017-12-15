#include <bits/stdc++.h>
using namespace std;
#define MAXN 409
#define MAXM 1009
#define INF 1e9
#define EPS 1e-9

typedef pair<int,int> ii;
typedef long long int ll;

int N, W, vis[MAXN*MAXM], w[MAXN*MAXM], sumdiff;
ii x[MAXN];

bool sorte(ii a, ii b){
	if (a.first + a.second != b.first + b.second)
		return a.first + a.second < b.first + b.second;
	return a.first < b.first;
}

inline bool solve(int skip){
	int idx = 1, nidx;
	vis[0] = 1, w[0] = 0;
	
	for (int i = 0; i < N; i++){
		if (i == skip)continue;
		
		int u = x[i].second - x[i].first;
		nidx = idx;
		
		for (int j = 0; j < idx; j++){
			if (!vis[u + w[j]]){
				vis[u + w[j]] = 1;
				w[nidx++] = u + w[j];
			}
		}
		idx = nidx;
	}
	return vis[sumdiff/2];
}

int main(){
	int a, b, totalsum;
	bool solved;
	
	while (scanf("%d",&N),N){
		sumdiff = totalsum = 0;
		solved = false;
		
		for (int i = 0; i < N; i++){
			scanf("%d%d", &a, &b);
			if (a > b)swap(a, b);
			x[i] = ii(a, b);
			sumdiff += b - a;
			totalsum += b + a;
		}
		sort(x, x + N, sorte);
		
		for (int i = -1; i < N; i++){
			if (i >= 0){
				sumdiff -= x[i].second - x[i].first;
			}
			if (sumdiff % 2 != 0){
				if (i >= 0){
					sumdiff += x[i].second - x[i].first;
				}
				continue;
			}
			memset(vis, 0, sizeof(vis));
			if (solve(i)){
				solved = true;
				if (i == -1)printf("%d discard none\n",totalsum/2);
				else printf("%d discard %d %d\n",(totalsum - x[i].first - x[i].second)/2, x[i].first, x[i].second);
				break;
			}
			sumdiff += x[i].second - x[i].first;
		}
		
		if (!solved)printf("impossible\n");
	}
}