#include <bits/stdc++.h>
#define EPS 1e-9
#define _USE_MATH_DEFINES
using namespace std;

struct point{
    double x,y;

    point(){x=y=0.0;}
    point(double _x,double _y){x = _x,y=_y;}
    bool operator <(point other)const{
        if (fabs(x-other.x)>EPS)return x<other.x;
        return y<other.y;
    }

    point rotate(point p,double rad){
        return point(x+p.x*cos(rad)-p.y*sin(rad),y+p.x*sin(rad)+p.y*cos(rad));
    }
};

bool ccw(point a,point b,point c){
    return (c.y-b.y)*(b.x-a.x)<(c.x-b.x)*(b.y-a.y);
}

vector<point> convexHull(vector<point> P){
    sort(P.begin(),P.end());
    vector<point> res;
    int n = P.size();
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
    int n,t;
    double x,y,w,h,angle;
    vector<point> vec,sol;
    cin>>t;
    point aux;
    double used;
    while (t>0){
        cin>>n;
        vec.clear();
        used=0;
        for (int i=0;i<n;i++){
            cin>>x>>y>>w>>h>>angle;
            angle = -(angle*M_PI)/180;

            aux = point(x,y);
            vec.push_back(aux.rotate(point(w/2,h/2),angle));
            vec.push_back(aux.rotate(point(-w/2,h/2),angle));
            vec.push_back(aux.rotate(point(w/2,-h/2),angle));
            vec.push_back(aux.rotate(point(-w/2,-h/2),angle));
            used+=w*h;
        }
        sol = convexHull(vec);
        //for (int i=0;i<sol.size();i++)cout<<sol[i].x<<" "<<sol[i].y<<endl;
        double result = 0;
        int n = sol.size();
        for (int i=0;i<n-1;i++){
            result+=(sol[i].x*sol[i+1].y-sol[i+1].x*sol[i].y);
        }
        printf("%.1lf %%\n",100*used/(fabs(result/2)));
        t--;
    }
}
