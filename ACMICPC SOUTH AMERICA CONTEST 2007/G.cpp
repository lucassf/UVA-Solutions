#include <cstdio>
#include <algorithm>
#include <stack>
#include <cstring>

using namespace std;

typedef pair<int, int> p;

bool used[100][101];
char map[100][101];
int working[100][101];
int c,r;

int verify(int i,int j,int value){
	if (value == 0)working[i][j] = 0;
	else if (working[i][j] == value||(map[i][j]=='I'&&value!=3))working[i][j] = value = 0;
	else {
		value = value == 2 ? 3 : 2;
		working[i][j] = value;
	}
	return value;
}

int getElem(int i,int j,int value){
	used[i][j] = true;
	int v=1;
	if (i > 0 && map[i - 1][j] != '.'){
		v = verify(i - 1, j,value);
		if (!used[i - 1][j]){
			v=getElem(i - 1, j,v);
		}
		if (v == 0)value=0;
	}
	if (i > 0 && j<c-1&&map[i - 1][j+1] != '.'){
		v=verify(i - 1, j+1,value);
		if (!used[i - 1][j+1]){
			v=getElem(i - 1, j+1,v);
		}
		if (v == 0)value = 0;
	}
	if (j<c - 1 && map[i][j + 1] != '.'){
		v = verify(i, j+1,value);
		if (!used[i][j+1]){
			v = getElem(i, j+1,v);
		}
		if (v == 0)value = 0;
	}
	if (j>0 && map[i][j - 1] != '.'){
		v=verify(i, j-1,value);
		if (!used[i][j-1]){
			v=getElem(i, j-1,v);
		}
		if (v == 0)value = 0;
	}
	if (i < r-1 && map[i + 1][j] != '.'){
		v=verify(i + 1, j,value);
		if (!used[i + 1][j]){
			v=getElem(i + 1, j,v);
		}
		if (v == 0)value = 0;
	}
	if (i <r-1 && j>0 && map[i + 1][j - 1] != '.'){
		v=verify(i + 1, j - 1,value);
		if (!used[i + 1][j-1]){
			v=getElem(i + 1, j-1,v);
		}
		if (v == 0)value = 0;
	}
	return v;
}

int main(){
	stack<p> u;
	p p;
	while (scanf("%d%d", &r, &c) && r != 0){
		for (int i = 0; i < r; i++){
			scanf("%s", &map[i]);
			for (int j = 0; j < c; j++){
				if (map[i][j] == 'I'){
					working[i][j] = 2;
					used[i][j] = false;
					u.push(make_pair(i, j));
				}
				else if (map[i][j] == '*')working[i][j] = 1, used[i][j] = false;
			}
		}
		while (!u.empty()){
			p = u.top();
			u.pop();
			if (!used[p.first][p.second]){
				if (getElem(p.first, p.second, 2) == 0){
					for (int i = 0; i < r; i++){
						for (int j = 0; j < c; j++){
							used[i][j] = false;
						}
					}
					getElem(p.first, p.second, 0), working[p.first][p.second] = 0;
				}
			}
		}
		printf("\n");
		for (int i = 0; i < r; i++){
			for (int j = 0; j < c; j++){
				if (map[i][j] == '*' || map[i][j] == 'I'){
					if (working[i][j] == 0)map[i][j] = 'B';
					else if (working[i][j] == 1)map[i][j] = 'F';
					else if (working[i][j] == 2)map[i][j] = '(';
					else map[i][j] = ')';
				}
			}
			printf("%s\n",map[i]);
		}
	}
}
