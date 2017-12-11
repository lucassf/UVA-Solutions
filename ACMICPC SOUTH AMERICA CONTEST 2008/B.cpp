#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef vector<ll> poly;

inline void reduce(poly &a){
    int N = (int)a.size();

    while (N > 0 && a[N - 1] == 0)a.pop_back(), N--;
}

inline poly add(poly &a, poly &b){
    int N = (int)a.size(), M = (int)b.size();
    int K = min(N, M);

    poly ans;
    if (N == 0 && M == 0)return ans;
    ans.resize(max(N, M));

    for (int i = 0; i < K; i++)ans[i] = a[i] + b[i];
    for (int i = K; i < N; i++)ans[i] = a[i];
    for (int i = K; i < M; i++)ans[i] = b[i];

    reduce(ans);
    return ans;
}

inline poly subtract(poly &a, poly &b){
    int N = (int)a.size(), M = (int)b.size();
    int K = min(N, M);

    poly ans;
    if (N == 0 && M == 0)return ans;
    ans.resize(max(N, M));

    for (int i = 0; i < K; i++)ans[i] = a[i] - b[i];
    for (int i = K; i < N; i++)ans[i] = a[i];
    for (int i = K; i < M; i++)ans[i] = -b[i];

    reduce(ans);
    return ans;
}

inline poly multiply(poly &a, poly &b){
    int N = (int)a.size(), M = (int)b.size();

    poly ans;
    if (N == 0 || M == 0)return ans;
    ans.assign(N + M - 1, 0);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            ans[i + j] += a[i] * b[j];
        }
    }
    reduce(ans);

    return ans;
}

inline poly gen(ll a){
    poly ans;
    while (a > 0){
        ans.push_back(a % 10);
        a /= 10;
    }
    return ans;
}

bool isRoot(poly &a, ll x){
    ll ans = 0;
    for (int i = 0; i < (int)a.size(); i++){
        ans /= x;
        ans += a[i];
        if (ans % x != 0)return false;
    }
    return ans == 0;
}

int minBase;

inline vector<ll> getIntRoots(poly &a){
    vector<ll> ans;

    if (a.size() == 0)return ans;
    int n = 0;

    while (a[n] == 0)n++;

    ll u = abs(a[n]);
    for (ll i = 1; i*i <= u; i++){
        if (u % i == 0){
            if (i >= minBase && isRoot(a, i))ans.push_back(i);
            if (u / i != i && u / i >= minBase && isRoot(a, u / i))ans.push_back(u / i);
        }
    }
}

char *sec;

poly verifyExpression(char *str){
    poly ans, cur;
    ll num = 0;

    cur.assign(1, 1);
    int n = strlen(str);
    char u;

    for (int i = 0; i < n; i++){
        num = 0;
        while (i < n && str[i] >= '0' && str[i] <= '9'){
            u = str[i];
            num = num*10 + u -'0';
            minBase = max(minBase, u - '0' + 1);
            i++;
        }
        u = str[i];
        poly p = gen(num);
        cur = multiply(cur, p);
        if (u != '*'){
            ans = add(ans, cur);
            cur.assign(1, 1);
        }
        if (u == '='){
            sec = str + i + 1;
            break;
        }
    }

    return ans;
}

void printPol(poly &a){
    for (int i = 0; i < (int)a.size(); i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

int main(){
    poly a, b;
    char str[109];

    while (scanf("%s", str) && str[0]!='='){
        minBase = 2;

        a = verifyExpression(str);
        b = verifyExpression(sec);

        //printPol(a);
        //printPol(b);
        a = subtract(a, b);
        //printPol(a);
        if (a.size() == 0)printf("%d+\n",minBase);
        else{
            vector<ll> ans = getIntRoots(a);
            if (ans.size() == 0)printf("*\n");
            else{
                printf("%lld",ans[0]);
                for (int i = 1; i < (int)ans.size(); i++)printf(" %lld",ans[i]);
                printf("\n");
            }
        }
    }
}
