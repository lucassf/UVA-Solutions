#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

int getNum(char c){
    if (c>='0'&&c<='9')return c-'0';
    if (c=='T')return 10;
    if (c=='J')return 11;
    if (c=='Q')return 12;
    return 13;
}

int getCar(int num){
    if (num<10&&num>0)return num+'0';
    if (num==10)return 'T';
    if (num==11)return 'J';
    if (num==12)return 'Q';
    return 'K';
}

int suitNum(char c){
    if(c=='H')return 0;
    if (c=='C')return 1;
    if (c=='D')return 2;
    return 3;
}

struct card{
    char suit;
    int num,idx;
    int suitN;

    bool operator<(card other)const{
        if (suit!=other.suit)return suitN<other.suitN;
        return num<other.num;
    }
};

int main(){
    int N;
    char suit,c;
    card cards[4];
    scanf("%d",&N);
    while (N-->0){
        for (int i=0;i<4;i++){
            cin>>c>>suit;
            cards[i].suit = suit;
            cards[i].num = getNum(c);
            cards[i].idx = i;
            cards[i].suitN = suitNum(suit);
        }
        sort(cards+1,cards+4);
        int val;
        if (cards[1].idx==1)val = cards[2].idx==2?1:2;
        else if (cards[2].idx==1)val = cards[1].idx==2?3:4;
        else if (cards[3].idx==1)val = cards[1].idx==2?5:6;

        val = (cards[0].num+val)%13;
        printf("%c%c\n",getCar(val),cards[0].suit);
    }
}
