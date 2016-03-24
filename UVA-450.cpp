#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

struct file {
	string title, firstname, lastname, address, 
		homephone, workphone, campusmail, department;

	bool operator<(file a) {
		return lastname < a.lastname;
	}
};

file f[100000];

int main() {
	int n,i,p=0;
	char c;
	string dep,s,a;
	cin >> n;
	getline(cin, dep);
	for (; n > 0; n--) {
		getline(cin, dep);
		while (getline(cin, s)&&!s.empty()) {
			i = 0, a = "";
			while (s[i] != ',')a += s[i++];
			f[p].title = a, a = "", i++;
			while (s[i] != ',')a += s[i++];
			f[p].firstname = a, a = "", i++;
			while (s[i] != ',')a += s[i++];
			f[p].lastname = a, a = "", i++;
			while (s[i] != ',')a += s[i++];
			f[p].address = a, a = "", i++;
			while (s[i] != ',')a += s[i++];
			f[p].homephone = a, a = "", i++;
			while (s[i] != ',')a += s[i++];
			f[p].workphone = a, a = "", i++;
			while (i<s.length())a += s[i++];
			f[p].campusmail = a, a = "", i++;
			f[p++].department = dep;
		}
	}sort(f, f + p);
	for (i = 0; i < p; i++) {
		cout << "----------------------------------------" << endl <<
			f[i].title << " " << f[i].firstname << " "<<f[i].lastname << endl <<
			f[i].address << endl <<
			"Department: " << f[i].department <<endl<<
			"Home Phone: " << f[i].homephone <<endl<<
			"Work Phone: " << f[i].workphone <<endl<<
			"Campus Box: " << f[i].campusmail<<endl;
	}
}
