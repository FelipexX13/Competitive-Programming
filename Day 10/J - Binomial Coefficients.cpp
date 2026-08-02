// <3
// Tema: Math / Combinatoria (Factoriales Modulares)
// Resuelve "Binomial Coefficients": calcula n coeficientes binomiales C(a,b) modulo
// 1e9+7. Precomputa fact[i] = i! mod MOD para todo i hasta MAXN=1e6, y su inverso
// modular invFact[i] de atras hacia adelante en O(MAXN) (calculando solo una
// exponenciacion modular invFact[MAXN] = fact[MAXN]^(MOD-2) via Fermat, y derivando el
// resto con invFact[i-1] = invFact[i]*i). Cada consulta responde en O(1) con la formula
// fact[a] * invFact[b] * invFact[a-b] mod MOD.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MOD = 1000000007;
const int MAXN = 1000000;

vector<ll> fact(MAXN + 1), invFact(MAXN + 1);

ll modPow(ll a, ll e) {
    ll res = 1;
    while (e > 0) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = fact[i - 1] * i % MOD;

    invFact[MAXN] = modPow(fact[MAXN], MOD - 2);

    for (int i = MAXN; i >= 1; i--)
        invFact[i - 1] = invFact[i] * i % MOD;

    int n;
    cin >> n;

    while (n--) {
        int a, b;
        cin >> a >> b;

        ll ans = fact[a];
        ans = ans * invFact[b] % MOD;
        ans = ans * invFact[a - b] % MOD;

        cout << ans << '\n';
    }

    return 0;
}