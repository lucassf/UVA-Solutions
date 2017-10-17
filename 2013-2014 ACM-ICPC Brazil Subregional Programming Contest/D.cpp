#include <bits/stdc++.h>
using namespace std;

int a[15],b[15],n,m;

bool verify(int l){
    int i;
    for (i=0;i<m;i++){
        if (a[i+l]!=b[i])break;
    }if (i==m)return true;
    for (i=0;i<m;i++){
        if (a[i+l]!=b[m-i-1])break;
    }if (i==m)return true;
    return false;
}

void printA(int l,int r){
    for (int i=l;i<=r;i++){
        cout<<a[i]<<" ";
    }cout<<endl;
}

bool traverse(int l,int r){
    int qtt = r-l+1,k;
    //printA(l,r);
    if (qtt==m){
        if (verify(l))return true;
        return false;
    }if (qtt<m)return false;
    for (int i=1;i<=qtt/2;i++){
        k =1;
        for (int j=i+l;j<2*i+l;j++)a[j]+=a[j-k],k+=2;
        if (traverse(i+l,r))return true;
        k = 1;
        for (int j=i+l;j<2*i+l;j++)a[j]-=a[j-k],k+=2;
        k = 1;
        for (int j=r-i;j>r-2*i;j--)a[j]+=a[j+k],k+=2;
        if (traverse(l,r-i))return true;
        k = 1;
        for (int j=r-i;j>r-2*i;j--)a[j]-=a[j+k],k+=2;
    }
    return false;
}

int main(){
    while (cin>>n){
        for (int i=0;i<n;i++)cin>>a[i];
        cin>>m;
        for (int i=0;i<m;i++)cin>>b[i];
        if (traverse(0,n-1))cout<<"S"<<endl;
        else cout<<"N"<<endl;
    }
}
