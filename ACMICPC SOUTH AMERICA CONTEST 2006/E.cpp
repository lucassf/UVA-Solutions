#include <stdio.h>
#include <cmath>
#include <algorithm>

struct points{
	bool used;
	int x, y;
};

bool Sort(points a,points b){
	if (a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

int Cross(points x1, points x2, points x3){
	return (x3.x - x2.x)*(x2.y - x1.y) - (x2.x - x1.x)*(x3.y - x2.y);
}

int main(){
	int n, u, d, val, cont, up[2000], t,last,j;
	points p[2000], aux;
	while (scanf("%d", &n) != EOF&&n != 0){
		for (int i = 0; i < n; i++){
			scanf("%d%d",&p[i].x,&p[i].y);
			p[i].used = false;
		}
		std::sort(p, p + n, Sort);
		d=val=cont=0;
		while (val < n){
			u = j = 0;
			while (p[j].used)
				j++;
			last = j;
			for (; j < n; j++){
				aux = p[j];
				if (!aux.used){
					while (u >= 2 && Cross(p[up[u-2]],p[up[u-1]],aux)<0)u--;
					up[u++] = j;
				}
			}t = u + 1;
			for (int i = 0; i < u; i++)
				p[up[i]].used = true;
			for (int i = up[u-1]-1; i > last; i--){
				aux = p[i];
				if (!aux.used){
					while (u >= t && Cross(p[up[u - 2]], p[up[u - 1]], aux) < 0)u--;
					up[u++] = i;
				}
			}
			while (u >= t && Cross(p[up[u - 2]], p[up[u - 1]],p[last]) < 0)u--;
			for (int i = 0; i < u; i++)
				p[up[i]].used = true;
			cont++;
			val += u;
		}
		if (cont % 2 == 0)
			printf("Do not take this onion to the lab!\n");
		else
			printf("Take this onion to the lab!\n");
	}
}