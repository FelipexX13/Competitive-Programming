// <3
// Tema: Math / Criba de Factor Primo Minimo + Inclusion-Exclusion
// Resuelve "Ingredients that may Harm You" (Maratona SBC de Programacao 2024, Problem I): en un
// restaurante self-service con N platillos identificados por numeros (donde cada primo que los
// divide representa un ingrediente basico, con multiplicidad), cada uno de Q comensales tiene un
// numero X que identifica sus alergias (los primos que dividen a X); para cada comensal hay que
// contar cuantos subconjuntos de platillos se pueden combinar sin que ninguno de ellos contenga
// un ingrediente al que sea alergico.
// El codigo precalcula el menor factor primo (spf) hasta 1e6 con una criba, para factorizar
// rapido cualquier numero, y para cada platillo enumera por mascara de bits (mask) todos los
// divisores libres de cuadrados formados por sus primos, acumulando cnt[d]. Para cada consulta
// factoriza X y aplica inclusion-exclusion sobre los divisores de X (sumando o restando cnt[d]
// segun la paridad de bits del mask) para contar cuantos platillos son coprimos con X; la
// respuesta final es 2^(coprimos) mod 1e9+7, ya que cada platillo compatible puede incluirse o
// no libremente en el plato.

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 1000000;
const int MOD = 1000000007;

int spf[MAXV + 1];
int cnt[MAXV + 1];
int pw[100005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // SPF
    for (int i = 0; i <= MAXV; i++) spf[i] = i;
    for (int i = 2; i * i <= MAXV; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j <= MAXV; j += i)
                if (spf[j] == j) spf[j] = i;
        }
    }

    int N;
    cin >> N;

    pw[0] = 1;
    for (int i = 1; i <= N; i++)
        pw[i] = (2LL * pw[i - 1]) % MOD;

    while (N--) {
        int x;
        cin >> x;

        vector<int> p;
        while (x > 1) {
            int pr = spf[x];
            p.push_back(pr);
            while (x % pr == 0) x /= pr;
        }

        int m = p.size();

        for (int mask = 0; mask < (1 << m); mask++) {
            int d = 1;
            for (int i = 0; i < m; i++)
                if (mask & (1 << i))
                    d *= p[i];
            cnt[d]++;
        }
    }

    int Q;
    cin >> Q;

    while (Q--) {
        int x;
        cin >> x;

        vector<int> p;
        while (x > 1) {
            int pr = spf[x];
            p.push_back(pr);
            while (x % pr == 0) x /= pr;
        }

        int m = p.size();

        int coprime = 0;

        for (int mask = 0; mask < (1 << m); mask++) {
            int d = 1;
            int bits = 0;

            for (int i = 0; i < m; i++) {
                if (mask & (1 << i)) {
                    d *= p[i];
                    bits++;
                }
            }

            if (bits & 1)
                coprime -= cnt[d];
            else
                coprime += cnt[d];
        }

        cout << pw[coprime] << '\n';
    }

    return 0;
}