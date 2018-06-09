#include <stdio.h>

int main()
{
	int n,m, qtd, aux[4], a, p;
	bool out;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		qtd=0;
		for (int i=n;i<=m;i++)
		{
			a = i;
			p=0;
			while(a>0)
			{
				aux[p++] = a%10;
				a/=10;
			}
			out=false;
			for (int j=0;j<p-1&&!out;j++)
				for (int t=j+1;t<p;t++)
					if (aux[j]==aux[t])
					{
						qtd++;
						out=true;
						break;
					}
		}
		printf("%d\n",m-n+1-qtd);
	}
}