#include <stdio.h>

int main() {
	bool in;
	char con[10],con1[10];
	gets(con);
	gets(con1);
	in = false;
	for (int i = 0; i < 10; i+=2)
		if (con1[i] == con[i])
			in = true;
	if (in)
		printf("N\n");
	else
		printf("Y\n");
}
