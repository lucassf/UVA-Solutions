#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> ii;
#define MAXN 100009
#define INF 1e9

ll V, wmax[MAXN], wmin[MAXN];
ii p[MAXN];
vector<ii> p1, p2;

ll cross(ii q1, ii q2){
	return q1.first * q2.second - q1.second * q2.first;
}

ll area(vector<ii> &p){
	ll ans = 0;
	for (int i = 0; i < (int) p.size() - 1; i++){
		ans += cross(p[i], p[i + 1]);
	}
	return abs(ans) / 2;
}

ll perymeter(vector<ii> &p){
	ll ans = 0;
	for (int i = 0; i < (int) p.size() - 1; i++){
		ans += abs(p[i].first - p[i + 1].first) +
			abs(p[i].second - p[i + 1].second);
	}
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll X, Y, y1, y2, ymax, ymin;
	while (cin>>V){
		for (int i = 0; i < V; i++){
			cin>>X>>Y;
			p[i] = ii(X, Y);
		}
		sort(p, p + V);
		p1.clear(); p2.clear();
		
		wmax[V - 1] = wmin[V - 1] = p[V - 1].second;
		for (int i = V - 2; i >= 0; i--){
			wmax[i] = max(p[i].second, wmax[i + 1]);
			wmin[i] = min(p[i].second, wmin[i + 1]);
		}
		
		for (int i = 0; i < V; ){
			X = p[i].first;
			y1 = p[i].second;
			
			ymin = wmin[i];
			ymax = wmax[i];
			
			while (i < V && p[i].first == X)
				i++;
			
			y2 = p[i - 1].second;
			
			if (p1.empty()){
				p1.push_back(ii(X - 1, y1 - 1));
				p1.push_back(ii(X, y1 - 1));
				p2.push_back(ii(X - 1, y2 + 1));
				p2.push_back(ii(X, y2 + 1));
				continue;
			}
			
			ll h1 = p1[p1.size() - 1].second;
			ll h2 = p2[p2.size() - 1].second;
			ll x = p1[p1.size() - 1].first;
			
			if (ymin <= h1){
				p1.push_back(ii(X - 1, h1));
				if (y1 <= h1) {
					p1.push_back(ii(X - 1, y1 - 1));
					p1.push_back(ii(X, y1 - 1));
				}else{
					p1.push_back(ii(X, h1));
				}
			}else{
				p1.push_back(ii(x + 1, h1));
				p1.push_back(ii(x + 1, ymin - 1));
				p1.push_back(ii(X, ymin - 1));
			}
			
			if (ymax < h1){
				p2.push_back(ii(x + 1, h2));
				p2.push_back(ii(x + 1, h1 + 1));
				p2.push_back(ii(X, h1 + 1));
				p2.push_back(ii(X, ymax + 1));
			}else if (ymin > h2){
				p2.push_back(ii(x, ymin));
				p2.push_back(ii(X - 1, ymin));
				p2.push_back(ii(X - 1, y2 + 1));
				p2.push_back(ii(X, y2 + 1));
			}
			else if (ymax >= h2){
				p2.push_back(ii(X - 1, h2));
				if (y2 >= h2) {
					p2.push_back(ii(X - 1, y2 + 1));
					p2.push_back(ii(X, y2 + 1));
				}else{
					p2.push_back(ii(X, h2));
				}
			}else{
				p2.push_back(ii(x + 1, h2));
				p2.push_back(ii(x + 1, ymax + 1));
				p2.push_back(ii(X, ymax + 1));
			}
		}
		p1.push_back(ii(p1[p1.size() - 1].first + 1, p1[p1.size() - 1].second));
		p2.push_back(ii(p2[p2.size() - 1].first + 1, p2[p2.size() - 1].second));
		
		for (int i = p2.size() - 1; i >= 0; i--){
			p1.push_back(p2[i]);
		}
		p1.push_back(p1[0]);
		
		/*for (int i = 0; i < p1.size(); i++){
			cout<<p1[i].first<<" "<<p1[i].second<<endl;
		}*/
		
		cout<<perymeter(p1)<<" "<<area(p1)<<endl;
	}
}
