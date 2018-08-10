#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
#define MAXN 10009
#define INF 1e9
#define MAXZ 'z' - 'a' + 1

struct trie{
	trie * nxt[MAXZ];
	trie(){
		for (int i = 0; i < MAXZ; i++){
			nxt[i] = NULL;
		}
	}
	
	~trie(){
		for (int i = 0; i < MAXZ; i++) delete nxt[i];
	}
};

ll cnt;
ll qtt[MAXZ];

void add(trie * t, char * s, bool rev){
	int n = strlen(s);
	trie * aux = t;
	
	if (rev) reverse(s, s + n);
	
	for (int i = 0; i < n; i++){
		int c = s[i] - 'a';
		if (aux -> nxt[c] == NULL){
			aux -> nxt[c] = new trie();
			if (aux != t) qtt[c]++; 
			cnt++;
		}
		aux = aux -> nxt[c];
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	trie *pref, *suf;
	int N, M;
	ll port, ans, qttport[MAXZ];
	char s[1009];
	
	while (cin>>N>>M, N){
		pref = new trie(), suf = new trie();
		cnt = 0;
		memset(qtt, 0, sizeof qtt);
		
		for (int i = 0; i < N; i++){
			cin>>s;
			add(pref, s, false);
		}
		for (int i = 0; i < MAXZ; i++) qttport[i] = qtt[i];
		port = cnt;
		
		cnt = 0;
		memset(qtt, 0, sizeof qtt);
		
		for (int i = 0; i < M; i++){
			cin>>s;
			add(suf, s, true);
		}
		ans = port * cnt;
		for (int i = 0; i < MAXZ; i++) ans -= qttport[i] * qtt[i];
		
		cout<<ans<<endl;
	}
}
