// <3
// Tema: CSES / Identidad MEX = XOR
// Se pide la grilla donde cada celda es el MEX de lo que ya hay a su izquierda en la fila y arriba
// en la columna, y resulta que eso es EXACTAMENTE i ^ j. Una sola linea, sin construir nada ni
// calcular ningun MEX. Verificado calculando el MEX de verdad en una grilla de 60x60.
// DE DONDE SALE: es la tabla de valores de Grundy del Nim con dos montones. La regla de Grundy es
// "el MEX de los estados alcanzables", y para dos montones da el xor, que es el teorema de
// Sprague-Grundy en su caso mas chico. Los dos problemas son literalmente la misma tabla.
// CUANDO SOSPECHARLO: si un problema define una tabla o secuencia como "el MEX de los anteriores",
// vale la pena calcular los primeros valores a mano y buscar el patron: casi siempre es un xor o
// algo periodico. Calcular el MEX de verdad suele ser innecesario.

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (i ^ j) << ' ';
        }
        cout << '\n';
    }
}
