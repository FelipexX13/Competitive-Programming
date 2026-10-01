// <3
// Tema: CSES / Prefix Sums 2D
// Resumen: Prefix sums en dos dimensiones, donde lo unico nuevo es la inclusion-exclusion
// O: (n^2) de construccion y (1) por consulta
// Detalle: Prefix sums en dos dimensiones, donde lo unico nuevo es la inclusion-exclusion: al
// construir se suma arriba e izquierda y se RESTA la diagonal, que se conto dos veces, y al
// consultar el rectangulo se hace lo mismo al reves con las cuatro esquinas. CUANDO USAR:
// consultas de suma sobre submatrices en una matriz que no cambia. Construccion O(n^2), cada
// consulta O(1). Si la matriz cambia hay que irse a Fenwick 2D o segment tree 2D, que es
// bastante mas codigo. El truco de reservar (n+1)x(n+1) con la fila y columna 0 en cero es lo
// que hace que los indices i-1 y j-1 nunca se salgan, sin un solo if de borde.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> pref(n + 1, vector<int>(n + 1));

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        for (int j = 1; j <= n; j++) {
            int tree = (s[j - 1] == '*');

            pref[i][j] = tree
                       + pref[i - 1][j]
                       + pref[i][j - 1]
                       - pref[i - 1][j - 1];
        }
    }

    while (q--) {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;

        cout << pref[y2][x2]
             - pref[y1 - 1][x2]
             - pref[y2][x1 - 1]
             + pref[y1 - 1][x1 - 1]
             << '\n';
    }
}
