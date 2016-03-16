#include <algorithm>
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

struct team {
	int score,gamesplayed,scored,suffered;
	string name;
	bool operator<(const team& a) const{
		if (score != a.score)return score > a.score;
		if (scored - suffered != a.scored - a.suffered)return scored - suffered > a.scored - a.suffered;
		if (scored != a.scored)return scored > a.scored;
		string u=name,j=a.name;
		transform(name.begin(), name.end(), u.begin(), ::tolower);
		transform(a.name.begin(), a.name.end(), j.begin(), ::tolower);
		return u < j;
	}

	bool operator==(const team& a) const {
		if (score == a.score&&scored - suffered == a.scored - a.suffered&&scored == a.scored)return true;
		return false;
	}
};

int main() {
	int t, k1,k2,g,p1,p2,q1,q2,classification;
	string s,s1;
	bool first = true;
	team aux,prev,teams[28];
	char dash;
	while (cin>>t>>g && t != 0) {
		if (!first)printf("\n");
		first = false;
		for (int i = 0; i < t; i++) {
			cin >> s, teams[i].name = s;
			teams[i].gamesplayed = teams[i].score = teams[i].scored = teams[i].suffered = 0;
		}
		for (int i = 0; i < g; i++) {
			cin >> s >> p1 >> dash>>p2 >> s1;
			for (int i = 0; i < t; i++) {
				if (teams[i].name == s)k1 = i;
				else if (teams[i].name == s1)k2 = i;
			}
			if (p1 > p2)q1 = 3, q2 = 0;
			else if (p1 == p2)q1 = q2 = 1;
			else q1 = 0, q2 = 3;
			aux = teams[k1];
			aux.score += q1, aux.gamesplayed++, aux.scored += p1, aux.suffered += p2;
			teams[k1] = aux;
			aux = teams[k2];
			aux.score += q2, aux.gamesplayed++, aux.scored += p2, aux.suffered += p1;
			teams[k2] = aux;
		}
		sort(teams, teams + t);
		classification = 1;
		for (int i = 0; i < t;i++) {
			aux = teams[i];
			if (i>0 && aux == prev)printf("%4c",' ');
			else printf("%2d. ",classification);
			printf("%15s%4d%4d%4d%4d%4d",aux.name.c_str(),aux.score,aux.gamesplayed,aux.scored,aux.suffered,
				aux.scored-aux.suffered);
			if (aux.gamesplayed==0)printf("%7s\n","N/A");
			else printf("%7.2lf\n",(double)100*aux.score/(3*aux.gamesplayed));
			classification++;
			prev = aux;
		}
	}
}
