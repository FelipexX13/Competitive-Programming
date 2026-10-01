// <3
// Tema: CSES / Monotonic Stack + Binary Lifting
// Resumen: Dos tecnicas encadenadas, y la combinacion es lo que vale
// Detalle: Dos tecnicas encadenadas, y la combinacion es lo que vale. Primero una PILA MONOTONA
// de derecha a izquierda calcula nxt[i], el siguiente edificio mas alto que i. Eso deja un
// arbol implicito donde el padre de i es nxt[i]: desde i, los edificios que se ven son i,
// nxt[i], nxt[nxt[i]]... Y como hay que contar cuantos de esos caben antes de pasarse de r, se
// le monta BINARY LIFTING encima: up[j][i] es el resultado de saltar 2^j veces, asi que contar
// los saltos se hace en O(log n) bajando de la potencia mas alta a la mas baja, en vez de
// caminar uno por uno. CUANDO USAR CADA UNA: la pila monotona para "el siguiente mayor o menor"
// en O(n), que es la base de los histogramas y de los rangos donde un elemento es el maximo. El
// binary lifting cuando hay que seguir una cadena de punteros MUCHAS veces y cada salto es
// fijo: el mismo mecanismo del LCA. LA IDEA QUE SE REPITE: si un puntero define una funcion i
// -> f(i), entonces las potencias de esa funcion se precalculan con doubling y cualquier
// cantidad de saltos sale en O(log n). Sirve para LCA, para funciones de permutacion y para los
// "k pasos adelante" de cualquier grafo funcional.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> h(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> h[i];

    vector<int> nxt(n + 1, 0);
    stack<int> st;

    for (int i = n; i >= 1; i--) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();

        if (!st.empty())
            nxt[i] = st.top();

        st.push(i);
    }

    int LOG = 18;
    vector<vector<int>> up(LOG, vector<int>(n + 1));

    for (int i = 1; i <= n; i++)
        up[0][i] = nxt[i];

    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            if (up[j - 1][i])
                up[j][i] = up[j - 1][up[j - 1][i]];
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;

        int pos = a;
        int ans = 1;

        for (int j = LOG - 1; j >= 0; j--) {
            int x = up[j][pos];

            if (x != 0 && x <= b) {
                pos = x;
                ans += (1 << j);
            }
        }

        cout << ans << '\n';
    }
}
