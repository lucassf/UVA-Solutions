#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int main() {
	string s, a;
	set<string> inuse;
	char c;
	while (getline(cin, s)) {
		a = "";
		s.push_back('.');
		for (int i = 0; i < s.length(); i++) {
			c = s[i];
			if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z')a.push_back(c);
			else if (!a.empty()){
				transform(a.begin(), a.end(), a.begin(), ::tolower);
				inuse.insert(a);
				a = "";
			}
		}
	}for (set<string>::iterator it = inuse.begin(); it != inuse.end(); it++)cout << *it<<endl;
}
