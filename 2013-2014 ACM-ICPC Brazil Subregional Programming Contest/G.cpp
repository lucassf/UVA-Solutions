#include <bits/stdc++.h>
using namespace std;

int grid[309][309];
int l,c;

void show(){
    for (int i=0;i<l;i++){
        for (int j=0;j<c;j++){
            cout<<grid[i][j]<<" ";
        }cout<<endl;
    }
}

bool verify(){
    for (int i=0;i<l;i++){
        for (int j=0;j<c;j++){
            if (grid[i][j]!=i*c+j)return false;
        }
    }
    return true;
}

void shiftCol(int c1,int c2){
    int aux;
    for (int i=0;i<l;i++){
        aux = grid[i][c1];
        grid[i][c1] = grid[i][c2];
        grid[i][c2] = aux;
    }
}

void shiftLin(int l1,int l2){
    int aux;
    for (int j=0;j<c;j++){
        aux = grid[l1][j];
        grid[l1][j] = grid[l2][j];
        grid[l2][j] = aux;
    }
}

int main(){
    int posx,posy,ans;

    while (cin>>l>>c){
        ans = 0;

        for (int i=0;i<l;i++){
            for (int j=0;j<c;j++){
                cin>>grid[i][j];
                grid[i][j]--;
                if (grid[i][j]==0)posx = i, posy = j;
            }
        }
        if (posx!=0){shiftLin(0,posx);ans++;}
        if (posy!=0){shiftCol(0,posy);ans++;}
        //show();
        for (int i=1;i<c;i++){
            for (int j=i;j<c;j++){
                if (grid[0][j]==i){
                    if (j!=i){shiftCol(i,j);ans++;}
                    break;
                }
            }
        }//show();
        for (int i=1;i<l;i++){
            for (int j=i;j<l;j++){
                if (grid[j][0]==c*i){
                    if (j!=i){shiftLin(i,j);ans++;}
                    break;
                }
            }
        }//show();
        if (verify())cout<<ans<<endl;
        else cout<<"*"<<endl;
    }
}

