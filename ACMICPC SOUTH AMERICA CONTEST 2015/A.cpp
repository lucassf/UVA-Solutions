#include <bits/stdc++.h>
using namespace std;
#define MAXN 20
typedef long long int ll;

char str[MAXN], sol[MAXN];
int qtt[10], u, N;

bool solve(int idx, bool less){
	if (idx == N) return 1;
	
	sol[u] = 0;
	
	for (int i = less ? str[idx] : '9'; i >= '0'; i--){
		if (qtt[i - '0'] == 2) continue;
		qtt[i - '0']++;
		if (i != '0' || u != 0) sol[u++] = i;
		if (solve(idx + 1, i == str[idx] ? less : 0)) return 1;
		u--;
		u = max(u, 0);
		qtt[i - '0']--;
	}
	return 0;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	while (cin>>str){
		memset(qtt, 0, sizeof qtt);
		N = strlen(str);
		u = 0;
		solve(0, 1);
		sol[u] = 0;
		cout<<sol<<endl;
	}
}