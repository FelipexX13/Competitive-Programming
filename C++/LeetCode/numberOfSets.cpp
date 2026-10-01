// <3
// Tema: Combinatorics / Formula Cerrada con Inverso Modular
// Resumen: Con n puntos alineados hay que contar de cuantas formas se dibujan k segmentos que
// no se solapen (si pueden...
// Detalle: Resuelve "Number of Sets of K Non-Overlapping Line Segments" (LeetCode 1621): con n
// puntos alineados hay que contar de cuantas formas se dibujan k segmentos que no se solapen
// (si pueden compartir un extremo), modulo 1e9+7. Toda la DP se colapsa en un solo binomial: la
// respuesta es C(n+k-1, 2k). La idea es que elegir k segmentos equivale a escoger 2k extremos
// de entre n+k-1 posiciones, porque cada extremo compartido se "desdobla" agregando k-1
// posiciones ficticias. Como hay que dividir en modular, se precomputan factoriales y sus
// inversos: una sola exponenciacion modular para inverso[limite] = factorial[limite]^(MOD-2)
// por Fermat, y el resto baja con inverso[i-1] = inverso[i] * i. Asi cada binomial sale en O(1)
// en vez de pagar un modpow por consulta. Costo total O(n + k + log MOD). OJO con el indice: si
// 2k > limite, limite - 2k se sale del arreglo. No pasa dentro de las restricciones del
// problema (k <= n-1 obliga a 2k <= n+k-1), pero si reusas este patron en otro problema, valida
// el rango antes.

class Solution {
public:
    long long MOD = 1000000007;

    long long modpow(long long a, long long e) {
        long long ans = 1;

        while (e) {
            if (e & 1)
                ans = ans * a % MOD;

            a = a * a % MOD;
            e >>= 1;
        }

        return ans;
    }

    long long division_mod(long long a, long long b) {
        return a % MOD * modpow(b, MOD - 2) % MOD;
    }

    int numberOfSets(int n, int k) {
        long long limite = n + k - 1;

        vector<long long> factorial(limite + 1);
        vector<long long> inverso(limite + 1);

        factorial[0] = 1;

        for (long long i = 1; i <= limite; i++) {
            factorial[i] = factorial[i - 1] * i % MOD;
        }

        inverso[limite] = modpow(factorial[limite], MOD - 2);

        for (long long i = limite; i >= 1; i--) {
            inverso[i - 1] = inverso[i] * i % MOD;
        }

        long long GOD = factorial[limite];

        GOD = GOD * inverso[2 * k] % MOD;
        GOD = GOD * inverso[limite - 2 * k] % MOD;

        return GOD;

        // Lo mismo sin la variable limite, escribiendo C(n+k-1, 2k) completo:
        //
        //     long long GOD = factorial[n + k - 1];
        //
        //     GOD = GOD * inverso[2 * k] % MOD;
        //     GOD = GOD * inverso[n - k - 1] % MOD;
        //
        //     return GOD;
        //
        // Es identico porque limite - 2k = (n + k - 1) - 2k = n - k - 1.
        // Ayuda a ver que esto es literalmente C(arriba, abajo) con la forma
        // factorial[arriba] * inverso[abajo] * inverso[arriba - abajo].
    }
};
