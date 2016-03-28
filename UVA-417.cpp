#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string, int> value;
int qtt;

void generateValues(int id, char min, string val) {
	if (id == 0) {
		value[val] = qtt++; 
		return;
	}
	for (int i = min; i <= 'z'; i++) {
		val.push_back(i),generateValues(id-1, i+1, val), val.pop_back();
	}
}

int main() {
	string s;
	qtt = 1;
	for (int i = 1; i < 6;i++) generateValues(i, 'a', "");
	while (cin >> s)cout << value[s]<<endl;
}
