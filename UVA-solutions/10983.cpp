#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000
#define MAXN 100009
#define MAXD 11
#define MAXM 900000

struct trip
{
    int u,v,c,p,e;

    trip(int _u,int _v,int _c,int _p,int _e)
    {
        u=_u,v=_v,c=_c,p=_p,e=_e;
    }
    trip() {}
};

vector<trip> edges;
int n,m,d,zt,source,sink,ned;
int first[MAXM], cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN], prv[MAXN];

void init(){

   memset(first, -1, sizeof first);

   ned = 0;

}



void add(int u, int v, int f){

    to[ned] = v, cap[ned] = f;

    nxt[ned] = first[u];

    first[u] = ned++;



    to[ned] = u, cap[ned] = 0;

    nxt[ned] = first[v];

    first[v] = ned++;

}



int augment(int v, int minEdge, int s) {

	int e = prv[v];

	if (e == -1) return minEdge;

	int f = augment(to[e^1], min(minEdge, cap[e]), s);

	cap[e] -= f;

	cap[e^1] += f;

	return f;

}



bool bfs(int s, int t){

	int u, v;

	memset(&dist, -1, sizeof dist);

	dist[s] = 0;

	queue<int> q; q.push(s);

	memset(&prv, -1, sizeof prv);

	while (!q.empty()) {

		u = q.front(); q.pop();

		if (u == t) break;

		for(int e = first[u]; e!=-1; e = nxt[e]){

			v = to[e];

			if (dist[v] < 0 && cap[e] > 0) {

				dist[v] = dist[u] + 1;

				q.push(v);

				prv[v] = e;

			}

		}

	}

	return dist[t] >= 0;

}



//O(VE^2)

bool edmondskarp(int s, int t){

	int result = 0;

	while (bfs(s, t)) {

		result += augment(t, INF, s);

	}

	return result==zt;

}

void buildGraph(int cost)
{
    trip aux;
    int u,v;

    init();
    for (int i=1; i<=n; i++)
    {
        for (int j=0; j<d; j++)
        {
            u = i*MAXD+j, v = i*MAXD+j+1;
            add(u,v,INF);
        }
    }

    for (int i=0; i<(int)edges.size(); i++)
    {
        aux = edges[i];
        if (aux.p>cost)continue;

        u = aux.u*MAXD+max(aux.e,0),
        v = aux.v*MAXD+aux.e+1;

        add(u,v,aux.c);

    }
    add(n*MAXD+d,sink,INF);
}

int bin_search(int first,int last)
{
    int mid = -1;
    while (first<=last)
    {
        mid = (first+last)/2;
        buildGraph(mid);
        //cout<<mid<<" ";
        if (edmondskarp(source,sink))
        {
            if (last==first)return mid;
            last = mid;
        }
        else first = mid+1;
    }
    return -1;
}

int main()
{
    int t,u,v,c,p,e,tes = 1;
    int z;

    cin>>t;
    while (t-->0)
    {
        cin>>n>>d>>m;
        edges.clear();
        source = 0;
        sink = (n+1)*MAXD;

        for (int i=0; i<m; i++)
        {
            cin>>u>>v>>c>>p>>e;
            //u = i%n, v = (i+1)%n, c = i, p = i, e = i%10;
            edges.push_back(trip(u,v,c,p,e));
        }
        zt = 0;
        for (int i=1; i<=n; i++)
        {
            cin>>z;
            //z = i;
            zt+=z;
            edges.push_back(trip(0,i,z,0,-1));
        }

        int val = bin_search(0,100000);
        if (val!=-1)cout<<"Case #"<<tes++<<": "<<val<<endl;
        else cout<<"Case #"<<tes++<<": Impossible"<<endl;
    }
}
