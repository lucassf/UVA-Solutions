#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009

int main(){
	int n,ans,a,qtt[MAXN],j;
	while (scanf("%d",&n)!=EOF&&n!=0){
		ans = j = 0;
		memset(qtt,0,sizeof(qtt));
		for (int i=0;i<n;i++){
			scanf("%d",&a);
			if (a==0)qtt[j]++;
			else j++;
		}
		if (j!=0)ans+=(qtt[0]+qtt[j--])/2;
		else ans+=ceil((double)qtt[0]/2);
		while (j>0)ans+=qtt[j--]/2;
		printf("%d\n",ans);
	}
}
