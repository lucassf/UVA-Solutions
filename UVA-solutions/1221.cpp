#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> ii;
#define MAX_INT 2000000000

int days[250][250],h,a;
ii spaces[250], alien[250];
vector<int> adjList[250],match,vis;

int Aug(int l) { // return 1 if an augmenting path is found
    if (vis[l]) return 0; // return 0 otherwise
    vis[l] = 1;
    for (int j = 0; j < (int)adjList[l].size(); j++) {
        int r = adjList[l][j]; // edge weight not needed -> vector<vi> AdjList
        if (match[r] == -1 || Aug(match[r])) {
            match[r] = l; return 1; // found 1 matching
        }
    }
    return 0; // no matching
}

bool matches(){
    int mcbm = 0;
    match.assign(a,-1);
    for (int i=0;i<h;i++){
        vis.assign(h,0);
        mcbm+=Aug(i);
    }
    return mcbm==a;
}

void computeArr(ll time){
    ll mammoths, ships, n ,dn;
    for (int i=0;i<h;i++)adjList[i].clear();
    for (int i=0;i<h;i++){
        for (int j=0;j<a;j++){
            n = spaces[i].first - alien[j].first - days[i][j]*alien[j].second;
            dn = spaces[i].second - alien[j].second;
            ships = spaces[i].first + (time-days[i][j])*spaces[i].second;
            mammoths = alien[j].first + time*alien[j].second;

            if (days[i][j]<=time&&(ships>=mammoths||(n>=0&&dn<=0)))adjList[i].push_back(j);
        }
    }
}

ll binarySearch(ll first,ll last){
    while (first<=last){
        ll mid = (first+last)/2;
        computeArr(mid);
        if (!matches())first=mid+1;
        else {
            if (last==first)return mid;
            last = mid;
        }
    }return -1;
}

int main(){
    while (cin>>h>>a&&h!=0){
        for (int i=0;i<h;i++)cin>>spaces[i].first>>spaces[i].second;
        for (int i=0;i<a;i++)cin>>alien[i].first>>alien[i].second;
        for (int i=0;i<h;i++){
            for (int j=0;j<a;j++){
                cin>>days[i][j];
            }
        }
        int val = binarySearch(0,MAX_INT);
        if (val!=-1)cout<<val<<endl;
        else cout<<"IMPOSSIBLE"<<endl;
    }
}
