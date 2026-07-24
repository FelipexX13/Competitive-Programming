
#include <iostream>
using namespace std;
typedef long long ll;
ll MOD = 1000000007;

ll expmod(ll b, ll e, ll m) 
{
    ll ans = 1;
    while (e) {
        if (e&1) ans = (1ll*ans*b) % m;
        b = (1ll*b*b) % m;
        e /= 2;
    }
    return ans;
}


int main()
{
    ll n; cin >> n;
    
    while(n--)
    {
        ll a , b , c; cin >> a >> b >> c;
        
        cout<< expmod(a,expmod(b,c,MOD-1),MOD)<< endl;
    }

    return 0;
}