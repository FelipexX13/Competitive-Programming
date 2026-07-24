#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<ll> divisores(ll n) 
{
    vector<ll> div;
    for(ll i = 1; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            div.push_back(i);
            if(i != n/i) div.push_back(n/i);
        }
    }
    return div;
}

int main()
{
    ll n; cin >> n;
    vector<ll> xd(n);
    for(int i = 0; i < n; i++) 
    {
        cin >> xd[i];
    }
    
    vector<ll> juan = divisores(n); 
    sort(juan.begin(), juan.end());
    
    for(ll k : juan)
    {
        if(k >= 2) 
        {
        
            vector<ll> cont(k, 0);
            for(ll v : xd) 
            {
                cont[v % k]++;
            }
            
            bool ok = true;
            for(ll c : cont)
            {
                if(c != n/k) { ok = false; break; }
            }
            
            if(ok)
            {
                cout << k << endl;
                return 0;
            }
        }
    }
    
    cout << -1 << endl;
    return 0;
}