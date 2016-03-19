#include <string>
#include <iostream>
using namespace std;

struct person {
	string name;
	int dd, mm, yyyy;
	bool operator <(person a) {
		if (yyyy != a.yyyy)return yyyy > a.yyyy;
		if (mm != a.mm)return mm > a.mm;
		if (dd != a.dd)return dd > a.dd;
	}
};

int main() {
	person pmax,aux,pmin;
	int n;
	cin >> n;
	cin >> aux.name >> aux.dd >> aux.mm >> aux.yyyy;
	pmin = pmax = aux;
	for (int i = 1; i < n; i++) {
		cin >> aux.name >> aux.dd >> aux.mm >> aux.yyyy;
		if (aux < pmin)pmin = aux;
		if (pmax < aux)pmax = aux;
	}cout << pmin.name << endl << pmax.name << endl;
}
