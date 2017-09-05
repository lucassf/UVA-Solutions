#include <bits/stdc++.h>
using namespace std;

int n;
int allBit,bsize;
int grid[9][9];
int lineVal[10],colVal[10],squareVal[10];

int squarePos(int i,int j){
    return n*(i/n)+j/n;
}

void printSol(){
    for (int i=0;i<bsize;i++){
        cout<<grid[i][0];
        for (int j=1;j<bsize;j++){
            cout<<" "<<grid[i][j];
        }cout<<endl;
    }
}

bool findSol(int row,int col){
    if (row==bsize){
        return true;
    }
    if (col==bsize)return findSol(row+1,0);
    if (grid[row][col]!=0)return findSol(row,col+1);

    int pos = allBit&(~(lineVal[row]|colVal[col]|squareVal[squarePos(row,col)]));
    //cout<<row<<" "<<col<<" "<<pos<<endl;
    while (pos!=0){
        int val = pos&(-pos);
        pos-=val;

        grid[row][col] = log2((double)val)+1;

        lineVal[row]^=val;
        colVal[col]^=val;
        squareVal[squarePos(row,col)]^=val;

        bool res = findSol(row,col+1);
        if (res)return true;

        lineVal[row]^=val;
        colVal[col]^=val;
        squareVal[squarePos(row,col)]^=val;
        grid[row][col] = 0;
    }

    return false;
}

int main(){
    bool first = true,poss;
    while(cin>>n){
        if (!first)cout<<endl;
        allBit = (1<<(n*n))-1,bsize=n*n;
        poss = false;
        for (int i=0;i<bsize;i++)lineVal[i]=colVal[i]=squareVal[i]=0;

        for (int i=0;i<bsize;i++){
            for (int j=0;j<bsize;j++){
                cin>>grid[i][j];
                int pos = (1<<(grid[i][j]-1));
                if (grid[i][j]!=0){
                    poss = (pos&lineVal[i])||(pos&squareVal[squarePos(i,j)])||
                    (pos&colVal[j]);
                    lineVal[i]|=pos,
                    squareVal[squarePos(i,j)]|=pos,
                    colVal[j]|=pos;

                }
            }
        }
        if (!poss&&findSol(0,0))printSol();
        else cout<<"NO SOLUTION"<<endl;
        first = false;
    }
}
