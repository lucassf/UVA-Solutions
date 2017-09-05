#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 1048576

vector<ll> primes;
bitset<MAXN> bs;

void sieve(int n) {
	int sievesize = n-2;
	bs.set();
	bs[0] = bs[1] = 0;
	for (ll i = 2; i <= sievesize; i++) {
        //cout<<i<<endl;
		if (bs[i]) {
			for (ll j = i * i; j <= (ll)sievesize; j += i) bs[j] = 0;
			primes.push_back(i);
		}
	}
}

int qtt[5];

int primeFactors(int N) {
	int factors = 0;
	int PF_idx = 0, PF = primes[PF_idx];
	while (PF * PF <= N) {
        if (N%PF==0){

            while (N % PF == 0) {
                N /= PF;
                qtt[factors]++;
            }
            factors++;
        }
		PF = primes[++PF_idx];
		if (factors>3)break;
	}
	// special case if N is a prime
	if (N != 1) qtt[factors++] =1;
	return factors;
}

int main(){
    sieve(MAXN);
    int n,c=1;
    bool poss;

    while (scanf("%d",&n)!=EOF){
        for (int i=0;i<5;i++)qtt[i] = 0;
        int factors = primeFactors(n);
        poss = false;
        if (factors>=4)poss = true;
        else if (factors == 3){
            if (qtt[0]>1||qtt[1]>1||qtt[2]>1)poss=true;
        }else if (factors == 2){
            if ((qtt[0]>1&&qtt[1]>1)||qtt[0]>4||qtt[1]>4)poss=true;
        }else if (qtt[0]>7)poss=true;

        printf("Instancia %d\n",c++);
        if (poss)printf("sim\n\n");
        else printf("nao\n\n");
    }
}
