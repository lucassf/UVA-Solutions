#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
#define MAXN 1000009

ll F, C[MAXN];

inline ll gcd(ll a, ll b){
	ll aux;
	while (b != 0){
		aux = b;
		b = a % b;
		a = aux;
	}
	return a;
}

inline ll getVal(ll n, ll sum){
	ll s = n * F;
	if (sum % s != 0) return 0;
	
	ll mod = (C[0] - s - n) % s;
	ll b = (1ll) << 62;
	for (int i = 0; i < F; i++){
		ll a = C[i] - s - n;
		if (a < 0 || a % s != mod)return 0;
		b = min(b, a / s + 1);
	}
	return b;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll u, sum;
	
	while (cin>>F, F){
		
		u = sum = 0;
		
		for (int i = 0; i < F; i++){
			cin>>C[i];
			u = gcd(C[i], u);
			sum += C[i];
		}
		ll ans = 0;
		
		for (ll n = 1; n * n <= u; n ++){
			if (u % n != 0)continue;
			ans += getVal(n, sum);
			if (n * n != u)ans += getVal(u / n, sum);
		}
		cout<<ans<<endl;
	}
}
