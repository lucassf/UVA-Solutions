#include <bits/stdc++.h>
#define EPS 1e-9
using namespace std;

struct point{
    double x,y;
    point(){x=y=0;}
    point(double _x,double _y){x = _x,y = _y;}
    bool operator ==(point other){
        return fabs(x-other.x)<EPS&&
        fabs(y-other.y)<EPS;
    }
    point operator -(point other) const{
        return point(x-other.x,y-other.y);
    }
    point operator +(point other) const{
        return point(x+other.x,y+other.y);
    }
};

point lineIntersectSeg(point p,point q,point A,point B){
    double a = B.y - A.y;
    double b = A.x - B.x;
    double c = B.x*A.y - A.x*B.y;
    double u = fabs(a*p.x + b*p.y + c);
    double v = fabs(a*q.x + b*q.y + c);
    return point((p.x*v+q.x*u)/(u+v),(p.y*v+q.y*u)/(u+v));
}

double cross(point p1,point p2){
    return p1.x*p2.y-p1.y*p2.x;
}

bool ccw(point p,point q,point r){
    return cross(q-p,r-p)>0;
}

vector<point> cutPolygon(point a,point b,vector<point> P){
    vector<point> R;
    double left1,left2;
    for (int i=0;i<P.size();i++){
        left1 = cross(b-a,P[i]-a);
        if (i!=P.size()-1)left2 = cross(b-a,P[i+1]-a);
        else left2 = 0;
        if (left1 > -EPS)R.push_back(P[i]);
        if (left1*left2<-EPS)R.push_back(lineIntersectSeg(P[i],P[i+1],a,b));
    }
    if (!(R.front()==R.back()))R.push_back(R[0]);
    return R;
}

double area(vector<point> P){
    double result = 0;
    for (int i=0;i<P.size()-1;i++){
        result += (P[i].x*P[i+1].y-P[i+1].x*P[i].y);
    }
    return fabs(result)/2;
}

int main(){
    int n,w,h,x,y,t = 1;
    int x1,y1,x2,y2;
    point goal;
    vector<point> pol;

    while (cin>>n>>w>>h>>x>>y){
        pol.clear();
        pol.push_back(point(0,0));
        pol.push_back(point(0,h));
        pol.push_back(point(w,h));
        pol.push_back(point(w,0));
        pol.push_back(point(0,0));
        goal = point(x,y);

        for (int i=0;i<n;i++){
            cin>>x1>>y1>>x2>>y2;
            point a = point(x1,y1);
            point b = point(x2,y2);
            if (ccw(a,b,goal))pol = cutPolygon(a,b,pol);
            else pol = cutPolygon(b,a,pol);
            //for (int i=0;i<pol.size();i++)cout<<pol[i].x<<" "<<pol[i].y<<endl;
            //cout<<endl;
        }
        printf("Case #%d: %.3lf\n",t++,area(pol));
    }
}
