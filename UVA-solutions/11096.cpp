#include <bits/stdc++.h>
using namespace std;
#define EPS 10e-10

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

double dist(point p1,point p2){
    return hypot(p1.x-p2.x,p1.y-p2.y);
}

double cross(point p1,point p2){
    return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p,point q,point r){
    return cross(p-q,r-p)>0;
}

double perimeter(vector<point> P){
    double result = 0;
    for (int i=0;i<(int)P.size()-1;i++){
        result+=dist(P[i],P[i+1]);
    }return result;
}

vector<point> convexHull(vector<point> P){
    vector<point> res;
    int n;
    sort(P.begin(),P.end());
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

int main(){
    int n,l,p,x,y;
    vector<point> P;
    cin>>n;
    for (int c=0;c<n;c++){
        P.clear();
        cin>>l>>p;
        for (int i=0;i<p;i++){
            cin>>x>>y;
            P.push_back(point(x,y));
        }
        P = convexHull(P);
        printf("%.5lf\n",max(perimeter(P),(double)l));
    }
}
