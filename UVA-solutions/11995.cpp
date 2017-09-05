#include <cstdio>
#include <stack>
#include <queue>
using namespace std;

int main() {
	int n,a,b;
	bool isst, isq, ispq,poss;
	stack<int> st;
	queue<int> q;
	priority_queue<int> pq;
	while (scanf("%d", &n) != EOF) {
		isst = isq = ispq = true;
		while (!st.empty())st.pop(), pq.pop(), q.pop();
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			if (a == 1)pq.push(b), st.push(b), q.push(b);
			else if (!st.empty()){
				if (b != st.top())isst = false;
				if (b != q.front())isq = false;
				if (b != pq.top())ispq = false;
				st.pop(), q.pop(), pq.pop();
			}
			else ispq = isq = isst = false;
		}poss = isst | isq | ispq;
		if (!poss)printf("impossible\n");
		else if ((isst&isq) | (isst&ispq) | (isq&ispq))printf("not sure\n");
		else if (isst)printf("stack\n");
		else if (isq)printf("queue\n");
		else printf("priority queue\n");
	}
}
