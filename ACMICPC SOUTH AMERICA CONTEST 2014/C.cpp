#include <stdio.h>
#include <cstring>

char input[1000001];

int main()
{
	int size,a0=0,a1=0,a2=0,aux;
	unsigned long long int cont=0;
	char now;
	scanf("%s",&input);

	size=strlen(input);
	for (int i=0;i<size;i++){
		now=input[i];
		if (now<'0'||now>'9')
			a0=a1=a2=0;
		else if (now=='0'||now=='3'||now=='6'||now=='9'){
			a0++;
			cont+=a0;
		}else if (now=='1'||now=='4'||now=='7'){
			cont+=a2;
			aux=a2;
			a2=a1;
			a1=a0+1;
			a0=aux;
		} else{
			cont+=a1;
			aux=a2;
			a2=a0+1;
			a0=a1;
			a1=aux;
		}
	}
	printf("%llu\n",cont);

}
