#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
	int n,l,c,r;
	string files[100],sep;
	for (int i = 0; i < 60; i++)sep.push_back('-');
	while (cin>>n) {
		l = 0;
		for (int i = 0; i < n; i++)cin>>files[i],l=max(l,(int)files[i].length());
		sort(files, files + n);
		c = 62 / (l + 2), r = ceil((double)n / c);
		cout<<sep<<endl;
		for (int i = 0; i < r;i++) {
			for (int j = 0; j < c; j++) {
				if (r*j + i >= n)break;
				printf("%-*s",j==c-1?l:l+2,files[r*j+i].c_str());
			}printf("\n");
		}
	}
}
