#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<int, int> ii;

int main() {
	char s[10];
	priority_queue<ii> queries;
	ii aux;
	int qnum, period, k, value[3001];
	while (scanf("%s", &s) && s[0] != '#') {
		scanf("%d%d ",&qnum,&period);
		queries.push(make_pair(-period, -qnum));
		value[qnum] = period;
	}
	scanf("%d",&k);
	for (int i = 0; i < k; i++) {
		aux = queries.top();
		queries.pop();
		printf("%d\n",-aux.second);
		aux.first -= value[-aux.second];
		queries.push(aux);
	}
}
