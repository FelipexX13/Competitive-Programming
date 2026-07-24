#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    ll ans1=0,ans2=0,ans3=0;
    
    //1
    if(s[0]== 'U' && s[1] == 'U') ans1+=0;
    else if(s[0]== 'U' && s[1] == 'D') ans1+=2;
    else if(s[0]== 'D' && s[1] == 'D') ans1+=1;
    else ans1+=1;
    for(int i = 2; i < s.size(); i++)
    {
        if(s[i] == 'D') ans1+=2;
    }
    
    //2
    if(s[0]== 'U' && s[1] == 'U') ans2+=1;
    else if(s[0]== 'U' && s[1] == 'D') ans2+=1;
    else if(s[0]== 'D' && s[1] == 'D') ans2+=0;
    else ans2+=2;
    for(int i = 2; i < s.size(); i++)
    {
        if(s[i] == 'U') ans2+=2;
    }
    
    //3 
    char act = s[0];
    for(int i = 1 ; i < s.size(); i++)
    {
        if(s[i] != act)
        {
            ans3++;
            act = s[i];
        }
    }
    
    cout << ans1 << endl;
    cout << ans2 << endl;
    cout << ans3 << endl;
    

    return 0;
}