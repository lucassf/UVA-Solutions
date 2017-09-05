#include <bits/stdc++.h>
using namespace std;
#define N 10

int pt[10];
int ow = (1<<10)-1;

bool offTile(int row,int col){
    return (pt[row]&(1<<col))==0;
}

int printBit(int val){
    if (val>0)return 1;
    return 0;
}

void printSol(){
    for (int i=0;i<N;i++){
        for (int j=0;j<N;j++)cout<<printBit(pt[i]&(1<<j));
        cout<<endl;
    }
    cout<<endl;
}

void setBit(int row,int index){
    if (row!=0)pt[row-1]^=(1<<index);
    if (row!=N-1)pt[row+1]^=(1<<index);
    if (index!=0)pt[row]^=(1<<(index-1));
    if (index!=N-1)pt[row]^=(1<<(index+1));
    pt[row]^=(1<<index);
}

int nextRows(int row,int depth){
    if (row==N){
        if (pt[row-1]!=0)return 101;
        //printSol();
        return depth;
    }
    int wasSet[N];

    for (int i=0;i<N;i++){
        int bit = pt[row-1]&(1<<i);
        if (bit){
            setBit(row,i);
            depth++;
        }
        wasSet[i] = bit;
    }

    //printSol();
    int ans = nextRows(row+1,depth);
    for (int i=0;i<N;i++)if (wasSet[i]>0)setBit(row,i);
    return ans;
}

int k = 1;

int firstRowRecurse(int index,int depth){
    if (index==N){
        //cout<<k++<<endl<<endl;
        //printSol();
        return nextRows(1,depth);
    }


    int ans = firstRowRecurse(index+1,depth);
    setBit(0,index);
    ans = min(ans,firstRowRecurse(index+1,depth+1));
    setBit(0,index);
    return ans;
}

int main(){
    string name,s;
    while(cin>>name&&name!="end"){
        for (int i=0;i<N;i++){
            cin>>s;
            pt[i]=0;
            for (int j=0;j<N;j++){
                if (s[j]=='O')pt[i]+=1<<j;
            }
        }
        int ans = firstRowRecurse(0,0);
        cout<<name<<" "<<(ans>100?-1:ans)<<endl;
    }
}
