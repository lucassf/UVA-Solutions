#include <map>
#include <cstdio>
#include <queue>
using namespace std;

int main() {
	map<int,int> occur;
	queue<int> seq;
	int a;
	while (scanf("%d", &a) != EOF) {
		if (occur[a] == 0)seq.push(a);
		occur[a]++;
	}while (!seq.empty())printf("%d %d\n",seq.front(),occur[seq.front()]),seq.pop();
}
