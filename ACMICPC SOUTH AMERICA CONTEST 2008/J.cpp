#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

inline int getSuit(char c){
    if (c == 'C')return 0;
    if (c == 'D')return 1;
    if (c == 'H')return 2;
    return 3;
}

int N, P, M;
vector<ii> p[19];
queue<ii> stock;
ii discard;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int rk,sk;
    char suit;
    while (cin>>P>>M>>N, P){

        while (!stock.empty())stock.pop();
        for (int i = 0; i < P; i++){
            p[i].clear();
            for (int j = 0; j < M; j++){
                cin>>rk>>suit;
                p[i].push_back(ii(rk,getSuit(suit)));
            }
        }
        cin>>rk>>suit;
        discard = ii(rk,getSuit(suit));
        for (int i = P*M + 1; i < N; i++){
            cin>>rk>>suit;
            stock.push(ii(rk,getSuit(suit)));
        }
        int player = 0, dir = 1;
        bool apply = true;

        if (discard.first == 12)dir = -1;

        while (true){

            //cout<<player<<" "<<discard.first<<" "<<discard.second<<endl;

            if (apply && discard.first == 7){
                p[player].push_back(stock.front());
                stock.pop();
                p[player].push_back(stock.front());
                stock.pop();
                apply = false;
            }else if (apply && discard.first == 1){
                p[player].push_back(stock.front());
                stock.pop();
                apply = false;
            }
            else if (apply && discard.first == 11)apply = false;
            else{
                ii val = ii(0, 0);
                bool found = false;
                apply = false;
                for (int i = 0; i < p[player].size(); i++){
                    rk = p[player][i].first;
                    sk = p[player][i].second;

                    if (rk == discard.first || sk == discard.second){
                        found = true; break;
                    }
                }
                if (!found){p[player].push_back(stock.front());stock.pop();}
                found = false;
                int idx = 0;
                for (int i = 0; i < p[player].size(); i++){
                    rk = p[player][i].first;
                    sk = p[player][i].second;

                    if (rk == discard.first || sk == discard.second){
                        found = true;
                        if (val < ii(rk, sk)){idx = i, val = ii(rk, sk);}
                    }
                }
                if (found){
                    apply = true;
                    discard = p[player][idx];
                    for (int i = idx; i < p[player].size() - 1;i++){
                        p[player][i] = p[player][i+1];
                    }
                    p[player].pop_back();
                }
            }

            if (p[player].empty())break;

            if (apply && discard.first == 12)dir = -dir;
            player = (player + dir + P) % P;
        }
        cout<<player + 1<<endl;
    }
}
