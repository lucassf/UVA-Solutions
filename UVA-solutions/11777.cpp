#include <cstdio>

int main() {
	int t,t1,t2,f,a,c1,c2,c3,c,score;
	bool half;
	scanf("%d",&t);
	for (int k = 1; k <= t; k++) {
		scanf("%d%d%d%d%d%d%d",&t1,&t2,&f,&a,&c1,&c2,&c3);
		c = 0;
		if (c1 > c2) {
			c += c1;
			if (c2 > c3)c += c2;
			else c += c3;
		}
		else {
			c += c2;
			if (c1 > c3)c += c1;
			else c += c3;
		}score = 2*(t1 + t2 + f + a) + c;
		printf("Case %d: ",k);
		if (score < 120)printf("F\n");
		else if (score < 140)printf("D\n");
		else if (score < 160)printf("C\n");
		else if (score < 180)printf("B\n");
		else printf("A\n");
	}
}
