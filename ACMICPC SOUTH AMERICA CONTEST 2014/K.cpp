#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> ii;
#define MAXN 1000009
#define INF 1000000007

int K, D;
int used[MAXN], occ[MAXN];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int A, B;
	ll ans;
	while (cin>>K>>D){
		memset(used, 0, sizeof used);
		memset(occ, 0, sizeof occ);
		
		for (int i = 0; i < D; i++){
			cin>>A>>B;
			A--, B--;
			used[A] = 1;
			occ[B] = 1;
		}
		int acum = 0, u = 0;
		for (int i = 0; i < K; i++){
			acum += occ[i] - used[i];
			if (acum < 0) u = (i + 1) % K, acum = 0;
		}
		ans = 1;
		acum = 0;
		for (int i = u; ; ){
			if (!used[i]) acum++;
			if (!occ[i]){
				ans = ans * acum % INF;
				acum--;
			}
			
			i = (i + 1) % K;
			if (i == u) break;
		}
		cout<<ans<<endl;
	}
}
