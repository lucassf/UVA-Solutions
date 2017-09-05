#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

#define NCHECK 2

ii r[3];
int checkdist[2];
int checkpoint[2];
int movx[4]={1,-1,0,0};
int movy[4]={0,0,-1,1};
int n,m,N,ind,invalid;

vector<int> used;
vector<vector<int> > ans[2];

bool bfs(int init,int dist){
    queue<ii> inuse;
    bool auxused[65]={};
    int posx,posy,x,y,p;

    inuse.push(ii(init,dist));
    auxused[init]=true;

    int val,qtt;

    while (!inuse.empty()){
        val = inuse.front().first;
        qtt = inuse.front().second;
        inuse.pop();

        //cout<<val<<" ";

        for (int i=0;i<2;i++){
            if (val==checkpoint[i]&&qtt>checkdist[i])return false;
        }

        posx = val/m, posy =val%m;

        for (int i=0;i<4;i++){
            x = movx[i]+posx;
            y = movy[i]+posy;
            p = x*m+y;

            if (x>=0&&x<n&&y>=0&&y<m&&!used[p]&&!auxused[p]){
                auxused[p]=true;
                dist++;
                inuse.push(ii(p,qtt+1));
            }
        }
    }
    //cout<<dist<<endl;
    return dist==N;
}

void dfs(int val,int qtt){
    int x,y,p;
    int posx = val/m,posy = val%m;

    //cout<<val<<" "<<qtt<<endl;

    for (int i=0;i<NCHECK;i++){
        if ((val==checkpoint[i]&&qtt!=checkdist[i])||
            (qtt==checkdist[i]&&val!=checkpoint[i]))return;
    }
    if (!bfs(val,qtt))return;
    if (qtt==checkdist[1]){
        ans[ind].push_back(used);
        //cout<<"sol"<<endl;
        return;
    }
    used[val] = true;

    int neighbors = 0,x1,y1,p1,needindex=0,needqtt=0;

    for (int i=0;i<4;i++){
        x = posx+movx[i];
        y = posy+movy[i];
        p = x*m+y;

        if (x>=0&&x<n&&y>=0&&y<m&&!used[p]&&p!=invalid){
            neighbors = 0;
            for (int j=0;j<4;j++){
                x1 = x+movx[j];
                y1 = y+movy[j];
                p1 = x1*m+y1;

                if (x1>=0&&x1<n&&y1>=0&&y1<m&&!used[p1])neighbors++;
            }
            //cout<<p<<" "<<neighbors<<endl;
            if (neighbors==1)needindex=p,needqtt++;

        }
    }//cout<<endl;

    if (needqtt>1){
        used[val] = false;
        return;
    }
    else if (needqtt==1){
        dfs(needindex,qtt+1);
        used[val]=false;
        return;
    }

    for (int i=0;i<4;i++){
        x = posx+movx[i];
        y = posy+movy[i];
        p = x*m+y;

        if (x>=0&&x<n&&y>=0&&y<m&&!used[p]){
            if (p!=invalid)dfs(p,qtt+1);
        }
    }
    used[val]=false;
}

int main(){
    int k,finalans,t=1;

    while (cin>>n>>m&&n!=0){
        N=m*n;
        used.assign(N,false);
        finalans = 0;
        ans[0].clear();
        ans[1].clear();

        for (int i=0;i<3;i++){
            cin>>r[i].first>>r[i].second;
        }if (N%2==1){
            cout<<"Case "<<t++<<": 0"<<endl;
            continue;
        }
        checkdist[0]=N/4;
        checkdist[1]=N/2;

        checkpoint[0] = r[0].first*m+r[0].second;
        checkpoint[1] = r[1].first*m+r[1].second;
        ind=0;

        invalid=1;
        dfs(0,1);
        //cout<<endl;

        checkdist[0]=1+N-(3*N)/4;
        checkdist[1]=1+N-N/2;
        checkpoint[0] = r[2].first*m+r[2].second;
        checkpoint[1] = r[1].first*m+r[1].second;
        ind=1;

        invalid=0;
        if (!ans[0].empty())dfs(1,1);

        for (int i=0;i<ans[0].size();i++){
            for (int j=0;j<ans[1].size();j++){
                for (k=0;k<N;k++){
                    if (ans[0][i][k]&&ans[1][j][k])break;
                }
                if (k==N)finalans++;
            }
        }
        cout<<"Case "<<t++<<": "<<finalans<<endl;
    }
}
