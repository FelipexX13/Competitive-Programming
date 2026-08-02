// <3
// Tema: Dynamic Programming / Valor Esperado
// Resuelve "Revenge of The Salary of AtCoder Inc.": con un dado de N caras y x=0, en
// cada ronda se tira el dado (resultado y); si x<y se cobra A_y yen y x pasa a valer y,
// si no el proceso termina. Hay que hallar el valor esperado del salario total, modulo
// 998244353. Define E[i] = valor esperado de pago futuro estando en x=i; por linealidad
// de la esperanza, E[i] = (1/N) * suma sobre y>i de (A_y + E[y]), ya que tirar y<=i
// termina el proceso sin pago adicional. El codigo calcula esto de atras hacia adelante
// (i de N a 1) manteniendo S = suma acumulada de (A_y+E[y]) para y>i, de modo que
// E[i] = S * invN (invN es el inverso modular de N via Fermat); el resultado final es
// E[0] = S * invN tras procesar todo el arreglo.

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