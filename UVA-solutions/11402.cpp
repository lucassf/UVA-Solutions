#include <bits/stdc++.h>
using namespace std;

int arr[1100000];

#include <cstdio>
#include <vector>
#include <algorithm>
#define INF (1<<30)
using namespace std;

const int neutral = 0; //comp(x, neutral) = x
int comp(int a, int b) {
	return a+b;
}

class SegmentTree {
private:
	vector<int> st;
	vector<char> lazy;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A[l];
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	void push(int p, int l, int r) {
	    if (lazy[p]=='F')st[p] = r-l+1;
	    else if (lazy[p]=='E')st[p] = 0;
	    else if (lazy[p]=='I')st[p] = r-l+1-st[p];

		if (l != r) {
		    char k,u,v;
            k = lazy[p];
            u = lazy[right(p)];
            v = lazy[left(p)];

            if (k=='I'){
                if (u=='F')u = 'E';
                else if (u=='E')u = 'F';
                else if (u=='I')u = 0;
                else u = k;

                if (v=='F')v = 'E';
                else if (v=='E')v = 'F';
                else if (v=='I')v = 0;
                else v = k;
            }else if (k!=0)u=v=k;

			lazy[right(p)] = u;
			lazy[left(p)] = v;
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, char k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
            lazy[p] = k;
			push(p, l, r);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = query(left(p), l, (l + r) / 2, a, b);
		int p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	void reset(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		lazy.assign(4 * size, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, char k) { update(1, 0, size - 1, a, b, k); }
};

int main(){
    int t,m,n,o,q,a,b,c=1,query;
    char com;
    SegmentTree seg;
    cin>>t;
    string s;

    while (t-->0){
        cin>>m;
        n = 0;
        for (int i=0;i<m;i++){
            cin>>o;
            cin>>s;
            for (int j=0;j<o;j++){
                for (int k=0;k<s.size();k++){
                    arr[n++] = s[k]-'0';
                }
            }
        }
        seg.reset(arr,arr+n);
        cin>>q;
        cout<<"Case "<<c++<<":"<<endl;
        query = 1;

        while (q-->0){
            cin>>com>>a>>b;
            if (com=='S')cout<<"Q"<<query++<<": "<<seg.query(a,b)<<endl;
            else seg.update(a,b,com);
        }
    }
}
