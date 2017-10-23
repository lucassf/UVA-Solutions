#include <bits/stdc++.h>
using namespace std;
#define MAXN 10
typedef pair<int,int> ii;

char face[6][3][3];
ii dir[6][4] = {{ii(4,3),ii(1,3),ii(5,3),ii(3,1)},{ii(0,1),ii(4,2),ii(2,3),ii(5,0)},
    {ii(1,1),ii(4,1),ii(3,3),ii(5,1)},{ii(0,3),ii(5,2),ii(2,1),ii(4,0)},
    {ii(0,0),ii(3,0),ii(2,0),ii(1,0)},{ii(1,2),ii(2,2),ii(3,2),ii(0,2)}};


bool isSolved(){
    for (int i=0;i<6;i++){
        char c = face[i][0][0];
        for (int j=0;j<3;j++){
            for (int k=0;k<3;k++){
                if (face[i][j][k]!=c)return false;
            }
        }
    }return true;
}

void clockRot(int n){
    char nxt[6][3][3];

    for (int i=0;i<6;i++)for (int j=0;j<3;j++)for (int k=0;k<3;k++)nxt[i][j][k] = face[i][j][k];
    for (int i=0;i<3;i++)for (int j=0;j<3;j++)nxt[n][i][j] = face[n][2-j][i];

    ii coord[4][3];

    for (int i=0;i<4;i++){
        int d = dir[n][i].second;
        if (d==0)for (int j=0;j<3;j++)coord[i][j] = ii(0,2-j);
        if (d==1)for (int j=0;j<3;j++)coord[i][j] = ii(2-j,2);
        if (d==2)for (int j=0;j<3;j++)coord[i][j] = ii(2,j);
        if (d==3)for (int j=0;j<3;j++)coord[i][j] = ii(j,0);
    }for (int i=1;i<=4;i++){
        for (int j=0;j<3;j++){
            nxt[dir[n][i%4].first][coord[i%4][j].first][coord[i%4][j].second] =
            face[dir[n][i-1].first][coord[i-1][j].first][coord[i-1][j].second];
        }
    }

    for (int i=0;i<6;i++)for (int j=0;j<3;j++)for (int k=0;k<3;k++)face[i][j][k] = nxt[i][j][k];
}

void printCube(){
    for (int i=0;i<6;i++){
        for (int j=0;j<3;j++){
            for (int k=0;k<3;k++){
                cout<<face[i][j][k];
            }cout<<endl;
        }cout<<endl<<endl;
    }
}

int main(){
    int t,n;
    cin>>t;
    while(t-->0){
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                cin>>face[4][i][j];
            }
        }for (int i=0;i<3;i++){
            for (int j=0;j<12;j++){
                cin>>face[j/3][i][j%3];
            }
        }for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                cin>>face[5][i][j];
            }
        }
        while (cin>>n&&n!=0){
            if (n>0)clockRot(n-1);
            else{
                for (int i=0;i<3;i++)clockRot(-n-1);
            }
            //printCube();
        }
        if (isSolved())printf("Yes, grandpa!\n");
        else printf("No, you are wrong!\n");
    }
}
