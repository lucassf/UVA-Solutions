#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define MAXN 5009

void printArr(int *arr,int n){
    for (int i=0;i<n;i++){
        cout<<arr[i];
    }
    cout<<endl;
}

bool addNum(int *arr,int n,int num){
    int p = num,nxt;
    for (int i=n-1;i>=0;i--){
         nxt = arr[i]+p;
         p = nxt>>1;
         arr[i] = nxt&1;
    }
    //printArr(arr,n);
    return p==0;
}

bool remNum(int *arr,int n,int num){
    int p = num,nxt;
    for (int i=n-1;i>=0;i--){
         nxt = arr[i]-p;
         p = nxt>=0?0:1;
         arr[i] = nxt>=0?nxt:2+nxt;
    }
    //printArr(arr,n);
    return p==0;
}

char getCar(int x,int y){
    if (x==0&&y==0)return 'p';
    else if (x==0&&y==1)return 's';
    else if (x==1&&y==0)return 'q';
    return 'r';
}

string toS(int *posx,int *posy,int n){
    string ans = "m";
    for (int i=0;i<n;i++){
        ans.push_back(getCar(posx[i],posy[i]));
    }
    return ans;
}

int main(){
    map<char,ii> pos;
    pos['p'] = ii(0,0);
    pos['q'] = ii(1,0);
    pos['s'] = ii(0,1);
    pos['r'] = ii(1,1);

    int n,t;
    cin>>t;
    string s;
    int posx[MAXN], posy[MAXN];

    while (t-->0){
        cin>>s;
        n = s.size();
        n--;
        for (int i=0;i<n;i++){
            posx[i] = pos[s[i+1]].first;
            posy[i] = pos[s[i+1]].second;
        }
        //printArr(posx,n);
        //printArr(posy,n);
        if (remNum(posy,n,1)){
            cout<<toS(posx,posy,n)<<" ";
        }else{
            cout<<"<none> ";
        }
        addNum(posy,n,1);
        if (addNum(posy,n,1)){
            cout<<toS(posx,posy,n)<<" ";
        }else{
            cout<<"<none> ";
        }
        remNum(posy,n,1);
        if (remNum(posx,n,1)){
            cout<<toS(posx,posy,n)<<" ";
        }else{
            cout<<"<none> ";
        }
        addNum(posx,n,1);
        if (addNum(posx,n,1)){
            cout<<toS(posx,posy,n)<<endl;
        }else{
            cout<<"<none>\n";
        }
    }
}
