// <3
// Tema: Number Theory / Diferencia de Cuadrados
// Resumen: Resuelve "SquareDiff" (problema C, ICPC 2024)
// Detalle: Resuelve "SquareDiff" (problema C, ICPC 2024). El codigo responde si n se puede
// escribir como diferencia de dos cuadrados, y toda la solucion es una condicion: n = a^2 - b^2
// tiene solucion <=> n mod 4 != 2 Por que: a^2 - b^2 = (a - b)(a + b), y esos dos factores
// tienen la MISMA paridad (se diferencian en 2b). Dos impares dan un producto impar, y dos
// pares dan un multiplo de 4; nunca sale algo que sea par pero no multiplo de 4. Y al reves
// siempre se puede: un impar 2k+1 = (k+1)^2 - k^2, y un multiplo de 4, 4m = (m+1)^2 - (m-1)^2.
// Verificado por fuerza bruta para n de 1 a 3000. El reflejo que deja este problema: ante "se
// puede escribir como...", factorizar la expresion y mirar la PARIDAD de los factores suele
// matarlo en una linea. OJO si n pudiera ser negativo: en C++ n % 4 conserva el signo, asi que
// -2 % 4 da -2 y no 2.

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    while (cin >> n && n != 0) {
        cout << (n % 4 == 2 ? 'N' : 'Y') << '\n';
    }

    return 0;
}
