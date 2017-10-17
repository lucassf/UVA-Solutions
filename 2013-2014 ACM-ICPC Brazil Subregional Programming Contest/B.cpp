#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <cstdio>
using namespace std;
typedef long long int ll;
#define MAXN 300009
#define INF 1000000009

int N,C,K;

struct point{
    ll x,y;
    int type,num;

    point(){}
    point(ll _x,ll _y){
        x = _x, y = _y;
    }
    point(ll _x,ll _y,int _type,int _num){
        x = _x, y = _y, type = _type, num = _num;
    }
    point operator -(point other)const{
        return point(x-other.x,y-other.y);
    }
    bool operator<(point other)const{
        if (x!=other.x)return x<other.x;
        if (type!=other.type) return type<other.type;
        return y<other.y;
    }
};
typedef pair<point,point> seg;

ll cross(point p1,point p2){
    return p1.x*p2.y - p1.y*p2.x;
}

point p[MAXN];
seg segs[MAXN];

bool cmp(int a,int b){
    point ap1 = segs[a].first, ap2 = segs[a].second;
    point bp1 = segs[b].first, bp2 = segs[b].second;

    if (ap1.x<bp1.x)return cross(ap1-bp1,ap2-bp1)>0;
    return cross(bp1-ap1,bp2-ap1)<0;
}

set<int,bool(*)(int,int)> inuse(cmp);
set<int,bool(*)(int,int)>::iterator it;
int nxt[MAXN], pnxt[MAXN];
point dp[MAXN];

int getNxt(int n){
    it++;
    if (it==inuse.end())return -1;
    return *it;
}

void printSet(){
    for (it = inuse.begin();it!=inuse.end();it++){
        cout<<*it<<" ";
    }cout<<endl;
}

void solve(){
    point p1,p2;
    int n;

    for (int i=0;i<K;i++){
        n = p[i].num;
        //printSet();
        if (p[i].type==0){
            inuse.insert(n);
            it = inuse.find(n);
            p1 = segs[n].first, p2 = segs[n].second;
            if (p1.y>p2.y)nxt[n] = getNxt(n);
        }else if (p[i].type==1){
            it = inuse.begin();
            if (it == inuse.end())pnxt[n] = -1;
            else pnxt[n] = *it;
        }else{
            it = inuse.find(n);
            p1 = segs[n].first, p2 = segs[n].second;
            if (p1.y<p2.y)nxt[n] = getNxt(n);
            else if (p1.y==p2.y)nxt[n] = -1;
            inuse.erase(n);
        }
    }
}

point recurse(ll x,ll y,int num){
    if (num==-1)return point(x,y);

    point p1 = segs[num].first, p2 = segs[num].second;

    if (p1.y==p2.y)return point(x,p1.y);
    if (dp[num].x!=-1)return dp[num];

    //cout<<num<<": "<<x<<", "<<y<<", "<<nxt[num]<<endl;


    ll x1,y1;

    x1 = (p1.y<p2.y?p2.x:p1.x);
    y1 = 0;

    //cout<<x1<<" "<<y1<<endl;

    return dp[num] = recurse(x1,y1,nxt[num]);
}

int main(){
    int x1,y1,x2,y2,t1,t2;
    point p1;
    int query[MAXN];

    while (scanf("%d%d",&N,&C)!=EOF){
        K = 0;

        for (int i=0;i<N;i++){
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            if (x1<x2){
                t1 = 0, t2 = 2;
                segs[i] = seg(point(x1,y1),point(x2,y2));
            }
            else {
                t1 = 2, t2 = 0;
                segs[i] = seg(point(x2,y2),point(x1,y1));
            }
            dp[i] = point(-1,-1);
            p[K++] = point(x1,y1,t1,i);
            p[K++] = point(x2,y2,t2,i);
        }for (int i=0;i<C;i++){
            scanf("%d",&x1);
            p[K++] = point(x1,0,1,i);
            query[i] = x1;
        }
        sort(p,p+K);
        solve();
        //for (int i=0;i<N;i++)cout<<nxt[i]<<" ";
        //cout<<endl;
        for (int i=0;i<C;i++){
            p1 = recurse(query[i],0,pnxt[i]);
            if (p1.y==0)printf("%lld\n",p1.x);
            else printf("%lld %lld\n",p1.x,p1.y);
        }
    }
}
