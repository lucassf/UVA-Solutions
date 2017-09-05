#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

bool sign[8];
bool prime[16] = {};
map<int,bool> used;

bool isPrime(int a,int b){
    return prime[a+b+2];
}

void printArr(int val){
    for (int i=0;i<8;i++){
        cout<<(val&7)<<" ";
        val>>=3;
    }
    cout<<endl;
}

int main(){
    int last = 0,first,val,cur,pos,t=1,arr[8];
    int s,u,v,w,all = (1<<24)-1;
    queue<ii> inuse;
    bool poss;
    ii aux;

    prime[2] = prime[3] = prime[5] = prime[7] = prime[11] = prime[13] = true;
    for (int i=0;i<8;i++){
        last|=i<<(3*i);
    }
    while (cin>>val&&val!=0){
        sign[abs(val)-1]=val<0;
        first = abs(val)-1;
        used.clear();
        for (int j=1;j<8;j++){
            cin>>val;
            sign[abs(val)-1]=val<0;
            first |= ((abs(val)-1)<<(3*j));
        }
        poss = false;
        inuse.push(ii(first,0));
        used[first]=true;

        while (!inuse.empty()){
            aux = inuse.front();
            inuse.pop();
            val = cur = aux.first, pos = aux.second;
            //printArr(val);
            if (cur==last){
                poss = true;
                break;
            }for (int i=0;i<8;i++){
                arr[i]=cur&7;
                cur>>=3;
            }for (int i=0;i<8;i++){
                if (!sign[arr[i]])continue;
                for (int j=0;j<8;j++){
                    if (sign[arr[j]]||i==j||!isPrime(arr[i],arr[j]))continue;
                    cur = 0,s=0;
                    for (int k=0;k<8;k++){
                        if (k==i)continue;
                        if (k==j)cur|=(arr[i])<<(3*s++);
                        cur|=(arr[k])<<(3*s++);
                    }
                    if (!used[cur]){
                            //printArr(cur);
                        used[cur] = true;
                        inuse.push(ii(cur,pos+1));
                    }cur=s=0;
                    for (int k=0;k<8;k++){

                        if (k==i)continue;
                        cur|=(arr[k])<<(3*s++);
                        if (k==j)cur|=(arr[i])<<(3*s++);
                    }
                    if (!used[cur]){
                        //printArr(cur);
                        used[cur] = true;
                        inuse.push(ii(cur,pos+1));
                    }
                    cur = 0,s=0;
                    for (int k=0;k<8;k++){
                        if (k==j)continue;
                        if (k==i)cur|=(arr[j])<<(3*s++);
                        cur|=(arr[k])<<(3*s++);
                    }
                    if (!used[cur]){
                            //printArr(cur);
                        used[cur] = true;
                        inuse.push(ii(cur,pos+1));
                    }cur=s=0;
                    for (int k=0;k<8;k++){

                        if (k==j)continue;
                        cur|=(arr[k])<<(3*s++);
                        if (k==i)cur|=(arr[j])<<(3*s++);
                    }
                    if (!used[cur]){
                        //printArr(cur);
                        used[cur] = true;
                        inuse.push(ii(cur,pos+1));
                    }
                }
            }
        }while(!inuse.empty())inuse.pop();
        if (poss)cout<<"Case "<<t++<<": "<<pos<<endl;
        else cout<<"Case "<<t++<<": -1"<<endl;
    }
}
