#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

bool isDigit(char c){
    return c>='0'&&c<='9';
}

bool isChar(char c){
    return c>='A'&&c<='Z';
}

int charVal(char c){
    if (c=='B')return 0;
    if (c<'I')return c-'A'-2;
    if (c<'M')return c-'A'-3;
    if (c<'P')return c-'A'-4;
    return c-'A'-5;
}

ll firstBase(char *s){
    ll ans = 0;
    for (int i=0;i<7;i++){
        ans = i<3?ans*26+s[i]-'A':ans*10+s[i]-'0';
    }
    return ans;
}

ll secondBase(char *s){
    ll ans = 0;
    for (int i=0;i<7;i++){
        ans = i<5?ans*21+charVal(s[i]):ans*10+s[i]-'0';
    }
    return ans + 175760000;
}

int main(){
    ll n,p1,p2;
    char s1[8],s2[8];
    bool isValid;

    while (scanf("%s %s %lld",&s1,&s2,&n)&&strcmp(s1,"*")){
        isValid = true;
        if ((isDigit(s2[3])&&isChar(s2[4]))||(isDigit(s2[4])&&isChar(s2[3])))isValid = false;
        if (isChar(s2[3])){
            for (int i=0;i<5;i++){
                if (s2[i]=='A'||s2[i]=='C'||s2[i]=='M'||s2[i]=='I'||s2[i]=='P')isValid = false;
            }
        }
        if (isValid){
            p1 = isDigit(s1[3])?firstBase(s1):secondBase(s1);
            p2 = isDigit(s2[3])?firstBase(s2):secondBase(s2);
            isValid = p2>p1 && p2-p1<=n;
        }
        if (isValid)printf("Y\n");
        else printf("N\n");
    }
}
