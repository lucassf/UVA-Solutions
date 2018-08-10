#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
#define MAXN 1009

ll arr[MAXN][MAXN] = {}, ans;
ll sol[MAXN] = {}, best[MAXN];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	ll ans;
	while (cin>>N, N){
		memset(arr, 0, sizeof(arr));
		ans = 0;
		for (int i = 1; i <= N; i++){
			for (int j = 1; j <= i; j++){
				cin>>arr[i][j];
			}
		}
		ans = 0;
		sol[0] = 0;
		for (int j = 1; j <= N; j++){
			sol[j] = sol[j - 1] + arr[j][1];
		}
		best[N] = sol[N];
		for (int i = N - 1; i >= 1; i--){
			best[i] = max(best[i + 1], sol[i]);
		}
		ans = max(ans, best[1]);
		
		for (int j = 2; j <= N; j++){
			int acum = 0;
			for (int i = j; i <= N; i++){
				sol[i] = best[i - 1] + arr[i][j] + acum;
				acum += arr[i][j];
			}
			best[N] = sol[N];
			for (int i = N - 1; i >= j; i--){
				best[i] = max(best[i + 1], sol[i]);
				//cout<<best[i]<<" ";
			}
			//cout<<endl;
			ans = max(ans, best[j]);
		}
		cout<<ans<<endl;
	}
}
