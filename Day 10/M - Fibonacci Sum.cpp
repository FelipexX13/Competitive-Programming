// <3
// Tema: Math / Fibonacci (Fast Doubling)
// Resuelve "Fibonacci Sum": para T casos con N y M (hasta 1e9), calcula la suma
// F(N)+F(N+1)+...+F(M) modulo 1e9+7. Usa la identidad telescopica de que la suma de
// Fibonacci sum_{i=0}^{k} F(i) = F(k+2) - 1, por lo que la suma pedida es
// F(M+2) - F(N+1) mod MOD (visible en la linea fibmod(b+2) - fibmod(a+1)). Cada F(n)
// se calcula en O(log n) con el algoritmo de duplicacion rapida (fast doubling), que
// recorre los bits de n de mas a menos significativo aplicando las formulas
// F(2k)=F(k)*(2*F(k+1)-F(k)) y F(2k+1)=F(k)^2+F(k+1)^2 en aritmetica modular.

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