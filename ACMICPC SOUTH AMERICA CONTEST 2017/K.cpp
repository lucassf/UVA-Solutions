#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef pair<ll, ll> ii;

#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define MAXN 10009
#define INF 1000000007
#define EPS 1e-9
#define PMOD(a) (a % INF + INF) % INF

int N, M, n, k[MAXN][MAXN][2] = {};
char str[MAXN];
vector<int> adjU[MAXN], U;
int pairU[MAXN], pairV[MAXN];
bool vis[MAXN];

int dirx[4] = {0, 0, 1, -1};
int diry[4] = {1, -1, 0, 0};

bool dfs(int u)
{
    vis[u] = true;
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i){
        v = adjU[u][i];
        if (!vis[pairV[v]] && dfs(pairV[v])){
            pairV[v] = u; pairU[u] = v;
            return true;
        }
    }
    return false;
}

int hungarian()
{
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    for (int u : U){
        memset(&vis, false, sizeof vis);
        if (pairU[u]==0 && dfs(u))
            result++;
    }
    return result;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin>>N>>M;
	int acum = 1;

	FOR(i, N) {
		cin>>str;
		FOR(j, M){
			if (str[j] == '-')k[i][j][0] = acum++, k[i][j][1] = acum++;
			else k[i][j][0] = acum++;
		}
	}
	n = 0;
	FOR(i, N){
		FOR(j, M){
			if ((i + j) % 2) continue;
			FOR(p, 4){
				int x = i + dirx[p];
				int y = j + diry[p];

				if (x < 0 || y < 0 || x >= N || y >= M) continue;

				FOR(s, 2)FOR(t, 2) if (k[i][j][s] && k[x][y][t]){ adjU[k[i][j][s]].push_back(k[x][y][t]);}
			}
			U.push_back(k[i][j][0]);
			if (k[i][j][1]) U.push_back(k[i][j][1]);
		}
	}
	if (hungarian() * 2 == acum - 1) cout<<"Y\n";
	else cout<<"N\n";
}