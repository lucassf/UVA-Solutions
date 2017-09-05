#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vi dfs_num, AdjList[27], used;
int let[20],letToIndex[27];
int n;

bool dfs2(int u) { // different function name compared to the original dfs
    dfs_num[u] = 1;
    bool possible = true;
    for (int j = 0; j < (int)AdjList[u].size(); j++) {
        int v = AdjList[u][j];
        if (!dfs_num[v])
            dfs2(v);
        if (dfs_num[v]==1)
            return false;
    }
    dfs_num[u] = 2;
    return possible;
}

void printAns(){
    for (int i=0;i<dfs_num.size()-1;i++)printf("%c ",let[dfs_num[i]]+'A');
    if (dfs_num.size()>0)printf("%c",let[dfs_num[dfs_num.size()-1]]+'A');
    cout<<endl;
}

void findAns(int index){
    if (index==n){printAns(); return;}

    int u,v,j;
    for (int i=0;i<n;i++){
        if (used[i])continue;

        for (j=0;j<AdjList[i].size();j++){
            v = AdjList[i][j];
            if (!used[v])break;
        }
        if (j==AdjList[i].size()){
            used[i] = true;
            dfs_num.push_back(i);
            findAns(index+1);
            dfs_num.pop_back();
            used[i] = false;
        }
    }
}

int main(){
    int t,a,b;
    bool possible;
    string line;

    cin>>t;
    getline(cin,line);
    while (t-->0){
        getline(cin,line);
        getline(cin,line);

        n = 0;
        for (int i=0;i<line.size();i+=2){
            let[n++] = line[i]-'A';
        }
        sort(let,let+n);

        dfs_num.assign(n,0);
        for (int i=0;i<n;i++){
            AdjList[i].clear();
        }for (int i=0;i<n;i++)letToIndex[let[i]] = i;


        getline(cin,line);

        for (int i=0;i<line.size();i+=4){
            a = line[i]-'A', b = line[i+2] - 'A';
            AdjList[letToIndex[b]].push_back(letToIndex[a]);
        }
        possible = true;
        for (int i=0;i<n;i++){
            if (!dfs_num[i]&&!dfs2(i)){
                possible = false;
                break;
            }
        }if (!possible)cout<<"NO"<<endl;
        else {
            dfs_num.clear();
            used.assign(n,0);
            findAns(0);
        }
        if (t>0)cout<<endl;
    }
}
