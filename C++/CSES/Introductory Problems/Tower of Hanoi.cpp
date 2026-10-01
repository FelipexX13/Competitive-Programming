// <3
// Tema: CSES / Recursion Clasica
// Resumen: La recursion de siempre: mover n-1 al auxiliar, mover el disco grande al destino
// Detalle: La recursion de siempre: mover n-1 al auxiliar, mover el disco grande al destino,
// mover los n-1 del auxiliar al destino. El caso base es n == 0 y no hace nada. El total es 2^n
// - 1 movimientos, que se imprime antes porque se sabe de formula. LO QUE HAY QUE VER: los tres
// parametros ROTAN en cada llamada. El auxiliar de un nivel es el destino del de abajo.
// Escribir eso bien es todo el problema, y equivocarse en el orden de los argumentos es el
// unico error posible. CUANDO USAR: el patron es "resolver dos subproblemas de tamano n-1 con
// los roles cambiados". Es el ejemplo canonico para ver que la recursion que genera 2^n salidas
// es inevitable cuando la SALIDA misma tiene tamano 2^n.

#include <bits/stdc++.h>
using namespace std;

void hanoi(int n, int origen, int destino, int auxiliar) {
    if (n == 0) return;

    hanoi(n - 1, origen, auxiliar, destino);
    cout << origen << ' ' << destino << '\n';
    hanoi(n - 1, auxiliar, destino, origen);
}

int main() {
    int n;
    cin >> n;

    cout << (1 << n) - 1 << '\n';

    hanoi(n, 1, 3, 2);
}
