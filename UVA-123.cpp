#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

map<string, bool> nouse;
map<string, vector<int> > kwic;
vector<int> aux;

string tolower(string s) {
	for (int i = 0; i < s.length(); i++)if (s[i] >= 'A'&&s[i] <= 'Z')s[i] += 'a' - 'A';
	return s;
}

string toupper(string s) {
	for (int i = 0; i < s.length(); i++)if (s[i] >= 'a'&&s[i] <= 'z')s[i] += 'A' - 'a';
	return s;
}

int main() {
	string s,word,a,ans, titles[200];
	int n = 0,qtt,cnt,u;
	while (getline(cin, s) && s != "::")nouse[tolower(s)] = true;
	while (getline(cin, s) && s != "::") {
		s = titles[n]=tolower(s);
		word = "";
		for (int i = 0; i <= s.length(); i++) {
			if (i == s.length() || s[i] == ' ') {
				if (!nouse[word]) kwic[word].push_back(n);
				word = "";
			}
			else word += s[i];
		}n++;
	}
	for (map<string, vector<int> >::iterator it=kwic.begin(); it != kwic.end(); it++) {
		word = it->first, aux = it->second;
		qtt = 1, u = -1;
		for (int i = 0; i < aux.size(); i++) {
			if (u == aux[i])qtt++;
			else qtt = 1;
			cnt = 0, a = "", u = aux[i];
			s = titles[u];
			ans = "";
			for (int j = 0; j <= s.length(); j++) {
				if (j == s.length() || s[j] == ' ') {
					if (a==word)cnt++;
					if (cnt == qtt)ans += toupper(a),cnt++;
					else ans += a;
					if (j!=s.length())ans+=s[j];
					a = "";
				}
				else a += s[j];
			}cout << ans<< endl;
		}
	}
}
