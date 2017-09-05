#include <bits/stdc++.h>
using namespace std;

void reverseN(int *arr,int index){
    int aux;
    for (int i=0;i<index/2;i++){
        aux = arr[i];
        arr[i] = arr[index-i-1];
        arr[index-i-1] = aux;
    }
}

int main(){
    int d[31],n=0,s[31],val;
    char c;

    while (scanf("%d%c",&d[n++],&c)!=EOF){
        s[n-1] = d[n-1];
        cout<<d[n-1];
        while(c!='\n'){
            scanf("%d%c",&d[n++],&c);
            s[n-1] = d[n-1];
            cout<<" "<<d[n-1];
        }cout<<endl;
        sort(s,s+n);
        for (int i=n-1;i>=0;i--){
            val = s[i];
            for (int j=i;j>=0;j--){
                if (val != d[j])continue;
                if (i==j)break;
                //cout<<i<<" "<<j<<endl;
                if (j!=0){
                    cout<<n-j<<" ";
                    reverseN(d,j+1);
                }
                cout<<n-i<<" ";
                //for (int k=0;k<n;k++)cout<<d[k]<<" ";
                reverseN(d,i+1);
            }
        }cout<<"0"<<endl;
        n=0;
    }
}
