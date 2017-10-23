#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
    int n;
    ll m,k,q,qtt;
    double p,ans;

    q = 4*3*2;
    while (scanf("%d%lf",&n,&p)&&n!=0){
        p/=100;
        m = n*n;
        k = m*(m-1)*(m-2)*(m-3);
        qtt = 0;
        for (int x=0;x<n;x++){
            for (int y=1;y+x<n;y++){
                qtt += (n-x-y)*(n-x-y);
            }
        }
        printf("%.2lf\n",(double)k/(qtt*q)*p);
    }
}
