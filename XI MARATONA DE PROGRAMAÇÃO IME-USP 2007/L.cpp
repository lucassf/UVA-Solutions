#include <bits/stdc++.h>
using namespace std;

int dig[1000001];

int main(){
    int c = 1,n;
    int pow2[4] = {2,4,6,8};

    int acum = 1;
    dig[0] = 1;
    dig[1] = 1;
    dig[2] = 2;
    dig[3] = 6;
    dig[4] = 4;
    dig[5] = 2;
    dig[6] = 2;
    dig[7] = 4;
    dig[8] = 2;
    dig[9] = 8;

    for (int i=10;i<=1000000;i++){
        if (((i/10)%10)%2==0)
            dig[i] = (6*dig[i/5]*dig[i%10])%10;
        else
            dig[i] = (4*dig[i/5]*dig[i%10])%10;
    }

    while (cin>>n){
        cout<<"Instancia "<<c++<<"\n"<<dig[n]<<"\n\n";
    }
}
