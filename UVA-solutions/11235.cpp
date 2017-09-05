#include <bits/stdc++.h>
#define INF (1<<30)
using namespace std;

int a[100000], last[100000];

const int neutral = 0; //comp(x, neutral) = x
int comp(int a, int b) {
	return max(a,b);
}

class SegmentTree {
private:
	vector<int> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A[l];
			pos[l] = p;
		}
		else {
			build(left(p), l, (l + r) / 2, A);
			build(right(p), (l + r) / 2 + 1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = find(left(p), l, (l + r) / 2, a, b);
		int p2 = find(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	void reset(int* begin, int* end) {
		size = (int)(end - begin);
		st.assign(4 * size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size - 1, begin);
	}
	int query(int a, int b) { return find(1, 0, size - 1, a, b); }
};

int main(){
    int n,q,l,r,prev;
    SegmentTree seg;
    while (cin>>n&&n!=0){
        cin>>q;
        prev = -1000000000;
        for (int i=0;i<n;i++){
            cin>>a[i];
            if (a[i]==prev)a[i] = a[i-1]+1;
            else{
                if (i>0)
                    for (int j = i-a[i-1];j<i;j++)
                        last[j] = i-1;
                 prev = a[i], a[i] = 1;
            }
        }
        for (int j = n-a[n-1];j<n;j++)
            last[j] = n-1;
        /*for (int i=0;i<n;i++){
            cout<<a[i]<<" ";
        }cout<<endl;
        for (int i=0;i<n;i++){
            cout<<last[i]<<" ";
        }cout<<endl;*/
        seg.reset(a,a+n);
        for (int i=0;i<q;i++){
            cin>>l>>r;
            l--,r--;
            if (last[l]>=r)cout<<r-l+1<<endl;
            else{
                cout<<max(last[l]-l+1,seg.query(last[l]+1,r))<<endl;
            }
        }
    }
}
