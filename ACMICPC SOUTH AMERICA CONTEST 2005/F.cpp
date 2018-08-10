#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define MAXN 1009

ii reversal[MAXN];

int main(){
	int n,q,r,a,b,c,t = 1;
	while (scanf("%d",&n)&&n!=0){
		scanf("%d",&r);
		for (int i=0;i<r;i++){
			scanf("%d%d",&a,&b);
			reversal[i] = ii(a,b);
		}
		scanf("%d",&q);
		printf("Genome %d\n",t++);
		for (int i=0;i<q;i++){
			scanf("%d",&c);
			for (int j=0;j<r;j++){
				a = reversal[j].first, b = reversal[j].second;
				if (c<a||c>b)continue;
				c = a + b - c;
			}
			printf("%d\n",c);
		}
		
	}
}
