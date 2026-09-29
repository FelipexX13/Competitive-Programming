// <3
// Tema: Implementation / Lights Out (Primera Fila Forzada)
// Resuelve "Turnswitch" (problema F, ICPC 2024). Una grilla n x n de interruptores que estan en
// '|' o en '-'; girar uno lo cambia a el y a sus cuatro vecinos. El codigo busca el minimo de
// giros para dejar todo igual, probando las dos opciones (todo '|' o todo '-').
// Es un "Lights Out", y tiene dos datos que lo desarman. Primero, el orden de los giros no
// importa y girar dos veces el mismo es no girarlo, asi que cada interruptor se gira 0 o 1 vez.
// Segundo, y es la clave: SI SE DECIDE LA PRIMERA FILA, TODO LO DEMAS QUEDA FORZADO. Una vez
// resuelta la fila r-1, la unica forma de arreglar la casilla (r-1, c) que siga mal es girar
// (r, c), porque es el ultimo interruptor que la toca. Entonces la fila siguiente no se elige: se
// deduce.
// Asi la busqueda baja de 2^(n*n) a 2^n combinaciones de la primera fila, cada una completada en
// O(n^2), y al final solo hay que ver si la ultima fila quedo bien.
// CUANDO USAR: cualquier puzzle de "presionar cambia a los vecinos" en una grilla. Si n es
// grande para 2^n, el mismo sistema se resuelve con eliminacion gaussiana sobre GF(2).

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    while (cin >> n && n != 0) {

        vector<string> a(n);

        for (auto &row : a)
            cin >> row;

        int ans = 1e9;

        // Probamos los dos objetivos:
        // 1. Todas verticales '|'
        // 2. Todas horizontales '-'
        for (int target = 0; target < 2; target++) {

            char wanted = (target == 0 ? '|' : '-');

            // Probamos todas las formas de girar la primera fila
            for (int mask = 0; mask < (1 << n); mask++) {

                vector<string> b = a;
                int cnt = 0;

                // Funcion para girar una casilla
                auto turn = [&](int r, int c) {
                    cnt++;

                    // Propia
                    b[r][c] = (b[r][c] == '|') ? '-' : '|';

                    // Arriba
                    if (r > 0)
                        b[r - 1][c] =
                            (b[r - 1][c] == '|') ? '-' : '|';

                    // Abajo
                    if (r + 1 < n)
                        b[r + 1][c] =
                            (b[r + 1][c] == '|') ? '-' : '|';

                    // Izquierda
                    if (c > 0)
                        b[r][c - 1] =
                            (b[r][c - 1] == '|') ? '-' : '|';

                    // Derecha
                    if (c + 1 < n)
                        b[r][c + 1] =
                            (b[r][c + 1] == '|') ? '-' : '|';
                };

                // Decidimos que switches girar en la primera fila
                for (int c = 0; c < n; c++) {
                    if (mask & (1 << c))
                        turn(0, c);
                }

                // Desde la segunda fila, los movimientos son obligatorios
                for (int r = 1; r < n; r++) {
                    for (int c = 0; c < n; c++) {

                        // Si la casilla de arriba esta mal,
                        // debemos girar esta.
                        if (b[r - 1][c] != wanted)
                            turn(r, c);
                    }
                }

                // Comprobamos si la ultima fila quedo correcta
                bool ok = true;

                for (int c = 0; c < n; c++) {
                    if (b[n - 1][c] != wanted) {
                        ok = false;
                        break;
                    }
                }

                if (ok)
                    ans = min(ans, cnt);
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
