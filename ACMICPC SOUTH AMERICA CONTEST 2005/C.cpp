#include <stdio.h>
#include <cstring>

int main()
{
	int n,d,cont,used[101];
	char dinner[200];
	while(scanf("%d%d ",&n,&d)&&n!=0){
		cont=0;
		for (int i=0;i<n;i++)
			used[i]=0;
		for (int i=0;i<d;i++){
			gets(dinner);
			for (int j=0;j<n&&cont<n;j++)
				if (dinner[2*j]=='0'&&!used[j]){
					used[j]=1;
					cont++;
				}
		}
		if (cont==n)
			printf("no\n");
		else
			printf("yes\n");
	}
}
