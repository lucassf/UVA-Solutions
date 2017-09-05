#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
typedef vector<int> vi;

int N,M;

class UnionFind { // OOP style
private: vi p, rank; // remember: vi is vector<int>
public:
    void reset(int N) {
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++) p[i] = i;
    }
    int findSet(int i) {
        return (p[i] == i) ? i : (p[i] = findSet(p[i]));
    }
    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) { // if from different set
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) p[y] = x; // rank keeps the tree short
            else { p[x] = y;
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }
};

int values[3] = {1235,8977,10923};
int vals[MAXN][MAXN];
UnionFind un;

int solve(){
    int ans = 0;
    int w;

    for (int k=0;k<3;k++){
        w = values[k];
        for (int i=0;i<N;i++){
            for (int j=i+1;j<N;j++){
                if (vals[i][j]==w&&!un.isSameSet(i,j)){
                    un.unionSet(i,j);
                    ans+=w;
                }
            }
        }
    }
    return ans;
}

int main(){
    int c = 1;
	while(scanf("%d %d", &N, &M)!=EOF){
        int u, v, w;
        un.reset(N);
        for (int i=0;i<N;i++)for (int j=0;j<N;j++)vals[i][j]=100000000;
        for (int i = 0; i < M; i++) {
            scanf("%d %d %d", &u, &v, &w);
            u--,v--;
            vals[u][v] = vals[v][u] = min(w,vals[u][v]);
        }
        printf("Instancia %d\n",c++);
        printf("%d\n\n", solve());
    }
}

