// <3
// Tema: CSES / Identidad i XOR (i >> 1)
// Resumen: El codigo Gray de i es exactamente i ^ (i >> 1)
// Detalle: El codigo Gray de i es exactamente i ^ (i >> 1). Eso es todo: no hay recursion ni
// construccion por niveles, es una sola operacion por numero. POR QUE FUNCIONA: al pasar de i a
// i+1 cambia una racha de bits bajos, y el xor con el desplazamiento hace que ese cambio se
// reduzca a UN solo bit de diferencia, que es justo la definicion del codigo Gray. La vuelta
// (de Gray a binario) es acumular xor de todos los bits mas altos, que no es simetrica y
// conviene recordar que existe. CUANDO USAR: recorrer todos los subconjuntos cambiando UN
// elemento a la vez. Es util cuando recalcular desde cero cuesta caro pero agregar o quitar un
// elemento cuesta O(1), el mismo espiritu de Mo o de los problemas de torres de Hanoi.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < (1 << n); i++) {
        int x = i ^ (i >> 1);

        for (int j = n - 1; j >= 0; j--)
            cout << ((x >> j) & 1);

        cout << '\n';
    }
}
