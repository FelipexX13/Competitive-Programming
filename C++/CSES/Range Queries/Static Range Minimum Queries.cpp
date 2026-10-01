// <3
// Tema: CSES / Sparse Table
// Resumen: Sparse table: st[k][i] es el minimo de los 2^k elementos que arrancan en i
// O: (n log n) de tabla y (1) por consulta
// Detalle: Sparse table: st[k][i] es el minimo de los 2^k elementos que arrancan en i. Se
// construye en O(n log n) partiendo cada rango en dos mitades de 2^(k-1), y cada consulta se
// responde en O(1) cubriendo [l,r] con DOS bloques de tamano 2^k que se solapan. Solaparse no
// es problema, y esa es la clave: el minimo es IDEMPOTENTE, contar un elemento dos veces no
// cambia nada. CUANDO USAR: arreglo estatico y operacion idempotente (min, max, gcd, and, or).
// Consulta O(1), mas rapido que cualquier segment tree. CUANDO NO: si el arreglo cambia, la
// sparse table no se puede actualizar y toca segment tree. Y para SUMA no sirve, porque solapar
// los dos bloques contaria de mas.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // K = cantidad de niveles que necesitamos.
    // st[k][i] = minimo de 2^k elementos empezando en i.
    int K = 1;

    while ((1 << K) <= n)
        K++;

    vector<vector<ll>> st(K, vector<ll>(n + 1));

    // Nivel 0: rangos de tamano 1.
    for (int i = 1; i <= n; i++)
        cin >> st[0][i];

    // Construimos los demas niveles.
    for (int k = 1; k < K; k++) {

        // Tamano del rango = 2^k
        int len = 1 << k;

        for (int i = 1; i + len - 1 <= n; i++) {

            // Dividimos el rango en dos partes
            // de tamano 2^(k-1).
            st[k][i] = min(
                st[k - 1][i],
                st[k - 1][i + (len / 2)]
            );
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;

        int len = b - a + 1;

        // Mayor potencia de 2 que cabe en len.
        int k = 0;

        while ((1 << (k + 1)) <= len)
            k++;

        // Primer bloque de tamano 2^k
        ll x = st[k][a];

        // Segundo bloque de tamano 2^k,
        // empezando desde el final.
        ll y = st[k][b - (1 << k) + 1];

        cout << min(x, y) << '\n';
    }
}
