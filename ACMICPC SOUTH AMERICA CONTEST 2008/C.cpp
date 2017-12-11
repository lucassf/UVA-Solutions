#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int arr[MAXN], N, M, a[MAXN];

int main(){
    while (scanf("%d%d",&N,&M),M){
        for (int i = 0; i < N; i++){
            for (int j = 0; j < M; j++){
                scanf("%d", &a[j]);
            }
            for (int j = M-1; j>=0; j--){
                a[j] = max(a[j] + (j + 2<M?a[j + 2]:0), (j + 1<M?a[j + 1]:0));
            }
            arr[i] = a[0];
        }
        for (int i = N-1; i >= 0; i--){
            arr[i] = max(arr[i] + (i + 2<N?arr[i + 2]:0), (i + 1<N?arr[i + 1]:0));
        }
        printf("%d\n",arr[0]);
    }
}
