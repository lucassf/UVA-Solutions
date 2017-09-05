#include <bits/stdc++.h>
using namespace std;
#define MAXN 1100
typedef long long int ll;

int b[MAXN];
ll grid[MAXN][MAXN],vec[MAXN];
string np,mp;

void KMP(int m){
    b[0] = -1;
    for(int i = 0, j = -1; i < m;) {
        while (j >= 0 && vec[i] != vec[j]) j = b[j];
        i++; j++;
        b[i] = j;
    }
}
vector<int> match(int index,int n,int m){
    vector<int> ans;
    for (int i=0, j=0; i < n;) {
        while (j >= 0 && grid[i][index] != vec[j]) j = b[j];
        i++; j++;
        if (j == m) {
            ans.push_back(i - j);
            j = b[j];
        }
    }
    return ans;
}

int main(){
    int n,m,c=1,k,o;
    string s1;
    vector<int> ans;
    bool found;
    ll bit,acum;

    ios_base::sync_with_stdio(false);

    while (cin>>n>>m){
        k = 1;
        bit = ~((1ll)<<(m-1));
        o = n-m+1;
        found = false;

        for (int i=0;i<n;i++){
            cin>>np;
            acum = 0;
            for (int j=0;j<m;j++){
                acum<<=1;
                acum+=np[j]=='|'?0:1;
            }
            for (int j=0;j<o;j++){
                grid[i][j] = acum;
                acum&=bit;
                acum<<=1;
                acum+=np[j+m]=='|'?0:1;
            }
        }
        for (int i=0;i<m;i++){
            cin>>mp;
            acum = 0;
            for (int j=0;j<m;j++){
                acum<<=1;
                acum+=mp[j]=='|'?0:1;
            }
            vec[i] = acum;
        }
        /*for (int i=0;i<n;i++){
                for (int j=0;j<o;j++)cout<<grid[i][j];
            cout<<endl;
        }*/
        KMP(m);
        cout<<"Instancia "<<c++<<"\n";
        for (int j=0;j<o;j++){
            ans = match(j,n,m);
            for (int i=0;i<ans.size();i++){
                cout<<ans[i]<<" "<<j<<"\n";
                found = true;
            }
        }if (!found)cout<<"nenhuma ocorrencia\n";
        cout<<"\n";
    }
}
