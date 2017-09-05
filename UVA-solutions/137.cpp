#include <bits/stdc++.h>
#define _USE_MATH_DEFINES
#define EPS 10e-9
#define INF 10e9
using namespace std;

struct point{
    double x,y;
    point(){x=y=0;}
    point(double _x,double _y){x=_x,y=_y;}
    bool operator <(point other) const{
        if (fabs(x-other.x)>EPS)return x<other.x;
        return y<other.y;
    }bool operator ==(point other) const{
        return (fabs(x-other.x)<EPS)&&
        (fabs(y-other.y)<EPS);
    }
    point operator +(point other) const{
        return point(x+other.x,y+other.y);
    }point operator -(point other) const{
        return point(x-other.x,y-other.y);
    }
};

vector<point> pol;

double dist(point p1, point p2){
    return hypot(p1.x-p2.x,p1.y-p2.y);
}

double inner(point p1,point p2){
    return p1.x*p2.x+p1.y*p2.y;
}

double cross(point p1,point p2){
    return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p,point q,point r){
    return cross(p-q,r-p)>0;
}

double angle(point a,point o,point b){
    return acos(inner(a-o,b-o)/(dist(o,a)*dist(o,b)));
}

bool inLineSegment(point a,point b,point p){
    point s = p-a;
    point t = b - p;
    return (s.x*t.x>-EPS)&&(s.y*t.y>-EPS)&&fabs(cross(s,t))<EPS;
}

point lineIntersects(point a,point b,point u,point v){
    point t1 = b-a;
    point t2 = v-u;

    double p = cross(t1,t2);
    if (fabs(p)<EPS){
        return point(INF,INF);
    }double k = cross(u-a,t2)/p;
    double q = cross(u-a,t1)/p;
    if (k>0&&k<1&&q>0&&q<1)return a+point(k*t1.x,k*t1.y);
    return point(INF,INF);
}

void lineIntersects(point a,point b,vector<point> P){
    for (int i=0;i<P.size()-1;i++){
        point q = lineIntersects(a,b,P[i],P[i+1]);
        if (abs(q.x)<INF)pol.push_back(q);
    }
}

bool inPolygon(point pt,vector<point> P){
    if (P.size()==0)return false;
    double sum = 0;
    for (int i=0;i<P.size()-1;i++){
        if (inLineSegment(P[i],P[i+1],pt))return true;
        if (ccw(pt,P[i],P[i+1]))sum+=angle(P[i],pt,P[i+1]);
        else sum-= angle(P[i],pt,P[i+1]);
    }
    return fabs(fabs(sum)-2*M_PI)<EPS;
}

vector<point> convexHull(vector<point> T){
    vector<point> res,P;
    int n=T.size();
    if (n<3)return res;
    sort(T.begin(),T.end());
    P.push_back(T[0]);
    for (int i=1;i<T.size();i++){
        if (T[i]==T[i-1])continue;
        P.push_back(T[i]);
    }
    n = P.size();
    res.push_back(P[0]);
    res.push_back(P[1]);
    int j,k=2;
    for (int i=2;i<n;i++){
        while (k>1&&!ccw(res[k-2],res[k-1],P[i]))res.pop_back(),k--;
        res.push_back(P[i]),k++;
    }j = res.size();
    res.push_back(P[n-2]);
    k++;
    for (int i=n-3;i>=0;i--){
        while (k>j&&!ccw(res[k-2],res[k-1],P[i]))res.pop_back(),k--;
        res.push_back(P[i]),k++;
    }
    return res;
}

double area(vector<point> P){
    double result = 0;

    for (int i=0;i<(int)P.size()-1;i++){
        result+=(P[i].x*P[i+1].y-P[i+1].x*P[i].y);
    }
    return fabs(result)/2;
}

void printpol(){
    for (int i=0;i<pol.size();i++){
        cout<<pol[i].x<<" "<<pol[i].y<<endl;
    }
    cout<<endl;
}

int main(){
    int n,x,y;
    vector<point> pol1,pol2;
    while (cin>>n&&n!=0){
        pol1.clear();
        pol2.clear();
        pol.clear();
        for (int i=0;i<n;i++){
            cin>>x>>y;
            pol1.push_back(point(x,y));
        }pol1.push_back(pol1[0]);
        cin>>n;
        for (int i=0;i<n;i++){
            cin>>x>>y;
            pol2.push_back(point(x,y));
        }pol2.push_back(pol2[0]);

        for (int i=0;i<pol1.size()-1;i++){
            if (inPolygon(pol1[i],pol2))pol.push_back(pol1[i]);
            lineIntersects(pol1[i],pol1[i+1],pol2);
        }//printpol();
        for (int i=0;i<pol2.size()-1;i++){
            if (inPolygon(pol2[i],pol1))pol.push_back(pol2[i]);
        }
        //printpol();
        pol = convexHull(pol);
        //printpol();
        double res = area(pol1)+area(pol2)-2*area(pol);
        printf("%8.2lf",res);
    }
    printf("\n");
}
