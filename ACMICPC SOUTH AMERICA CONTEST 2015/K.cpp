#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1<<30)
typedef long long int ll;

const int neutral = INF;
int comp(int a, int b) {
	return min(a, b);
}

class SegmentTree {
	vector<int> a;
	int n;
public:
	SegmentTree(int* st, int* en) {
		int sz = int(en-st);
		for (n = 1; n < sz; n <<= 1);
		a.assign(n << 1, neutral);
		for(int i=0; i<sz; i++) a[i+n] = st[i];
		for(int i=n+sz-1; i; i--)
			a[i>>1] = comp(a[i>>1], a[i]);
	}
	void update(int i, int x) {
		a[i+n] = x; //substitui
		for (i += n, i >>= 1; i; i >>= 1)
			a[i] = comp(a[i<<1], a[1+(i<<1)]);
	}
	int query(int l, int r) {
		int ans = neutral;
		for (l += n, r += n+1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) ans = comp(ans, a[l++]);
			if (r & 1) ans = comp(ans, a[--r]);
		}
		return ans;
	}
};

int E[MAXN], val[MAXN], pos[MAXN];
vector<int> C[MAXN], S[MAXN];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int l, r, s, c, e;
	int N, M;
	while (cin>>N>>M){
		for (int i = 0; i < N; i++) {
			cin>>E[i];
			C[i].clear();
			S[i].clear();
		}
		for (int i = 0; i < M; i++){
			cin>>l>>s>>c;
			l--;
			C[l].push_back(c);
			S[l].push_back(s);
		}
		int acum = 0;
		memset(val, INF, sizeof val);
		SegmentTree st(val, val + N + 1);
		st.update(0, 0);
		pos[0] = 0;
		
		for (int i = N - 1; i >= 0; i--){
			int best = INF;
			e = E[i];
			
			for (int j = 0; j < (int)C[i].size(); j++){
				c = C[i][j], s = S[i][j];
				if (s < e) continue;
				s = acum - (s - e);
				
				int u = lower_bound(pos, pos + N - i, s) - pos;
				best = min(best, c + st.query(u, N - i - 1));
			}
			
			//cout<<best<<" ";
			acum += E[i];
			pos[N - i] = acum;
			st.update(N - i, best);
		}
		l = st.query(N, N);
		cout<<(l >= INF ? -1 : l)<<endl;
	}
}