#include <bits/stdc++.h>
using namespace std;

int getLength(char c)
{
    if (c == 'W')
        return 64;
    else if (c == 'H')
        return 32;
    else if (c == 'Q')
        return 16;
    else if (c == 'E')
        return 8;
    else if (c == 'S')
        return 4;
    else if (c == 'T')
        return 2;
    return 1;
}

int main()
{
    string s;
    int acum, ans;
    while (cin >> s && s != "*")
    {
        acum = ans = 0;
        for (int i = 1; i < s.length(); i++)
        {
            if (s[i] == '/')
            {
                if (acum == 64)
                    ans++;
                acum = 0;
            }
            else
            {
                acum += getLength(s[i]);
            }
        }
        cout << ans << endl;
    }
}
