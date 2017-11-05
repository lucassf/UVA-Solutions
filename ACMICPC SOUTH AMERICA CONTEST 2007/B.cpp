#include <bits/stdc++.h>
using namespace std;
typedef pair<double,double> dd;
#define INF 1e9
#define EPS 1e-9

int L,C,X,Y;

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

double dist(point p1, point p2) {
	return hypot(p1.x - p2.x, p1.y - p2.y);
}

double inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

double cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

bool ccw(point p, point q, point r) {
	return cross(q-p, r-p) > 0;
}

bool collinear(point p, point q, point r) {
	return fabs(cross(p-q, r-p)) < EPS;
}

point rotate(point p, double rad) {
	return point(p.x * cos(rad) - p.y * sin(rad),
	p.x * sin(rad) + p.y * cos(rad));
}

double angle(point a, point o, point b) {
	return acos(inner(a-o, b-o) / (dist(o,a)*dist(o,b)));
}

point proj(point u, point v){
	return v*(inner(u,v)/inner(v,v));
}

bool between(point p, point q, point r) {
    return collinear(p, q, r) && inner(p - q, r - q) <= 0;
}

struct circle{
	point c;
	double r;
	circle(){ c = point(); r = 0; }
	circle(point _c, double _r) : c(_c), r(_r) {}
	double area() { return M_PI*r*r; }
	double chord(double rad) { return  2*r*sin(rad/2.0); }
	double sector(double rad) { return 0.5*rad*area()/M_PI; }
	bool intersects(circle other){
		return dist(c, other.c) < r + other.r;
	}
	bool contains(point p) { return dist(c, p) <= r + EPS; }

	pair<point,point> getTangentPoint(point p){
        double d1 = dist(p,c);
        double theta = asin(r/d1);
        point p1 = rotate(c-p,-theta);
        point p2 = rotate(c-p,theta);
        p1 = p1*(sqrt(d1*d1-r*r)/d1)+p;
        p2 = p2*(sqrt(d1*d1-r*r)/d1)+p;

        return make_pair(p1,p2);
    }
};

typedef pair<point,point> line;
point auxP;

bool segIntersects(point a,point b,point p,point q){
    point u = b-a, v = q-p;
    if (fabs(cross(v,u))<EPS) return false;
    double k1 = (cross(a,v)-cross(p,v))/cross(v,u);
    double k2 = (cross(a,u)-cross(p,u))/cross(v,u);
    auxP = a+u*k1;
    //cout<<auxP.x<<" "<<auxP.y<<endl;
    return k1 >= 0 && k1 < 1 && k2 >= 0;
}

vector<point> bulbs;
vector<circle> collumns;
line borders[4];

set<dd> segs[4];
set<dd> interv[4];

void merges(set<dd> &segs){
    set<dd> ans;
    set<dd>::iterator it,aux;

    double l,r;

    for (it=segs.begin();it!=segs.end();){
        l = (*it).first;
        r = (*it).second;
        aux = it;
        aux++;
        segs.erase(it);
        it = aux;
        while (it!=segs.end() && (*it).first<=r){
            r = max(r,(*it).second);
            aux = it;
            aux++;
            segs.erase(it);
            it = aux;
        }
        segs.insert(dd(l,r));
    }
}

set<dd> invert(set<dd> &segs,double r){
    set<dd> ans;
    double l = 0;

    set<dd>::iterator it;

    for (it=segs.begin();it!=segs.end();it++){
        ans.insert(dd(l,(*it).first));
        l = (*it).second;
    }
    ans.insert(dd(l,r));
    return ans;
}

void printInterval(set<dd> &segs){
    for (set<dd>::iterator it=segs.begin();it!=segs.end();it++){
        cout<<(*it).first<<" "<<(*it).second<<" . ";
    }
    cout<<endl;
}

void compute(int index){
    set<dd> vals[4];
    int p1,p2;
    double w1,w2,t;

    for (int i=0;i<4;i++)interv[i].clear();

    for (int i=0;i<C;i++){
        pair<point,point> inters = collumns[i].getTangentPoint(bulbs[index]);
        //cout<<"p1: "<<inters.first.x<<" "<<inters.first.y<<endl;
        //cout<<"p2: "<<inters.second.x<<" "<<inters.second.y<<endl;
        for (int j=0;j<4;j++){
                //cout<<j<<":"<<endl;
            if (segIntersects(borders[j].first,borders[j].second,bulbs[index],inters.first)){
                p1 = j, w1 = j%2==0?auxP.x:auxP.y;
                break;
            }
        }for (int j=0;j<4;j++){
            if (segIntersects(borders[j].first,borders[j].second,bulbs[index],inters.second)){
                p2 = j, w2 = j%2==0?auxP.x:auxP.y;
                break;
            }
        }//cout<<w1<<" "<<w2<<" "<<p1<<" "<<p2<<endl;
        if (p1==p2){
            interv[p1].insert(dd(min(w1,w2),max(w1,w2)));
        }else{
            if (p1==0||p1==1)t = 0;
            else if (p1==2)t = X;
            else t = Y;
            //cout<<t<<endl;
            interv[p1].insert(dd(min(t,w1),max(t,w1)));
            p1 = (p1+1)%4;
            while (p1!=p2){
                interv[p1].insert(dd(0,p1%2==0?X:Y));
                p1 = (p1+1)%4;
            }
            if (p1==0)t = X;
            else if (p1==1)t = Y;
            else t = 0;
            //cout<<t<<endl;
            interv[p1].insert(dd(min(t,w2),max(t,w2)));
        }//for (int j=0;j<4;j++){cout<<j<<": ";printInterval(interv[j]);}
    }for (int i=0;i<4;i++){
        merges(interv[i]);
        //cout<<i<<": ";printInterval(interv[i]);
        interv[i] = invert(interv[i],i%2==0?X:Y);
        //cout<<i<<": ";printInterval(interv[i]);
        segs[i].insert(interv[i].begin(),interv[i].end());
    }
}

int main(){
    int x,y,r;

    while (scanf("%d%d%d%d",&L,&C,&X,&Y)&&L!=0){
        bulbs.clear();
        collumns.clear();

        borders[0] = line(point(0,Y),point(X,Y));
        borders[1] = line(point(0,0),point(0,Y));
        borders[2] = line(point(X,0),point(0,0));
        borders[3] = line(point(X,Y),point(X,0));

        for (int i=0;i<4;i++)segs[i].clear();
        for (int i=0;i<L;i++){
            scanf("%d%d",&x,&y);
            bulbs.push_back(point(x,y));
        }for (int i=0;i<C;i++){
            scanf("%d%d%d",&x,&y,&r);
            collumns.push_back(circle(point(x,y),r));
        }
        for (int i=0;i<L;i++){
            compute(i);
        }
        double ans = 0;
        for (int i=0;i<4;i++){
            merges(segs[i]);
            for (set<dd>::iterator it = segs[i].begin();it!=segs[i].end();it++){
                ans+=(*it).second-(*it).first;
            }
        }
        printf("%.4lf\n",ans);
    }
}
