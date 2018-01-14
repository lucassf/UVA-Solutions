#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF 1000000007
typedef long long int ll;
typedef pair<int, int> ii;

int P, V;

struct point{
	int x, y;
	ll c;
	point(){}
	point (int _x, int _y){
		x = _x, y = _y;
	}
	point (ll _c, int _x, int _y){
		x = _x, y = _y, c = _c;
	}
	bool operator<(point other) const{
		if (x != other.x) return x < other.x;
		if (c != other.c) return c > other.c; 
		return y < other.y;
	}
};

int N;
point p[2 * MAXN];
set<ii> interv;

inline bool inInterv(int y){
	set<ii>::iterator it;
	
	it = interv.upper_bound(ii(y, INF));
	if (it == interv.begin()) return 0;
	it--;
	return y >= it -> first && y <= it->second;
}

inline void intersect(int y1, int y2){
	set<ii>::iterator it, it2;
	
	it = interv.upper_bound(ii(y1, INF));
	
	it2 = it;
	int change = 0;
	if (it != interv.begin()) it--, change = 1;
	
	if (it2 != interv.end() && it2 -> first == y2){
		y2 = it2 -> second;
		interv.erase(it2);
	}
	
	if (change){
		if (it -> second == y1){
			interv.insert(ii(it -> first, y2));
			interv.erase(it);
		}else if (y1 >= it -> first && y2 <= it -> second){
			if (it -> first != y1) interv.insert(ii(it -> first, y1));
			if (it -> second != y2) interv.insert(ii(y2, it -> second));
			interv.erase(it);
		}else
			interv.insert(ii(y1, y2));
		
	}else{
		interv.insert(ii(y1, y2));
	}
}

void prin(){
	set<ii>::iterator it;
	for (it = interv.begin(); it != interv.end(); it++){
		cout<<"("<<(it->first)<<", "<<(it->second)<<") ";
	}
	cout<<endl;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int X, Y;
	ll ans;
	
	while (cin>>P>>V){
		N = 0;
		ans = 0;
		for (int i = 0; i < P; i++){
			cin>>X>>Y;
			p[N++] = point(i + 1, X, Y);
		}
		for (int i = 0; i < V; i++){
			cin>>X>>Y;
			p[N++] = point(-1, X, Y);
		}
		sort(p, p + N);
		interv.clear();
		
		for (int i = 0; i < N;){
			X = p[i].x;
			while (i < N && p[i].x == X && p[i].c > 0){
				if (!inInterv(p[i].y)) ans += p[i].c;
				i++;
			}
			while (i < N && p[i].x == X){
				intersect(p[i].y, p[i + 1].y);
				i += 2;
			}
			//prin();
		}
		
		cout<<ans<<endl;
	}
}