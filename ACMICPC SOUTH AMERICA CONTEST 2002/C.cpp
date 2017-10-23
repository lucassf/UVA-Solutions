#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9
#define INF 1e9
#define MAXN 1009
typedef pair<double,int> di;

int N;

struct point{
    double x,y;
    point(){}
    point(double _x,double _y){x=_x,y=_y;}

    point operator+(point other)const{
        return point(x+other.x,y+other.y);
    }
    point operator-(point other)const{
        return point(x-other.x,y-other.y);
    }
    point operator*(double k)const{
        return point(x*k,y*k);
    }
};
typedef pair<point,point> seg;

double inner(point p1,point p2){
    return p1.x*p2.x+p1.y*p2.y;
}

double dist(point p1,point p2){
    return hypot(p1.x-p2.x,p1.y-p2.y);
}

double cross(point p1,point p2){
    return p1.x*p2.y-p1.y*p2.x;
}

bool collinear(point p,point q,point r){
    return fabs(cross(p-q,r-p))<EPS;
}

bool between(point p,point q,point r){
    return collinear(p,q,r)&&inner(p-q,r-q)<EPS;
}

point closestToLineSegment(point p,point a,point b){
    double u = inner(p-a,b-a)/inner(b-a,b-a);
    if (u<0.0)return a;
    if (u>1.0)return b;
    return a+((b-a)*u);
}

double distToLineSegment(point p,point a,point b){
    point c = closestToLineSegment(p,a,b);
    return dist(p,c);
}

bool segIntersects(point a,point b,point p,point q){
    point u = b-a, v = q-p;
    if (fabs(cross(v,u))<EPS)return between(a,p,b)||between(a,q,b);
    double k1 = (cross(a,u)-cross(p,u))/cross(v,u);
    double k2 = (cross(a,v)-cross(p,v))/cross(v,u);
    return k1>=0&&k1<=1&&k2>=0&&k2<=1;
}

double calcDist(seg s1,seg s2){
    if (segIntersects(s1.first,s1.second,s2.first,s2.second))return 0;
    double u = min(distToLineSegment(s1.first,s2.first,s2.second),distToLineSegment(s1.second,s2.first,s2.second));
    double v = min(distToLineSegment(s2.first,s1.first,s1.second),distToLineSegment(s2.second,s1.first,s1.second));
    return min(u,v);
}

vector<seg> segs;
double dists[MAXN][MAXN];

int main(){
    int x,y,dir;
    point p1,p2;

    priority_queue<di> inuse;
    double value[MAXN];
    bool used[MAXN];

    while (scanf("%d",&N)&&N!=0){
        segs.clear();
        for (int i=0;i<N;i++){
            scanf("%d%d%d",&x,&y,&dir);
            p1 = point(x,y);
            if (dir<0)p2 = point(x,y-dir);
            else if (dir==0)p2 = point(INF,INF);
            else p2 = point(x+dir,y);
            segs.push_back(seg(p1,p2));

            value[i] = INF;
            used[i] = false;
            for (int j=0;j<i;j++){
                if (segs[j].second.x>=INF-1){
                    if (segs[i].second.x>=INF-1)dists[i][j] = dists[j][i] = dist(segs[i].first,segs[j].first);
                    else dists[i][j] = dists[j][i] = distToLineSegment(segs[j].first,segs[i].first,segs[i].second);
                }else if (segs[i].second.x>=INF-1){
                    dists[i][j] = dists[j][i] = distToLineSegment(segs[i].first,segs[j].first,segs[j].second);
                }
                else dists[i][j] = dists[j][i] = calcDist(segs[i],segs[j]);
                //cout<<dists[i][j]<<" ";
            }//cout<<endl;
        }
        inuse.push(di(0,0));
        value[0] = 0;
        while (!inuse.empty()){
            double d = -inuse.top().first;
            int index = inuse.top().second;
            inuse.pop();

            if (used[index])continue;
            if (index==1)break;

            used[index] = true;

            for (int i=1;i<N;i++){
                if (!used[i]&&max(d,dists[index][i])<value[i]){
                    value[i] = max(d,dists[index][i]);
                    inuse.push(di(-value[i],i));
                }
            }
        }
        while (!inuse.empty())inuse.pop();
        printf("%.2lf\n",value[1]+EPS);
    }
}
