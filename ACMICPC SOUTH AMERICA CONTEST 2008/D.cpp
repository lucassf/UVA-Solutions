#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
typedef pair<int,int> ii;

int K;
int arr[MAXN][MAXN];
int tlast[MAXN][MAXN];
string a, b;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int u, v;
    while(cin>>K && K){
        cin>>a>>b;
        int N = a.length(), M = b.length();

        memset(arr, 0, sizeof(arr));

        for (int i = 1; i <= N; i++){
            char a1 = a[i - 1];
            for (int j = 1; j <= M; j++){
                char a2 = b[j - 1];

                arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);

                int n = 0;
                while (i - n > 0){
                    if (a[i - 1 - n] != b[j - 1 - n])break;
                    n++;
                    if (n >= K)arr[i][j] = max(arr[i][j], n + arr[i - n][j - n]);
                }
            }
        }
        cout << arr[N][M] << endl;
    }
}
