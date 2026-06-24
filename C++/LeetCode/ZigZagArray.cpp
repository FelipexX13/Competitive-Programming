// <3
// Tema: Dynamic Programming / Prefix Sums
// Cuenta los arreglos "zigzag" de longitud n con valores en [l, r] (cada elemento alterna entre
// mayor y menor que su vecino), modulo 1e9+7. DP sobre la longitud manteniendo, para cada valor,
// cuantas secuencias terminan subiendo (up) o bajando (down); las transiciones se aceleran con
// sumas de prefijos y sufijos en O(n * (r-l)).

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    static constexpr int MOD = 1'000'000'007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<long long> up(m), down(m);
        vector<long long> pref(m + 1);
        vector<long long> suff(m + 1);
        vector<long long> newUp(m);
        vector<long long> newDown(m);

        for (int i = 0; i < m; i++) {
            up[i] = i;
            down[i] = m - 1 - i;
        }

        for (int len = 3; len <= n; len++) {
            pref[0] = 0;
            for (int i = 0; i < m; i++) {
                pref[i + 1] = (pref[i] + down[i]) % MOD;
            }

            suff[m] = 0;
            for (int i = m - 1; i >= 0; i--) {
                suff[i] = (suff[i + 1] + up[i]) % MOD;
            }

            for (int i = 0; i < m; i++) {
                newUp[i] = pref[i];
                newDown[i] = suff[i + 1];
            }

            up.swap(newUp);
            down.swap(newDown);
        }

        long long ans = 0;
        for (int i = 0; i < m; i++) {
            ans = (ans + up[i] + down[i]) % MOD;
        }

        return (int)ans;
    }
};