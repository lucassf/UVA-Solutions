#include <stdio.h>

int proxesq[100002];
int proxdir[100002];

int main()
{
	int s,b,min,max,rad;
	scanf("%d%d",&s,&b);
	while(s!=0&&b!=0)
	{
		for (int i=0;i<=s;i++)
		{
			proxesq[i]=i-1;
			proxdir[i]=i+1;
		}
		for (int k=0;k<b;k++)
		{
			scanf("%d%d",&min,&max);
			proxdir[proxesq[min]]=proxdir[max];
			proxesq[proxdir[max]]=proxesq[min];
			if (proxdir[max]==s+1&&proxesq[min]==0)
				printf("* *\n");
			else if (proxdir[max]==s+1)
				printf("%d *\n",proxesq[min]);
			else if (proxesq[min]==0)
				printf("* %d\n",proxdir[max]);
			else
				printf("%d %d\n",proxesq[min],proxdir[max]);
		}
		printf("-\n");
		scanf("%d%d",&s,&b);
	}
}
