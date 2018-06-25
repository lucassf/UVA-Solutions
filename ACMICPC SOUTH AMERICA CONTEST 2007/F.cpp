#include <cstdio>
#include <cstring>

int qtd[300][300][301];

int main(){
	int a, b, c;
	char map[300][301],ver;
	while (scanf("%d%d%d", &a, &b, &c)&&a!=0){
		for (int i = 0; i < a; i++){
			scanf("%s", &map[i]);
		}
		for (int i = a - 1; i >= 0; i--){
			for (int j = b - 1; j >= 0; j--){
				for (int u = 1; u <= b - j; u++){
					ver = map[i][j] == '.' ? 1 : 0;
					qtd[i][j][u] = u == 1 ? ver : ver + qtd[i][j + 1][u - 1];
				}
			}
		}
		qtd[0][0][2] = 1;
		int value, u, min = 9999999;
		for (int j = 0; j < b; j++){
			for (int size = 1; size <= b - j; size++){
				u = 0;
				value = 0;
				for (int i = 0; i < a; i++){
					value += qtd[i][j][size];
					while (value >= c){
						if (size*(i - u + 1) < min)min = size*(i - u + 1);
						value -= qtd[u++][j][size];
					}
				}
			}
		}
		printf("%d\n", min);
	}
}
