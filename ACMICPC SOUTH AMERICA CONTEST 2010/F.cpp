#include <bits/stdc++.h>
using namespace std;

bool isEqual(char c1, char c2)
{
    if (c1 >= 'A' && c1 <= 'Z')
        c1 += 'a' - 'A';
    if (c2 >= 'A' && c2 <= 'Z')
        c2 += 'a' - 'A';
    return c1 == c2;
}

int main()
{
    string s;
    bool first, poss;
    char c;
    while (getline(cin, s) && s != "*")
    {
        first = poss = true;
        c = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
                first = true;
            else if (first)
            {
                if (c != 0 && !isEqual(s[i], c))
                {
                    poss = false;
                    break;
                }
                else if (c == 0)
                    c = s[i];
                first = false;
            }
        }
        if (poss)
            printf("Y\n");
        else
            printf("N\n");
    }
}
