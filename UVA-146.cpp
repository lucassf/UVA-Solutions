#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	bool found;
	char wmin,aux;
	int idx;
	while (cin >> s&&s != "#") {
		found = false;
		for (int i = s.length() - 2; i >= 0; i--) {
			wmin = 'z'+1;
			for (int j = s.length() - 1; j > i; j--) {
				if (s[j]>s[i]&&s[j] < wmin)wmin = s[j], idx = j, found = true;
			}if (found) {
				aux = s[idx], s[idx] = s[i], s[i] = aux;
				for (int j = i + 1; j < s.length(); j++) {
					wmin = s[j], idx = j;
					for (int k = j + 1; k < s.length(); k++) {
						if (s[k] < wmin)wmin = s[k], idx = k;
					}aux = s[j], s[j] = s[idx], s[idx] = aux;
				}
				break;
			}
		}if (!found)cout << "No Successor" << endl;
		else cout << s << endl;
	}
}
