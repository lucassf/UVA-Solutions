#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

#define MAXN 4009
#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3

int num[MAXN], vis[MAXN], component[MAXN], low[MAXN];
int value[MAXN], N, M, counter, root, numSCC;
stack<int> S;
vector<int> adjList[MAXN], toposort, C[MAXN];
set<int> adjComp[MAXN];
bool adj[MAXN][MAXN];

void dfs(int u) {
	low[u] = num[u] = counter++;
	S.push(u);
	vis[u] = 1;
	int v;
	for (int j = 0; j < (int)adjList[u].size(); j++) {
		v = adjList[u][j];
		if (num[v] == UNVISITED) dfs(v);
		if (vis[v]) low[u] = min(low[u], low[v]);
	}
	if (low[u] == num[u]) {
		while (true) {
			v = S.top(); S.pop(); vis[v] = 0;
			component[v] = numSCC;
			if (u == v) break;
		}
		numSCC++;
	}
}

void tarjan(){
	counter = numSCC = 0;
	memset(&num, UNVISITED, sizeof num);
	memset(&vis, 0, sizeof vis);
	memset(&low, 0, sizeof low);
	for (int i = 0; i < N; i++){
		if (num[i] == UNVISITED)
			dfs(i);
	}
}

void ts(int u){
	vis[u] = VISITED;
	set<int>::iterator it;
	for(it = adjComp[u].begin(); it!=adjComp[u].end(); it++){
		if (vis[*it] == UNVISITED) dfs(*it);
	}
	toposort.push_back(u);
}

bool ffill(int u, int k){
	value[u] = k;
	int v = (u>=N/2 ? u-N/2 : u+N/2);
	if (value[v] == value[u]) return false;
	if (value[v] == -1 && !ffill(v, 1-k)) return false;
	for(int i=0; i<(int)adjList[u].size(); i++){
		v = adjList[u][i];
		if (value[v] == 0 && k == 1) return false;
		if (value[v] == -1 && (component[u] == component[v]
			|| k == 1) && !ffill(v, k)) return false;
	}
	return true;
}

bool twosat(){
	tarjan();
	for (int i=0;i<N;i++)C[i].clear(), adjComp[i].clear();
	for(int i=0; i<N/2; i++){
		if (component[i]==component[i+N/2]) return false;
	}
	for(int u=0, v; u<N; u++){
		C[component[u]].push_back(u);
		for(int i=0; i<(int)adjList[u].size(); i++){
			v = adjList[u][i];
			if (component[u] != component[v])
				adjComp[component[u]].insert(component[v]);
		}
	}
	memset(&vis, UNVISITED, sizeof vis);
	toposort.clear();
	for(int i=0; i<numSCC; i++){
		if (vis[i] == UNVISITED) ts(i);
	}
	memset(&value, -1, sizeof value);
	for(int i=0, c, u; i<(int)toposort.size(); i++){
		c = toposort[i];
		for(int j=0; j<(int)C[c].size(); j++){
			u = C[c][j];
			if (value[u] == -1 && !ffill(u, 1))
				return false;
		}
	}
	return true;
}

int main(){
    int t,k,c=1,pos1,pos2,x1,x2;
    int knot1,knot2;
    string s1,s2;
    map<string,int> pos;
    queue<ii> edges;
    ii val1,val2;

    while(scanf("%d",&t)!=EOF){
        pos.clear();
        k = 0;
        for (int i=0;i<t;i++){
            cin>>s1>>s2;
            knot1=knot2=0;
            if (s1[0]=='!')knot1 = 1, s1=s1.substr(1,s1.size()-1);
            if (s2[0]=='!')knot2 = 1, s2=s2.substr(1,s2.size()-1);

            if (!pos.count(s1))pos[s1]=k++;
            if (!pos.count(s2))pos[s2]=k++;
            edges.push(ii(pos[s1],knot1));
            edges.push(ii(pos[s2],knot2));
        }
        N = 2*k;
        for (int i=0;i<N;i++){
            adjList[i].clear();
            for (int j=0;j<N;j++)adj[i][j]=false;
        }
        while (!edges.empty()){
            val1 = edges.front();
            edges.pop();
            val2 = edges.front();
            edges.pop();

            pos1 = (val1.second==1?N/2:0)+val1.first;
            pos2 = (val2.second==1?N/2:0)+val2.first;
            x1 = pos1>=N/2?pos1-N/2:pos1+N/2;
            x2 = pos2>=N/2?pos2-N/2:pos2+N/2;

            if (!adj[pos1][pos2]){
                adjList[x1].push_back(pos2);
                adjList[x2].push_back(pos1);
                adj[pos1][pos2] = adj[pos2][pos1] = true;
            }
        }/*for (int i=0;i<N;i++){
            cout<<i<<": ";
            for (int j=0;j<(int)adjList[i].size();j++){
                cout<<adjList[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<N<<endl;*/

        printf("Instancia %d\n",c++);
        if (twosat())printf("sim\n\n");
        else printf("nao\n\n");
    }

}
