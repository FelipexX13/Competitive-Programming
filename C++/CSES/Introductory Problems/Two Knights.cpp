// <3
// Tema: CSES / Conteo por Complemento
// Resumen: Contar por el complemento: total de parejas menos las que se atacan
// Detalle: Contar por el complemento: total de parejas menos las que se atacan. El total es
// C(k^2, 2) = k^2*(k^2-1)/2, y las parejas que se atacan son 4*(k-1)*(k-2), porque cada
// rectangulo de 2x3 aporta exactamente 2 ataques y hay (k-1)*(k-2) de ellos en cada una de las
// dos orientaciones. Formula verificada contra fuerza bruta para k de 1 a 25. CUANDO CONTAR POR
// COMPLEMENTO: cuando lo que se pide ("que no se ataquen") es dificil de contar directo pero su
// negacion ("que se ataquen") es facil y estructurada. Es el primer reflejo que hay que tener
// en conteo, junto con inclusion-exclusion. long long obligatorio: con k = 10^4, k^2*(k^2-1)/2
// anda por 5*10^15.

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    for (long long k = 1; k <= n; k++) {
        long long total = k * k * (k * k - 1) / 2;
        long long attack = 4 * (k - 1) * (k - 2);

        cout << total - attack << '\n';
    }
}
