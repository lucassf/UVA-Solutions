#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
typedef unsigned long long int ll;

int N;
ll x[MAXN], y[MAXN];

ll cross(int i, int j){
	return x[i] * y[j] - x[j] * y[i];
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll area, acumarea, best, lim, parea;
	
	while(cin>>N){
		for (int i = 0; i < N; i++){
			cin>>x[i]>>y[i];
		}
		x[N] = x[0], y[N] = y[0];
		area = 0;
		for (int i = 1; i <= N; i++){
			area += cross(i - 1, i);
		}
		acumarea = cross(0, 1);
		best = 0, parea = 0;
		int i = 1, p = 0;
		
		for (int j = 0; j < N; j++){
			while ((acumarea + cross(i, j)) * 2 <= area){
				parea += cross((i + N - 1) % N, i);
				acumarea += cross(i, (i + 1) % N);
				p = i;
				i = (i + 1) % N;
			}
			lim = max(parea + cross(p, j), area - (acumarea + cross(i, j)));
			best = max(best, area - lim);
			
			acumarea -= cross(j, j + 1);
			parea -= cross(j, j + 1);
		}
		cout<<best<<" "<<area - best<<endl;
	}
}