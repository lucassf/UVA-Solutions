#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
#define MAXN 100009

ll neutral = 1;
ll cmp(ll a, ll b){
	return a * b;
}

class SegmentTree{
	private:
	vector<ll> st, pos;
	int size;
	#define parent(p) (p >> 1)
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	
	void build(int p, int l, int r, ll *A){
		if (l == r){
			st[p] = A[l] > 0? 1 : (A[l] == 0 ? 0 : -1);
			pos[l] = p;
		}else{
			build(left(p), l, (l + r)/2, A);
			build(right(p), (l + r)/2 + 1, r, A);
			st[p] = cmp(st[left(p)], st[right(p)]);
		}
	}
	ll find(int p, int l, int r, int a, int b){
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		ll p1 = find(left(p), l, (l + r) / 2, a, b);
		ll p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return cmp(p1, p2);
	}
public:
	void reset(int N, ll *A){
		size = N;
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, A);
	}
	ll query(int a, int b){
		return find(1, 0, size - 1, a - 1, b - 1);
	}
	void update(int n, ll num){
		n--;
		st[pos[n]] = num > 0 ? 1 : (num == 0 ? 0 : -1);
		n = parent(pos[n]);
		while (n > 0){
			st[n] = cmp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N, K, l, r;
	char c;
	ll A[MAXN];
	SegmentTree st;
	while (cin>>N>>K){
		for (int i = 0; i < N; i++){
			cin>>A[i];
		}
		st.reset(N, A);
		while (K-- > 0){
			cin>>c>>l>>r;
			if (c == 'C')st.update(l, r);
			else{
				ll u = st.query(l, r);
				if (u == 0)cout<<0;
				else if (u < 0)cout<<'-';
				else cout<<'+';
			}
		}
		cout<<endl;
	}
}