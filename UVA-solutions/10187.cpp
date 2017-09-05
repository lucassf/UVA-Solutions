#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
#define INF 1000000000

bool sameSide(int arr1,int arr2){
    return (arr1>=18&&arr2>=18)||
        (arr1<=6&&arr2<=6);
}

struct edge{
    string b;
    int dep,arr;

    edge(){}
    edge(string _b,int _dep,int _arr){
        b = _b,dep=_dep,arr=_arr;
    }

    bool operator <(edge other)const{
        if (other.dep!=dep)return dep<other.dep;
        if (sameSide(arr,other.arr))return arr<other.arr;
        return arr>=18;
    }

    bool operator >(edge other)const{
        if (other.dep!=dep)return dep>other.dep;
        if (sameSide(arr,other.arr))return arr>other.arr;
        return arr<=6;
    }
};

struct MyComparator{
    bool operator()(edge e1,edge e2){
        return e1>e2;
    }
};

bool isValid(int a,int b){
    return (a<b&&sameSide(a,b))||(a>=18&&b<=6);
}

int otherTime(int a,int b){
    return ((a<=b&&sameSide(a,b))||(a>=18&&b<=6))?0:1;
}

map<string,vector<edge> > route;

int main(){
    int t,e,dep,arr,litre,l,c=1;
    map<string,ii> val;
    edge aux,e1;
    ii aux1;
    bool poss;
    string a,b,start,finish;
    priority_queue<edge,vector<edge>, MyComparator > inuse;

    cin>>t;
    while (t-->0){
        route.clear();
        val.clear();
        poss = false;
        cin>>e;
        for(int i=0;i<e;i++){
            cin>>a>>b>>dep>>arr;
            arr+=dep;
            if (isValid(dep%24,arr%24)){
                route[a].push_back(edge(b,dep%24,arr%24));
                if (val[a].first!=INF)val[a]=ii(INF,INF);
                if (val[b].first!=INF)val[b]=ii(INF,INF);
            }
        }
        cin>>start>>finish;
        inuse.push(edge(start,0,18));
        val[start] = ii(0,18);

        while (!inuse.empty()){
            aux = inuse.top();
            inuse.pop();
            a = aux.b;
            litre = aux.dep;
            arr = aux.arr;

            if (edge(a,litre,arr)>
                  edge(a,val[a].first,val[a].second))continue;
            //cout<<a<<" "<<litre<<" "<<arr<<endl;

            if (a==finish){
                poss = true;
                break;
            }

            for (int i=0;i<(int)route[a].size();i++){
                e1 = route[a][i];
                b = e1.b;
                l = litre + otherTime(arr,e1.dep);
                if (edge(b,l,e1.arr)<edge(b,val[b].first,val[b].second)){
                    val[b]=ii(l,e1.arr);
                    inuse.push(edge(b,l,e1.arr));
                    //cout<<b<<" "<<l<<" "<<e1.arr;
                }//cout<<endl;
            }
        }while(!inuse.empty())inuse.pop();
        cout<<"Test Case "<<c++<<"."<<endl;
        if (poss)cout<<"Vladimir needs "<<litre<<" litre(s) of blood."<<endl;
        else cout<<"There is no route Vladimir can take."<<endl;
    }
}
