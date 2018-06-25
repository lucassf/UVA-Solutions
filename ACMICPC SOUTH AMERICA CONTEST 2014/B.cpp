#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef long long int ll;
#define MAXN 5009

ll pd[MAXN][MAXN];
ll A, B;
char str[MAXN];

int solve(int l, int r){
	if (l >= r) return 0;
	if (pd[l][r] != -1) return pd[l][r];
	
	if (str[l] == 'B') return pd[l][r] = solve(l + 1, r);
	if (str[r] == 'W') return pd[l][r] = solve(l, r - 1);
	
	int l1, r1;
	ll ans = solve(l + 1, r - 1) + A;
	ll w = 0, acum = 0;
	
	for (int i = l; i <= r; i++){
		while (i <= r && str[i] == 'W') i++, w++;
		acum += w * (A - B);
	}
	
	return pd[l][r] = min(ans, acum);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (cin>>A>>B){
		cin>>str;
		int n = strlen(str);
		memset(pd, -1, sizeof pd);
		cout<<solve(0, n - 1)<<endl;
	}
}
