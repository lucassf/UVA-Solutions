#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

#define MAXN 50009
#define UNVISITED -1
#define EXPLORED -2
#define VISITED -3

int num[MAXN], vis[MAXN], component[MAXN], low[MAXN];
int N, counter, numSCC;
stack<int> S;
vector<int> adjList[MAXN];

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

bool twosat(){
	tarjan();
	for(int i=0; i<N/2; i++){
		if (component[i]==component[i+N/2]) return false;
	}
	return true;
}

void insertVals(int u,int v,int dir){
    if (u>=0&&v>=0){
        if (dir>0){
            adjList[u+N/2].push_back(v);
            adjList[v+N/2].push_back(u);
        }else{
            adjList[u].push_back(v+N/2);
            adjList[v].push_back(u+N/2);
        }
    }else if (u>=0){
        if (dir>0){
            adjList[u+N/2].push_back(u);
        }else{
            adjList[u].push_back(u+N/2);
        }
    }else if (v>=0){
        if (dir>0){
            adjList[v+N/2].push_back(v);
        }else{
            adjList[v].push_back(v+N/2);
        }
    }
}

int main(){
    int c,p,x,y,s,t;

    while (scanf("%d%d",&c,&p)&&c!=0){
        N = 2*p;

        for (int i=0;i<N;i++)adjList[i].clear();

        for (int i=0;i<c;i++){
            scanf("%d%d%d%d",&x,&y,&s,&t);
            x--,y--,s--,t--;
            insertVals(x,y,1);
            insertVals(s,t,-1);
        }
        if (twosat())printf("yes\n");
        else printf("no\n");
    }
}
