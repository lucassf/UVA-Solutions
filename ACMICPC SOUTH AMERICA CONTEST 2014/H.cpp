#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef long long int ll;
#define MAXN 1009

int N, a[MAXN], pd[MAXN][MAXN];

inline int getVal(int b1, int b2){
	return min(abs(b2 - b1), 24 - abs(b2 - b1));
}

int solve(int l,int r){
	if (l >= r) return 0;
	if (pd[l][r] != -1) return pd[l][r];
	
	int ans = getVal(a[l], a[l + 1]) + solve(l + 2, r);
	return pd[l][r] = min(ans, getVal(a[l], a[r]) + solve(l + 1, r - 1));
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (cin>>N){
		
		for (int i = 0; i < N; i++){
			cin>>a[i];
		}
		sort(a, a + N);
		memset(pd, -1, sizeof(pd));
		cout<<solve(0, N - 1)<<endl;
	}
}
