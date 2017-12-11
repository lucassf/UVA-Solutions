#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long int ll;
typedef pair<ll, ll> ii;

ll a1,a2,b1,b2,c1,c2,d1,d2,tnum,tden,k,ta,tb;

inline ll lcd(ll a, ll b){
    ll aux;
    while (b != 0){
        aux = b;
        b = a % b;
        a = aux;
    }
    return max(1ll,a);
}

bool sorte(ii a, ii b){
    return a.first * b.second < a.second * b.first;
}

inline bool isValid(ll &num, ll &den){
    if (num < 0 && den < 0)num = -num, den = -den;
    if (num == 0 && den != 0)den = 1;
    if (num < 0 || den < 0)return false;
    return true;
}

inline ii sameReadius(){
    ll num = 0, den = 0;
    ll c = (c2 - c1), d = (d2 - d1), k;

    if (a1 == a2 && b1 == b2){
        if (c == 0 && d % 360 == 0)num = 0, den = 1;
        else if (c > 0)
            k = ceil((double)d / 360);
        else if (c < 0)
            k = floor((double)d / 360);
        if (c != 0){
            num = -d + 360 * k;
            den = c;
        }
    }else if (a1 != a2){
        num = b2 - b1;
        den = a1 - a2;

        if (c * num % den != 0 || (c * num / den + d) % 360 != 0){
            num = den = 0;
        }
    }
    if (!isValid(num, den))return ii(0, 0);
    return ii(num, den);
}

inline ii minusReadius(){
    ll num = 0, den = 0;
    ll c = (c2 - c1), d = (d2 - d1), k;

    if (a1 == -a2 && b1 == -b2){
        if (c == 0 && (d + 180) % 360 == 0)num = 0, den = 1;
        else if (c > 0)
            k = ceil((double)(d - 180) / 360);
        else if (c < 0)
            k = floor((double)(d - 180) / 360);
        if (c != 0){
            num = -d + 360 * k + 180;
            den = c;
        }
    }else if (a1 != -a2){
        num = - b2 - b1;
        den = a1 + a2;

        if (c * num % den != 0 || (c * num / den + d + 180) % 360 != 0){
            num = den = 0;
        }
    }
    if (!isValid(num, den))return ii(0, 0);
    return ii(num, den);
}

ii radius0(){
    ll num = 0, den = 0;

    if (a1 == 0 && b1 == 0){
        if (a2 == 0 && b2 == 0)num = 0, den = 1;
        if (a2 != 0){
            num = -b2;
            den = a2;
        }
    }else if (a1 != 0){
        num = -b1;
        den = a1;

        if (a2 * num != -b2 * den)
            num = den = 0;
    }

    if (!isValid(num, den))return ii(0, 0);
    return ii(num, den);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<ii> poss;

    while (cin>>a1>>b1>>c1>>d1>>a2>>b2>>c2>>d2, a1|a2|b1|b2|c1|c2|d1|d2){
        poss.clear();

        ii a = sameReadius();
        if (a != ii(0, 0))poss.push_back(a);

        a = minusReadius();
        if (a != ii(0, 0))poss.push_back(a);

        a = radius0();
        if (a != ii(0, 0))poss.push_back(a);

        if (poss.empty())cout<<"0 0\n";
        else {
            sort(poss.begin(), poss.end(),sorte);
            a = poss[0];
            ll l = lcd(a.first, a.second);
            cout<<a.first/l<<" "<<a.second/l<<"\n";
        }
    }
}
