#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int wmax;
string best;

void prevlesser(int cur,string a) {
	int dist=100;
	for (int i = 1; i < a.length(); i++)dist = min(dist, abs(a[i] - a[i - 1]));
	if (dist >= wmax)best = a,wmax=dist;
	if (cur == 10)return;
	char t;
	int idx, aux;
	for (int i = a.length() - 2; i >= 0; i--) {
		idx = -1, t = 0;
		for (int j = a.length() - 1; j > i; j--) {
			if (a[j] < a[i] && a[j] > t)t = a[j], idx = j;
		}
		if (idx != -1) {
			aux = a[idx], a[idx] = a[i], a[i] = aux;
			for (int j = i + 1; j < a.length(); j++) {
				t = 0;
				for (int k = j; k < a.length(); k++)
					if (a[k]>t)t = a[k], idx = k;
				aux = a[idx], a[idx] = a[j], a[j] = aux;
			}
			prevlesser(cur + 1, a);
			break;
		}
	}//cout << a << endl;
}

void nextlarger(int cur,string a) {
	int dist = 100;
	for (int i = 1; i < a.length(); i++)dist = min(dist, abs(a[i] - a[i - 1]));
	if (dist > wmax)best = a,wmax=dist;
	if (cur == 10)return;
	char t;
	int idx, aux;
	for (int i = a.length() - 2; i >= 0; i--) {
		idx = -1, t = 'Z'+1;
		for (int j = a.length() - 1 ; j > i; j--) {
			if (a[j] > a[i] && a[j] < t)t = a[j], idx = j;
		}
		if (idx!=-1) {
			aux = a[idx], a[idx] = a[i], a[i] = aux;
			for (int j = i+1; j < a.length(); j++) {
				t = 'Z'+1;
				for (int k = j; k < a.length(); k++)
					if (a[k]<t)t=a[k],idx = k;
				aux = a[idx], a[idx] = a[j], a[j] = aux;
			}
			//cout << a << endl;
			nextlarger(cur + 1, a );
			break;
		}
	}
}

int main() {
	string user;
	int n;
	while (cin>>user) {
		wmax = 0;
		prevlesser(0,user);
		nextlarger(0,user);
		cout << best << wmax << endl;
	}
}
