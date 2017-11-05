#include <stdio.h>
#include <cstring>

int main(){
	char emot[100][16],a[100],l;
	int n, m, current[100],size,t[100][16],ans;
	while (scanf("%d%d", &n, &m)&&n!=0&&m!=0){
		ans = 0;
		for (int i = 0; i < n; i++){
			scanf("%s%c", &emot[i],&l);
			size = strlen(emot[i]);
			t[i][0] = -1;
			t[i][1] = 0;
			int cnt = 0;
			int j = 2;
			while (j < size){
				if (emot[i][j - 1] == emot[i][cnt])t[i][j++] = ++cnt;
				else if (cnt > 0) cnt = t[i][cnt];
				else t[i][j++] = 0;
			}
		}
		for (int i = 0; i < m; i++){
			gets(a);
			for (int p = 0; p < n; p++)current[p] = 0;
			char now;
			size = strlen(a);
			for (int j = 0; j < size; j++){
				now = a[j];
				for (int k = 0; k < n; k++){
					while (current[k]>0 && emot[k][current[k]] != now) current[k] = t[k][current[k]];
					if (emot[k][current[k]] == now){
						current[k]++;
						if (emot[k][current[k]] == 0){
							for (int p = 0; p < n; p++)current[p] = 0;
							a[j] = ' ';
							ans++;
							break;

						}
					}
				}
			}
		}
		printf("%d\n",ans);
	}
}
