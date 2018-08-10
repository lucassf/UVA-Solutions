#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;
#define MAXN 1009

char num[MAXN];
string braile[3];
char conv[10][3][3] = {{".*","**",".."}, {"*.","..",".."}, {"*.","*.",".."}, {"**","..",".."}, {"**",".*",".."},
	{"*.",".*",".."}, {"**","*.",".."}, {"**","**",".."}, {"*.","**",".."}, {".*","*.",".."}};

void ntob(int car, int idx){
	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 3; j++)braile[j].push_back(conv[car][j][i]);
	}
}

int bton(int idx){
	int val = 0;
	for (int j = 0; j < 3; j++){
		for (int i = 0; i < 2; i++){
			val = val * 2 + (braile[j][idx + i] == '*'? 1 : 0);
		}
	}
	if (val == 32)return 1;
	if (val == 40)return 2;
	if (val == 48)return 3;
	if (val == 52)return 4;
	if (val == 36)return 5;
	if (val == 56)return 6;
	if (val == 60)return 7;
	if (val == 44)return 8;
	if (val == 24)return 9;
	if (val == 28)return 0;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int N;
	char cod;
	while (cin >> N, N){
		cin>>cod;
		if (cod == 'S'){
			cin>>num;
			for (int j = 0; j < 3; j++)braile[j].clear();
			for (int i = 0; i < N; i++){
				ntob(num[i] - '0', 3 * i);
				if (i < N - 1){
					for (int j = 0; j < 3; j++)
						braile[j].push_back(' ');
				}
			}
			cout<<braile[0]<<endl<<braile[1]<<endl<<braile[2]<<endl;
		}
		else{
			getline(cin, braile[0]);
			for (int j = 0; j < 3; j++){
				getline(cin, braile[j]);
			}
			for (int i = 0; i < N; i++){
				cout<<bton(3 * i);
			}
			cout<<endl;
		}
	}
}
