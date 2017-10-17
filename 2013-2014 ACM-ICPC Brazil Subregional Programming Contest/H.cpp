#include <bits/stdc++.h>
using namespace std;
#define MAXINT 1000000
typedef long long int ll;
typedef vector<vector<ll> > matrix;

matrix operator *(matrix a,matrix b){
    int n = (int)a.size();
    int m = (int)b.size();
    int p = (int)b[0].size();
    matrix c;
    c.resize(n);
    for (int i=0;i<n;i++){
        c[i].assign(p,0);
        for (int j=0;j<p;j++){
            for (int k=0;k<m;k++){
                c[i][j] = (c[i][j]+a[i][k]*b[k][j])%MAXINT;
            }
        }
    }
    return c;
}

matrix id(int n){
    matrix a;
    a.resize(n);
    for (int i=0;i<n;i++){
        a[i].assign(n,0);
        a[i][i] = 1;
    }
    return a;
}

matrix matrixExp(matrix a,ll n){
    if (n==0)return id(a.size());
    matrix c = matrixExp(a,n/2);
    c = c*c;
    if (n%2!=0)c = c*a;
    return c;
}

int main(){
    ll n,k,l;
    while (cin>>n>>k>>l){
        n/=5;
        k%=MAXINT, l%=MAXINT;
        matrix a;
        a.resize(2);
        a[0].assign(2,1);
        a[1].assign(2,0);
        a[0][0] = k;
        a[1][0] = l;
        a = matrixExp(a,n-1);
        printf("%06lld\n",(k*a[0][0]+a[1][0])%MAXINT);
    }
}
