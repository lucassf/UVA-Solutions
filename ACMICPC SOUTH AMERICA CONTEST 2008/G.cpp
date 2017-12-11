#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

int main(){
    int N, c, p, arr[MAXN];
    bool poss;
    while (cin>>N && N){

        memset(arr, 0, sizeof(arr));
        poss = true;

        for (int i = 0; i < N; i++){
            cin >> c >> p;

            if (p + i < 0 || p + i >= N || arr[p + i])poss = false;
            else arr[p + i] = c;
        }
        if (!poss)cout<<"-1\n";
        else{
            for (int i = 0; i < N-1; i++)cout<<arr[i]<<" ";
            cout<<arr[N - 1]<<"\n";
        }
    }
}
