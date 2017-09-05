#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

#define FLEAS (1<<16)-1
#define DIE (1<<20)-(1<<16)
#define FLEASINDIE (1<<26)-(1<<20)
#define N 4

int movx[4] = {-1,1,0,0};
int movy[4] = {0,0,1,-1};

int vec[6];

void printGrid(int pos){
    int flea = pos&FLEAS;
    int die = (pos&DIE)>>16;
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++){
            if (die==(i*N+j))cout<<'D';
            else if (flea&(1<<(N*i+j)))cout<<'X';
            else cout<<'.';
        }cout<<endl;
    }
    cout<<((pos&FLEASINDIE)>>20)<<endl<<endl;
}

void intToVec(int fleasindie){
    int i=0;
    while (i<6)vec[i++]=fleasindie&1,fleasindie>>=1;
}

int vecToInt(){
    int ans=0;
    for (int i=0;i<6;i++)ans|=vec[i]<<i;
    return ans;
}

int moveUp(int fleasindie){
    int aux;
    intToVec(fleasindie);
    aux = vec[0];
    vec[0] = vec[4];
    vec[4] = vec[5];
    vec[5] = vec[2];
    vec[2] = aux;
    return vecToInt();
}

int moveRight(int fleasindie){
    int aux;
    intToVec(fleasindie);
    aux = vec[0];
    vec[0] = vec[3];
    vec[3] = vec[5];
    vec[5] = vec[1];
    vec[1] = aux;
    return vecToInt();
}

int moveDown(int fleasindie){
    int aux;
    intToVec(fleasindie);
    aux = vec[0];
    vec[0] = vec[2];
    vec[2] = vec[5];
    vec[5] = vec[4];
    vec[4] = aux;
    return vecToInt();
}

int moveLeft(int fleasindie){
    int aux;
    intToVec(fleasindie);
    aux = vec[0];
    vec[0] = vec[1];
    vec[1] = vec[5];
    vec[5] = vec[3];
    vec[3] = aux;
    return vecToInt();
}

int main(){
    int t,pos,first,diepos,fleas,die,fleasindie,qtt;
    int x,y,afleas,adie,afleasindie,addflea,removeflea;
    queue<ii> inuse;
    char grid[5];
    bool poss;
    map<int,bool> used;

    cin>>t;
    while(t-->0){
        first=0;
        poss=false;
        used.clear();
        for (int i=0;i<N;i++){
            cin>>grid;
            for (int j=0;j<N;j++){
                if (grid[j]=='D')diepos = N*i+j;
                else if (grid[j]=='X')first|=1<<(N*i+j);
            }
        }first|=diepos<<16;
        inuse.push(ii(first,0));
        used[first]=true;

        while (!inuse.empty()){
            pos = inuse.front().first;
            qtt = inuse.front().second;
            inuse.pop();
            fleas = pos&FLEAS;
            die = (pos&DIE)>>16;
            fleasindie = (pos&FLEASINDIE)>>20;

            if (fleas==0){
                poss=true;
                break;
            }

            //printGrid(pos);

            int diex = die/N;
            int diey = die%N;

            for (int i=0;i<4;i++){
                x = movx[i]+diex;
                y = movy[i]+diey;
                if (x<0||x>=N||y<0||y>=N)continue;
                pos = x*N+y;

                if (i==0)afleasindie = moveUp(fleasindie);
                else if (i==1)afleasindie = moveDown(fleasindie);
                else if (i==2)afleasindie = moveRight(fleasindie);
                else afleasindie = moveLeft(fleasindie);

                addflea = afleasindie&1;
                removeflea = (1<<pos)&fleas;

                adie = pos;
                afleas = fleas;
                if (removeflea&&!addflea)afleasindie|=1,afleas^=(1<<pos);
                else if (addflea&&!removeflea)afleas|=(1<<pos),afleasindie^=1;

                pos = afleas|(adie<<16)|(afleasindie<<20);
                if(!used[pos]){
                    used[pos]=true;
                    inuse.push(ii(pos,qtt+1));
                }
            }
        }
        while(!inuse.empty())inuse.pop();
        if (poss)cout<<qtt<<endl;
        else cout<<"impossible"<<endl;
    }
}
