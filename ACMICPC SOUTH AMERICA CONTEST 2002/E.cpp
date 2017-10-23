#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define EPS 1e-9
#define INF 1e9

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

point origin;
point nails[MAXN];
double area[MAXN][MAXN];
int B,N;
point pivot(0,0);

int dir(point a){
    return a.x>=origin.x?1:-1;
}

bool sorte(point a,point b){
    if (dir(a)!=dir(b))return a.x>b.x;
    return ccw(a,origin,b)==0;
}

int leftmostIndex(vector<point> &P){
	int ans = 0;
	for(int i=1; i<(int)P.size(); i++){
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

bool angleCmp(point a, point b){
	if (collinear(pivot, a, b)) return dist(pivot, a) < dist(pivot, b);
	double d1x = a.x-pivot.x, d1y = a.y-pivot.y;
	double d2x = b.x-pivot.x, d2y = b.y-pivot.y;
	return atan2(d1y, d1x) - atan2(d2y, d2x) < 0;
}

vector<point> convexHull(vector<point> P){
	int i, j, n = (int)P.size();
	if (n <= 3){
		if (!(P[0] == P[n-1])) P.push_back(P[0]);
		return P;
	}
	int P0 = leftmostIndex(P);
	swap(P[0], P[P0]);
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.push_back(P[n-1]);
	S.push_back(P[0]);
	S.push_back(P[1]);
	i = 2;
	while(i < n){
		j = (int)S.size()-1;
		if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
		else S.pop_back();
	}
	return S;
}

double signedArea(vector<point> P){
	double result = 0.0;
	for (int i = 0; i < (int)P.size()-1; i++) {
		result += cross(P[i], P[i+1]);
	}
	return fabs(result/2.0);
}

double dp[MAXN][MAXN];

double findAns(int b,int pos,int first){
    if (b==0 && pos==first)return 0;
    if (b==0)return INF;

    if (dp[b][pos]>0)return dp[b][pos];

    int rem = first>pos?first-pos:N-(pos-first);
    //cout<<pos<<" "<<b<<" "<<rem<<endl;
    double ans = INF;
    for (int i=(pos+1)%N;i!=first;i=(i+1)%N){
        if (area[pos][i]<0 || b*2>rem)break;
        ans = min(ans,findAns(b-1,(i+1)%N,first)+area[pos][i]);
        rem--;
    }
    return dp[b][pos] = ans;
}

int main(){
    int x,y;
    double ans;
    vector<point> poly;

    while (scanf("%d%d",&B,&N)&&N!=0){
        scanf("%d%d",&x,&y);
        origin = point(x,y);
        N--;
        for (int i=0;i<N;i++){
            scanf("%d%d",&x,&y);
            nails[i] = point(x,y);
            for (int j=0;j<N;j++)area[i][j] = -1;
        }
        sort(nails,nails+N,sorte);

        for (int i=0;i<N;i++){
            poly.clear();
            poly.push_back(origin);
            poly.push_back(nails[i]);
            //cout<<nails[i].x<<" "<<nails[i].y<<" "<<endl;
            for (int j=(i+1)%N;;j=(j+1)%N){
                if (cross(origin-nails[i],nails[j]-nails[i])>0)break;

                poly.push_back(nails[j]);
                area[i][j] = signedArea(convexHull(poly));
                //cout<<area[i][j]<<" ";
            }//cout<<endl;
        }
        ans = INF;
        for (int i=0;i<N;i++){
            for (int j=0;j<=B;j++)for (int k=0;k<N;k++)dp[j][k] = -1;
            //cout<<i<<"\n\n";
            ans = min(ans,findAns(B,i,i));
            //for (int j=0;j<=B;j++){for (int k=0;k<N;k++)cout<<dp[j][k]<<" ";cout<<endl;}
        }
        printf("%.2lf\n",ans);
    }
}
