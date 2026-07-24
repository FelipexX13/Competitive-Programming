#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

ll fibmod(ll n, ll mod) {
    ll a = 0, b = 1, c;
    for (int i = 63 - __builtin_clzll(n); i >= 0; i--) {
        c = a;
        a = (c * (2 * b - c + mod)) % mod;
        b = (c * c + b * b) % mod;

        if ((n >> i) & 1) {
            c = (a + b) % mod;
            a = b;
            b = c;
        }
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    while (q--) {
        ll a, b;
        cin >> a >> b;

        ll ans = (fibmod(b + 2, MOD) - fibmod(a + 1, MOD) + MOD) % MOD;
        cout << ans << '\n';
    }
}