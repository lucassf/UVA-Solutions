#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n, a, ans;
	while (cin>>n){
		ans = 0;
		for (int i = 0; i < 5; i++){
			cin>>a;
			if (a == n) ans++;
		}
		cout<<ans<<endl;
	}
}