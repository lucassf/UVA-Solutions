#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
typedef long long int ll;

ll B, P, L, N;

const int neutral = 0;
ll cmp(ll a, ll b){
	return (a + b) % P;
}

ll extGcd(ll a, ll b, ll & x, ll &y){
	if (b == 0){
		x = 1, y = 0;
		return a;
	}
	ll g = extGcd(b, a % b, y, x);
	y -= a / b * x;
	return g;
}

ll modInv(ll a, ll m){
	ll x, y;
	extGcd(a, m, x, y);
	return (x % m + m ) % m;
}

ll modExp(ll a, ll b, ll m){
	if (b == 0)return 1;
	ll c = modExp(a, b / 2, m);
	c = (c * c) % m;
	if (b % 2 != 0)c = (c * a) % m;
	return c;
}

class SegmentTree{
	private:
	vector<ll> st, pos;
	int size;
	#define parent(p) (p >> 1)
	#define left(p) (p << 1)
	#define right(p) ((p << 1) + 1)
	
	void build(int p, int l, int r){
		if (l == r){
			st[p] = 0;
			pos[l] = p;
		}else{
			build(left(p), l, (l + r)/2);
			build(right(p), (l + r)/2 + 1, r);
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
	void reset(int N){
		size = N;
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1);
	}
	ll query(int a, int b){
		return find(1, 0, size - 1, a - 1, b - 1);
	}
	void update(int n, ll num){
		n--;
		st[pos[n]] = num * modExp(B, L - n - 1, P) % P;
		n = parent(pos[n]);
		while (n > 0){
			st[n] = cmp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
	void print(){
		for (int i = 0; i < size; i++){
			cout<<st[pos[i]]<<" ";
		}
		cout<<endl;
	}
};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	char com;
	ll a, b;
	
	SegmentTree st;
	while(cin>>B>>P>>L>>N, B){
		st.reset(L);
		for (int i = 0; i < N; i++){
			cin>>com>>a>>b;
			if (com == 'E')st.update(a, b);
			else cout<<(st.query(a, b) * modInv(modExp(B, L - b, P), P) % P)<<endl;
			//st.print();
		}
		cout<<"-\n";
	}
	
}
