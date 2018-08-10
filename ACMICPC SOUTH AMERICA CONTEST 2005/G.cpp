#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 1000000009

ll base[27][1009];

void constructBase(int N){
	ll p = N;
	ll qtt = 0;
	int i = 0;
	
	while (qtt<MAXN){
		qtt = (i+1)*p;
		p*=N;
		base[N][i++] = qtt;
		//if (N==2)cout<<base[N][i-1]<<" ";
	}
}

int main(){
	int N,Q;
	char song[27][109];
	ll p,cnt,k;
	for (int i=2;i<27;i++)constructBase(i);
	
	while (scanf("%d%d",&N,&Q),N||Q){
		for (int i=0;i<N;i++)scanf("%s",&song[i]);
		
		for (int i=0;i<Q;i++){
			scanf("%lld",&k);
			
			if (N==1){
				printf("%s\n",song[0]);
				continue;
			}
			int j = 0;
			while(k>base[N][j])k-=base[N][j],j++;
			//cout<<k<<endl;
			j++;
			p = (k-1)/j;
			k = k-p*j;
			while (j!=k){
				p/=N;
				j--;
			}printf("%s\n",song[p%N]);
		}
		printf("\n");
	}
}
