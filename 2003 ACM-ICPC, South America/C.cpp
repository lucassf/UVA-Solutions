#include <bits/stdc++.h>
using namespace std;
#define MAXN 8
#define MAXM 256

int p;
int movx[8] = {1,1,2,2,-1,-1,-2,-2};
int movy[8] = {2,-2,1,-1,2,-2,-1,1};
int pals[MAXN];
int val[256][256];

struct state{
    int killed,h,dist;
    state(){}
    state(int _killed,int _h,int _dist){
        killed = _killed, dist = _dist,h = _h;
    }
    bool operator <(state other)const{
        return dist>other.dist;
    }
};

int solve(int H){
    int h,dist,killed,x,y,rem,nextkill,nextpalpos;
    state cur;
    int curpals[MAXN];
    bool poss;

    memset(val,-1,sizeof(val));
    priority_queue<state> inuse;
    inuse.push(state(0,H,0));
    val[0][H] = 0;

    while (!inuse.empty()){
        cur = inuse.top();
        inuse.pop();
        h = cur.h, dist = cur.dist, killed = cur.killed;
        if (dist>val[killed][h])continue;


        //cout<<h<<" "<<dist<<" "<<killed<<endl;

        if (killed == (1<<p)-1)return dist;

        rem = 0;
        for (int i=0;i<p;i++){
            if (((1<<i)&killed)==0){
                curpals[rem++] = i;
                //cout<<pals[i]<<" ";
            }//cout<<endl;
        }

        for (int i=0;i<8;i++){
            x = movx[i]+(h/8);
            y = movy[i]+(h%8);

            if (x<0||y<0||x>=8||y>=8)continue;
            x = x*8+y;
            poss = true;
            nextkill = killed;
            for (int j=0;j<rem;j++){
                //cout<<rem<<endl;
                nextpalpos = pals[curpals[j]]+8*dist;
                if (nextpalpos==x)nextkill|=(1<<curpals[j]);
                else if (nextpalpos+8==x||nextpalpos+8>=64)poss = false;
            }
            if (poss && (val[nextkill][x]==-1||val[nextkill][x]>dist+1)){
                inuse.push(state(nextkill,x,dist+1));
                val[nextkill][x] = dist+1;
            }
        }
    }
    return -1;
}

int main(){
    int h,ans;
    while (scanf("%d",&p)&&p!=0){
        for (int i=0;i<p;i++){
            scanf("%d",&pals[i]);
            pals[i]--;
        }
        scanf("%d",&h);
        h--;
        ans = solve(h);
        if (ans>=0)printf("%d\n",ans);
        else printf("impossible\n");
    }
}
