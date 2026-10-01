// <3
// Tema: Number Theory / Reconstruccion con Divisores
// Resumen: Reconstruye el multiconjunto oculto K a partir de la sucesion S(n) = suma de (n mod
// k) para todo k en K
// Detalle: Reconstruye el multiconjunto oculto K a partir de la sucesion S(n) = suma de (n mod
// k) para todo k en K, dados S(1)..S(N). Se apoya en dos observaciones: como todo k es al menos
// 2, 1 mod k = 1 y por tanto S(1) es directamente el tamano |K|; y al mirar la diferencia S(n)
// - S(n-1), cada k que NO divide a n aporta +1 mientras que cada k que si divide a n aporta
// -(k-1), de modo que D = |K| - (S(n) - S(n-1)) termina siendo exactamente la suma de los
// elementos de K que dividen a n. Con eso se procesa n de menor a mayor: se le restan a D los
// aportes k*cnt[k] de los divisores propios ya conocidos, y lo que sobra es cnt[n]*n, de donde
// sale la multiplicidad de n en K. Al final se expande el conteo en la lista ordenada de
// elementos.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    if (!(cin >> N)) return 0;

    vector<long long> S(N + 1, 0);          // S[0] = 0
    for (int i = 1; i <= N; i++) cin >> S[i];

    long long m = S[1];                     // |K| = S(1)
    vector<long long> cnt(N + 1, 0);

    for (int n = 2; n <= N; n++) {
        long long D = m - (S[n] - S[n - 1]); // suma de los k de K que dividen a n
        for (int k = 2; k < n; k++)
            if (n % k == 0) D -= (long long)k * cnt[k];
        if (D > 0) cnt[n] = D / n;          // lo que queda es cnt[n]*n
    }

    vector<int> K;
    for (int k = 2; k <= N; k++)
        for (int i = 0; i < cnt[k]; i++) K.push_back(k);

    cout << K.size();
    for (int x : K) cout << ' ' << x;
    cout << '\n';
    return 0;
}
