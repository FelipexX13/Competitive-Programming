// <3
// Tema: CSES / Cubetas por Potencia de 2 + Segment Tree
// Resumen: La version por rangos del clasico "menor suma que no se puede formar"
// Detalle: La version por rangos del clasico "menor suma que no se puede formar". El greedy de
// siempre es ordenar las monedas y mantener sum: si la siguiente moneda es <= sum+1 se absorbe,
// si no la respuesta es sum+1. Ordenar cada rango seria O(n log n) por consulta; lo que lo
// evita son las CUBETAS: la moneda x va a la cubeta floor(log2 x), o sea que en la cubeta k
// todo esta en [2^k, 2^(k+1)). LA OBSERVACION QUE HACE FUNCIONAR LAS CUBETAS: dentro de una
// misma cubeta, cualquier moneda es menor que el doble de la mas chica. Asi que si la mas chica
// de la cubeta cabe (es <= sum+1), despues de absorberla TODAS las demas de esa cubeta tambien
// caben, y se pueden sumar de golpe con una suma prefija. Solo hace falta saber el MINIMO de
// cada cubeta en el rango, y para eso va un segment tree de minimos por cubeta. Con 30 cubetas
// cada consulta cuesta O(30 log n) en vez de ordenar. Es pesado en memoria: las dos tablas de
// 30 columnas suman cerca de 100 MB. En CSES entra (512 MB); en un juez de 256 tambien, pero no
// sobra mucho.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 200005;
const int K = 30;
const int INF = 2e9;

int st[2 * N][K];
ll pref[N][K];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < 2 * N; i++)
        for (int j = 0; j < K; j++)
            st[i][j] = INF;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        int k = 31 - __builtin_clz(x);

        st[N + i][k] = x;
        pref[i][k] = x;
    }

    for (int i = 1; i <= n; i++)
        for (int k = 0; k < K; k++)
            pref[i][k] += pref[i - 1][k];

    for (int i = N - 1; i >= 1; i--)
        for (int k = 0; k < K; k++)
            st[i][k] = min(st[i * 2][k], st[i * 2 + 1][k]);

    while (q--) {
        int l, r;
        cin >> l >> r;

        int L = l + N;
        int R = r + N;

        int mn[K];

        for (int k = 0; k < K; k++)
            mn[k] = INF;

        while (L <= R) {
            if (L & 1) {
                for (int k = 0; k < K; k++)
                    mn[k] = min(mn[k], st[L][k]);
                L++;
            }

            if (!(R & 1)) {
                for (int k = 0; k < K; k++)
                    mn[k] = min(mn[k], st[R][k]);
                R--;
            }

            L /= 2;
            R /= 2;
        }

        ll sum = 0;

        for (int k = 0; k < K; k++) {
            if (sum + 1 < mn[k] &&
                sum + 1 < (1LL << (k + 1))) {
                cout << sum + 1 << '\n';
                goto done;
            }

            sum += pref[r][k] - pref[l - 1][k];
        }

        cout << sum + 1 << '\n';

        done:;
    }
}
