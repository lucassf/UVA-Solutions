#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

struct teams {
	string name;
	int points, wins,losses,scored,suf, games;

	bool operator<(const teams& a) const {
		if (points != a.points)return points > a.points;
		if (wins != a.wins)return wins > a.wins;
		if (scored - suf != a.scored - a.suf)return scored - suf > a.scored - a.suf;
		if (scored != a.scored)return scored > a.scored;
		if (games != a.games)return games < a.games;
		string u = name, v = a.name;
		transform(u.begin(), u.end(), u.begin(), ::tolower);
		transform(v.begin(), v.end(), v.begin(), ::tolower);
		return u < v;
	}
};

int main() {
	teams t[30];
	int n,c,g,g1,g2,p1,p2,k1,k2,j;
	char use;
	string cupname,s,s1,s2;
	cin >> n;
	getline(cin, cupname);
	for (; n > 0; n--) {	
		getline(cin, cupname);
		cin >> c;
		getline(cin, t[0].name);
		for (int i = 0; i < c; i++) {
			getline(cin,t[i].name);
			t[i].games = t[i].losses=t[i].points = t[i].scored = t[i].suf = t[i].wins = 0;
		}cin >> g;
		getline(cin, s);
		for (int i = 0; i < g; i++) {
			getline(cin,s);
			s1 = s2 = "", j = g1 = g2 = 0;
			while (s[j] != '#')s1.push_back(s[j++]);
			j++;
			while (s[j] != '@')g1 = 10 * g1 + s[j++] - '0';
			j++;
			while (s[j] != '#')g2 = 10 * g2 + s[j++] - '0';
			j++;
			while (j<s.length())s2.push_back(s[j++]);
			for (int i = 0; i < c; i++) {
				if (s1 == t[i].name)k1 = i;
				else if (s2 == t[i].name)k2 = i;
			}if (g1 > g2)p1 = 3, p2 = 0,t[k1].wins++,t[k2].losses++;
			else if (g1 == g2)p1 = p2 = 1;
			else p1 = 0, p2 = 3,t[k2].wins++,t[k1].losses++;
			t[k1].games++, t[k2].games++;
			t[k1].points += p1, t[k1].scored += g1, t[k1].suf += g2;
			t[k2].points += p2, t[k2].scored += g2, t[k2].suf += g1;
		}sort(t, t + c);
		cout << cupname << endl;
		for (int i = 0; i < c; i++) {
			cout << i+1<<") "<<t[i].name<<' '<<t[i].points<<"p, "<<t[i].games<<"g ("<<t[i].wins<<
				"-"<<t[i].games-(t[i].wins+t[i].losses)<<"-"<<t[i].losses<<"), "<<t[i].scored-t[i].suf<<
				"gd ("<<t[i].scored<<"-"<<t[i].suf<<")\n";
		}if (n > 1)cout << endl;
	}
}
