// <3
// Tema: Geometry / Contar Cruces de Cuerdas con Fenwick
// Resumen: Cada criatura define una recta que corta una parabola en dos puntos, o sea una
// CUERDA de la region
// O: (n log n), cruces de cuerdas contadas como inversiones con Fenwick
// Detalle: Resuelve "Lonely Creatures" (problema L, Regionals 2025): cada criatura define una
// recta que corta una parabola en dos puntos, o sea una CUERDA de la region, y hay que contar
// cuantos pares de cuerdas se cruzan por dentro. DOS PASOS, Y EL PRIMERO ES EL QUE SE PIENSA:
// 1) Sacar los extremos de cada cuerda resolviendo la ecuacion cuadratica A*x^2 - M*x + (B-C) =
// 0. El discriminante D = M^2 - 4A(B-C) decide: si es negativo o cero la recta no entra al
// interior y esa criatura se descarta. 2) Dos cuerdas (l1,r1) y (l2,r2) se cruzan por dentro si
// y solo si sus extremos se INTERCALAN: l1 < l2 < r1 < r2. Ordenando por el extremo izquierdo,
// contar los cruces se vuelve contar INVERSIONES sobre los extremos derechos, que es lo que
// hace el Fenwick. El desempate importa: si dos cuerdas comparten el extremo izquierdo no se
// cruzan por dentro (se tocan en la frontera), y por eso el orden y las comparaciones usan < y
// no <=. Ese detalle cambia la respuesta y no lo avisa ningun caso chico. Los extremos son
// reales, asi que se comprimen con lowerBound y upperBound escritos a mano sobre long double, y
// con EPS para los empates. Cuando se puede, es preferible comparar en enteros (como en "C -
// Clean Streets"); aqui las raices son irracionales y no queda opcion. Es el mismo conteo de
// inversiones de "frosh" (Frosh Week, CCPL) de este cuaderno, aplicado a geometria.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

const ld EPS = 1e-12L;

struct Chord {
    ld L, R;
};

struct Fenwick {
    int n;
    vector<int> bit;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    void add(int pos, int val) {
        for (; pos <= n; pos += pos & -pos)
            bit[pos] += val;
    }

    int sum(int pos) {
        int ans = 0;

        for (; pos > 0; pos -= pos & -pos)
            ans += bit[pos];

        return ans;
    }
};

// ------------------------------------------------------------
// Primer indice cuyo valor es > x
// ------------------------------------------------------------
int upperBound(const vector<ld>& a, ld x) {
    int l = 0;
    int r = a.size();

    while (l < r) {
        int m = (l + r) / 2;

        if (a[m] <= x + EPS)
            l = m + 1;
        else
            r = m;
    }

    return l;
}

// ------------------------------------------------------------
// Primer indice cuyo valor es >= x
// ------------------------------------------------------------
int lowerBound(const vector<ld>& a, ld x) {
    int l = 0;
    int r = a.size();

    while (l < r) {
        int m = (l + r) / 2;

        if (a[m] < x - EPS)
            l = m + 1;
        else
            r = m;
    }

    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll A, B;

    cin >> N >> A >> B;

    vector<Chord> chords;

    for (int i = 0; i < N; i++) {

        ll M, C;
        cin >> M >> C;

        /*
            Mx + C = A*x^2 + B

            A*x^2 - M*x + (B-C) = 0

            D = M^2 - 4A(B-C)
        */

        ll D = M * M - 4LL * A * (B - C);

        // No entra al interior.
        if (D <= 0)
            continue;

        ld sq = sqrtl((ld)D);

        ld L = ((ld)M - sq) / (2.0L * A);
        ld R = ((ld)M + sq) / (2.0L * A);

        chords.push_back({L, R});
    }

    if (chords.size() < 2) {
        cout << 0 << '\n';
        return 0;
    }

    // --------------------------------------------------------
    // Ordenar por L.
    //
    // Si L es igual, NO pueden cruzarse dentro:
    // se encuentran sobre la frontera.
    // --------------------------------------------------------

    sort(chords.begin(), chords.end(), [](const Chord& a,
                                          const Chord& b) {

        if (fabsl(a.L - b.L) > EPS)
            return a.L < b.L;

        return a.R < b.R;
    });

    // --------------------------------------------------------
    // Compresion de R
    // --------------------------------------------------------

    vector<ld> vals;

    for (auto &c : chords)
        vals.push_back(c.R);

    sort(vals.begin(), vals.end());

    vals.erase(
        unique(vals.begin(), vals.end(),
            [](ld a, ld b) {
                return fabsl(a - b) <= EPS;
            }),
        vals.end()
    );

    Fenwick fw(vals.size());

    ll ans = 0;

    int i = 0;
    int processed = 0;

    while (i < (int)chords.size()) {

        int j = i + 1;

        while (j < (int)chords.size() &&
               fabsl(chords[j].L - chords[i].L) <= EPS) {
            j++;
        }

        /*
            Todas las cuerdas anteriores tienen:

                L_anterior < L_actual

            porque estamos procesando un grupo completo
            de L iguales.

            Queremos:

                L_actual < R_anterior < R_actual

            Entonces:

                count(R <= L_actual)
              -
                count(R >= R_actual)

            equivalente a:

                # R en (L_actual, R_actual)
        */

        for (int k = i; k < j; k++) {

            ld L = chords[k].L;
            ld R = chords[k].R;

            // cantidad de R <= L
            int p1 = upperBound(vals, L);
            int left = fw.sum(p1);

            // cantidad de R < R
            int p2 = lowerBound(vals, R);
            int beforeR = fw.sum(p2);

            /*
                Queremos estrictamente:

                    L < R_previous < R
            */

            ans += beforeR - left;
        }

        // Ahora agregamos las cuerdas de este grupo.
        for (int k = i; k < j; k++) {

            int pos = lowerBound(vals, chords[k].R) + 1;

            fw.add(pos, 1);
            processed++;
        }

        i = j;
    }

    cout << ans << '\n';

    return 0;
}
