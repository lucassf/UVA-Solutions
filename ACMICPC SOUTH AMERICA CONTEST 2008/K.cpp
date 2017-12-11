#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

int x[MAXN];
set<int> vals;
int N, X;

inline bool solve(int p){
    int n = X/p;

    if (n <= 2 || n > N)return false;
    vals.clear();

    int i = 0, pnxt = p;
    while (i < N && x[i] < pnxt)vals.insert(x[i++]+p);
    pnxt += p;
    bool found;

    while (i < N){
        found = false;
        while (i < N && x[i] < pnxt){
            if (vals.count(x[i])){
                vals.insert(x[i] + p);
                found = true;
            }
            i++;
        }
        if (!found)return false;
        pnxt += p;
    }
    return pnxt > X;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int ans;

    while (cin>>N && N){
        ans = -1;
        x[0] = 0;
        for (int i = 1; i <= N; i++){
            cin>>x[i];
            x[i] += x[i-1];
        }
        X = x[N];
        for (int i = 1; i <= sqrt(X); i++){
            if (X % i == 0){
                if (solve(i))ans = max(ans, X/i);
                if (solve(X/i))ans = max(ans, i);
            }
        }
        if (ans == -1)cout<<ans<<endl;
        else cout<<N - ans<<endl;
    }

}
