// <3
// Tema: Data Structures / Conteo de Inversiones y Redondeo Exacto
// Resumen: Cuenta las inversiones de la secuencia de alturas (pares i < j con h[i] > h[j]) y
// responde la fraccion que...
// Detalle: Resuelve "Skyline" (problema K, ICPC 2024): cuenta las inversiones de la secuencia
// de alturas (pares i < j con h[i] > h[j]) y responde la fraccion que son del total de pares,
// inversiones / (N(N-1)/2), con 3 decimales. El conteo es el de "frosh" (Frosh Week, CCPL, en
// este cuaderno): recorriendo de izquierda a derecha, los i elementos anteriores menos los que
// son <= h[i] dan los mayores que quedaron a la izquierda. DOS TRAMPAS, Y LA PRIMERA VERSION DE
// ESTE ARCHIVO CAIA EN LAS DOS: 1) El enunciado dice -20 < h < 300, pero su propio sample trae
// una altura de -29. La primera version indexaba el Fenwick con h + 21, y con -29 quedaba en
// -8: fw.add(-8) no termina nunca (i & -i se hace 0 y el indice deja de avanzar). Se colgaba
// con el sample. Por eso ahora se comprime, que funciona con cualquier valor. Leccion: cuando
// el sample contradice las cotas, manda el sample. 2) Las reglas generales piden redondear con
// los empates HACIA ARRIBA. Con double y printf, un empate exacto como 0.0625 (N = 32 con 31
// inversiones) se redondea hacia el par y sale 0.062. Ahora se calcula con enteros: (2000*HD +
// PHD) / (2*PHD) da las milesimas con el empate hacia arriba. Verificado en 48 empates exactos
// y 1500 casos generales. El caso N = 1 va aparte porque el total de pares seria 0 y la
// division, 0/0.

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<long long> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }

    long long sum(int idx) {
        long long res = 0;

        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;

    while (cin >> N && N != 0) {

        vector<int> h(N);

        for (int &x : h)
            cin >> x;

        if (N == 1) {
            cout << "0.000\n";
            continue;
        }

        // Compresion de coordenadas: no se confia en el rango del enunciado,
        // porque el propio sample trae una altura de -29.
        vector<int> v = h;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());

        Fenwick fw(v.size());

        long long inversions = 0;

        for (int i = 0; i < N; i++) {

            int x = lower_bound(v.begin(), v.end(), h[i]) - v.begin() + 1;

            // Elementos anteriores que son <= h[i]
            long long leq = fw.sum(x);

            // De los i anteriores, los demas son > h[i]
            inversions += i - leq;

            fw.add(x, 1);
        }

        long long totalPairs = 1LL * N * (N - 1) / 2;

        // Redondeo a 3 decimales con enteros: empates hacia arriba, como pide
        // el enunciado. Con double + printf un empate exacto (0.0625) puede
        // redondearse hacia el par y dar 0.062 en vez de 0.063.
        long long mil = (2000 * inversions + totalPairs) / (2 * totalPairs);

        string frac = to_string(mil % 1000);
        while (frac.size() < 3)
            frac = "0" + frac;

        cout << mil / 1000 << '.' << frac << '\n';
    }

    return 0;
}
