// <3
// Tema: CSES / Greedy + Binary Lifting sobre el Tiempo
// Maximo de peliculas que se pueden ver enteras dentro de [a,b]. El greedy de intervalos es el de
// siempre: ver primero la que TERMINA mas temprano entre las que empiezan despues del momento
// actual (intercambio clasico: cambiar cualquier eleccion por la que termina antes nunca empeora).
// Aqui el truco es indexar por TIEMPO, no por pelicula: nxt[t] = el fin mas temprano de una
// pelicula que empieza en t o despues. Se calcula con un minimo de sufijos, y queda como una
// funcion t -> nxt[t] que es justo "ver la siguiente pelicula".
// Sobre esa funcion se monta binary lifting: up[k][t] es el momento tras ver 2^k peliculas, y cada
// consulta cuenta cuantos saltos caben antes de pasarse de b. O(log T) por consulta.
// Es el mismo patron que "Visible Building Queries": un puntero, doubling encima, y contar saltos.
// La tabla up[20][10^6] ocupa unos 80 MB, que es el precio de indexar por tiempo.

#include <bits/stdc++.h>
using namespace std;

const int MAXT = 1000000;
const int LOG = 20;

int up[LOG][MAXT + 2];
int nxt[MAXT + 2];
int en[MAXT + 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i <= MAXT + 1; i++)
        en[i] = MAXT + 1;

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        en[a] = min(en[a], b);
    }

    nxt[MAXT + 1] = MAXT + 1;

    for (int i = MAXT; i >= 1; i--)
        nxt[i] = min(en[i], nxt[i + 1]);

    for (int i = 1; i <= MAXT; i++)
        up[0][i] = nxt[i];

    up[0][MAXT + 1] = MAXT + 1;

    for (int k = 1; k < LOG; k++) {
        up[k][MAXT + 1] = MAXT + 1;

        for (int i = 1; i <= MAXT; i++) {
            int mid = up[k - 1][i];
            up[k][i] = up[k - 1][mid];
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;

        int pos = a;
        int ans = 0;

        for (int k = LOG - 1; k >= 0; k--) {
            if (up[k][pos] <= b) {
                ans += (1 << k);
                pos = up[k][pos];
            }
        }

        cout << ans << '\n';
    }
}
