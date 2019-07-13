#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define INF 1e9
typedef pair<int,int> ii;
typedef pair<ii,int> iii;

int C,R;
ii source,sink;
vector<iii> pound_begin[MAXN];
vector<iii> pound_end[MAXN];
int grid[MAXN][MAXN];
int movx[24] = {-2,-2,-2,-2,-2,-1,-1,-1,-1,-1,0,0,0,0,
    1,1,1,1,1,2,2,2,2,2};
int movy[24] = {-2,-1,0,1,2,-2,-1,0,1,2,-2,-1,1,2,-2,
    -1,0,1,2,-2,-1,0,1,2};
int cost[24] = {7,6,5,6,7,6,3,2,3,6,5,2,2,5,6,3,2,3,6,
    7,6,5,6,7};

void printGrid(){
    for (int i=0;i<R;i++){
        for (int j=0;j<C;j++){
            cout<<grid[i][j]<<" ";
        }
        cout<<endl;
    }cout<<endl;
}

inline void setPounds(){
    set<iii> inuse;
    set<iii>::iterator it;
    iii val;
    int c1,c2;

    for (int i=0;i<R;i++){
        for (int j=0;j<pound_begin[i].size();j++){
            inuse.insert(pound_begin[i][j]);
        }
        int wmax = 0,l,r;
        for (it = inuse.begin();it!=inuse.end();it++){
            val = *it;
            c1 = val.first.first, c2 = val.first.second;
            l = max(c1,wmax), r = c2;

            for (int j = l;j<=r;j++){
                grid[i][j] = -1;
            }
            wmax = max(wmax,r+1);
        }
        for (int j=0;j<pound_end[i].size();j++){
            inuse.erase(pound_end[i][j]);
        }
    }
}

inline int solve(){
    int x,y;

    priority_queue<iii> inuse;
    inuse.push(iii(ii(0,source.first),source.second));
    int x1,y1,x2,y2,dist,c;

    while (!inuse.empty()){
        dist = -inuse.top().first.first;
        x1 = inuse.top().first.second;
        y1 = inuse.top().second;
        inuse.pop();

        if (x1==sink.first && y1==sink.second)return dist;
        if (dist>grid[x1][y1]);

        for (int i=0;i<24;i++){
            x2 = x1+movx[i];
            y2 = y1+movy[i];
            c = dist+cost[i];

            if (x2>=0&&x2<R&&y2>=0&&y2<C&&c<grid[x2][y2]){
                grid[x2][y2] = c;
                inuse.push(iii(ii(-c,x2),y2));
            }
        }
    }
    return -1;
}

int main(){
    int w,c1,c2,r1,r2;
    while (scanf("%d%d",&C,&R) && C!=0){
        scanf("%d%d%d%d",&c1,&r1,&c2,&r2);
        c1--,c2--,r1--,r2--;
        source = ii(r1,c1);
        sink = ii(r2,c2);
        for (int i=0;i<R;i++){
            for (int j=0;j<C;j++)grid[i][j] = INF;
            pound_begin[i].clear();
            pound_end[i].clear();
        }
        grid[r1][c1] = 0;

        scanf("%d",&w);
        for (int i=0;i<w;i++){
            scanf("%d%d%d%d",&c1,&r1,&c2,&r2);
            c1--,c2--,r1--,r2--;
            pound_begin[r1].push_back(iii(ii(c1,c2),i));
            pound_end[r2].push_back(iii(ii(c1,c2),i));
        }
        setPounds();
        //printGrid();
        int ans = solve();
        //printGrid();
        if (ans==-1)printf("impossible\n");
        else printf("%d\n",ans);
    }
}
