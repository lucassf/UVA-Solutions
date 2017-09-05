#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class UnionFind { // OOP style
private: vi p, rank, uSize; // remember: vi is vector<int>
public:
    void reset(int N) {
        rank.assign(N, 0);
        p.assign(N, 0);
        uSize.assign(N,0);
        for (int i = 0; i < N; i++) p[i] = i, uSize[i] = 1;
    }
    int findSet(int i) {
        return (p[i] == i) ? i : (p[i] = findSet(p[i]));
    }
    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            // if from different set
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y]) p[y] = x, uSize[x] += uSize[y]; // rank keeps the tree short
            else {
                p[x] = y;
                if (rank[x] == rank[y]) rank[y]++;
                uSize[y] += uSize[x];
            }
        }
    }
    int getSize(int i){
        return uSize[findSet(i)];
    }
};

int main(){
    int t,n,cont;
    cin>>t;
    string a,b;
    map<string,int> convers;
    UnionFind u;

    while (t-->0){
        cin>>n;
        int p,q;

        u.reset(2*n+1);
        convers.clear();
        cont = 1;

        for (int i=0;i<n;i++){
            cin>>a>>b;
            if (!convers.count(a))convers[a] = cont++;
            if (!convers.count(b))convers[b] = cont++;
            p = convers[a], q = convers[b];
            u.unionSet(p,q);
            cout<<u.getSize(p)<<endl;
        }
    }
}
