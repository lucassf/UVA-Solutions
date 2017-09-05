#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int crossProduct(ii point1,ii point2,ii point3){
    return (point2.first-point1.first)*(point3.second-point2.second)
    -(point2.second-point1.second)*(point3.first-point2.first);
}

double getDistance(ii p1,ii p2,ii p3){
    int dx = p2.first-p1.first;
    int dy = p2.second-p1.second;
    double dist = sqrt((double)dx*dx+dy*dy);
    double val = abs(p1.first*(p2.second-p3.second)+
                  p2.first*(p3.second-p1.second)+
                  p3.first*(p1.second-p2.second));
    return val/dist;
}

int main(){
    ii point[101],p1,p2,p3;
    int sol[101];
    double wmin,wmax;
    int n,x,y,t=1;
    while(cin>>n&&n!=0){
        for (int i=0;i<n;i++){
                cin>>x>>y;
            point[i] = ii(x,y);
        }
        sort(point,point+n);
        sol[0] = 0;
        sol[1] = 1;
        int index = 2;
        int topconvex;
        for (int i=2;i<n;i++){
            while (index>1&&crossProduct(point[sol[index-2]],point[sol[index-1]],point[i])>=0)index--;
            sol[index++] = i;
        }topconvex = index;
        sol[index++] = n-2;
        for (int i=n-3;i>=0;i--){
            while (index>topconvex&&crossProduct(point[sol[index-2]],point[sol[index-1]],point[i])>=0)index--;
            sol[index++] = i;
        }index--;
        //for (int i=0;i<index;i++)printf("%d ",sol[i]);
        //printf("\n");
        wmin = 1000000000;

        for (int k=0;k<index;k++){
            wmax=-1;
            for (int u=0;u<index;u++){
                if (u==(k+1)%index||u==k)continue;
                p1 = point[sol[k]];
                p2 = point[sol[(k+1)%index]];
                p3 = point[sol[u]];
                wmax = max(wmax,getDistance(p1,p2,p3));
            }
            //cout<<wmax<<endl;
            wmin = min(wmax,wmin);
        }
        printf("Case %d: %.2lf\n",t++,wmin);
    }

}
