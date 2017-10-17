#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
#define MAXN 50009

int N,M;
vector<iii> edges;
int resp[MAXN];
vector<int> queries[MAXN];
set<int> values[MAXN];

class UnionFind {
private:
	vector<int> parent, rank;
	set<int>::iterator it;
public:
	UnionFind(int N) {
		rank.assign(N+9, 0);
		parent.assign(N+9, 0);
		for (int i = 0; i < N; i++) {
            parent[i] = i;
            values[i].clear();
            for (int j=0;j<(int)queries[i].size();j++)values[i].insert(queries[i][j]);
		}
	}
	int find(int i) {
		while(i != parent[i]) i = parent[i];
		return i;
	}
	bool isSameSet(int i, int j) {
		return find(i) == find(j);
	}
	void unionSet (int i, int j, int w) {
		if (isSameSet(i, j)) return;
		int x = find(i), y = find(j);
		if (rank[x] < rank[y]) swap(x,y);
		parent[y] = x;
		for (it = values[y].begin();it!=values[y].end();it++){
            int s = *it;
            //cout<<i<<" "<<j<<" "<<s<<endl;
            if (resp[s]==-1){
                if (values[x].count(s)){
                    values[x].erase(s);
                    resp[s] = w;
                }else values[x].insert(s);
            }
		}

        if (rank[x] == rank[y]) rank[x]++;
	}
};

void prim(){
    int w,u,v;
    UnionFind UF(N);

    sort(edges.begin(),edges.end());

    for (int i=M-1;i>=0;i--){
        w = edges[i].first;
        u = edges[i].second.first;
        v = edges[i].second.second;

        UF.unionSet(u,v,w);
    }
}

int main(){
    int S,a,b,w;
    while(scanf("%d%d%d",&N,&M,&S)!=EOF){
        for (int i=0;i<N;i++)queries[i].clear();
        edges.clear();

        for (int i=0;i<M;i++){
            scanf("%d%d%d",&a,&b,&w);
            //a = i%N, b = (i+1)%N, w = i;
            a--,b--;
            edges.push_back(iii(w,ii(a,b)));
        }
        for (int i=0;i<S;i++){
            scanf("%d%d",&a,&b);
            //a = (2*i)%N, b = (3*i)%N;
            a--,b--;
            queries[a].push_back(i), queries[b].push_back(i);
            resp[i] = -1;
        }
        prim();
        for (int i=0;i<S;i++)printf("%d\n",resp[i]);
    }
}
