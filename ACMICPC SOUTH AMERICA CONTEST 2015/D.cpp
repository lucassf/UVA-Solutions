#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef unsigned long long int ll;

int getVal(int b){
	if (b < 1) return 0;
	if (b < 10) return 1;
	if (b < 100) return 10;
	if (b < 1000) return 100;
	if (b < 10000) return 1000;
	return 10000;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, M, B, a, ans, acum, p;
	while (cin>>N>>M){
		ans = acum = 0;
		for (int i = 0; i < M; i++){
			cin>>B>>p;
			
			for (int j = 1; j < N; j++){
				cin>>a;
				B -= a;
			}
			if (B - p >= 0)acum += p;
			ans += getVal(B);
		}
		cout<<ans - acum<<endl;
	}
}