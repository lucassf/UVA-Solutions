#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

bool comp(string a,string b) {
	string c = a + b,d = b+a;
	return c > d;
}

int main() {
	int n;
	string a[50];
	while (cin>>n&&n!=0) {
		for (int i = 0; i < n; i++)cin>>a[i];
		std::sort(a, a + n,comp);
		for (int i = 0; i < n; i++)cout<<a[i];
		cout<<endl;
	}
}
