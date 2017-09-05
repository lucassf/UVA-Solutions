#include <bits/stdc++.h>
using namespace std;
#define NSIZE 3
#define O NSIZE*NSIZE-1
#define INF 1000000000

typedef unsigned long long int ull;

int movx[4]={-1,1,0,0};
int movy[4]={0,0,1,-1};
char mov[4]={'u','d','r','l'};
char seq[50],seqi;
int grid[4][4];
map<ull,int> used;
int nextd;

int inith(){
    int x,y,x1,y1,ans=0,val;
    for (int i=0;i<NSIZE*NSIZE;i++){
        x = i/NSIZE,y=i%NSIZE;
        val = grid[x][y];
        if (val==O)continue;
        x1 = val/NSIZE,y1 = val%NSIZE;
        ans+=abs(x-x1)+abs(y-y1);
    }
    return ans;
}

int updateh(int i,int j,int newi,int newj){
    int val = grid[i][j];
    int x = val/NSIZE,y = val%NSIZE;
    //cout<<i<<" "<<j<<" "<<newi<<" "<<newj<<endl;
    return abs(newi-x)+abs(newj-y)-abs(i-x)-abs(j-y);
}

void gridSwap(int i,int j,int x,int y){
    int aux = grid[i][j];
    grid[i][j]=grid[x][y];
    grid[x][y]=aux;
}

void printGrid(){
    for (int i=0;i<NSIZE;i++){
        for (int j=0;j<NSIZE;j++){
            cout<<grid[i][j]<<" ";
        }cout<<endl;
    }cout<<endl;
}

bool dfs(int g,int h,int pos,int maxdepth){

    //cout<<pos<<" "<<g<<" "<<h<<" "<<endl;
    //cout<<h<<endl;
    //printGrid();

    if (g+h>maxdepth){
        nextd = min(nextd,g+h);
        return false;
    }
    if (h==0)return true;
    ull state = 0;

    for (int i=0;i<NSIZE;i++){
        for (int j=0;j<NSIZE;j++){
            state <<= NSIZE;
            state|=grid[i][j];
        }
    }
    if (used.count(state)&&used[state]<=g)return false;

    used[state] = g;

    int x,y,posx,posy;
    posx = pos/NSIZE, posy = pos%NSIZE;

    for (int i=0;i<4;i++){
        x = posx+movx[i];
        y = posy+movy[i];

        if (x<0||x>=NSIZE||y<0||y>=NSIZE)continue;

        int dh = updateh(x,y,posx,posy);
        gridSwap(posx,posy,x,y);
        seq[seqi++]=mov[i];
        if (dfs(g+1,h+dh,x*NSIZE+y,maxdepth))return true;
        seqi--;
        gridSwap(posx,posy,x,y);

    }
    return false;
}

bool ids(int start){
    int d = inith();
    int firsth = d;
    seqi = 0;
    while (d<=31){
        nextd = INF;
        used.clear();

        if (dfs(0,firsth,start,d)){
            seq[seqi]=0;
            return true;
        }
        d = nextd;
    }
    return false;
}

int main(){
    int t,a;
    char b;
    int start;
    cin>>t;
    while (t-->0){
        for (int i=0;i<NSIZE;i++){
            for (int j=0;j<NSIZE;j++){
                cin>>b;
                grid[i][j]=b=='x'?O:b-'0'-1;
                if (b=='x')start = i*NSIZE+j;
            }
        }

        int inversions = 0;
        int val1,val2;

        for (int i=1;i<=O;i++){
            for (int j=0;j<i;j++){
                val1 = grid[i/NSIZE][i%NSIZE];
                val2 = grid[j/NSIZE][j%NSIZE];
                if (val1!=O&&val2!=O&&val2>val1)inversions++;
            }
        }

        if (inversions%2==0&&ids(start)){
            cout<<seq<<endl;
        }else cout<<"unsolvable"<<endl;
        if (t!=0)cout<<endl;
    }
}

