#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
typedef long long int ll;
typedef pair<int,int> ii;

ll V[MAXN][MAXN];
int R, C;
int vis[MAXN][MAXN];
int movx[4] = {0, 0, 1, -1};
int movy[4] = {1, -1, 0, 0};

void dfs(int i, int j){
	vis[i][j] = 1;
	for (int k = 0; k < 4; k++){
		int x = movx[k] + i;
		int y = movy[k] + j;
		if (x < R && x >= 0 && y < C && y >= 0 && !vis[x][y] && V[x][y] == V[i][j])
			dfs(x, y);
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ll ans;
	
	while (cin>>R>>C){
		for (int i = 0; i < R; i++){
			for (int j = 0; j < C; j++){
				cin>>V[i][j];
			}
		}
		ans = 5;
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < R; i++){
			for (int j = 0; j < C; j++){
				if (!vis[i][j]) dfs(i, j), ans++;
			}
		}
		int dir, ndir, h1, h2, prev1, prev2;
		
		for (int i = 0; i < R - 1; i++){
			dir = prev1 = prev2 = 0;
			for (int j = 0; j < C; j++){
				if (V[i][j] == V[i + 1][j]) ndir = 0, h1 = h2 = V[i][j];
				else if (V[i][j] > V[i + 1][j]) ndir = 1, h1 = V[i][j], h2 = V[i + 1][j];
				else ndir = -1, h1 = V[i + 1][j], h2 = V[i][j];
				
				if (ndir && (ndir != dir || h2 >= prev1 || h1 <= prev2)) ans++;
				dir = ndir;
				prev1 = h1, prev2 = h2;
			}
		}
		for (int j = 0; j < C - 1; j++){
			dir = prev1 = prev2 = 0;
			for (int i = 0; i < R; i++){
				if (V[i][j] == V[i][j + 1]) ndir = 0, h1 = h2 = V[i][j];
				else if (V[i][j] > V[i][j + 1]) ndir = 1, h1 = V[i][j], h2 = V[i][j + 1];
				else ndir = -1, h1 = V[i][j + 1], h2 = V[i][j];
				
				if (ndir && (ndir != dir || h2 >= prev1 || h1 <= prev2)) ans++;
				dir = ndir;
				prev1 = h1, prev2 = h2;
			}
		}
		cout<<ans<<endl;
	}
}