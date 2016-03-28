#include <string>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

int main() {
	set<string> words;
	string a,b="";
	bool hyphened;
	while (getline(cin,a)) {
		transform(a.begin(), a.end(), a.begin(), ::tolower);
		hyphened = false;
		for (int i = 0; i < a.length(); i++) {
			if (a[i] >= 'a'&&a[i] <= 'z')b.push_back(a[i]);
			else if (a[i] == '-') {
				if (i == a.length() - 1)hyphened = true;
				else b.push_back('-');
			}
			else if (!b.empty())words.insert(b), b = "";
		}if (!hyphened&&!b.empty())words.insert(b),b="";
	}if (!b.empty())words.insert(b);
	for (set<string>::iterator it = words.begin(); it != words.end(); it++)cout << *it << endl;
}
