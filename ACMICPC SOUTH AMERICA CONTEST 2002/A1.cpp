#include <stdio.h>
#include <map>
using namespace std;

typedef map<int, bool> r;

int main()
{
	r mis;
	int n,m, k, dum;
	while(scanf("%d%d",&n,&m)&&(m!=0||n!=0))
	{
		dum = 0;
		for (int i=0;i<m;i++)
		{
			scanf("%d",&k);
			if (mis.count(k))
			    mis[k] = true;
			else
				mis[k]=false;
		}
		r::iterator it;
		for (it=mis.begin();it!=mis.end();it++)
			if (it->second)
				dum++;
		printf("%d\n",dum);
		mis.clear();
	}
}
