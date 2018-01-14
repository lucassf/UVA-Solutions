#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define INF 1000000007
typedef long long int ll;

ll D[MAXN][MAXN];

ll domb(int n, int k){
	if (k == 1 || n == k) return 1;
	if (D[n][k] != -1) return D[n][k];
	
	return D[n][k] = (k * domb(n - 1, k) % INF + (n - k + 1) * domb(n - 1, k - 1) % INF) % INF;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, K, Q, k;
	ll ans;
	
	memset(D, -1, sizeof D);
	
	while (cin>>N>>Q){
		for (int i = 0; i < Q; i++){
			cin>>K;
			k = min(N, K);
			ans = 0;
			
			for (int j = 1; j <= k; j++){
				ans += domb(N, j) % INF;
				ans %= INF;
			}
			if (i > 0) cout<<" "<<ans;
			else cout<<ans;
		}
		cout<<"\n";
	}
}