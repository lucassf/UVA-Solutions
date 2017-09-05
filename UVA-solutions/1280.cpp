#include <bits/stdc++.h>
using namespace std;
#define EPS 1E-9
#define _USE_MATH_DEFINES

double a[11],integ[22];
int n;

double value(double x){
    double res = 0;
    for (int i=2*n;i>=0;i--){
        res+=integ[i]/(i+1);
        res*=x;
    }
    return res;
}

double volume(double a,double b){

    return M_PI*abs(value(b)-value(a));
}

void findFact(){
    for (int i=0;i<=2*n;i++)integ[i]=0;
    for (int i=0;i<=n;i++){
        for (int j=0;j<=n;j++){
            integ[i+j]+=a[i]*a[j];
        }
    }
}

double findDist(double xlow,double a1,double a2,double mark){
    double v = volume(xlow,(a1+a2)/2);
    if (v>mark)return a1;
    return a2;
}

int main(){
    double xlow,xhigh,inc,dx,vol,mark;
    int j,t=1;
    double ans[8];
    while (cin>>n){
        vol = 0;
        j=0;
        for (int i=0;i<=n;i++)cin>>a[i];
        cin>>xlow>>xhigh>>inc;

        findFact();
        dx = 0.01;
        mark = inc;

        for (double i=xlow+dx;i<=xhigh;i+=dx){
            vol = volume(xlow,i);
            if (j<8&&vol>=mark)ans[j++] = findDist(xlow,i-dx,i,mark),mark+=inc;
        }
        printf("Case %d: %.2lf\n",t++,volume(xlow,xhigh));
        if (j==0)cout<<"insufficient volume"<<endl;
        else{
            printf("%.2lf",ans[0]-xlow);
            for (int i=1;i<j;i++)printf(" %.2lf",ans[i]-xlow);
            cout<<endl;
        }
    }
}
