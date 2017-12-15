//Cortesy of Lucas França de Oliveira

#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define MAXN 100
#define MAXM 2000
typedef pair<int,int> ii;
typedef pair<int,double> di;
typedef pair<double,ii> dii;

int N,M,L,FINAL,START;
double INF = 10000000000009;

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	bool operator < (point other) const {
		if (x == other.x) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point other) const {
		return x == other.x && y == other.y;
	}
	point operator +(point other) const{
		return point(x + other.x, y + other.y);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y);
	}
	point operator *(double k) const{
		return point(x*k, y*k);
	}
};

double getDist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) < -EPS;
}

bool lineIntersectSeg(point p, point q, point A, point B) {
	if (fabs(cross(p-q, A-B)) < EPS) return false;
	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = abs(a * p.x + b * p.y + c);
	double v = abs(a * q.x + b * q.y + c);
	point inter = point(p.x * v + q.x * u, p.y * v + q.y * u)*(1.0/(u+v));
	return between(A, inter, B);
}

vector<point> edges;
vector<di> adjList[MAXM];

bool isT(int i){
    return i>2*M&&i!=FINAL;
}

void buildGraph(){
    bool poss;
    double dist;

    for (int i=0;i<=FINAL;i++)adjList[i].clear();
    for (int i=0;i<=FINAL;i++){
        for (int j=i+1;j<=FINAL;j++){
            poss = true;
            for (int k=1;k<=2*M;k+=2){
                if (i!=k&&i!=k+1&&j!=k&&j!=k+1&&
                        lineIntersectSeg(edges[i],edges[j],edges[k],edges[k+1])){
                    poss = false;
                    break;
                }
            }if (poss){
                //cout<<i<<" "<<j<<endl;
                dist = (isT(i)&&isT(j))?0:getDist(edges[i],edges[j]);
                adjList[i].push_back(di(j,dist));
                adjList[j].push_back(di(i,dist));
            }
        }
    }
}

double solve(){
    double val[MAXN][MAXM],dist,d;
    bool vis[MAXN][MAXM];
    int u,v,n,n1;

    priority_queue<dii> inuse;
    inuse.push(dii(0,ii(0,N)));
    memset(vis,false,sizeof(vis));
    for (int j=0;j<MAXN;j++)for(int i=0;i<MAXM;i++)val[j][i] = INF;
    val[N][0] = 0;

    while (!inuse.empty()){
        dist = -inuse.top().first;
        u = inuse.top().second.first;
        n = inuse.top().second.second;
        inuse.pop();
        //cout<<endl<<"State: "<<n<<" "<<u<<" "<<dist<<endl<<endl;

        if (vis[n][u])continue;
        if (u==FINAL)break;

        vis[n][u] = true;

        for (int i=0;i<(int)adjList[u].size();i++){
            v = adjList[u][i].first;
            d = adjList[u][i].second+dist;
            n1 = isT(u)&&isT(v)?n-1:n;

            //cout<<n1<<" "<<v<<" "<<d<<" "<<endl;

            if (n1>=0&&!vis[n1][v]&&d<val[n1][v]){
                val[n1][v] = d;
                inuse.push(dii(-d,ii(v,n1)));
            }
        }
    }
    return dist;
}

int main(){
    int x1,y1,x2,y2;
    while (scanf("%d%d%d",&N,&M,&L),N|M|L){
        START = 0;
        FINAL = 2*M+L+1;

        edges.assign(2*M+L+2,point(0,0));

        for (int i=1;i<=M;i++){
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            edges[2*i-1] = point(x1,y1);
            edges[2*i] = point(x2,y2);
        }for (int i=1;i<=L;i++){
            scanf("%d%d",&x1,&y1);
            edges[2*M+i] = point(x1,y1);
        }
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        edges[START] = point(x1,y1);
        edges[FINAL] = point(x2,y2);
        buildGraph();
        printf("%.0lf\n",solve());
    }
}
