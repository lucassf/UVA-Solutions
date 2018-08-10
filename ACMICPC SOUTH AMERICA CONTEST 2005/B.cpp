#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 1e9
#define EPS 1e-9

struct point {
	double x, y;
	point() { x = y = 0.0; }
	point(double _x, double _y) : x(_x), y(_y) {}
	double norm(){
		return hypot(x, y);
	}
	point normalized(){
		return point(x,y)*(1.0/norm());
	}
	double angle(){ return atan2(y, x);	}
	double polarAngle(){
		double a = atan2(y, x);
		return a < 0 ? a + 2*M_PI : a;
	}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else return y < other.y;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
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

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > EPS;
}

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double angle(point a, point o, point b) {
	return acos(inner(a-o, b-o) / (dist(o,a)*dist(o,b)));
}

point closestToLineSegment(point p, point a, point b) {
	double u = inner(p-a, b-a) / inner(b-a, b-a);
	if (u < -EPS) return a;
	if (u > 1.0) return b;
	return a + ((b-a)*u);
}

double distToLineSegment(point p, point a, point b) {
	return dist(p, closestToLineSegment(p, a, b));
}

struct circle{
	point c;
	double r;
	circle(){ c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	bool intersects(circle other){
		return dist(c, other.c) <= r + other.r;
	}
	bool contains(point p) { return dist(c, p) <= r + EPS; }
};

int B,N,M;
vector<point> informers;
vector<point> border;
vector<circle> radar;
vector<point> poly;
vector<int> adjList[MAXN];
vector<int> vis;
vector<int> seq;
bool isValid[MAXN];

inline double insiderCoef(point p){
    double ans = INF;
    point a,b;

    for (int i=1;i<border.size();i++){
        a = border[i-1], b = border[i];
        ans = min(ans,distToLineSegment(p,a,b));
    }
    return ans;
}

inline bool inPolygon(vector<point> & P, point p) {
	if (P.size() == 0u) return false;
	double sum = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) {
		if (ccw(p, P[i], P[i+1])) sum += angle(P[i], p, P[i+1]);
		else sum -= angle(P[i], p, P[i+1]);
	}
	return fabs(fabs(sum) - 2*M_PI) <= EPS;
}

inline void verifyInsiders(){
    for (int i=0;i<N;i++){
        if (!isValid[i])continue;
        if (inPolygon(poly,informers[i]))isValid[i]=false;
    }
}

void dfs(int u){
    int v;
    vis[u] = 1;
    seq.push_back(u);
    for (int i=0;i<(int)adjList[u].size();i++){
        v = adjList[u][i];

        if (!vis[v])dfs(v);
        else{
            poly.clear();
            int j = 0;
            while(j<(int)seq.size()&&seq[j]!=v)j++;
            while(j<(int)seq.size()){
                //cout<<seq[j]<<" ";
                poly.push_back(radar[seq[j++]].c);
            }//cout<<endl;
            poly.push_back(radar[v].c);
            if (poly.size()<4)continue;
            verifyInsiders();
        }
    }
    seq.pop_back();
}

int main(){
    int x,y,r;
    while (scanf("%d",&B)){
        informers.clear();
        border.clear();
        radar.clear();

        for (int i=0;i<B;i++){
            scanf("%d%d",&x,&y);
            border.push_back(point(x,y));
        }
        if (B>0)border.push_back(border[0]);
        scanf("%d",&N);
        for (int i=0;i<N;i++){
            scanf("%d%d",&x,&y);
            informers.push_back(point(x,y));
            isValid[i] = true;
        }
        scanf("%d",&M);
        bool found;
        for (int i=0;i<M;i++){
            scanf("%d%d%d",&x,&y,&r);
            found = false;
            point c = point(x,y);
            for (int j=0;j<(int)radar.size();j++){
                if (c==radar[j].c){
                    radar[j].r = max(radar[j].r,(double)r);
                    i--,M--;
                    found = true;
                    break;
                }
            }if (found)continue;
            radar.push_back(circle(c,r));
            adjList[i].clear();
        }
        if (N==0&&M==0&&B==0)break;

        for (int i=0;i<M;i++){
            for (int j=i+1;j<M;j++){
                if (radar[i].intersects(radar[j])){
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
            for (int j=0;j<N;j++){
                if (radar[i].contains(informers[j]))isValid[j] = false;
            }
        }
        vis.assign(M,0);
        for (int i=0;i<M;i++)
            if (!vis[i])dfs(i);

        int ans = -1;
        double aux, best = -1;
        for (int i=0;i<N;i++){
            if (!isValid[i])continue;
            aux = insiderCoef(informers[i]);
            //cout<<i<<" "<<aux<<endl;
            if (aux>best){
                best = aux;
                ans = i+1;
            }
        }

        if (ans==-1)printf("Mission impossible\n");
        else printf("Contact informer %d\n",ans);
    }
}

