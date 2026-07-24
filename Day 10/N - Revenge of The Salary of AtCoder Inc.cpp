#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

ll binpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

ll inv(ll x) {
    return binpow(x, MOD - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<ll> A(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    ll invN = inv(N);

    vector<ll> E(N + 2, 0);

    ll S = 0;

    for (int i = N; i >= 1; i--) {
        E[i] = S * invN % MOD;
        S = (S + A[i] + E[i]) % MOD;
    }

    ll ans = S * invN % MOD;

    cout << ans << '\n';
}