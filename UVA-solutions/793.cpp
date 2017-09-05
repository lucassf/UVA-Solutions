#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class UnionFind { // OOP style
private: vi p, rank; // remember: vi is vector<int>
public:
    void reset(int N) { rank.assign(N, 0);
    p.assign(N, 0); for (int i = 0; i < N; i++) p[i] = i; }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j) {
    if (!isSameSet(i, j)) { // if from different set
    int x = findSet(i), y = findSet(j);
    if (rank[x] > rank[y]) p[y] = x; // rank keeps the tree short
    else { p[x] = y;
    if (rank[x] == rank[y]) rank[y]++; }
} } };

int main(){
    UnionFind u;
    int t,N,a,b,cont1,cont2;
    char c,trash;
    cin>>t;
    while (t-->0){
        cin>>N;
        u.reset(N);
        cont1 = cont2 = 0;

        while (scanf("%c%c",&c,&c)&&c!='\n'){
            cin>>a>>b;
            a--,b--;
            if (c=='c')u.unionSet(a,b);
            else u.isSameSet(a,b)?cont1++:cont2++;
        }
        cout<<cont1<<","<<cont2<<endl;
        if (t>0)cout<<endl;
    }
}
