// <3
// Tema: CSES / Prefix Sums
// La estructura mas barata que existe: pref[i] = suma de los primeros i, y la suma de [a,b] sale
// como pref[b] - pref[a-1]. Construccion O(n), consulta O(1), y ni una linea de estructura.
// CUANDO USAR: el arreglo NO cambia y la operacion tiene INVERSA (suma, xor, producto sin ceros).
// Eso es todo. Si hay actualizaciones se necesita Fenwick; si la operacion no tiene inversa
// (min, max, gcd) no se puede restar y toca sparse table o segment tree.
// Lo del indice 1 no es capricho: con pref de tamano n+1 y pref[0]=0 desaparece el if del borde
// cuando a = 1. Y long long, porque n valores de 10^9 se pasan de int sin avisar.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, q;
    cin >> n >> q;

    vector<ll> pref(n + 1);

    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }

    while (q--) {
        ll a, b;
        cin >> a >> b;

        cout << pref[b] - pref[a - 1] << '\n';
    }
}
