// <3
// Tema: CSES / Formula de Legendre
// Resumen: Los ceros al final de n! los deciden los factores 5, no los 2, porque un cero
// necesita un par (2
// Detalle: Los ceros al final de n! los deciden los factores 5, no los 2, porque un cero
// necesita un par (2,5) y los 2 sobran siempre. La cuenta es la formula de Legendre: floor(n/5)
// + floor(n/25) + floor(n/125) + ..., que el while hace dividiendo n entre 5 repetidamente y
// acumulando. POR QUE HAY QUE SEGUIR DIVIDIENDO: 25 aporta dos cincos, 125 aporta tres. Contar
// solo floor(n/5) es el error clasico y se queda corto. CUANDO USAR: exponente de un PRIMO p en
// n!, cambiando el 5 por p. Sirve para saber si un binomial es divisible por algo, para el
// teorema de Kummer, y para cualquier pregunta de divisibilidad sobre factoriales sin calcular
// el factorial.

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    long long ans = 0;

    while (n) {
        n /= 5;
        ans += n;
    }

    cout << ans << '\n';
}
