#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int> > matrix;

int N;

double calc(matrix A,matrix B){
    int diff = 0;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (abs(A[i][j]-B[i][j])<=100)diff++;
        }
    }
    return (double)diff/(N*N);
}

matrix rot(matrix A){
    matrix B;
    B.assign(N,vector<int>(N));
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            B[i][j] = A[j][N-i-1];
        }
    }
    return B;
}

matrix turn(matrix A){
    matrix B;
    B.assign(N,vector<int>(N));
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            B[i][j] = A[i][N-j-1];
        }
    }
    return B;
}

int main(){
    matrix A,B;
    double ans;
    while (scanf("%d",&N)&&N!=0){
        A.assign(N,vector<int>(N));
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++)scanf("%d",&A[i][j]);
        }
        B.assign(N,vector<int>(N));
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++)scanf("%d",&B[i][j]);
        }
        ans = 0;
        for (int i=0;i<4;i++){
            ans = max(ans,calc(A,B));
            B = rot(B);
        }B = turn(B);
        for (int i=0;i<4;i++){
            ans = max(ans,calc(A,B));
            B = rot(B);
        }
        printf("%.2lf\n",ans*100);
    }
}
