#include <cstdio>
#include <queue>
using namespace std;
typedef long long int lld;

int main() {
	int n,a,b;
	lld val;
	priority_queue<lld> inuse;
	while (scanf("%d", &n)&&n!=0) {
		for (int i = 0; i < n; i++)scanf("%d",&a) , inuse.push(-a);
		val = 0;
		while (true) {
			a = inuse.top(), inuse.pop();
			if (inuse.empty())break;
			b = inuse.top(), inuse.pop();
			val -= a + b;
			inuse.push(a + b);
		}printf("%lld\n",val);
	}
}
