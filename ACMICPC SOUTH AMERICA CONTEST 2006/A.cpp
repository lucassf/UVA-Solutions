#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int main(){
	int n,c,k,a;
	ii qtt[109];

	while(cin>>n>>c>>k && n!=0){
		memset(qtt,0,sizeof(qtt));
		for (int i=0;i<k;i++)qtt[i] = ii(0,i+1);
		for (int i=0;i<n*c;i++){
			cin>>a;
			a--;
			qtt[a] = ii(qtt[a].first+1,a+1);
		}
		sort(qtt,qtt+k);
		int val = qtt[0].first;
		cout<<qtt[0].second;
		for (int i=1;i<=k && qtt[i].first==val;i++){
			cout<<" "<<qtt[i].second;
		}cout<<endl;
	}
}
