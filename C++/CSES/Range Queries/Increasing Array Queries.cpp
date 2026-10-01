// <3
// Tema: CSES / Monotonic Stack + Binary Lifting con Costos
// Resumen: Para cada consulta [l,r], el minimo de sumas para que el tramo quede no decreciente
// Detalle: Para cada consulta [l,r], el minimo de sumas para que el tramo quede no decreciente.
// La solucion optima es subir cada elemento al MAXIMO DE PREFIJO del tramo, y ese maximo solo
// cambia en los "siguientes mayores". Entonces el tramo se parte en bloques: desde i, todo
// hasta antes de up[0][i] (el siguiente estrictamente mayor) se sube al valor a[i], y cuesta
// a[i] * (j - i - 1) - (pref[j-1] - pref[i]) El siguiente mayor sale con una pila monotona de
// derecha a izquierda, con a[n+1] = 1e18 de centinela para que todos tengan a donde apuntar. EL
// BINARY LIFTING GUARDA EL COSTO JUNTO CON EL SALTO: up[k][i] es a donde se llega con 2^k
// saltos, y cost[k][i] lo que se paga en ese camino. Cada consulta baja de la potencia mas alta
// a la mas baja mientras el salto no se pase de r, y el tramo final (de x hasta r, sin llegar
// al siguiente mayor) se cobra aparte con la misma formula. Es la misma combinacion que
// "Visible Building Queries", con una sola diferencia: aqui cada salto ademas acumula un valor.
// Ese es el patron general: si un puntero define una funcion y cada paso tiene un costo, el
// doubling precalcula a la vez el destino y la suma.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 200005;
const int LOG = 20;

ll a[N], pref[N], cost[LOG][N];
int up[LOG][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    a[n + 1] = 1e18;

    for (int k = 0; k < LOG; k++)
        up[k][n + 1] = n + 1;

    stack<int> st;
    st.push(n + 1);

    for (int i = n; i >= 1; i--) {
        while (a[st.top()] <= a[i])
            st.pop();

        up[0][i] = st.top();

        int j = up[0][i];

        cost[0][i] =
            a[i] * (j - i - 1)
            - (pref[j - 1] - pref[i]);

        st.push(i);
    }

    for (int k = 1; k < LOG; k++) {
        for (int i = 1; i <= n; i++) {
            int mid = up[k - 1][i];

            up[k][i] = up[k - 1][mid];

            cost[k][i] =
                cost[k - 1][i] +
                cost[k - 1][mid];
        }
    }

    while (q--) {
        int l, r;
        cin >> l >> r;

        int x = l;
        ll ans = 0;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][x] <= r) {
                ans += cost[k][x];
                x = up[k][x];
            }
        }

        if (x < r) {
            ans += a[x] * (r - x)
                 - (pref[r] - pref[x]);
        }

        cout << ans << '\n';
    }
}
