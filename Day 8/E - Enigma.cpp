
#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s1,s2;
    cin >> s1 >> s2;
    int god=0;
    
    for(int i = 0 ; i <= s1.size()-s2.size();i++)
    {
        string tempi = s1.substr(i,s2.size());
        bool ok = false;
        for(int j = 0 ; j < s2.size() && ok == false;j++)
        {
            if(tempi[j]==s2[j])
            {
                ok = true;
            }
        }
        if(ok == false)
        {
            god++;
        }
    }
    
    cout << god << endl;

    return 0;
}