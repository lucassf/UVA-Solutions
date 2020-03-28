#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define INF 1000000007
typedef long long int ll;

inline bool isPrime(int a)
{
    int b = sqrt(a);
    if (a % 2 == 0 && a != 2)
        return 0;

    for (int i = 3; i <= b; i += 2)
    {
        if (a % i == 0)
            return 0;
    }
    return 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    while (cin >> N)
    {
        while (!isPrime(N))
            N--;
        cout << N << endl;
    }
}
