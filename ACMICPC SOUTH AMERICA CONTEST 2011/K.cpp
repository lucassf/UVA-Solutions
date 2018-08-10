#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
#define MAXN 13*13*14

int getRank(int a, int b, int c){
	int pot = 0;
	
	if (a == b && b == c)return 1000000*a;
	if (b == c) swap(a, c);
	else if (a == c) swap(b, c);
	
	if (a != b)return 0;
	return a * 100 + c;
}

bool sorte(iii a, iii b){
	int a1 = a.first.first, b1 = a.first.second, c1 = a.second;
	int a2 = b.first.first, b2 = b.first.second, c2 = b.second;
	
	return getRank(a1, b1, c1) < getRank(a2, b2, c2);
}

iii cards[MAXN];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int u = 0;
	for (int i = 1; i <= 13; i++){
		for (int k = i; k <= 13; k++){
			cards[u++] = iii(ii(i, i) , k);
			if (i != k)cards[u++] = iii(ii(i, k) , k);
		}		
	}
	sort(cards, cards + u, sorte);
	
	int A, B, C;
	iii toFind;
	while (cin>>A>>B>>C, A){
		toFind = iii(ii(A, B), C);
		int idx = upper_bound(cards, cards + u, toFind, sorte) - cards;
		if (idx == u)cout<<"*"<<endl;
		else cout<<cards[idx].first.first<<" "<<cards[idx].first.second<<" "<<cards[idx].second<<endl;
	}
}
