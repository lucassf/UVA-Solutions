#include <stdio.h>

int main()
{
	int n,i=0;
	char l[100000];
	char ans[181]={'Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N',
		'N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y',
		'N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N',
		'Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N',
		'N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N',
		'N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N',
		'N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N',
		'N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y','N','N','N','N','N','Y'};
	while (scanf("%d",&n)!=EOF){
		l[i++]=ans[n];
		l[i++]='\n';
	}
	l[i]=0;
	printf("%s",l);
}