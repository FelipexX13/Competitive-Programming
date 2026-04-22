#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static inline int64 comb3(int64 n) {
    if (n < 3) return 0;
    return n * (n - 1) * (n - 2) / 6;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p, q;
    cin >> p >> q;

    if (p > q) swap(p, q); // p = lado pequeño, q = lado grande

    const int W = p + 1; // cantidad de columnas de puntos
    const int H = q + 1; // cantidad de filas de puntos

    // gtProd[s][k] = cantidad de alpha en [0..s] con alpha*(s-alpha) > k
    // eqProd[s][k] = cantidad de alpha en [0..s] con alpha*(s-alpha) = k
    int maxS = p;
    int maxK = maxS * maxS / 4;

    vector<vector<int>> gtProd(maxS + 1, vector<int>(maxK + 1, 0));
    vector<vector<int>> eqProd(maxS + 1, vector<int>(maxK + 1, 0));

    for (int s = 0; s <= maxS; s++) {
        int localMax = s * s / 4;
        vector<int> freq(localMax + 1, 0);

        for (int alpha = 0; alpha <= s; alpha++) {
            int val = alpha * (s - alpha);
            freq[val]++;
        }

        int suf = 0;
        for (int k = localMax; k >= 0; k--) {
            gtProd[s][k] = suf;
            suf += freq[k];
            eqProd[s][k] = freq[k];
        }
    }

    auto getGt = [&](int s, int64 k) -> int64 {
        int64 localMax = 1LL * s * s / 4;
        if (k > localMax) return 0;
        return gtProd[s][(int)k];
    };

    auto getEq = [&](int s, int64 k) -> int64 {
        int64 localMax = 1LL * s * s / 4;
        if (k > localMax) return 0;
        return eqProd[s][(int)k];
    };

    int64 acute = 0, right = 0, obtuse = 0, degenerate = 0;

    // ------------------------------------------------------------
    // 1) Todos en la misma fila -> degenerados
    // ------------------------------------------------------------
    degenerate += 1LL * H * comb3(W);

    // ------------------------------------------------------------
    // 2) Triángulos usando exactamente 2 filas
    //
    // Si la distancia vertical es h:
    // - caso "punto solo entre la base"
    // - caso "punto solo afuera de la base"
    // ------------------------------------------------------------
    for (int h = 1; h <= q; h++) {
        int64 verticalWays = 2LL * (H - h); // escoger las dos filas y cuál tiene 2 puntos

        for (int s = 1; s <= p; s++) {
            int64 waysPlaceX = W - s;
            int64 weight = verticalWays * waysPlaceX;

            // Punto solo entre los dos de la base
            int64 rightBetween = 2 + getEq(s, 1LL * h * h); // extremos + posibles internos
            int64 obtuseBetween = getGt(s, 1LL * h * h);
            int64 acuteBetween = (s + 1) - rightBetween - obtuseBetween;

            // Punto solo fuera del intervalo horizontal de la base
            // todos esos son obtusos, salvo el caso alineado con un extremo,
            // que ya quedó contado en "between" con alpha=0 o beta=0
            int64 obtuseOutside = 2LL * (s - 1);

            right += weight * rightBetween;
            obtuse += weight * (obtuseBetween + obtuseOutside);
            acute += weight * acuteBetween;
        }
    }

    // ------------------------------------------------------------
    // 3) Triángulos usando exactamente 3 filas distintas
    //
    // Distancias verticales:
    // fila1 -> fila2 = a
    // fila2 -> fila3 = b
    //
    // Se cuenta por span horizontal total s.
    // ------------------------------------------------------------
    for (int a = 1; a < q; a++) {
        for (int b = 1; a + b <= q; b++) {
            int64 verticalWays = H - (a + b);
            int64 ab = 1LL * a * b;
            int64 A = 1LL * a * (a + b);
            int64 B = 1LL * b * (a + b);

            for (int s = 0; s <= p; s++) {
                int64 waysPlaceX = W - s;
                int64 weight = verticalWays * waysPlaceX;

                // Caso monótono:
                // x1<=x2<=x3 o x1>=x2>=x3
                // Todo no degenerado aquí es obtuso.
                int64 orient = (s == 0 ? 1 : 2);

                int64 degHit = 0;
                if ((1LL * a * s) % (a + b) == 0) {
                    degHit = 1;
                }

                degenerate += weight * orient * degHit;
                obtuse += weight * orient * ((s + 1) - degHit);

                if (s == 0) continue;

                // --------------------------------------------
                // Caso donde x1 queda estrictamente "en medio"
                // u < 0 y u+v > 0
                // alpha en [1 .. s-1]
                // --------------------------------------------
                {
                    int64 total = s - 1;
                    if (total > 0) {
                        int64 low = min<int64>(total, (ab - 1) / s);
                        int64 rightLin = ((ab % s == 0) && (1 <= ab / s) && (ab / s <= s - 1)) ? 1 : 0;

                        int64 obt1 = low + getGt(s, A);
                        int64 rig1 = rightLin + getEq(s, A);
                        int64 acu1 = total - obt1 - rig1;

                        obtuse += weight * 2 * obt1;
                        right += weight * 2 * rig1;
                        acute += weight * 2 * acu1;
                    }
                }

                // --------------------------------------------
                // Caso donde x3 queda en medio o empata con x1
                // v < 0 y u+v >= 0
                // alpha en [0 .. s-1]
                // --------------------------------------------
                {
                    int64 total = s;
                    int64 low = min<int64>(total, (ab - 1) / s);
                    int64 rightLin = ((ab % s == 0) && (1 <= ab / s) && (ab / s <= s)) ? 1 : 0;

                    int64 obt3 = low + getGt(s, B);
                    int64 rig3 = rightLin + getEq(s, B);
                    int64 acu3 = total - obt3 - rig3;

                    obtuse += weight * 2 * obt3;
                    right += weight * 2 * rig3;
                    acute += weight * 2 * acu3;
                }
            }
        }
    }

    cout << acute << '\n';
    cout << right << '\n';
    cout << obtuse << '\n';
    cout << degenerate << '\n';

    return 0;
}