#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;

map<ull,int> step[11];

int cut(int* num,int *num2,int n,int i,int j){
    int index = n-(j-i)-1,p=0;
    for (int k=0;k<n;k++){
        while (k>=i&&k<=j)num2[index++]=num[k++];
        if (k<n)num2[p++]=num[k];
    }
    return index;
}

ull paste(int* num,int n,int k,int diff){
    int index = n-diff-1;
    ull ans=0;
    for (int p=0;p<k;p++)ans<<=4,ans|=num[p];
    while (index<n)ans<<=4,ans|=num[index++];
    for (int p=k;p<n-diff-1;p++)ans<<=4,ans|=num[p];

    return ans;
}

void printM(int* num,int n){
    for (int i=0;i<n;i++)cout<<num[i]<<" ";
    cout<<endl;
}

int compute(ull val,int n,int depth,bool precomp){
    int num[10],num2[10],index=n-1;
    ull valaux = val;

    while (valaux>0){
        num[index--] = valaux&15;
        valaux>>=4;
    }
    if (step[n][val]){
        if (!precomp||step[n][val]<=depth)return depth+step[n][val]-2;
    }
    if (precomp){
        step[n][val]=depth;
    }

    //cout<<step[n][val]<<endl;
    //printM(num,n);


    if (depth==3)return 5;

    int ans = 5;

    for (int i=0;i<n;i++){
        for (int j=i;j<n;j++){
            cut(num,num2,n,i,j);

            for (int k=0;k<n-(j-i);k++){
                ans = min(ans,compute(paste(num2,n,k,j-i),n,depth+1,precomp));
            }
        }
    }
    return ans;
}

void precompute(){
    ull val = 0;
    for (int i=1;i<=10;i++){
        val|=i;
        compute(val,i,1,true);
        val<<=4;
    }
}

int main(){
    int n,a,t=1;
    ull start;
    precompute();

    while (cin>>n&&n!=0){
        start = 0;
        for (int i=0;i<n;i++){
            cin>>a;
            start<<=4;
            start|=a;
        }
        cout<<"Case "<<t++<<": "<<compute(start,n,1,false)<<endl;
    }
}
