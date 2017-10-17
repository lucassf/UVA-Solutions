#include <bits/stdc++.h>
using namespace std;

int main(){
    int a1,a2,a3;
    char win;
    bool found = false;
    cin>>a1>>a2>>a3;
    if ((a1==1&&a2==0&&a3==0)||(a1==0&&a2==1&&a3==1))found = true,win = 'A';
    else if ((a2==1&&a1==0&&a3==0)||(a2==0&&a1==1&&a3==1))found = true,win = 'B';
    else if ((a3==1&&a2==0&&a1==0)||(a3==0&&a2==1&&a1==1))found = true,win = 'C';
    else win = '*';
    cout<<win<<endl;
}
