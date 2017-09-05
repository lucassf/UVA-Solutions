#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES
#define a 9.8
#define EPS 1E-9

double h[102],d[102];

int main(){
    int n,j,i;
    double angle,vel,vx,vy,t,h1;
    while(cin>>n){
        for (i=0;i<n;i++){
            cin>>h[i]>>d[i];
            if (i>0)d[i]+=d[i-1];

        }
        for (i=1;i<9000;i++){
            angle = M_PI*i/18000;
            vel = sqrt(a*d[n-1]/sin(2*angle));
            vx = vel*cos(angle), vy = vel*sin(angle);

            for (j=1;j<n-1;j++){
                t = d[j-1]/vx;
                h1 = t*(vy-a*t/2);
                if (h1<h[j])break;

                t = d[j]/vx;
                h1 = t*(vy-a*t/2);
                if (h1<h[j])break;
            }
            if (j==n-1)break;
        }
        printf("%.2lf %.2lf\n",(double)i/100,vel);
    }
}
