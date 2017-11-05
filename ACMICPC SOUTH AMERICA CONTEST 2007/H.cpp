#include <bits/stdc++.h>
using namespace std;

int main(){
    int a,b[12],c[12],d;
    bool ok;

    while (cin>>a>>d&&a!=0){
        for (int i=0;i<a;i++)cin>>b[i];
        for (int i=0;i<d;i++)cin>>c[i];
        sort(c,c+d);
        ok = true;
        for (int i=0;i<a;i++){
            if (b[i]<c[1]){
                ok = false;
                break;
            }
        }if (ok)cout<<"N"<<endl;
        else cout<<"Y"<<endl;
    }
}
