#include <bits/stdc++.h>
using namespace std;
#define MAXN 10

string lines[MAXN];
string names[MAXN],prices[MAXN];
int N,K,pos[MAXN], res[MAXN][MAXN];

bool solve(int n,int k,int sum){

    if (k==K){
        int val = 0,acum = 0;
        for (int i=pos[n];i<(int)prices[n].size();i++){
            val = val*10+prices[n][i]-'0';
        }
        for (int i=0;i<K;i++)acum+=res[n][i];
        if (acum!=val)return false;
        res[n][k] = val;
        if (n==N+1)return true;
        return solve(n+1,k,sum);
    }

    int val = 0,u,rem = K-k,left;
    int m = min(pos[n]+3,(int)prices[n].size());
    if (n==N+1)m = (int)prices[n].size();
    u = pos[n];

    for (int i=pos[n];i<m;i++){
        val = val*10+prices[n][i]-'0';
        left = prices[n].size() - i - 1;

        //cout<<n<<" "<<k<<" "<<val<<endl;

        pos[n] = i+1;
        res[n][k] = val;
        if (n<=N &&solve(n+1,k,sum+val))return true;
        else if (n==N+1){
            if(sum==val && solve(1,k+1,0))return true;
            if (val>sum){
                pos[n] = u;
                break;
            }
        }
        pos[n] = u;

        if (prices[n][u]=='0')break;
    }
    return false;
}

int main(){
    int t,i;
    cin>>t;

    while(t-->0){
        int n = 0,m;
        while (cin>>lines[n]){

            if (lines[n][0]=='T'&&lines[n][1]=='P')break;
            if (n>0){
                string u = "";
                for (i=0;i<lines[n].size();i++){
                    char c = lines[n][i];
                    if ((c>='a'&&c<='z')||(c>='A'&&c<='Z'))u.push_back(c);
                    else {
                        names[n] = u;
                        break;
                    }
                }
                while (i<lines[n].size())prices[n].push_back(lines[n][i++]);
            }
            n++;
            prices[n] = "";
            pos[n] = 0;
        }
        for (i=2;i<lines[n].size();i++)prices[n].push_back(lines[n][i]);
        N = n-1;
        K = (lines[0].size()-6)/2;

        memset(pos,0,sizeof(pos));
        memset(res,0,sizeof(res));

        solve(1,0,0);
        for (int k=0;k<K;k++)printf("P%d ",k+1);
        printf("Totals\n");
        for (i=1;i<n;i++){
            printf("%s",names[i].c_str());
            for (int k=0;k<=K;k++){
                printf(" %d",res[i][k]);
            }
            printf("\n");
        }
        printf("TP");
        for (int k=0;k<=K;k++){
            printf(" %d",res[i][k]);
        }
        printf("\n");
    }
}
