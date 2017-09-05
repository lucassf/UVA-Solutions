#include <bits/stdc++.h>
using namespace std;
typedef pair<string,int> si;


bool sorte(si s1,si s2){
    if (s1.second!=s2.second)return s1.second>s2.second;
    return s1.first<s2.first;
}

int main(){
    int n,t,grade,c=1;
    si students[101];
    string s;

    while (cin>>n){
        for (int i=0;i<n;i++){
            cin>>s>>grade;
            students[i] = si(s,grade);
        }
        sort(students,students+n,sorte);
        //for (int i=0;i<n;i++)cout<<students[i].first<<" ";
        cout<<"Instancia "<<c++;
        cout<<"\n"<<students[n-1].first<<"\n\n";
    }
}
