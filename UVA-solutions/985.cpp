#include <bits/stdc++.h>
using namespace std;

int movx[4] = {0,1,0,-1};
int movy[4] = {-1,0,1,0};

int getDirN(char dir){
    if (dir=='N')return 0;
    if (dir=='E')return 1;
    if (dir=='S')return 2;
    return 3;
}

struct mp{
    int rot;
    int pos;
    int r,c;
    mp(){};
    mp(int _r,int _c,int _rot,int _pos){
        rot = _rot, pos = _pos, r = _r, c = _c;
    }
};

string grid[500][500];
bool used[500][500][4];

int main(){
    int r,c,x,y,rot,pos;
    queue<mp> inuse;
    mp aux;
    bool poss;

    while(cin>>r>>c){
        for (int i=0;i<r;i++)for (int j=0;j<c;j++){
            for (int k=0;k<4;k++)used[i][j][k] = false;
            if (i==r-1&&j==c-1)break;
            cin>>grid[i][j];
        }
        inuse.push(mp(0,0,0,0));
        used[0][0][0]=true;
        poss = false;
        int val;

        while (!inuse.empty()){
            aux = inuse.front();
            inuse.pop();
            //cout<<aux.r<<" "<<aux.c<<" "<<aux.rot<<" "<<aux.pos<<endl;
            if (aux.r == r-1&&aux.c == c-1){
                poss = true;
                break;
            }
            rot = (aux.rot+1)%4;
            pos = aux.pos+1;
            for (int i=0;i<grid[aux.r][aux.c].size();i++){
                val = (getDirN(grid[aux.r][aux.c][i]) + aux.rot)%4;
                y = aux.c + movx[val];
                x = aux.r + movy[val];
                if (x>=0&&y>=0&&x<r&&y<c&&!used[x][y][rot]){
                    used[x][y][rot] = true;
                    inuse.push(mp(x,y,rot,pos));
                }
            }
        }
        while (!inuse.empty())inuse.pop();
        if (!poss)cout<<"no path to exit"<<endl;
        else cout<<aux.pos<<endl;
    }

}
