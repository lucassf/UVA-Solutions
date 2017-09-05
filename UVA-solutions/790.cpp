#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

struct problem {
	bool solved;
	int penalty;
};

struct team {
	problem prob[7];
	int totaltime,solved,id;
};

struct input {
	int id;
	int problem, time;
	bool solved;
};

bool operator<(team a, team b) {
	if (a.solved != b.solved)return a.solved > b.solved;
	if (a.totaltime != b.totaltime)return a.totaltime < b.totaltime;
	return a.id < b.id;
}

bool operator<(input a, input b) {
	if (a.time != b.time)return a.time < b.time;
	return a.solved < b.solved;
}

bool operator==(team a, team b) {
	return a.solved == b.solved&&a.totaltime == b.totaltime;
}

vector<input> inp;

int main() {
	team p[30];
	input in;
	istringstream iss;
	string s;
	int wmax,j,cases,prev,n,rank,id,h,m;
	char c,status;
	for (scanf("%d ", &cases); cases > 0; cases--) {
		wmax = 0;
		inp.clear();
		while (getline(cin, s) && !s.empty()) {
			iss.str(s);
			iss >> in.id >> c >> h >> status >> m >> status;
			iss.clear();
			in.solved = status == 'Y', in.problem = c - 'A', in.time = h * 60 + m, inp.push_back(in), wmax = max(in.id, wmax);
		}sort(inp.begin(), inp.end());
		for (int i = 1; i <= wmax; i++) {
			for (j = 0; j < 7; j++) p[i].prob[j].solved = false, p[i].prob[j].penalty = 0;
			p[i].solved = p[i].totaltime = 0;
			p[i].id = i;
		}
		for (int i = 0; i < inp.size(); i++) {
			in = inp[i];
			id = in.id;
			n = in.problem;
			if (!p[id].prob[n].solved) {
				if (in.solved)p[id].solved++, p[id].prob[n].solved = true, p[id].totaltime += p[id].prob[n].penalty + in.time;
				else p[id].prob[n].penalty += 20;
			}
		}
		sort(p + 1, p + wmax + 1);
		printf("RANK TEAM PRO/SOLVED TIME\n");
		prev = 1;
		for (int i = 1; i <= wmax; i++) {
			if (i > 1 && p[i] == p[i - 1])rank = prev;
			else rank = i, prev = i;
			if (p[i].solved == 0) printf("%4d%5d\n", rank, p[i].id);
			else printf("%4d%5d%5d%11d\n", rank, p[i].id, p[i].solved, p[i].totaltime);
		}if (cases > 1)printf("\n");
	}
}
