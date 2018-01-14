#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define EPS 1e-9
typedef long long int ll;
typedef pair<double, int> di;

struct edge{
	int u;
	int A, B;
	edge(){}
	edge(int u, int a, int b){
		this->u = u, A = a, B = b;
	}
};

int N, M;
vector<edge> e[MAXN];

inline double djkstra(double t){
	priority_queue<di> inuse;
	vector<double> val;
	
	val.assign(N, -1);
	inuse.push(di(0, 0));
	val[0] = 0;
	
	while (!inuse.empty()){
		double d = -inuse.top().first;
		int u = inuse.top().second;
		inuse.pop();
		
		if (u == N - 1) break;
		if (d - val[u] > EPS) continue;
		
		for (int i = 0; i < (int) e[u].size(); i++){
			edge aux = e[u][i];
			int v = aux.u;
			double cost = d + t * aux.A + aux.B;
			
			if (val[v] < 0 || cost < val[v]){
				val[v] = cost;
				inuse.push(di(-cost, v));
			}
		}
	}
	return val[N - 1];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int I, J, A, B;
	while (cin>>N>>M){
		for (int i = 0; i < N; i++){
			e[i].clear();
		}
		for (int i = 0; i < M; i++){
			cin>>I>>J>>A>>B;
			I--, J--;
			e[I].push_back(edge(J, A, B));
			e[J].push_back(edge(I, A, B));
		}
		double l = 0, r = 24 * 60;
		double maxi = 80, val1, val2;
		
		while (maxi-- > 0){
			double mid1 = (2 * l + r) / 3;
			double mid2 = (l + 2 * r) / 3;
			
			val1 = djkstra(mid1);
			val2 = djkstra(mid2);
			
			if (val1 > val2) r = mid2;
			else l = mid1;
		}
		printf("%.5lf\n", val1);
	}
	return 0;
}