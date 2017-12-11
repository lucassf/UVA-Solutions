#include <bits/stdc++.h>
using namespace std;

inline bool isLeap(int y){
    return y % 400 == 0 || (y % 100 != 0 && y % 4 == 0);
}

inline bool monthLim(int d, int m, int y){
    if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)return d == 31;
    else if (m == 2)return isLeap(y)?d == 29: d == 28;
    return d == 30;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, D, M, Y, C;
    int d, m, y, c, ans, cons;

    while (cin>>N && N){
        d = -1;
        ans = cons = 0;

        for (int i = 0; i < N; i++){
            cin>>D>>M>>Y>>C;
            if (D == d && M == m && Y == y){
                ans++;
                cons += C - c;
            }
            if (!monthLim(D, M, Y)){
                y = Y, d = D + 1, m = M;
            }
            else if (M == 12){
                y = Y + 1, d = 1, m = 1;
            }else{
                y = Y, d = 1, m = M + 1;
            }

            c = C;
        }
        cout<<ans<<" "<<cons<<"\n";
    }
}
