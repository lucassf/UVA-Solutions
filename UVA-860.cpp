#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
	string line,a;
	map<string, int> occur;
	char c;
	int n, lamb;
	double et,er;
	lamb = 0;
	while (getline(cin, line) && line != "****END_OF_INPUT****") {
		if (line == "****END_OF_TEXT****") {
			n = occur.size(), et = 0, er = log10(lamb);
			for (map<string, int>::iterator it = occur.begin(); it != occur.end(); it++) {
				et -= it->second*log10(it->second);
			}et=et/lamb+er;
			printf("%d %.1lf %.0lf\n",lamb,et,et*100/er);
			occur.clear();
			lamb = 0;
			continue;
		}
		line.push_back(' ');
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		a = "";
		for (int i = 0; i < line.size(); i++) {
			c = line[i];
			if (c!=' '&&c!='\t'&&c!='\n'&&c!=','&&c!='.'&&c!=':'&&c!=';'&&c!='!'&&c!='?'&&c!='"'&&c!='('&&c!=')')a.push_back(c);
			else if (!a.empty()) {
				occur[a]++, a = "";
				lamb++;
			}
		}
	}
}
